#include <vector>
#include <iostream>
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include "single_alias.hpp"
#include "../config/fs.hpp"

static std::string parser(const std::string &line)
{
	std::vector<std::string> tokens;
	std::string token;
	char c;
	bool inDoubleQuote = false;
	bool inSingleQuote = false;

	for (size_t i = 0; i < line.size(); i++)
	{
		c = line[i];
		if (inDoubleQuote || inSingleQuote)
		{
			if (c == '"')
				inDoubleQuote = false;
			else if (c == '\'')
				inSingleQuote = false;
			else
			{
				if (c == '\\' && i + 1 < line.size() && line[i + 1] == '"')
					c = line[++i];
				token.push_back(c);
			}
		}
		else
		{
			if (std::isspace(static_cast<unsigned char>(c)))
			{
				if (!token.empty())
				{
					tokens.push_back(token);
					token.clear();
				}
			}
			else if (c == '"')
				inDoubleQuote = true;
			else if (c == '\'')
				inSingleQuote = true;
			else if (c == '\\')
			{
				if (i + 1 < line.size())
				{
					c = line[++i];
					token.push_back(c);
				}
				else
				{
					tokens.clear();
					break;
				}
			}
			else
				token.push_back(c);
		}
	}
	if (!token.empty())
		tokens.push_back(token);
	if (tokens.size() == 2 && tokens[0] == "alias")
	{
		std::string path = tokens[1];
		if (!isEnoentPrint(path) && !isEaccessOrEpermPrint(path) && !isEnotdirPrint(path) && !isDirEaccessPrint(path))
			return (path);
	}
	std::cerr << "Error: Invalid alias: " << line << std::endl;
	return ("");
}

Alias::Alias() : _line(""), _value(""), _isValid(false)
{
}

Alias::Alias(const std::string line) : _value(""), _isValid(false)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
}

Alias::Alias(const Alias &cpy)
{
	*this = cpy;
}

Alias::~Alias()
{
}

Alias &Alias::operator=(const Alias &other)
{
	this->_line = other._line;
	this->_value = parser(other._line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return *this;
}

std::string Alias::Get()
{
	return this->_value;
}

std::string Alias::Set(const std::string line)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return this->_value;
}

bool Alias::IsValid()
{
	return this->_isValid;
}
