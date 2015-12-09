#ifndef SAMINAL_HPP__
#define SAMINAL_HPP__


//damn I got into using the pre existing headers
#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/thread.hpp>
#include <stdlib.h>
#include <sys/types.h>
#include <exception>
#include <fstream>
#include <map>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>


//its a greatly named class
class Saminal{

    //typdef to make the func pointer declaration much nicer to read
    typedef int (Saminal::*FnPtr)(std::vector<std::string>);

    //set the map up to holp basic cmd and their function pointers
    std::map<std::string, FnPtr> b_cmd_map;

    //set the home directory from a env var of the system
    boost::filesystem::path homeDir;

private:

    ///
    /// list the contents of current dir or a passed in relative path to dir
    /// \param args: array of cmds, optional hold a path to a different dir
    /// \return: -1 for error, 1 for success
    ///
    int ls(std::vector<std::string> args);

    ///
    /// changes current working directory
    /// \param args: the path for which directory to change, relative path or use ~ for home dir
    /// \return -1 for error, 1 for success
    ///
    int cd(std::vector<std::string> args);

    ///
    /// prints the current working dir
    /// \param args: not used in this case, just to keep function pointers easy
    /// return: -1 for error, 1 for success
    ///
    int pwd(std::vector<std::string>);

    ///
    /// prints passed in file contents to the console
    /// \param args: the path to the file
    /// \return: -1 for error, 1 for success
    ///
    int cat(std::vector<std::string>);

    ///
    /// checks if cmd is basic, added or not there
    /// \param cmd: the cmd name
    /// \return: -1 for error, 0 for not found, 1 for basic, 2 for added
    ///
    int check_cmd_exist(std::string cmd);

    ///
    /// parses arg string into a vector of cmds
    /// \param args: string form the user witht the cmds
    /// return: vector with the stuff, NULL vector for error
    ///
    std::vector<std::string> parse_args(std::string args);

    ///
    /// exectues a basic cmd of the shell
    /// \param args: the arguments for the cmd
    /// return -1 for error, 1 for succcess
    ///
    int exec_basic(std::vector<std::string> args);

    ///
    /// exectues an added cmd of the shell (* not yet used)
    /// \param args: args for the cmd
    /// \return -1 for error, 1 for success
    ///
    int exec_added(std::vector<std::string> args);


    ///
    /// joins to files based on a passed in delemitor (*not yet implemented)
    ///
    /// Planning to have as separte exec, all secandary cmds will be exected that
    /// way to make it extremly easy to add cmds, just add the executable to the
    /// "local" folder.
    ///
    /// planning on using c++11 native threads, and the c++11 mutex library
    int join(std::vector<std::string> args);

    ///
    /// prints the passed in string all colory, nice helper function
    /// \param text: the text to be printed out
    /// \param color: the number of the color to print
    ///
    void printColor(std::string text,int color);

public:
    ///
    /// Sets up the vars for the terminal from teh current system
    ///
    Saminal();

    ///
    ///public interface to start the terminal
    ///
    void run();
};


#endif