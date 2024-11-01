#include "DistanceCondition.h"

bool DistanceCondition::IsTrue(Agent* agent) {
	return (glm::distance(agent->GetPosition(), agent->GetTarget()->GetPosition()) < distance) == lessThan;
}