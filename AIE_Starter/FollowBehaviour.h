#pragma once
#include "Behaviour.h"
#include "Agent.h"
#include <glm/glm.hpp>
class FollowBehaviour :
    public Behaviour
{
public:
    virtual void Update(Agent* agent, float dt);
    virtual void Enter(Agent* agent);

private:
    glm::vec2 lastTargetPosition;
};

