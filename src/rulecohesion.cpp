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
    	if( (*itr) != b){
    		if( itr->inRange(&b, 100)){
    			r++;
    			tmpv += itr->getVel();
    		}
    	}
    }
//    for(int i = 0; i < swarmsize; i++){
//        if((*swarm)[i] != b){
//            Float2 e = (*swarm)[i].getPos();
//            e -= b.getPos();
//            if( e.getLengthSquared() < 100 ){
//                r++;
//                tmpv += (*swarm)[i].getVel();
//            }else{
//
//            }
//        }
//    }
    if(r == 0) return;
    tmpv = tmpv * (1.0/(r)) - b.getVel();
    tmpv = tmpv * 0.5 + b.getVel();
    b.setVel(tmpv);

}
