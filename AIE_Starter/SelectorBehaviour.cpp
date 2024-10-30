#include "SelectorBehaviour.h"

void SelectorBehaviour::Update(Agent* agent, float dt)
{
	float dist = (agent->GetPosition().x + agent->GetPosition().y) - (agent->GetTarget()->GetPosition().x + agent->GetTarget()->GetPosition().y);

	if (dist < 0) {
		dist *= -1; // make the number positive
	}
	if (dist < agent->GetNodeMap()->GetCellSize() * 5) {
		SetBehaviour(b1, agent);
		agent->SetColor({ 255,0,0,255 });
	}
	else {
		SetBehaviour(b2, agent);
		agent->SetColor({ 0,255,255,255 });
	}
	selected->Update(agent, dt);
}

void SelectorBehaviour::SetBehaviour(Behaviour* b, Agent* agent)
{
	if (selected != b) {
		selected = b;
		std::cout << "RESETTING\n";
		agent->Reset();
	}
}
