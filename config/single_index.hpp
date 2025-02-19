#pragma once

#include <string>
#include <iostream>

class Index
{
private:
	std::string _line;
	std::string _value;
	bool _isValid;

public:
	Index();
	Index(const std::string line);
	Index(const Index &cpy);
	~Index();
	Index &operator=(const Index &other);
	std::string Get();
	std::string Set(const std::string line);
	bool IsValid();
};
