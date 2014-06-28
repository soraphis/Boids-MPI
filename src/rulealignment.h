#ifndef RULEALIGNMENT_H
#define RULEALIGNMENT_H

#include "IBoidRule.h"
#include "Float2.h"

class RuleAlignment : public IBoidRule
{
private:
	Float2 tmpv;
public:
    RuleAlignment();
    virtual ~RuleAlignment();
    virtual void followRule(Boid &b, Boid *swarm, const int swarmsize);
};

#endif // RULEALIGNMENT_H
