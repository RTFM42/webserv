#pragma once

#include <string>
#include <iostream>

class Root
{
private:
	std::string _line;
	std::string _value;
	bool _isValid;

public:
	Root();
	Root(const std::string line);
	Root(const Root &cpy);
	~Root();
	Root &operator=(const Root &other);
	std::string Get();
	std::string Set(const std::string line);
	bool IsValid();
};
