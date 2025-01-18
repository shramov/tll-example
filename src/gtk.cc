#include <gtkmm.h>
#include <gtkmm/application.h>

#include <glib.h>
#include <glib-unix.h>

#include <fmt/format.h>

#include <tll/config.h>
#include <tll/channel.h>
#include <tll/logger.h>
#include <tll/processor/loop.h>
#include <tll/util/time.h>

class Window : public Gtk::Window {
 public:
	Gtk::Label label;

	Window()
	{
		add(label);
		set_title("Gtk TLL example");
		resize(300, 300);
		label.set_text("No data...");
		show_all();
	}
};

struct GLibTLLLoop
{
	tll::processor::Loop loop;

	int fd() const { return tll_processor_loop_get_fd(&loop); }

	gboolean step(Glib::IOCondition condition)
	{
		loop.step(tll::duration());
		return TRUE;
	}
};

int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv, "ru.org.psha.tllexample");
	Window widget;

	{
		tll::Config cfg;
		cfg.set("type", "spdlog");
		cfg.set("levels.tll", "info");
		tll::Logger::config(cfg);
	}

	tll::Logger log("tll.gtk.example");

	auto tllctx = tll::channel::Context(tll::Config());
	GLibTLLLoop tllloop;
	tllloop.loop.init(tll::Config());

	auto channel = tllctx.channel("timer://;clock=realtime;interval=1s;name=timer");
	if (!channel)
		return log.fail(1, "Failed to create timer channel");

	channel->add_callback([](auto * c, const tll_msg_t * msg, void * user)
			{
				using namespace std::chrono;
				auto label = (Gtk::Label *) user;
				auto ts = time_point<system_clock, nanoseconds>(nanoseconds(*(uint64_t *) msg->data));
				label->set_text(tll::conv::to_string(ts) + " UTC");
				label->show();
				return 0;
			}, &widget.label, TLL_MESSAGE_MASK_DATA);
	channel->open();
	tllloop.loop.add(channel.get());

	Glib::signal_io().connect(sigc::mem_fun(tllloop, &GLibTLLLoop::step), tllloop.fd(), Glib::IOCondition::IO_IN);

	// Creates a iochannel from the file descriptor
	auto tllsource = Glib::IOChannel::create_from_fd(tllloop.fd());

	auto r = app->run(widget);

	return r;
}
