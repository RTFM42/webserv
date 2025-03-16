#pragma once

#include <string>
#include <iostream>

class Listen
{
private:
    u_int16_t _port;
    bool _isValid;

public:
    Listen();
    Listen(const std::string &config);
    ~Listen();
    u_int16_t Get();
    bool Set(const std::string &config);
    bool isValid();
};
