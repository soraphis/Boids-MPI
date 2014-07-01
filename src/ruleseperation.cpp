#include "ruleseperation.h"

//#include "Float2.h"
#include "Boid.h"
#include <stdio.h>

RuleSeperation::RuleSeperation()
{
}

RuleSeperation::~RuleSeperation(){

}

void RuleSeperation::followRule(Boid &b, std::vector<Boid> *swarm){
    /*
    Float2 v;
    for(int i = 0; i < swarmsize; i++){
        if(swarm[i] != b){
            v += swarm[i].getPos();
        }
    }
    v = v * (1.0/(swarmsize-1)) - b.getVel();
    v = v * 0.5 + b.getVel();
    b.setVel(v);
    /*/
    tmpv.setX(0); tmpv.setY(0);
    for ( auto itr = swarm->begin(), end = swarm->end(); itr != end; itr++ ){
    	if( (*itr) != b){
        tmpw.setX(itr->getPosX() - itr->getPosX());
        tmpw.setY(itr->getPosY() - itr->getPosY());
        //tmpw -= Float2(b.getPos().getX(), b.getPos().getY());
        if(tmpw.getLengthSquared() < 16){
            tmpv -= tmpw;
        }
    	}
    }
    b.setVel(b.getVel()+tmpv);
    //*/
}

