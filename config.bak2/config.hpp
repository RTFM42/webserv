#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "./scope_server.hpp"

class Config
{
private:
    bool _isValid;

public:
    Config();
    Config(const std::string &config);
    ~Config();
    bool Set(const std::string &config);
    bool isValid();

    std::vector<Server> servers;
};
