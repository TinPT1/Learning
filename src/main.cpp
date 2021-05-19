#include <iostream>
#include <string>
#include <array>
#include <iomanip>
#include <sstream>


int main()
{
	std::stringstream os;
	std::string string1{"123"};
	std::string string2{"123.456"};
	int intNumber{};
	double doubleNumber{};

	os << string1 << ' ' << string2;

	os >> intNumber >> doubleNumber;

	std::cout << intNumber << ' ' << doubleNumber;


	return 0;
}
