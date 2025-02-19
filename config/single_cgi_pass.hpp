#pragma once

#include <string>
#include <iostream>

class Cgi
{
private:
	std::string _line;
	std::string _value;
	bool _isValid;

public:
	Cgi();
	Cgi(const std::string line);
	Cgi(const Cgi &cpy);
	~Cgi();
	Cgi &operator=(const Cgi &other);
	std::string Get();
	std::string Set(const std::string line);
	bool IsValid();
};
