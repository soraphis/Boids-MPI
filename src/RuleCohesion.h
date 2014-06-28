#ifndef RULECOHESION_H
#define RULECOHESION_H

#include "IBoidRule.h"
#include "Float2.h"


class RuleCohesion : public IBoidRule
{
    public:
        RuleCohesion();
        virtual ~RuleCohesion();
        virtual void followRule(Boid &b, Boid *swarm, const int swarmsize);
    protected:
    private:
        Float2 tmpv;
};

#endif // RULECOHESION_H
