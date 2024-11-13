#include "ABDecision.h"

bool ABDecision::makeDecision(Agent* a, float dt)
{
	if (condition->IsTrue(a)) {
		decA->makeDecision(a, dt);
		return true;
	}
	else {
		decB->makeDecision(a, dt);
		return false;
	}
}
