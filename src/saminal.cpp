#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

#include "../include/saminal.hpp"

namespace fs = boost::filesystem;
using namespace std;

int main(int argc, char** argv){


    // fs::path full_path( fs::initial_path<fs::path>() );
    // cout<<full_path<<endl;
    // cout<<full_path.filename()<<endl;
    // cout<<fs::is_directory(full_path.parent_path())<<endl;
    Saminal s;


    return 0;
}


