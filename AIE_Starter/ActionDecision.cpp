#include "ActionDecision.h"

bool ActionDecision::makeDecision(Agent* a, float dt)
{
    a->SetBehaviour(action);
    return true;
}
