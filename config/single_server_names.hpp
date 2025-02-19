#pragma once

#include <string>
#include <iostream>
#include <vector>

class ServerNames
{
private:
	std::string _line;
	std::vector<std::string> _values;
	bool _isValid;

public:
	ServerNames();
	ServerNames(const std::string &line);
	ServerNames(const ServerNames &cpy);
	~ServerNames();
	ServerNames &operator=(const ServerNames &other);
	std::vector<std::string> Get();
	std::vector<std::string> Set(const std::string line);
	bool IsValid();
};
