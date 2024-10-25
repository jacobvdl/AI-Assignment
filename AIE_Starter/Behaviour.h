#pragma once
class Agent;
class Behaviour
{
public:
	virtual void Update(Agent* agent, float dt) = 0;
};

