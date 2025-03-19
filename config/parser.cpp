#include <iostream>

#include "./parser.hpp"
#include "./config_raw.hpp"

#define DEBUG std::cerr << "debug: " << __LINE__ << std::endl

int Parser::skipCommentSpace3Semiolon(const std::string &config)
{
	int i = 0;

	while (std::isspace(config[i]) || config[i] == ';' || config[i] == '#')
	{
		if (std::isspace(config[i]) || config[i] == ';')
			i++;
		else if (config[i] == '#')
			while (config[i] && config[i] != '\n')
				i++;
	}
	return (i);
}

int Parser::skipCommentSpace3(const std::string &config)
{
	int i = 0;

	while (std::isspace(config[i]) || config[i] == '#')
	{
		if (std::isspace(config[i]))
			i++;
		else if (config[i] == '#')
			while (config[i] && config[i] != '\n')
				i++;
	}
	return (i);
}

int Parser::extractKey(std::string *dst, const std::string &config)
{
	int i = 0;

	if (!config[i])
		return (0);
	while (('A' <= config[i] && config[i] <= 'Z') || ('a' <= config[i] && config[i] <= 'z') || '_' == config[i])
		i++;
	if (i == 0)
		return (0);
	*dst = config.substr(0, i);
	return (i);
}

int Parser::extractScope(std::vector<ConfigRaw *> *dst, const std::string &config)
{
	int i = 0;
	Parser *child = NULL;

	if (config[i] == '{')
	{
		i++;
		while (config[i])
		{
			child = new Parser(&config[i]);
			if (child->config == NULL || child->config->key.empty())
			{
				delete child;
				for (std::vector<ConfigRaw *>::iterator it = dst->begin(); it != dst->end(); it++)
				{
					delete *it;
				}
				return (0);
			}
			else
			{
				dst->push_back(child->config);
				i += child->config->count;
				delete child;
				while (std::isspace(config[i]) || config[i] == ';')
				{
					if (std::isspace(config[i]))
						i++;
					else if (config[i] == ';')
						i++;
				}
				if (config[i] == '}')
				{
					i++;
					return (i);
				}
			}
		}
		for (std::vector<ConfigRaw *>::iterator it = dst->begin(); it != dst->end(); it++)
		{
			delete *it;
		}
	}
	return (0);
}

int Parser::extractValue(std::vector<std::string *> *dst, const std::string &config)
{
	int n = 0;
	while (config[n] && !std::isspace(config[n]) && config[n] != ';' && config[n] != '{')
		n++;
	dst->push_back(new std::string(config.substr(0, n)));
	return (n);
}

Parser::Parser(const std::string &config)
{
	int i = 0;
	int n = 0;
	std::string key = "";
	std::vector<std::string *> value;
	std::vector<ConfigRaw *> scope;

	this->config = NULL;

	while (i == 0)
	{
		// SKIP COMMENT OUT, and SPACE and RETURN
		i += this->skipCommentSpace3Semiolon(&config[i]);

		// KEY
		i += this->extractKey(&key, &config[i]);
		// CHECK END OF KEY
		if (key.length() == 0 || !config[i])
		{
			std::cerr << "Error: invalid config(" << i << ")" << std::endl;
			return;
		}
		i += this->skipCommentSpace3(&config[i]);
		if (config[i] == ';')
		{
			i++;
			break;
		}
		else if (!config[i])
		{
			std::cerr << "Error: invalid config(" << i << ")" << std::endl;
			return;
		}

		// VALUE, SCOPE
		while (config[i])
		{
			// SKIP COMMENT OUT, and SPACE and RETURN
			n = this->skipCommentSpace3(&config[i]);
			i += n;
			if (n)
			{
				continue;
			}
			if (config[i] == ';')
			{
				i++;
				break;
			}
			else if (config[i] == '{')
			{
				// SCOPE
				n = this->extractScope(&scope, &config[i]);
				i += n;
				if (n == 0)
				{
					std::cerr << "Error: invalid config(" << i << ")" << std::endl;
					return;
				}
				break;
			}
			else
			{
				// VALUE
				n = this->extractValue(&value, &config[i]);
				i += n;
				if (n == 0)
				{
					std::cerr << "Error: invalid config(" << i << ")" << std::endl;
					return;
				}
			}
		}
		break;
	}
	this->config = new ConfigRaw();
	this->config->count = i;
	this->config->key = key;
	this->config->value = value;
	this->config->scope = scope;
}

Parser::~Parser()
{
}
