#include <tll/channel/base.h>

class Echo : public tll::channel::Base<Echo>
{
 public:
	static constexpr std::string_view channel_protocol() { return "echo"; }
	static constexpr auto process_policy() { return tll::channel::Base<Echo>::ProcessPolicy::Never; }

	// Send back message
	int _post(const tll_msg_t *msg, int flags) { return _callback_data(msg); }
};
