#pragma once

#include <string>
#include <iostream>
#include <vector>

class ReturnStatus
{
private:
    std::string _status;
    std::string _url;
    bool _isValid;

public:
    ReturnStatus();
    ReturnStatus(const std::string &config);
    ~ReturnStatus();
    std::vector<std::string> Get();
    bool Set(const std::string &config);
    bool isValid();
};
