#include <iostream>
#include <sstream>

#include "./config_raw.hpp"

ConfigRaw::ConfigRaw()
{
    this->count = 0;
    this->key = "";
}

ConfigRaw::~ConfigRaw()
{
    for (std::vector<std::string *>::iterator it = this->value.begin(); it != this->value.end(); it++)
    {
        delete *it;
    }
    for (std::vector<ConfigRaw *>::iterator it = this->scope.begin(); it != this->scope.end(); it++)
    {
        delete *it;
    }
}

std::ostream &operator<<(std::ostream &os, const ConfigRaw &config)
{
    os << config.key;
    for (std::vector<std::string *>::const_iterator it = config.value.begin(); it != config.value.end(); it++)
    {
        os << " " << **it;
    }
    if (config.scope.empty())
    {
        os << ";" << std::endl;
        return os;
    }
    else
    {
        os << " {" << std::endl;
    }
    for (std::vector<ConfigRaw *>::const_iterator it = config.scope.begin(); it != config.scope.end(); it++)
    {
        std::ostringstream oss;
        oss << **it;
        std::istringstream ss(oss.str());
        std::string line;
        while (std::getline(ss, line))
        {
            os << "    " << line << std::endl;
        }
    }
    os << "}" << std::endl;
    return os;
}
