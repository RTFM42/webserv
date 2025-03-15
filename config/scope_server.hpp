#pragma once

#include <string>
#include <iostream>

#include "./value_listen.hpp"
#include "./value_server_names.hpp"
#include "./value_root.hpp"
#include "./value_index.hpp"
#include "./scope_location.hpp"

class Server
{
private:
    bool _isValid;

public:
    Server();
    Server(const std::string &config);
    ~Server();
    bool Set(const std::string &config);
    bool isValid();

    Listen listen;
    ServerNames serverNames;
    Root root;
    Index index;
    Location location;
};
