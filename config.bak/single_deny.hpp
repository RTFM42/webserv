#pragma once

#include <string>
#include <iostream>

class Deny
{
private:
	std::string _line;
	std::string _value;
	bool _isValid;

public:
	Deny();
	Deny(const std::string line);
	Deny(const Deny &cpy);
	~Deny();
	Deny &operator=(const Deny &other);
	std::string Get();
	std::string Set(const std::string line);
	bool IsValid();
};
