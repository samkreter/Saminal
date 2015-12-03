#include <iostream>
#include <exception>
#include <fstream>


#define private public
#include "../include/saminal.hpp"


using namespace std;

void basic_cmd_tester();

int main(){

    cout<<"STARTING TESTS"<<endl;

    Saminal s;
    s.run();
    //basic_cmd_tester();

    cout<<"TESTS COMPLETE"<<endl;
}

void basic_cmd_tester(){
    Saminal s;
    string testPaths[3] = {"../bill","~/Downloads"};

    //test cd/////////////////////////////

    //test empty string
    assert(s.cd("") == -1);

    //test non existent canonical path
    assert(s.cd(testPaths[0]) == -1);

    //can go to home directory
    assert(s.cd(testPaths[1]) > 0);
    //end test cd//////////////////////////

    //test cat/////////////////////////////

    //test for empty file
    assert(s.cat("") == -1);

    //test file doesn't exist
    assert(s.cat("bill") == -1);

    //test a good file
    //change to home directory
    s.cd("~");
    //create simple file to cat
    //make sure name doesn't override something on whosever computer
    ofstream myfile("h767676765894938753ey.txt");
    for(int i = 0; i < 10; i++){
        myfile << "hello world\n";
    }
    myfile.close();

    //test can cat file
    assert(s.cat("h767676765894938753ey.txt") > 0);
    //remove the file
    system("rm h767676765894938753ey.txt");
    //end test cat/////////////////////////
}



