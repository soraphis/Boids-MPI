#include "rulereturnhome.h"

#include "Float2.h"
#include "Boid.h"
#include "test.h"

extern field myField;

RuleReturnHome::RuleReturnHome(){
    this->homes = new Boid[1];
    this->homecount = 1;
}

RuleReturnHome::RuleReturnHome(Boid* homes, int homecount)
{
    this->homes = homes;
    this->homecount = homecount;
}

RuleReturnHome::~RuleReturnHome(){
//    if(homes != NULL){
//    	delete [] homes;
//    	homes = NULL;
//    }
}

void RuleReturnHome::followRule(Boid &b, Boid *swarm, const int swarmsize){
//    Float2 v;
//    for(int i = 0; i < homecount; i ++){
//        v = b.getPos() - homes[i].getPos();
//
//
//    }
//    v *= (1/homecount); // average position of all homes
//    v -= b.getPos();    // vector from boid to this position
//
//    b.setVel(b.getVel()+v*(1.0/32.0));

	tmpv.setX(b.getPosX()+myField.width);
	tmpv.setY(b.getPosY()+myField.height);

    //Float2 v(b.getPos().getX()+myField.width, b.getPos().getY()+myField.height);
    tmpv.setX((int)tmpv.getX()%(int)(myField.width));
    tmpv.setY((int)tmpv.getY()%(int)(myField.height));
    b.setPos(tmpv);
}
