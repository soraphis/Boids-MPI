#ifndef IBOIDRULE_H
#define IBOIDRULE_H

#include <vector>

class Boid;

class IBoidRule
{
    public:
        virtual ~IBoidRule();
        //virtual void followRule(Boid &b, Boid *swarm, const int swarmsize) = 0;
        virtual void followRule(Boid &b, std::vector<Boid> *swarm) = 0;
    protected:
    private:
};

#endif // IBOIDRULE_H
