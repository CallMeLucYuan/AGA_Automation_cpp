#pragma once

class State
 {
public:
    virtual ~State() {}
    virtual void enter() = 0;
    virtual int update() = 0;
    virtual void exit() = 0;
};

class Idle_state : public State 
{
public:
    void enter() override;
    int update() override;
    void exit() override;
};

class Battle_state : public State 
{
public:
    void enter() override;
    int update() override;
    void exit() override;
};

class Stop_state : public State 
{
public:
    void enter() override;
    int update() override;
    void exit() override;
};
