#include "BehaviourCondition.h"

bool BehaviourCondition::IsTrue(Agent* agent)
{
    if (agent->GetBehaviour() == behaviour)
        return true;
    return false;
}
