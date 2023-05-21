#pragma once
#include "includes.h"

class StateMachine {
public:
    void changeState(State* newState);
    void run();

private:
    State* currentState_ =nullptr;
    int currentStateId_ = 1 ;
};


