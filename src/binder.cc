#include "binder.h"

#include <fmt/format.h>
#include <vector>

void dump(const std::vector<char>& buf)
{
	auto data = binder_test::Message::bind(buf);
	fmt::print("List size: {}\n", data.get_list().size());
	for (auto & i : data.get_list())
		fmt::print("{}: {}\n", i.get_key(), i.get_value());
}

void fill(std::vector<char>& buf, size_t size)
{
	auto data = binder_test::Message::bind_reset(buf);
	auto list = data.get_list();
	list.resize(size);
	unsigned idx = 0;
	for (auto & i : list) {
		i.set_key(fmt::format("key-{}", idx));
		i.set_value(fmt::format("value-{}", idx++));
	}
}

int main()
{
	std::vector<char> buf;
	fill(buf, 4);
	dump(buf);
	fill(buf, 2);
	dump(buf);
	return 0;
}
