#pragma once
#include "Decision.h"
class WanderDecision :
    public Decision
{
public:
    virtual void makeDecision(Agent* agent, float dt);
};

