#include <vector>
#include "single_root.hpp"
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
	if (!tokens.empty() && tokens.back().back() != ';')
	{
		std::cerr << "Error: Invalid token." << std::endl;//TODO
		return {};
	}
	tokens.back().pop_back();//最後のトークンの末尾のセミコロン削除
	if (tokens.size() == 2 && tokens[0] == "root")
	{
		std::string path = tokens[1];
		if (!isEnoentPrint(path) && !isEaccessOrEpermPrint(path) && !isEnotdirPrint(path) && !isDirEaccessPrint(path))
			return (path);
		else
			return ("");
	}
	std::cerr << "Error: Invalid root: " << line << std::endl;
	return ("");
}

Root::Root() : _line(""), _value(""), _isValid(false)
{
}

Root::Root(const std::string line) : _value("")
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = true;
	if (this->_value.empty())
		this->_isValid = false;
}

Root::Root(const Root &cpy)
{
	*this = cpy;
}

Root::~Root()
{
}

Root &Root::operator=(const Root &other)
{
	this->_line = other._line;
	this->_value = parser(other._line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return *this;
}

std::string Root::Get()
{
	return this->_value;
}

std::string Root::Set(const std::string line)
{
	this->_line = line;
	this->_value = parser(line);
	this->_isValid = false;
	if (this->_value.empty())
		this->_isValid = true;
	return this->_value;
}

bool Root::IsValid()
{
	return this->_isValid;
}