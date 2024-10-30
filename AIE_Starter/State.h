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
	~State();
	virtual void Update(Agent* agent, float dt);
};

