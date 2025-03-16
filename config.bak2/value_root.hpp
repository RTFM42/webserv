#pragma once

#include <string>
#include <iostream>

class Root
{
private:
    std::string _dir;
    bool _isValid;

public:
    Root();
    Root(const std::string &config);
    ~Root();
    std::string Get();
    bool Set(const std::string &config);
    bool isValid();
};
