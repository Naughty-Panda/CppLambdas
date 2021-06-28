//////////////////////////////////////////
//	C++ Lambda Expressions
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <iostream>
#include "phonebook.h"

#if _HAS_CXX20

int main() {

	std::ifstream file("PhoneBook.txt");

	try {
		PhoneBook pb{ file };

		std::cout << "\n-----Original PhoneBook-----\n";
		std::cout << pb;

		std::cout << "\n-------Search Results-------\n";
		auto i = pb.GetPhoneNumber("Gorev");

		std::cout << "\n------Sort by LastName------\n";
		pb.SortByName();
		std::cout << pb;

		std::cout << "\n-------Sort by Phone--------\n";
		pb.SortByPhone();
		std::cout << pb;
	}
	catch (const std::exception& ex) {
		std::cerr << '\n' << ex.what();
	}

	return 0;
}

#else
#pragma message("Requires CXX20!!!")
#endif // !_HAS_CXX20
