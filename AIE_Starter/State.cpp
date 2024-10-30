#include "State.h"

State::~State()
{
	for (Behaviour* b : behaviours)
		delete b;

	for (Transition t : transitions)
		delete t.condition;
}

void State::Update(Agent* agent, float dt)
{
	for (Behaviour* b : behaviours)
		b->Update(agent, dt);
}
