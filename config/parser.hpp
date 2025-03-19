#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

#include "./config_raw.hpp"

class Parser
{
private:
	int skipCommentSpace3Semiolon(const std::string &config);
	int skipCommentSpace3(const std::string &config);
	int extractKey(std::string *dst, const std::string &config);
	int extractScope(std::vector<ConfigRaw *> *dst, const std::string &config);
	int extractValue(std::vector<std::string *> *dst, const std::string &config);

public:
	Parser(const std::string &config);
	~Parser();
	ConfigRaw *config;
};

#endif
