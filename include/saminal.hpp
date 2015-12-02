#ifndef SAMINAL_HPP__
#define SAMINAL_HPP__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <exception>

class Saminal{

    const std::string basic_cmd[4] = {"ls","cd","pwd","cat"};
    boost::filesystem::path currDir;
private:
    Saminal();
    int ls();
    int cd(std::string args);
    int pwd();
    int cat();
    std::string* parse_args(std::string* args);
    int exec_basic(std::string* args);
    int exec_added(std::string* args);
    void printColor(std::string text,int color);

public:
    void run();
};


#endif