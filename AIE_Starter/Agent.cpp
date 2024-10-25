#include "Agent.h"

void Agent::Update(float dt)
{
	if (m_current)
		m_current->Update(this, dt);
	m_pa.Update(dt);
}

void Agent::Draw()
{
}

void Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nm->GetClosestNode(point);
	m_pa.GoToNode(end);
}
