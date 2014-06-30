#include "rulealignment.h"

#include "Boid.h"
#include <stdio.h>
//#include "Float2.h"

RuleAlignment::RuleAlignment()
{

}

RuleAlignment::~RuleAlignment()
{

}

void RuleAlignment::followRule(Boid &b, std::vector<Boid> *swarm){
	tmpv.setX(0); tmpv.setY(0);
    int r = 0;
    for ( auto itr = swarm->begin(), end = swarm->end(); itr != end; itr++ ){
    	if( (*itr) != b){
    		//if( itr->getPos().inRange(b.getPos(), 300) ){
    		if( itr->inRange(&b, 300)){
    			r++;
    			tmpv += itr->getPos();
    		}
    	}
    }
//    for(int i = 0; i < swarmsize; i++){
//        if((*swarm)[i] != b){
//            Float2 e = (*swarm)[i].getPos();// - b.getPos();
//            e -= b.getPos();
//            if( e.getLengthSquared() < 300 ){
//                r++;
//                tmpv += (*swarm)[i].getPos();
//            }
//        }
//    }
    if(r == 0) r = 1;
    tmpv *= (1.0/(r)); tmpv -= b.getPos();
    tmpv *= 0.125; tmpv += b.getVel();
    b.setVel(tmpv);
}
