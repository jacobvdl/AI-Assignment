#include "WanderBehaviour.h"

void WanderBehaviour::Update(Agent* agent, float dt)
{
	//std::cout << "WANDER UPDATE FIRED\n";
	if (agent->PathComplete()) {
		//std::cout << "WANDER PATH COMPLETE\n";
		Node* target = agent->GetNodeMap()->GetRandomNode();
		agent->GetPathAgent()->GoToNode(target);
	} //else 
		//std::cout << "WANDER PATH NOT COMPLETE\n";
}
