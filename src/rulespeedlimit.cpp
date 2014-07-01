#include "rulespeedlimit.h"
#include "Boid.h"
#include <cmath>
#include <stdio.h>

RuleSpeedLimit::RuleSpeedLimit()
{

}

RuleSpeedLimit::~RuleSpeedLimit(){

}

//void RuleSpeedLimit::followRule(Boid &b){
void RuleSpeedLimit::followRule(Boid &b, std::vector<Boid> *swarm){
	float r = b.getVel().getLengthSquared();
    if(r == 0){
        return;
    }
    r = sqrt(r);
    b.setVel(b.getVel() * (3.0/r));
}

