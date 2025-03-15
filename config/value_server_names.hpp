#pragma once

#include <string>
#include <iostream>
#include <vector>

class ServerNames
{
private:
    std::vector<std::string> _domains;
    bool _isValid;

public:
    ServerNames();
    ServerNames(const std::string &config);
    ~ServerNames();
    std::vector<std::string> Get();
    bool Set(const std::string &config);
    bool isValid();
};
