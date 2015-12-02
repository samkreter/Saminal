#include <iostream>
#include <exception>


#define private public
#include "../include/saminal.hpp"


using namespace std;

void basic_cmd_tester();

int main(){

    cout<<"STARTING TESTS"<<endl;

    // Saminal s;
    // s.run();
    basic_cmd_tester();

    cout<<"TESTS COMPLETE"<<endl;
}

void basic_cmd_tester(){
    Saminal s;
    string testPaths[3] = {"../test","~/Downloads"};

    //test cd/////////////////////////////

    //test empty string
    assert(s.cd("") == -1);

    //test non existent canonical path
    assert(s.cd(testPaths[0]) == -1);

    //can go to home directory
    assert(s.cd(testPaths[1]) > 0);
}



