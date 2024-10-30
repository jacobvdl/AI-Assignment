#include "FiniteStateMachine.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : states)
		delete s;
}

void FiniteStateMachine::Update(Agent* agent, float dt)
{
	currentState->Update(agent, dt);
}
