#include "Agent.h"
#include "Decision.h"

void Agent::Update(float dt)
{
	if (m_decisionTree != nullptr)
		m_decisionTree->makeDecision(this, dt);
	if (m_current)
		m_current->Update(this, dt);
	m_pa.Update(dt);
}

void Agent::Draw()
{
	m_pa.Draw(m_color);
}

void Agent::GoTo(glm::vec2 point)
{
	Node* end = m_nm->GetClosestNode(point);
	m_pa.GoToNode(end);
}

void Agent::SetNode(Node* n)
{
	m_pa.SetNode(n);
}

void Agent::SetSpeed(float spd)
{
	m_pa.SetSpeed(spd);
}

void Agent::SetTarget(Agent* target)
{
	m_target = target;
}

bool Agent::PathComplete()
{
	return m_pa.path.empty();
}

void Agent::Reset()
{
	m_pa.path.clear();
}

void Agent::SetColor(Color newColor)
{
	m_color = newColor;
}

void Agent::SetBehaviour(Behaviour* newBehaviour)
{
	if (m_current != newBehaviour) {
		if (m_current != nullptr)
			m_current->Exit(this);
		m_current = newBehaviour;
		m_current->Enter(this);
	}
}

void Agent::SetDecision(Decision* newDec)
{
	m_decisionTree = newDec;
}

