#include <iostream>
#include <vector>

#define private public
#include "../include/saminal.hpp"

using namespace std;

int main(){
    vector<string> test{"join","2","../test/test1.csv","2","../test/test2.csv","2","hey.csv"};
    Saminal s;
    s.join(test);

    return 0;
}