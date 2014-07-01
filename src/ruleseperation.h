#ifndef RULESEPERATION_H
#define RULESEPERATION_H

#include "IBoidRule.h"
#include "Float2.h"

class RuleSeperation : public IBoidRule
{
public:
    RuleSeperation();
    virtual ~RuleSeperation();
    virtual void followRule(Boid &b, std::vector<Boid> *swarm);
private:
    Float2 tmpv;
    Float2 tmpw;
};

#endif // RULESEPERATION_H
