#include "logic.h"

using namespace tll::channel;

int EchoLogic::_init(const tll::Channel::Url &url, tll::Channel * master)
{
	if (auto r = Base::_init(url, master); r)
		return _log.fail(EINVAL, "Base init failed");

	if (check_channels_size<EchoTag>(1, 1)) // One and only one 'echo' channel required
		return EINVAL;

	_echo_channel = _channels.get<EchoTag>().front().first;

	auto reader = channel_props_reader(url);
	_hello_enable = reader.getT("send-hello", true); 
	if (_hello_enable) {
		_hello_msgid = reader.getT("hello-msgid", 10u);
		_hello_text = reader.getT<std::string>("hello-text", "Hello");
	}
	if (!reader)
		return _log.fail(EINVAL, "Invalid parameters: {}", reader.error());
	return 0;
}

int EchoLogic::_open(const tll::ConstConfig &cfg)
{
	_log.info("Open logic");
	return Base::_open(cfg);
}

int EchoLogic::callback_tag(TaggedChannel<EchoTag> *c, const tll_msg_t *msg)
{
	if (msg->type == TLL_MESSAGE_STATE && msg->msgid == tll::state::Active) {
		tll_msg_t m = { .type = TLL_MESSAGE_DATA, .msgid = _hello_msgid };
		m.data = _hello_text.data();
		m.size = _hello_text.size();

		if (_echo_channel->post(&m))
			return _log.fail(EINVAL, "Failed to post hello");

		return 0;
	} else if (msg->type != TLL_MESSAGE_DATA) {
		return 0;
	}

	return _echo_channel->post(msg);
}

