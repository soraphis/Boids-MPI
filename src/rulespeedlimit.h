#ifndef RULESPEEDLIMIT_H
#define RULESPEEDLIMIT_H

#include "IBoidRule.h"

class RuleSpeedLimit : public IBoidRule
{
public:
    RuleSpeedLimit();
    virtual ~RuleSpeedLimit();
    virtual void followRule(Boid &b, Boid *swarm, const int swarmsize);
};

#endif // RULESPEEDLIMIT_H
