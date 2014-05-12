#include "type_switch.h"

#include <iostream>

template <typename T>
void test_match(T&& t)
{
	match (std::forward<T>(t)) (
		[](int i)          { std::cout << "match int " << i << '\n'; },
		[](double d)       { std::cout << "match double " << d << '\n'; },
		[](const char* s)  { std::cout << "match string " << s << '\n'; },
		otherwise([&t]()   { std::cout << "match unknown @" << &t << '\n'; })
	);
}

int main()
{
	auto f = overload(
		[](int i)         { std::cout << "overload int " << i << '\n'; },
		[](double d)      { std::cout << "overload double " << d << '\n'; },
		[](const char* s) { std::cout << "overload string " << s << '\n'; },
		otherwise([]()    { std::cout << "overload unknown\n"; })
	);

	f(10);
	f(9.99);
	f("hello");
	f(std::cout);

	test_match(10);
	test_match(9.99);
	test_match("hello");
	test_match(std::cout);

	system("pause");
	return 0;
}
