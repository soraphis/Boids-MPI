#include "rulecohesion.h"

//#include "Float2.h"
#include "Boid.h"
#include <iostream>


RuleCohesion::RuleCohesion()
{
    //ctor
}

RuleCohesion::~RuleCohesion()
{
    //dtor
}

void RuleCohesion::followRule(Boid &b, std::vector<Boid> *swarm){
	tmpv.setX(0); tmpv.setY(0);
	    int r = 0;
	    for ( auto itr = swarm->begin(), end = swarm->end(); itr != end; itr++ ){
	    	tmpv2.setX(0); tmpv2.setY(0);
	    	if( (*itr) != b){
	    		//*
	    		if( itr->inRange(&b, 1000)){
	    			r++;
	    			tmpv += itr->getPos();
	    		}
	    		/*/
	    		tmpv2 = b.getPos();
	    		tmpv2 -= itr->getPos();
	    		r++;
	    		tmpv += itr->getPos() * (100/(tmpv2.getLengthSquared()));
	    		//*/
	    	}
	    }
	    if(r == 0) return;
	    tmpv *= (1.0/(r)); tmpv -= b.getPos();
	    tmpv *= 0.125; tmpv += b.getVel();
	    b.setVel(tmpv);

}
