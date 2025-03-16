#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>

class ConfigRaw
{
public:
    ConfigRaw();
    ~ConfigRaw();
    friend std::ostream &operator<<(std::ostream &os, const ConfigRaw &config);
    unsigned long count;
    std::string key;
    std::vector<std::string *> value;
    std::vector<ConfigRaw *> scope;
};

#endif
