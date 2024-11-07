#pragma once
#include "Decision.h"
class ABDecision :
    public Decision
{
    Decision* DecA;
    Decision* DecB;
    Condition* currentCondition;

public:
    ABDecision(Decision* _decA, Decision* _decB);
    void setCondition(Condition* newcondition) { currentCondition = newcondition; }
    Condition* getCondition() { return currentCondition; }
    void setDecisions(Decision* _decA, Decision* _decB);

    virtual void makeDecision(Agent* agent, float dt);
};

