#pragma once
#include "Decision.h"
#include "Condition.h"
class ABDecision :
    public Decision
{
public:
	ABDecision(Condition* newCondition, Decision* newDecA, Decision* newDecB) {
		decA = newDecA;
		decB = newDecB;
		condition = newCondition;
	}
	virtual bool makeDecision(Agent* a, float dt);
private:
	Decision* decA;
	Decision* decB;
	Condition* condition;
};

