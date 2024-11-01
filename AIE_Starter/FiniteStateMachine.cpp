#include "FiniteStateMachine.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : states)
		delete s;
}

void FiniteStateMachine::Update(Agent* agent, float dt)
{
	State* newState = nullptr;

	for (State::Transition t : currentState->GetTransitions()) {
		if (t.condition->IsTrue(agent))
			newState = t.targetState;
	}

	if (newState != nullptr && newState != currentState) {
		currentState->Exit(agent);
		currentState = newState;
		currentState->Enter(agent);
	}

	currentState->Update(agent, dt);
}
