#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "./config_raw.hpp"

class Parser
{
public:
	Parser(const std::string &config);
	~Parser();
	ConfigRaw *config;
};

#endif
