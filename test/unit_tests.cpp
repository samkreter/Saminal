#include <iostream>
#include <exception>


#define private public
#include "../include/saminal.hpp"

using namespace std;

int pwd_tester();

int main(){
    Saminal s;
    s.ls();
}

int basic_cmd_tester(){
    Saminal s;
    s.pwd();
    //cout<<"filaed "<<__LINE__<<" "<<__FILE__<<endl;
    return 1;
}