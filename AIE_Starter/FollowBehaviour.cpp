#include "FollowBehaviour.h"

void FollowBehaviour::Update(Agent* agent, float dt)
{
	Agent* target = agent->GetTarget();

	float dist = glm::distance(target->GetPosition(), lastTargetPosition);
	if (dist > agent->GetNodeMap()->GetCellSize()) {
		lastTargetPosition = target->GetPosition();
		agent->GoTo(lastTargetPosition);
	}
}
