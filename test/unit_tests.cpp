#include <iostream>
#include <exception>
#include <fstream>


//this is a sketchy hack that turns all private functions into public ones
// so I can unit test them. Probably not best practice but pretty usful for
// something like this
// Its gotta be before including the header file so it overrides it
#define private public
#include "../include/saminal.hpp"


using namespace std;

void basic_cmd_tester();

int main(){

    cout<<"STARTING TESTS"<<endl;

    basic_cmd_tester();

    cout<<"ALL TESTS PASSED"<<endl;
}

void basic_cmd_tester(){
    Saminal s;
    vector<string> testPaths[6];

    //gotta put a place holder for the commands
    testPaths[0].push_back("cmd");
    testPaths[1].push_back("cmd");
    testPaths[2].push_back("cmd");
    testPaths[3].push_back("cmd");
    testPaths[4].push_back("cmd");
    testPaths[5].push_back("cmd");


    //testing paths to make it easier
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


    ///run test//////
    //make sure theres not exceptions during the run functions
    try{
        s.run();
    }
    catch(...){
        cerr<<"Run test failed line:"<<__LINE__<<" in file:"<<__FILE__<<endl;
        exit(-1);
    }
    ///
}



