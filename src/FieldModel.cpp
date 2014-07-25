/*
 * fieldmodel.cpp
 *
 *  Created on: 29.06.2014
 *      Author: oliver
 */

#include "FieldModel.h"
#include "Boid.h"
#include "Float2.h"
#include <mpi.h>
#include <time.h>
#include <cmath>
//#include <stdio.h>
#include <unistd.h> // sleep
#include "rulecohesion.h"
#include "rulespeedlimit.h"
#include "rulereturnhome.h"
#include "ruleseperation.h"
#include "rulealignment.h"
#include "test.h"
#include <assert.h>


extern field myField;
extern int tID, tCount;
extern int actionsperminute;
int dimX, dimY;

FieldModel::FieldModel() : s_SwarmSize(2)
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

FieldModel::FieldModel(int swarmsize){
	s_SwarmSize = swarmsize >= 2 ? swarmsize : 2;
	//swarm = new Boid[s_SwarmSize];
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

/*
 * splits the field correct in a*b parts with minimal circumference
 * a will always be <= b, so a should be Y if your field tends to be landscape format
 */
bool getFieldSplit(int Area, int &a, int &b){
	int x = (int) sqrtf(Area);
	for(; Area % x != 0; --x){}
	a = x;
	b = Area/a;
	if(Area > 2 && a == 1 && b == Area) return false;
	return true;
}

int AreaOfPoint(float x, float y){
	int _t1 = (int)(dimX*(float)x/(float)myField.width );
	int _t2 = (int)(dimY*(float)y/(float)myField.height );
	int t = (_t1 + _t2 * dimX);
	if(t < 0) printf("%d ← %.2f, %.2f", t, x, y),
	assert(t >= 0); assert(t < tCount);
	return t;
}

void FieldModel::init(){
	//int dimX, dimY;
	if(! getFieldSplit(tCount, dimY, dimX) ){
		printf("The Area of %d, was split in %d and %d", tCount, dimY, dimX);
		printf("It appears that the split was not optimal, maybe the number of processes is a prime");
		throw 1;
	}
	//tDim = (int)floorf(sqrtf((float)tCount));

	srand(time(NULL));
	for(int i = 0; i < s_SwarmSize; i++){
		int *x = new int[3];
		if(tID == 0){
			x[1] = rand() % myField.width;
			x[2] = rand() % myField.height;

			int t = AreaOfPoint(x[1], x[2]);
			x[0] = t; //sende boid zu task t

		}
		MPI_Bcast(x,3,MPI_FLOAT,0,MPI_COMM_WORLD);
		if(tID == x[0]){ // task t empfängt boid
			Boid* b = new Boid(Float2(x[1], x[2]));
			for(int j = 0; j < 5; j++){
				b->addRule(rules[j]);
			}
			swarm.push_back(*b);

		}
		delete [] x;
	}
	MPI_Barrier(MPI_COMM_WORLD);
//	printf("task %d hat %d Boids\n", tID, (int)swarm.size());
}


void FieldModel::update(){
	MPI_Barrier(MPI_COMM_WORLD);
	std::vector<std::pair<Boid, int>> out;
	int * outbox = new int[tCount]; // how many letters to house x
	for(int i = 0; i < tCount; ++i) outbox[i] = 0;
	int * inbox = new int[tCount];

	printf("task %d hat %d Boids\n", tID, (int)swarm.size());

	for (auto itr = swarm.begin(), end = swarm.end(); itr != end; itr++){
		itr->updatePosition();
	}
	for (auto itr = swarm.begin(), end = swarm.end(); itr != end; itr++)	itr->followRules(&swarm);
	for (auto itr = swarm.begin(), end = swarm.end(); itr != end; itr++){

		if(itr->getPosX() < 0 || itr->getPosX() >= myField.width ) printf("%.2f, %.2f", itr->getPosX(), itr->getVelX());

		assert((int)itr->getPosX() >= 0); assert((int)itr->getPosX() < myField.width);
		assert((int)itr->getPosY() >= 0); assert((int)itr->getPosY() < myField.height);

		int t = AreaOfPoint((float)itr->getPosX(), (float)itr->getPosY());
		if( t != tID && t >= 0 && t < tCount ){
			out.push_back({*itr, t});
			itr = swarm.erase(itr);
			outbox[t]++;
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	for(int i = 0; i < tCount; ++i){// each prozess asks every other process how many letters he'll receive
		MPI_Gather(&(outbox[i]), 1, MPI_INT, inbox, 1, MPI_INT, i, MPI_COMM_WORLD);
	}

//	printf("%d: [%d, %d, %d, %d] - %d \n", tID, inbox[0], inbox[1], inbox[2], inbox[3], (int)out.size());
	int inboxsize = 0;
	int * displs = new int[tCount];
	displs[0] = 0;
	for(int i = 0; i < tCount; i++){
		inbox[i] *= 4;
		inboxsize += inbox[i];
		if(i < tCount -1) displs[i+1] = inbox[i];
	}

	///----------------
	//printf("write letters \n");
	float ** y = new float*[tCount];
	for(int r = 0; r < tCount; r++){
		if(tID == r){
			y[r] = new float[4];
		}else{
			y[r] = new float[4*(outbox[r]+1)];

			int i = 0;
			for ( auto itr = out.begin(), end = out.end(); itr != end; itr++ ){
				if(itr->second != r){
					//itr++;
					continue;
				}
				y[r][0 + i*4] = itr->first.getPosX();
				y[r][1 + i*4] = itr->first.getPosY();
				y[r][2 + i*4] = itr->first.getVelX();
				y[r][3 + i*4] = itr->first.getVelY();
				i++;
				//itr = out.erase(itr);
			}
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	for(int r = 0; r < tCount; r++){
		float * x = NULL;
		if(tID == r) x = new float[std::max(inboxsize, 1)];
		assert(outbox[r] >= 0);
		assert(inboxsize >= 0);
		MPI_Gatherv(y[r], 4*outbox[r], MPI_FLOAT, x, inbox, displs, MPI_FLOAT, r, MPI_COMM_WORLD);
		//MPI_Gatherv(void*, int, MPI_Datatype, void*, int, int*, MPI_Datatype, int, MPI_Comm)
		if(tID != r) continue;
		for(int i = 0; i < inboxsize*0.25; i++){
			Boid * b = new Boid(Float2(x[0+i*4],x[1+i*4]));
			b->setVel(x[2+i*4],x[3+i*4]);
			assert(b->getPosX() >= 0); assert(b->getPosX() < myField.width);
			assert(b->getPosY() >= 0); assert(b->getPosY() < myField.height);
			for(int j = 0; j < 5; j++){
				b->addRule(rules[j]);
			}
			swarm.push_back(*b);
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	///----------------
/*
	for(int sender = 0; sender < tCount; ++sender){
		for(int recvr = 0; recvr < tCount; ++recvr){
			if(sender == recvr) continue;
			else if(tID == sender){
				printf("%d sends %d an letter with %d boids \n", tID, recvr, outbox[recvr]);
				float * x = new float[4*(outbox[recvr]+1)];

				int i = 0;
				for ( auto itr = out.begin(), end = out.end(); itr != end; itr++ ){
					if(itr->second != recvr) continue;
					x[0 + i*4] = itr->first.getPosX();
					x[1 + i*4] = itr->first.getPosY();
					x[2 + i*4] = itr->first.getVelX();
					x[3 + i*4] = itr->first.getVelY();
					i++;
					out.erase(itr);
				}
				x[0 + i*4] = 0;
				x[1 + i*4] = 0;
				x[2 + i*4] = 0;
				x[3 + i*4] = 0;
//				for(unsigned int i = 0; i < out.size(); ++i){
//					if(out[i].second != recvr) continue;
//
//					x[0 + i*4] = out[i].first.getPosX();
//					x[1 + i*4] = out[i].first.getPosY();
//					x[2 + i*4] = out[i].first.getVelX();
//					x[3 + i*4] = out[i].first.getVelY();
//
//				}
				MPI_Send(x, 4*outbox[recvr], MPI_FLOAT, recvr, sender, MPI_COMM_WORLD);
				printf("letter is out\n");
			}else if(tID == recvr){
				float * x = new float[4*(inbox[sender]+1)];
				MPI_Recv(x, 4*(inbox[sender]+1), MPI_FLOAT, sender, sender, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf("%d received an letter from %d with %d boids \n", tID, sender, inbox[sender]);
				for(int i = 0; i < (inbox[sender]-1); ++i){
					Boid b(Float2(x[0+i*4],x[1+i*4]));
					b.setVel(x[2+i*4],x[3+i*4]);
					swarm.push_back(b);
				}
			}
		}
	}
*/
	/*
	MPI_Barrier(MPI_COMM_WORLD);
	if(tID == 0) printf("--4--");
	// pocess tID sends his letters ...
	float * x = new float[4];
	for ( auto itr = out.begin(), end = out.end(); itr != end; itr++ ){
		x[0] = itr->first.getPosX();
		x[1] = itr->first.getPosY();
		x[2] = itr->first.getVelX();
		x[3] = itr->first.getVelY();

		//MPI_Status myStatus;
		//MPI_Request myRequest;
		printf("process %d is going to send a letter to %d ... ", tID, itr->second);
		MPI_Send(x, 4, MPI_FLOAT, tID, itr->second, MPI_COMM_WORLD);
		//MPI_Isend(x, 4, MPI_FLOAT, tID, itr->second, MPI_COMM_WORLD, &myRequest);
		//MPI_Wait(&myRequest, &myStatus);
		printf("... process %d send a letter to %d \n", tID, itr->second);

	}
	//MPI_Barrier(MPI_COMM_WORLD);
	if(tID == 0) printf("--5--");
	// and receives letters from other processes
	for(int r = 0; r < tCount; ++r){
		if(r == tID) continue;
		for(int i = 0; i < inbox[r]; ++i){
			MPI_Status myStatus;
			MPI_Request myRequest;
			printf("process %d waits for a letter letter from %d \n", tID, r);
			MPI_Irecv(x, 4, MPI_FLOAT, r, 0, MPI_COMM_WORLD, &myRequest);
			MPI_Wait(&myRequest, &myStatus);
			Boid b(Float2(x[0],x[1]));
			b.setVel(x[2],x[3]);
			swarm.push_back(b);
			printf("process %d got a letter from %d \n", tID, r);
		}
	}
	delete [] x;
	*/

	//printf("task %d hat %d Boids\n", tID, (int)swarm.size());
	//MPI_Barrier(MPI_COMM_WORLD);
	//sleep(1);
	actionsperminute++;

}
