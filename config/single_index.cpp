#include <vector>
#include "single_index.hpp"
#include "../fs/fs.hpp"

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
	if (tokens.back().back() != ';')
		std::cerr << "Error: Invalid token." << std::endl;//TODO
	if (tokens.size() == 2 && tokens[0] == "index")
	{
		std::string fname = tokens[1];
		return (fname);
	}
	std::cerr << "Error: Invalid index: " << line << std::endl;
	return ("");
}

Index::Index() : _line(""), _value(""), _isValid(false)
{
}

Index::Index(const std::string line) : _value("")
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = true;
	if (this->_value.empty())
		this->_isValid = false;
}

Index::Index(const Index &cpy)
{
	*this = cpy;
}

Index::~Index()
{
}

Index &Index::operator=(const Index &other)
{
	this->_line = other._line;
	this->_value = parser(other._line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return *this;
}

std::string Index::Get()
{
	return this->_value;
}

std::string Index::Set(const std::string line)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return this->_value;
}

bool Index::IsValid()
{
	return this->_isValid;
}
