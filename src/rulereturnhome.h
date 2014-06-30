#ifndef RULERETURNHOME_H
#define RULERETURNHOME_H

#include "IBoidRule.h"
//#include "Boid.h"
#include "Float2.h"

class RuleReturnHome : public IBoidRule
{
public:
    RuleReturnHome();
    RuleReturnHome(Boid* homes, int homecount);
    virtual ~RuleReturnHome();
    virtual void followRule(Boid &b, std::vector<Boid> *swarm);
private:
    Boid* homes;
    int homecount;
    Float2 tmpv;
};

#endif // RULERETURNHOME_H
