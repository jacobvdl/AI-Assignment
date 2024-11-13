#pragma once
#include "Condition.h"
#include "Agent.h"
#include "Behaviour.h"
class BehaviourCondition : public Condition
{
private:
    Behaviour* behaviour;
public:
    BehaviourCondition(Behaviour* behaviourToCheck) : behaviour(behaviourToCheck) {}
    virtual bool IsTrue(Agent* agent);
};

