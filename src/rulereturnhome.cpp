#include "rulereturnhome.h"

#include "Float2.h"
#include "Boid.h"
#include "test.h"
#include <assert.h>
#include <cmath>
#include <stdio.h>

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

void RuleReturnHome::followRule(Boid &b, std::vector<Boid> *swarm){
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

//	tmpv.setX(b.getPosX()+myField.width);
//	tmpv.setY(b.getPosY()+myField.height);
//
//    //Float2 v(b.getPos().getX()+myField.width, b.getPos().getY()+myField.height);
//    tmpv.setX((int)tmpv.getX()%(int)(myField.width));
//    tmpv.setY((int)tmpv.getY()%(int)(myField.height));
//    assert(tmpv.getX() >= 0);assert(tmpv.getX() < myField.width);
//    assert(tmpv.getY() >= 0);assert(tmpv.getY() < myField.height);
//    b.setPos(tmpv);
    //printf("solved rule return home with (%.2f, %.2f)\n", tmpv.getX(), tmpv.getY());

//    tmpv.setX(b.getPosX()-(int)b.getPosX());
//    tmpv.setY(b.getPosY()-(int)b.getPosY());

    tmpv.setX(((int)round(b.getPosX()) + myField.width) %myField.width );
    tmpv.setY(((int)round(b.getPosY()) + myField.height)%myField.height );

//    if(tmpv.getX() < 0) printf("%2.f, %d → %.2f", b.getPosX(), sizeof(b.getPosX()), tmpv.getX());

//    assert(tmpv.getX() >= 0);assert(tmpv.getX() < myField.width);
//	assert(tmpv.getY() >= 0);assert(tmpv.getY() < myField.height);

    b.setPos(tmpv);

    assert(b.getPosX() >= 0);assert(b.getPosX() < myField.width);
	assert(b.getPosY() >= 0);assert(b.getPosY() < myField.height);

}
