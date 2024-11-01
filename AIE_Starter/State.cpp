#include "State.h"

State::~State()
{
	for (Behaviour* b : behaviours)
		delete b;

	for (Transition t : transitions)
		delete t.condition;
}

void State::Enter(Agent* agent)
{
	for (Behaviour* b : behaviours)
		b->Enter(agent);
}

void State::Update(Agent* agent, float dt)
{
	for (Behaviour* b : behaviours)
		b->Update(agent, dt);
}

void State::Exit(Agent* agent)
{
	for (Behaviour* b : behaviours)
		b->Exit(agent);
}

void State::AddTransition(Condition* _condition, State* _state)
{
	Transition newTransiton;
	newTransiton.condition = _condition;
	newTransiton.targetState = _state;

	transitions.push_back(newTransiton);
}
