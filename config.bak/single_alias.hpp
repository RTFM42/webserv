#pragma once

#include <string>
#include <iostream>

class Alias
{
private:
	std::string _line;
	std::string _value;
	bool _isValid;

public:
	Alias();
	Alias(const std::string line);
	Alias(const Alias &cpy);
	~Alias();
	Alias &operator=(const Alias &other);
	std::string Get();
	std::string Set(const std::string line);
	bool IsValid();
};
