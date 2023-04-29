//
// Created by Eran on 6/26/2021.
//

#ifndef HW5_PARSER_H
#define HW5_PARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "Counter.h"
using namespace std;

class Parser{
public:
    void start();
private:
    vector<Counter<int> > vecInt;
    vector<Counter<string> > vecStr;
    int searchIntCounter(const string& name);
    int searchStringCounter(const string& name);
};

#endif //HW5_PARSER_H
