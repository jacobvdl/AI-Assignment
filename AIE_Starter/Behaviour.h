#pragma once
class Agent;
class Behaviour
{
public:
	virtual void Enter(Agent* agent) {}
	virtual void Update(Agent* agent, float dt) = 0;
	virtual void Exit(Agent* agent) {}
};

