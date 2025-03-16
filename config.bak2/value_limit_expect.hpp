#pragma once

#include <string>
#include <iostream>
#include <vector>

class LimitExpect
{
private:
    std::vector<std::string> _methods;
    bool _isValid;

public:
    LimitExpect();
    LimitExpect(const std::string &config);
    ~LimitExpect();
    std::vector<std::string> Get();
    bool Set(const std::string &config);
    bool isValid();
};
