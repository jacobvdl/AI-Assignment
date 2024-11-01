#pragma once
#include "Condition.h"
#include "Agent.h"
class DistanceCondition :
    public Condition
{
private:
    float distance;
    bool lessThan;
public:
    DistanceCondition(float d, bool lt) : distance(d), lessThan(lt) {}
    virtual bool IsTrue(Agent* agent);
};

