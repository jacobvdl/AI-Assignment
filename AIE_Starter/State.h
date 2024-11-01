#pragma once
#include <vector>
#include "Behaviour.h"
#include "Condition.h"
class State
{
public:
	struct Transition {
		Condition* condition;
		State* targetState;
	};
private:
	std::vector<Behaviour*> behaviours;
	std::vector<Transition> transitions;

public:
	State();
	State(Behaviour* behaviour) {
		behaviours.push_back(behaviour);
	}
	~State();
	virtual void Enter(Agent* agent);
	virtual void Update(Agent* agent, float dt);
	virtual void Exit(Agent* agent);
	std::vector<Transition> GetTransitions() { return transitions; }
	void AddTransition(Condition* _condition, State* _state);
};

