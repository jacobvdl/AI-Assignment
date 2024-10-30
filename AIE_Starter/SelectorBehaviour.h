#pragma once
#include "Behaviour.h"
#include "Agent.h"
class SelectorBehaviour :
    public Behaviour
{
private:
    Behaviour* b1;
    Behaviour* b2;
    Behaviour* selected;

public:
    SelectorBehaviour(Behaviour* _b1, Behaviour* _b2) : b1(_b1), b2(_b2), selected(_b2) {}
    virtual void Update(Agent* agent, float dt);
    void SetBehaviour(Behaviour* b, Agent* agent);
};

