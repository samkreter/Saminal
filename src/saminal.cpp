#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include "../include/saminal.hpp"

namespace fs = boost::filesystem;



    // fs::path full_path( fs::initial_path<fs::path>() );
    // cout<<full_path<<endl;
    // cout<<full_path.filename()<<endl;
    // cout<<fs::is_directory(full_path.parent_path())<<endl;


int Saminal::ls(){
    return -1;
}
int Saminal::cd(std::string* args){
    return -1;
}
int Saminal::pwd(){
    return 01;
}
int Saminal::cat(){
    return -1;
}
std::string* Saminal::parse_args(std::string* args){
    return nullptr;
}
int Saminal::exec_basic(std::string* args){
    return -1;
}
int Saminal::exec_added(std::string* args){
    return -1;
}

void Saminal::run(){
    fs::path full_path( fs::initial_path<fs::path>() );
    std::cout<<full_path<<std::endl;
    return;
}


