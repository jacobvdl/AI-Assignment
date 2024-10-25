#pragma once
#include "Behaviour.h"
#include "Agent.h"
class GoToPointBehaviour :
    public Behaviour
{
public:
    virtual void Update(Agent* agent, float dt);
};

