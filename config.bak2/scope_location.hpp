#pragma once

#include <string>
#include <iostream>

#include "./value_root.hpp"
#include "./value_index.hpp"
#include "./value_alias.hpp"
#include "./value_limit_expect.hpp"
#include "./value_return_status.hpp"
#include "./value_cgi_pass.hpp"

class Location
{
private:
    std::string _path;
    bool _isValid;

public:
    Location();
    Location(const std::string &config);
    ~Location();
    std::string Get();
    bool Set(const std::string &config);
    bool isValid();

    Root root;
    Index index;
    Alias alias;
    LimitExpect limitExpect;
    ReturnStatus returnStatus;
    CgiPass cgiPass;
};
