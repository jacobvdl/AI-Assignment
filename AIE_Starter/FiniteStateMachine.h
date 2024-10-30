#pragma once
#include "Behaviour.h"
#include <vector>
#include "State.h"
#include "Agent.h"
class FiniteStateMachine : public Behaviour
{
private:
	std::vector<State*> states;

	State* currentState;
	State* newState;

public:
	FiniteStateMachine(State* s) : currentState(s), newState(nullptr) {}
	virtual ~FiniteStateMachine();

	void Update(Agent* agent, float dt);


};

