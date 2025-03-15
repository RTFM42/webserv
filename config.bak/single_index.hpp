#pragma once

#include <string>
#include <iostream>
#include <vector>

class Index
{
private:
	std::string _line;
	std::vector<std::string> _values;
	bool _isValid;

public:
	Index();
	Index(const std::string &line);
	Index(const Index &cpy);
	~Index();
	Index &operator=(const Index &other);
	std::vector<std::string> Get();
	std::vector<std::string> Set(const std::string line);
	bool IsValid();
};
