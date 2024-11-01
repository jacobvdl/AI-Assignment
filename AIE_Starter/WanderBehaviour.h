#pragma once
#include "Behaviour.h"
#include "Agent.h"
class WanderBehaviour :
    public Behaviour
{
public:
    virtual void Update(Agent* agent, float dt);
    virtual void Enter(Agent* agent);
};

