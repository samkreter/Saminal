#include <iostream>
#include <exception>
#include <fstream>


#define private public
#include "../include/saminal.hpp"


using namespace std;

void basic_cmd_tester();

int main(){

    cout<<"STARTING TESTS"<<endl;

    // Saminal s;
    // s.parse_args(string("cmd hello there"));
    basic_cmd_tester();

    cout<<"TESTS COMPLETE"<<endl;
}

void basic_cmd_tester(){
    Saminal s;
    vector<string> testPaths[6];
    testPaths[0].push_back("");
    testPaths[1].push_back("../bill");
    testPaths[2].push_back("~/Downloads");
    testPaths[3].push_back("bill");
    testPaths[4].push_back("~");
    testPaths[5].push_back("h767676765894938753ey.txt");

    //test cd/////////////////////////////

    //test empty string
    assert(s.cd(testPaths[0]) == -1);

    //test non existent canonical path
    assert(s.cd(testPaths[1]) == -1);

    //can go to home directory
    assert(s.cd(testPaths[2]) > 0);
    //end test cd//////////////////////////

    //test cat/////////////////////////////

    //test for empty file
    assert(s.cat(testPaths[0]) == -1);

    //test file doesn't exist
    assert(s.cat(testPaths[3]) == -1);

    //test a good file
    //change to home directory
    s.cd(testPaths[4]);
    //create simple file to cat
    //make sure name doesn't override something on whosever computer
    ofstream myfile("h767676765894938753ey.txt");
    for(int i = 0; i < 10; i++){
        myfile << "hello world\n";
    }
    myfile.close();

    //test can cat file
    assert(s.cat(testPaths[5]) > 0);
    //remove the file
    system("rm h767676765894938753ey.txt");
    //end test cat/////////////////////////
}



