//////////////////////////////////////////
//	C++ Lambda Expressions
//	Naughty Panda @ 2021
//////////////////////////////////////////

#include <string>
#include <algorithm>
#include "phonebook.h"

//////////////////////////////////////////
//	Person Methods
//////////////////////////////////////////

std::ostream& operator << (std::ostream& ostr, const Person& person) {
	
	ostr << person.GetFirstName();
	ostr << " ";
	ostr << person.GetLastName();
	if (!person.GetSurName().has_value()) return ostr;
	ostr << " ";
	ostr << person.GetSurName().value();
	return ostr;
}

bool Person::operator < (const Person& p) {

	return std::make_tuple(GetFirstName(), GetLastName(), GetSurName()) < std::make_tuple(p.GetFirstName(), p.GetLastName(), p.GetSurName());
}

bool Person::operator == (const Person& p) {

	return std::make_tuple(GetFirstName(), GetLastName(), GetSurName()) == std::make_tuple(p.GetFirstName(), p.GetLastName(), p.GetSurName());
}

//////////////////////////////////////////
//	PhoneNumber Methods
//////////////////////////////////////////

PhoneNumber::PhoneNumber(const uint16_t& CountryCode, const uint16_t& CityCode, const std::string& Number, const std::optional<uint16_t>& AdditionalNumber)
	: _CountryCode(CountryCode), _CityCode(CityCode), _Number(Number), _AdditionalNumber(AdditionalNumber) {}

std::ostream& operator << (std::ostream& ostr, const PhoneNumber& n) {

	ostr << "+" << n._CountryCode;
	ostr << "(" << n._CityCode << ")";
	ostr <<n. _Number;
	if (!n._AdditionalNumber.has_value()) return ostr;
	ostr << ' ' << n._AdditionalNumber.value();
	return ostr;
}

//////////////////////////////////////////
//	PhoneBook Methods
//////////////////////////////////////////

PhoneBook::PhoneBook(std::ifstream& file) {

	if (!file || !file.is_open()) {
		throw(std::exception("No input file!"));
	}

	std::string line;

	//	Iterating lines
	while (std::getline(file, line)) {

		std::vector<std::string> string_container;
		std::vector<uint16_t> uint_container;

		std::string token;
		std::string delimiter{ ' ' };

		size_t start = 0U;
		size_t end = line.find(delimiter);

		//	 Iterating tokens
		while (end != std::string::npos) {

			end = line.find(delimiter);
			token = line.substr(start, end - start);

			//	If token is a string - push it to string container
			if (!isNumber(token)) {
				string_container.push_back(token);
			}

			// Else - push token to uint container
			else {
				uint_container.push_back(atoi(token.c_str()));
			}

			end = line.find(delimiter, start);
			line.erase(start, end + delimiter.size());
		}

#ifdef _DEBUG
		std::cout << "str_container: " << string_container.size() << " uint_container: " << uint_container.size() << '\n';
#endif

		//	Creating _list entries
		Person p{"", ""};
		switch (string_container.size())
		{
		case 2: p = { string_container.at(0), string_container.at(1) }; break;
		case 3: p = { string_container.at(0), string_container.at(1), string_container.at(2) }; break;
		default: break;
		}

		PhoneNumber pn{ 0, 0, ""};
		switch (uint_container.size())
		{
		case 3: pn = { uint_container.at(0), uint_container.at(1), std::to_string(uint_container.at(2)) }; break;
		case 4: pn = { uint_container.at(0), uint_container.at(1), std::to_string(uint_container.at(2)), uint_container.at(3) }; break;
		default: break;
		}

		//	Push back Person + PhoneNumber pair into vector
		_list.push_back({ p,pn });
	}
}

void PhoneBook::SortByName() {

	if (_list.empty()) throw std::exception("Empty list!");

	auto sort_by_name = [](const auto& p1, const auto& p2) -> bool {
		return p1.first.GetLastName().substr(0, 1) < p2.first.GetLastName().substr(0, 1);
	};

	std::sort(_list.begin(), _list.end(), sort_by_name);
}

void PhoneBook::SortByPhone() {

	if (_list.empty()) throw std::exception("Empty list!");

	auto sort_by_phone = [](const auto& p1, const auto& p2) -> bool {
		//	Convert _Number to integer and compare
		return atoi(p1.second.GetNumber().c_str()) < atoi(p2.second.GetNumber().c_str());
	};

	std::sort(_list.begin(), _list.end(), sort_by_phone);
}

std::tuple<std::string&, PhoneNumber&> PhoneBook::GetPhoneNumber(const std::string& name) const {

	if (_list.empty()) throw std::exception("Empty list!");

	size_t num = 0U;
	PhoneNumber pn{ 0, 0, "" };
	std::string str{ "" };

	auto find_person = [&name, &num, &pn](const auto& person) {
		if (person.first.GetLastName() == name) {
			pn = person.second;
			std::cout << pn << '\n';
			++num;
		}
	};

	for_each(_list.begin(), _list.end(), find_person);

	switch (num)
	{
	case 0: str = "Not found"; break;
	case 1: str.clear(); break;
	default: str = "Found more than 1"; break;
	}

	std::cout << std::boolalpha << str.empty() << ' ' << pn << '\n';

	return std::tie(str, pn);
}

std::ostream& operator << (std::ostream& ostr, const PhoneBook& pb) {

	for (const auto& [person, number] : pb._list) {
		ostr << person << ' ' << number << '\n';
	}

	return ostr;
}

//////////////////////////////////////////
//	Utility
//////////////////////////////////////////

bool isNumber(const std::string& str) {

	return !str.empty() && std::find_if(str.begin(), str.end(), [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}
