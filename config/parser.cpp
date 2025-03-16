#include <iostream>

#include "./parser.hpp"
#include "./config_raw.hpp"

Parser::Parser(const std::string &config)
{
    int i = 0;
    int n = 0;
    std::string key = "";
    std::vector<std::string *> value;
    std::vector<ConfigRaw *> scope;
    Parser *child = NULL;

    this->config = NULL;

    while (i == 0)
    {
        // KEY
        while (std::isspace(config[i]) || config[i] == ';' || config[i] == '#')
        {
            if (std::isspace(config[i]) || config[i] == ';')
                i++;
            else if (config[i] == '#')
                while (config[i] && config[i] != '\n')
                    i++;
        }
        if (!config[i])
        {
            std::cerr << "Error: invalid config key(" << i << ")" << std::endl;
            return;
        }
        n = 0;
        while (('A' <= config[i + n] && config[i + n] <= 'Z') || ('a' <= config[i + n] && config[i + n] <= 'z') || '_' == config[i + n])
            n++;
        if (n == 0)
        {
            std::cerr << "Error: invalid config key(" << i << ")" << std::endl;
            return;
        }
        key = config.substr(i, n);
        i += n;
        if (!config[i])
        {
            std::cerr << "Error: invalid config key(end)" << std::endl;
            return;
        }
        // KEY END
        while (std::isspace(config[i]))
            i++;
        if (config[i] == ';' && i++)
        {
            i++;
            break;
        }
        // VALUE and SCOPE
        while (config[i])
        {
            if (config[i] == ';')
            {
                i++;
                break;
            }
            else if (config[i] == '{')
            {
                // SCOPE
                i++;
                while (1)
                {
                    child = new Parser(&config[i]);
                    if (child->config == NULL || child->config->key.empty())
                    {
                        delete child;
                        return;
                    }
                    else
                    {
                        scope.push_back(child->config);
                        i += child->config->count;
                        delete child;
                        while (std::isspace(config[i]) || config[i] == ';')
                        {
                            if (std::isspace(config[i]))
                                i++;
                            else if (config[i] == ';')
                                i++;
                        }
                        if (config[i] == '}')
                            break;
                    }
                }
                if (!config[i])
                {
                    std::cerr << "Error: invalid config(end)" << std::endl;
                    return;
                }
                if (config[i] == '}')
                {
                    i++;
                    break;
                }
                else
                {
                    std::cerr << "Error: invalid config child(" << i << ")" << std::endl;
                    return;
                }
            }
            else
            {
                // VALUE
                n = 0;
                while (config[i + n] && config[i + n] != ';' && config[i + n] != '{')
                    n++;
                value.push_back(new std::string(config.substr(i, n)));
                i += n;
            }
        }
        break;
    }
    this->config = new ConfigRaw();
    this->config->count = i;
    this->config->key = key;
    this->config->value = value;
    this->config->scope = scope;
}

Parser::~Parser()
{
}
