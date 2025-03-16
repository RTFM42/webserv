#include <cctype>

#include "./config.hpp"

static bool startsWith(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}



static int parser(const std::string &config)
{
    int i = 0;

    while (config[i])
    {
        while (config[i])
        {
            while (std::isspace(config[i]))
                i++;
            if (!config[i])
            {
                std::cerr << "Error: invalid config(" << i << ")" << std::endl;
                return (1);
            }
            if (startsWith(&config[i], "server"))
                i += 6;
            else
            {
                std::cerr << "Error: invalid config(" << i << ")" << std::endl;
                return (1);
            }
            while (std::isspace(config[i]))
                i++;
            if (startsWith(&config[i], "{"))
                i++;
            else
            {
                std::cerr << "Error: invalid config(" << i << ")" << std::endl;
                return (1);
            }
            while (config[i])
            {
            }
        }
    }
}
