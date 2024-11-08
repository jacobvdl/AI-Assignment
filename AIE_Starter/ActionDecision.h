#pragma once
#include "Decision.h"
class ActionDecision :
    public Decision
{
public:
	virtual bool makeDecision(Agent* a, float dt);
};

