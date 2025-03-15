#pragma once

#include <string>
#include <iostream>
#include <stdint.h>

class Listen
{
private:
	std::string _line;
	uint16_t _value;
	bool _isValid;

public:
	Listen();
	Listen(const std::string line);
	Listen(const Listen &cpy);
	~Listen();
	Listen &operator=(const Listen &other);
	uint16_t Get();
	uint16_t Set(const std::string line);
	bool IsValid();
};
