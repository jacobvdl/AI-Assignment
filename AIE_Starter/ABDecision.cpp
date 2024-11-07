#include "ABDecision.h"

ABDecision::ABDecision(Decision* _decA, Decision* _decB)
{
	DecA = _decA;
	DecB = _decB;
}

void ABDecision::setDecisions(Decision* _decA, Decision* _decB)
{
	DecA = _decA;
	DecB = _decB;
}

void ABDecision::makeDecision(Agent* agent, float dt)
{
	if (currentCondition->IsTrue(agent))
		DecA->makeDecision(agent, dt);
	else
		DecB->makeDecision(agent, dt);
}
