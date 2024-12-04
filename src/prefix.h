#include <tll/channel/prefix.h>

class Prefix : public tll::channel::Prefix<Prefix>
{
	using Base = tll::channel::Prefix<Prefix>;
	bool _skip = false;
 public:
	static constexpr std::string_view channel_protocol() { return "prefix+"; }

	int _open(const tll::ConstConfig &cfg)
	{
		_skip = true;
		return Base::_open(cfg);
	}

	int _post(const tll_msg_t * msg, int flags)
	{
		if (msg->type == TLL_MESSAGE_DATA) {
			_skip = !_skip;
			if (_skip)
				return 0;
		}
		return _child->post(msg, flags);
	}

	int _on_data(const tll_msg_t * msg)
	{
		// Increase seq number
		tll_msg_t m = *msg;
		m.seq++;
		_callback_data(&m);
		return 0;
	}
};
