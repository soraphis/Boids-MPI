#include "BoidModel.h"
//#include <mpi/mpi.h>
#include <unistd.h>
#include <mpi.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <vector>
#include "rulecohesion.h"
#include "rulespeedlimit.h"
#include "rulereturnhome.h"
#include "ruleseperation.h"
#include "rulealignment.h"

#include "test.h"

extern field myField;
extern int actionsperminute;
extern int tCount;
extern int tID;

BoidModel::BoidModel() : s_SwarmSize(2)
{
    //swarm = new Boid[s_SwarmSize];
    //home = new Boid[1];
    rules = new IBoidRule*[5];
    rules[0] = new RuleCohesion();
    rules[1] = new RuleSeperation();
    rules[2] = new RuleAlignment();
    rules[3] = new RuleSpeedLimit();
    rules[4] = new RuleReturnHome();
}

BoidModel::BoidModel(int swarmsize){
    s_SwarmSize = swarmsize >= 2 ? swarmsize : 2;
    //swarm = new Boid[s_SwarmSize];
    //home = new Boid[1];

    rules = new IBoidRule*[5];
    rules[0] = new RuleCohesion();
    rules[1] = new RuleSeperation();
    rules[2] = new RuleAlignment();
    rules[3] = new RuleSpeedLimit();
    rules[4] = new RuleReturnHome();
}

BoidModel::~BoidModel(){
//	if(rules != NULL){
//		delete [] rules;
//		rules = NULL;
//	}
//	if(swarm != NULL){
//		delete [] swarm;
//		swarm = NULL;
//	}
//	if(home != NULL){
//			delete [] home;
//			home = NULL;
//	}
}

void BoidModel::print(){
    for(int i = 0; i < s_SwarmSize; i++){
        printf("%d has boid %d on position:\t[% .2f, % .2f]\t→\t[% .2f, % .2f]\n",
               tID, i, swarm[i].getPos().getX(), swarm[i].getPos().getY(),
               swarm[i].getVel().getX(), swarm[i].getVel().getY());
    }
}

void BoidModel::init(){
    srand(time(NULL));

    for(int i = 0; i < s_SwarmSize; i++){
        float *x = new float[2];
        if(tID == 0){
            x[0] = rand() % myField.width;
            x[1] = rand() % myField.height;
        }
        MPI_Bcast(x,2,MPI_FLOAT,0,MPI_COMM_WORLD);
        Boid* b = new Boid(Float2(x[0], x[1]));
        //swarm[i].setPos(x[0], x[1]);
        for(int j = 0; j < 5; j++){
            b->addRule(rules[j]);
        }
        swarm.push_back(*b);
        delete [] x;
    }
    MPI_Barrier(MPI_COMM_WORLD);
}


void BoidModel::update(){

	for(int i = tID; i < ceil((float)s_SwarmSize/(float)tCount); i+=tCount){
        if(i % tCount == tID){ // should never b false
        	if(i < s_SwarmSize) swarm[i].followRules(&swarm);
        }
    }
	// follow rules braucht die alten positionen deshalb seperate schleifen
	for(int i = tID; i < ceil((float)s_SwarmSize/(float)tCount); i+=tCount){
		if(i % tCount == tID){ // should never b false
			swarm[i].updatePosition();
		}
	}

	int t = 0;
	for ( auto itr = swarm.begin(), end = swarm.end(); itr != end; itr++ ){
		float *x = new float[5];
		if(t == tID){
			x[4] = t;
			x[0] = swarm[t].getPos().getX();	x[1] = swarm[t].getPos().getY();
			x[2] = swarm[t].getVel().getX();	x[3] = swarm[t].getVel().getY();
		}
		MPI_Bcast(x, 5, MPI_FLOAT, t, MPI_COMM_WORLD);
		if((int)x[4] != tID){
			swarm[(int)x[4]].setPos(Float2(x[0], x[1]));
			swarm[(int)x[4]].setVel(Float2(x[2], x[3]));
		}
		t = (++t)%tCount; // t = [0 .. tCount-1]
	}

	if(tID == 0){
        actionsperminute++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

void BoidModel::close(){

}
