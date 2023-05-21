#include "includes.h"

void StateMachine::changeState(State* newState) 
{
    if (currentState_) 
    {
        currentState_->exit();
        Sleep(500);
    }

    currentState_ = newState;

    if (currentState_) {
        currentState_->enter();
    }
}

void StateMachine::run() 
{
    int  result = STAY_STATE;
    while (true) 
    {
        if (currentState_) 
        {
            result = currentState_->update();
        }

        // if( true == flag && STATE_IDLE == currentStateId_)
        // {
        //     changeState(new Battle_state);
        //     currentStateId_ = STATE_BATTLE;
        // }
        // else if(false == flag && STATE_BATTLE == currentStateId_)
        // {
        //     changeState(new Idle_state);
        //     currentStateId_ = STATE_IDLE;
        // }

        switch(result)
        {
            case STAY_STATE:
            break;
            case STATE_IDLE:
                changeState(new Idle_state);
                currentStateId_ = STATE_IDLE;
                break;

            case STATE_BATTLE:
                changeState(new Battle_state);
                currentStateId_ = STATE_BATTLE;
                break;

            case STATE_STOP:
                changeState(new Stop_state);
                currentStateId_ = STATE_STOP;
                break;
            
            default:
            break;
        }

        
        Sleep(100);
    }
}
