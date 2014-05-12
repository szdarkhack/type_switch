#include "type_switch.h"

#include <iostream>

int main()
{
	auto f = overload(
		[](int)         { std::cout << "int\n"; },
		[](double)      { std::cout << "double\n"; },
		[](const char*) { std::cout << "string\n"; },
		otherwise([]()  { std::cout << "unknown\n"; })
	);

	f(10);
	f(9.99);
	f("hello");
	f(std::cout);

	system("pause");
	return 0;
}
