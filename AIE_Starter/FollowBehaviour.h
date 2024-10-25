#pragma once
#include "Behaviour.h"
#include "Agent.h"
#include <glm/glm.hpp>
class FollowBehaviour :
    public Behaviour
{
public:
    virtual void Update(Agent* agent, float dt);

private:
    glm::vec2 lastTargetPosition;
};

