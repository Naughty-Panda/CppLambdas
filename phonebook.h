//////////////////////////////////////////
//	C++ Lambda Expressions
//	Naughty Panda @ 2021
//////////////////////////////////////////

#pragma once

#include <cstdint>
#include <optional>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

//////////////////////////////////////////
//	Person Struct
//////////////////////////////////////////

struct Person {

private:
	std::string _firstName{ "" };
	std::string _lastName{ "" };
	std::optional<std::string> _surName{ std::nullopt };

public:
	Person(const std::string& fname, const std::string& lname, const std::optional<std::string>& sname = std::nullopt) : _firstName(fname), _lastName(lname), _surName(sname) {};

	std::string GetFirstName() const { return _firstName; }
	std::string GetLastName() const { return _lastName; }
	std::optional<std::string> GetSurName() const { return _surName; }

	void SetFirstName(const std::string& str) { _firstName = str; }
	void SetLastName(const std::string& str) { _lastName = str; }
	void SetSurName(const std::string& str) { _surName = str; }

	friend std::ostream& operator << (std::ostream& ostr, const Person& person);
	bool operator < (const Person& p);
	bool operator == (const Person& p);
};

//////////////////////////////////////////
//	PhoneNumber Struct
//////////////////////////////////////////

struct PhoneNumber {

private:
	uint16_t _CountryCode{};
	uint16_t _CityCode{};
	std::string _Number{ "" };
	std::optional<uint16_t> _AdditionalNumber{};

public:
	PhoneNumber(const uint16_t&, const uint16_t&, const std::string&, const std::optional<uint16_t>& = std::nullopt);

	std::string GetNumber() const { return _Number; }
	friend std::ostream& operator << (std::ostream& ostr, const PhoneNumber& n);
};

//////////////////////////////////////////
//	PhoneBook Class
//////////////////////////////////////////

class PhoneBook {

private:
	std::vector<std::pair<Person, PhoneNumber>> _list;

public:
	PhoneBook(std::ifstream& file);

	void SortByName();
	void SortByPhone();
	std::tuple<std::string&, PhoneNumber&> GetPhoneNumber(const std::string& name) const;
	friend std::ostream& operator << (std::ostream& ostr, const PhoneBook& pb);
};

//////////////////////////////////////////
//	Utility
//////////////////////////////////////////

bool isNumber(const std::string& str);
