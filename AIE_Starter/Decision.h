#pragma once
#include "Agent.h"
class Decision
{
public:
	virtual bool makeDecision(Agent* a, float dt) { return false; }
};

