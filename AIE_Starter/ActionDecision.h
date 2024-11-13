#pragma once
#include "Decision.h"
#include "Behaviour.h"
class ActionDecision :
    public Decision
{
public:
	ActionDecision(Behaviour* newAction) { action = newAction; }
	virtual bool makeDecision(Agent* a, float dt);
private:
	Behaviour* action;
};

