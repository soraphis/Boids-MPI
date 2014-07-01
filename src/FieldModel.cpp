/*
 * fieldmodel.cpp
 *
 *  Created on: 29.06.2014
 *      Author: oliver
 */

#include "FieldModel.h"
#include <mpi.h>
#include "Boid.h"
#include "Float2.h"
#include <time.h>
#include <cmath>
#include "rulecohesion.h"
#include "rulespeedlimit.h"
#include "rulereturnhome.h"
#include "ruleseperation.h"
#include "rulealignment.h"
#include "test.h"

extern field myField;
extern int tID, tCount;

FieldModel::FieldModel() : s_SwarmSize(2)
{
    swarm = new Boid[s_SwarmSize];
    //home = new Boid[1];

    rules = new IBoidRule*[5];
    rules[0] = new RuleCohesion();
    rules[1] = new RuleSeperation();
    rules[2] = new RuleAlignment();
    rules[3] = new RuleSpeedLimit();
    rules[4] = new RuleReturnHome();
}

FieldModel::FieldModel(int swarmsize){
	s_SwarmSize = swarmsize >= 2 ? swarmsize : 2;
	swarm = new Boid[s_SwarmSize];
	//	home = new Boid[1];

	rules = new IBoidRule*[5];
	rules[0] = new RuleCohesion();
	rules[1] = new RuleSeperation();
	rules[2] = new RuleAlignment();
	rules[3] = new RuleSpeedLimit();
	rules[4] = new RuleReturnHome();

}

FieldModel::~FieldModel() {
	}

void FieldModel::update(){

}

void FieldModel::init(){

	if(tID == 0){
		printf("%d == %d \n", (long)floorf(sqrtf((float)tCount)), (long)sqrtf((float)tCount));
		if((long)floorf(sqrtf((float)tCount)) != (long)sqrtf((float)tCount)){
			printf("Die Anzahl der Prozesse muss eine Quadratzahl sein\n");
			system("exit");
			return;
		}
	}

	srand(time(NULL));
	for(int i = 0; i < s_SwarmSize; i++){
		float *x = new float[2];
		if(tID == 0){
			x[0] = rand() % myField.width/1 + myField.width/1;
			x[1] = rand() % myField.height/1 + myField.height/1;
		}
		MPI_Bcast(x,2,MPI_FLOAT,0,MPI_COMM_WORLD);

		swarm[i].setPos(x[0], x[1]);
		for(int j = 0; j < 5; j++){
			swarm[i].addRule(rules[j]);
		}
		delete x;
	}
	MPI_Barrier(MPI_COMM_WORLD);
}
