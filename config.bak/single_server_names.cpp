#include "single_server_names.hpp"
#include "../fs/fs.hpp"

static std::vector<std::string> parser(const std::string &line)
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
	if (tokens.size() > 1 && tokens[0] == "server_names")
	{
		std::vector<std::string> server_name(tokens.begin() + 1, tokens.end());
		return server_name;
	}
	std::cerr << "Error: Invalid server_names: " << line << std::endl;
	return {};
}

ServerNames::ServerNames() : _line(""), _isValid(false)
{
}

ServerNames::ServerNames(const std::string &line) : _line(line), _isValid(false)
{
	this->_values = parser(line);
	this->_isValid = true;
	if (this->_values.empty())
		this->_isValid = false;
}

ServerNames::ServerNames(const ServerNames &cpy)
{
	*this = cpy;
}

ServerNames::~ServerNames()
{
}

ServerNames &ServerNames::operator=(const ServerNames &other)
{
	this->_line = other._line;
	this->_values = parser(other._line);
	this->_isValid = false;
	if (this->_values.empty())
		this->_isValid = true;
	return *this;
}

std::vector<std::string> ServerNames::Get()
{
	return this->_values;
}

std::vector<std::string> ServerNames::Set(const std::string line)
{
	this->_line = line;
	this->_values = parser(line);
	this->_isValid = false;
	if (this->_values.empty())
		this->_isValid = true;
	return this->_values;
}

bool ServerNames::IsValid()
{
	return this->_isValid;
}
