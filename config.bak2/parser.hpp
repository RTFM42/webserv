#pragma once

#include <string>
#include <iostream>
#include <vector>

class Parser
{
public:
    Parser();
    Parser(const std::string &config);
    ~Parser();
    std::string key;
    std::string value;
    std::vector<Parser> scope;
};

struct s_config_obj
{
    std::string key;
    std::string value;
    std::vector<s_config_obj> scopes;
};
