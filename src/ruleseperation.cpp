#include "ruleseperation.h"

//#include "Float2.h"
#include "Boid.h"


RuleSeperation::RuleSeperation()
{
}

RuleSeperation::~RuleSeperation(){

}

void RuleSeperation::followRule(Boid &b, Boid *swarm, const int swarmsize){
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

    for(int i = 0; i < swarmsize; i++){
        if(swarm[i] == b) continue;
        tmpw.setX(swarm[i].getPosX() - b.getPosX());
        tmpw.setY(swarm[i].getPosY() - b.getPosY());
        //tmpw -= Float2(b.getPos().getX(), b.getPos().getY());
        if(tmpw.getLengthSquared() < 4){
            tmpv -= tmpw;
        }
    }
    b.setVel(b.getVel()+tmpv);
    //*/
}

