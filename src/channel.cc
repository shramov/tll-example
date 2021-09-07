#include "tll/channel/base.h"

class Example : public tll::channel::Base<Example>
{
 public:
	static constexpr std::string_view channel_protocol() { return "example"; }

	int _init(const tll::Channel::Url &, tll::Channel *master) { return 0; }
	int _open(const tll::PropsView &) { return 0; }
	int _close() { return 0; }
	void _destroy() {}

	int _post(const tll_msg_t *msg, int flags) { return ENOTSUP; }
	int _process(long timeout, int flags) { return EAGAIN; }
};

TLL_DEFINE_IMPL(Example);

auto channel_module = tll::make_channel_module<Example>();
