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
            x[0] = rand() % myField.width/1 + myField.width/1;
            x[1] = rand() % myField.height/1 + myField.height/1;
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
    for(int i = 0; i < s_SwarmSize; i++){
        float *x = (float*) malloc(5*sizeof(float)) ;//new float[4];
        if(i % tCount == tID && i < s_SwarmSize){
            swarm[i].updatePosition();
            x[4] = i;
            x[0] = swarm[i].getPos().getX();
            x[1] = swarm[i].getPos().getY();
            x[2] = swarm[i].getVel().getX();
            x[3] = swarm[i].getVel().getY();
            // DEBUG:
            //printf("process %d calculated \t boid %d to \t %.2f, \t%.2f \t with \t %.2f, \t%.2f \tvelocity vector \n", tID, i, x[0], x[1], x[2], x[3]);
        }
        MPI_Bcast(x, 5, MPI_FLOAT, i%tCount, MPI_COMM_WORLD);
        if((int)x[4] % tCount != tID){
            swarm[(int)x[4]].setPos(Float2(x[0], x[1]));
            swarm[(int)x[4]].setVel(Float2(x[2], x[3]));
            // DEBUG:
            //printf("process %d moved \t boid %d to \t %.2f, \t%.2f \t with \t %.2f, \t%.2f \tvelocity vector \n", tID, (int)x[4], x[0], x[1], x[2], x[3]);
        }
        delete [] x;
    }


    if(tID == 0){
        actionsperminute++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
}

void BoidModel::close(){

}
