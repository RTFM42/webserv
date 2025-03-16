#pragma once

#include <string>
#include <iostream>

class Index
{
private:
    std::string _index;
    bool _isValid;

public:
    Index();
    Index(const std::string &config);
    ~Index();
    std::string Get();
    bool Set(const std::string &config);
    bool isValid();
};
