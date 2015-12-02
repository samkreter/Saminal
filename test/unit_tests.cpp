#include <iostream>
#include <exception>


#define private public
#include "../include/saminal.hpp"


using namespace std;

int basic_cmd_tester();

int main(){

    cout<<"STARTING TESTS"<<endl;
    basic_cmd_tester();

    cout<<"TESTS COMPLETE"<<endl;
}

int basic_cmd_tester(){
    Saminal s;
    string testPaths[3] = {"../test","~/samkreter"};

    //test cd/////////////////////////////

    //test empty string
    assert(s.cd("") == -1);

    //test non existent canonical path
    assert(s.cd(testPaths[0]) == -1);
    return 1;
}



