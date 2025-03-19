#include <fstream>
#include <iostream>

#include "./config/parser.hpp"

int main()
{
    std::ifstream file("./webserv.conf");
    if (!file)
    {
        std::cerr << "Error: file not found" << std::endl;
        return (1);
    }
    std::string config((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    Parser parser(config);
    std::cout << parser.config << std::endl;
    delete parser.config;
    return 0;
}
