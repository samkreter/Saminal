#ifndef SAMINAL_HPP__
#define SAMINAL_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <exception>
#include <fstream>

class Saminal{

    const std::string basic_cmds[4] = {"ls","cd","pwd","cat"};
    boost::filesystem::path currDir;
    boost::filesystem::path homeDir;
private:
    Saminal();
    int ls();
    int cd(std::string args);
    int pwd();
    int cat(std::string file);
    int check_cmd_exit(std::string cmd);
    std::vector<std::string> parse_args(std::string args);
    int exec_basic(std::string* args);
    int exec_added(std::string* args);
    void printColor(std::string text,int color);

public:
    void run();
};


#endif