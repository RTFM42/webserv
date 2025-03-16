#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

struct config_raw
{
    std::string key;
    std::string value;
    std::vector<config_raw*> scopes;
};

class Parser
{
public:
    Parser();
    Parser(const std::string &config);
    ~Parser();
    config_raw config;
};

#endif
