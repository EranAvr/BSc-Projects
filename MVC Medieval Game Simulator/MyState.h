//
// Created by Eran on 6/23/2023.
//

#ifndef HW3_MYSTATE_H
#define HW3_MYSTATE_H

#include "Agent.h"

class MyState{
public:
    MyState(Agent& _agnt) : agnt{_agnt} {}
    virtual ~MyState()= default;

    virtual void makeMove() = 0;
private:
    Agent& agnt;
};

#endif //HW3_MYSTATE_H
