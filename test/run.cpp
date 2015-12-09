#include <iostream>
#include <vector>

#define private public
#include "../include/saminal.hpp"

using namespace std;

int main(){
    vector<string> test{"join","3","../test/test1.csv","1","../test/test2.csv","1","../test/test3.csv","1","hey.csv"};
    Saminal s;
    s.join(test);

    return 0;
}