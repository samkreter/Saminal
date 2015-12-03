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
#include <map>



class Saminal{
    typedef int (Saminal::*FnPtr)(std::vector<std::string>);
    //const std::string basic_cmds[4] = {"ls","cd","pwd","cat"};
    std::map<std::string, FnPtr> b_cmd_map;
    boost::filesystem::path currDir;
    boost::filesystem::path homeDir;
private:
    Saminal();
    int ls(std::vector<std::string>);
    int cd(std::vector<std::string> args);
    int pwd(std::vector<std::string>);
    int cat(std::vector<std::string>);
    int check_cmd_exist(std::string cmd);
    std::vector<std::string> parse_args(std::string args);
    int exec_basic(std::vector<std::string> args);
    int exec_added(std::vector<std::string> args);
    void printColor(std::string text,int color);

public:
    void run();
};


#endif