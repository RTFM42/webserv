#pragma once

#include <string>
#include <iostream>
#include <vector>

class Alias
{
private:
    std::string _dir;
    bool _isValid;

public:
    Alias();
    Alias(const std::string &config);
    ~Alias();
    std::vector<std::string> Get();
    bool Set(const std::string &config);
    bool isValid();
};
