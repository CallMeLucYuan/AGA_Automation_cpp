#include "includes.h"

int screen_type;
std::atomic<bool> terminateThread(TRUE); //FLag to terminateThread
std::thread myThread;
int main() 
{
    init();
    StateMachine stateMachine;
    
    Idle_state idle_state;
    Battle_state battle_state;
    Stop_state   stop_state;


    stateMachine.changeState(&stop_state);
    stateMachine.run();

    return 0;
}
