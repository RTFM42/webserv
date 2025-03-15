#include <vector>
#include <cctype>
#include <sstream>
#include "single_listen.hpp"

static uint16_t parser(const std::string &line)
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
	if (!tokens.empty() && tokens.back().back() != ';')
	{
		std::cerr << "Error: Invalid token." << std::endl;//TODO
		return {};
	}
	tokens.back().pop_back();//最後のトークンの末尾のセミコロン削除
	if (tokens.size() == 2 && tokens[0] == "listen")
	{
		bool digit_ok = true;
		for (std::string::const_iterator it = tokens[1].begin(); it != tokens[1].end(); ++it)
		{
			if (!std::isdigit(static_cast<unsigned char>(*it)))
			{
				digit_ok = false;
				break;
			}
		}
		if (digit_ok)
		{
			int port = 0;
			std::istringstream iss(tokens[1]);
			iss >> port;
			if (!iss.fail() && port > 0 && port <= 65535)
				return static_cast<uint16_t>(port);
			else
			{
				std::cerr << "Error: " << port << ": port must be 1 to 65535" << std::endl;
				return static_cast<uint16_t>(0);
			}
		}
	}
	std::cerr << "Error: Invalid listen: " << line << std::endl;
	return (uint16_t)0;
}

Listen::Listen() : _line(""), _value(0), _isValid(false)
{
}

Listen::Listen(const std::string line) : _value(0), _isValid(false)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = true;
	if (this->_value > 0)
		this->_isValid = false;
}

Listen::Listen(const Listen &cpy)
{
	*this = cpy;
}

Listen::~Listen()
{
}

Listen &Listen::operator=(const Listen &other)
{
	this->_line = other._line;
	this->_value = parser(other._line);
	this->_isValid = false;
	if (this->_value > 0)
		this->_isValid = true;
	return *this;
}

uint16_t Listen::Get()
{
	return this->_value;
}

uint16_t Listen::Set(const std::string line)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = false;
	if (this->_value > 0)
		this->_value = true;
	return this->_value;
}

bool Listen::IsValid()
{
	return this->_isValid;
}
