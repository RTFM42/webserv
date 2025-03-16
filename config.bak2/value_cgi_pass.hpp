#pragma once

#include <string>
#include <iostream>
#include <vector>

class CgiPass
{
private:
    std::string _path;
    bool _isValid;

public:
    CgiPass();
    CgiPass(const std::string &config);
    ~CgiPass();
    std::string Get();
    bool Set(const std::string &config);
    bool isValid();
};
