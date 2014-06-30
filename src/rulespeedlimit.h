#ifndef RULESPEEDLIMIT_H
#define RULESPEEDLIMIT_H

#include "IBoidRule.h"

class RuleSpeedLimit : public IBoidRule
{
public:
    RuleSpeedLimit();
    virtual ~RuleSpeedLimit();
    virtual void followRule(Boid &b, std::vector<Boid> *swarm);
};

#endif // RULESPEEDLIMIT_H
