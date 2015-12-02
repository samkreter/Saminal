#include <iostream>
#include <exception>

#include "../include/saminal.hpp"

using namespace std;

int pwd_tester();

int main(){
    pwd_tester();
}

int pwd_tester(){
    Saminal s;
    s.run();
    cout<<"filaed "<<__LINE__<<" "<<__FILE__<<endl;
    return 1;
}