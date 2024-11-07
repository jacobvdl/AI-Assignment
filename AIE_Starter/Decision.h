#pragma once
#include "Agent.h"
#include "Condition.h"
class Decision : public Behaviour	
{
public:
	virtual void makeDecision(Agent* agent, float dt) {};
};

