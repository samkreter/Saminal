#include <iostream>
#include <vector>

#define private public
#include "../include/saminal.hpp"

using namespace std;

int main(){
    vector<string> test{"join","3","../data/cities.csv","3","../data/country_stats.csv","1","../data/country_leadership.csv","1","hey.csv"};
    Saminal s;
    s.join(test);


    return 0;
}