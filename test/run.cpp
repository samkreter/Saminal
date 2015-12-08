#include <iostream>
#include <vector>

#define private public
#include "../include/saminal.hpp"

using namespace std;

int main(){
    vector<string> test{"join","../test/test1.csv","a","../test/test2.csv","1","hey.csv"};
    Saminal s;
    cout<<test.size();
    s.join(test);

    return 0;
}