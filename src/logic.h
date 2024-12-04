#pragma once
#include <tll/channel/tagged.h>

struct EchoTag : public tll::channel::Tag<TLL_MESSAGE_MASK_ALL> { static constexpr std::string_view name() { return "echo"; } };

class EchoLogic : public tll::channel::Tagged<EchoLogic, EchoTag>
{
	using Base = tll::channel::Tagged<EchoLogic, EchoTag>;

	bool _hello_enable = true;
	int _hello_msgid = 0;
	std::string _hello_text;

	tll::Channel * _echo_channel = nullptr;
 public:
	static constexpr std::string_view channel_protocol() { return "echo-logic"; }

	int _init(const tll::Channel::Url &, tll::Channel *master);
	int _open(const tll::ConstConfig &);

	int callback_tag(tll::channel::TaggedChannel<EchoTag> *, const tll_msg_t *msg);
};
