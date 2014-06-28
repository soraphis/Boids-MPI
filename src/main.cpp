#include <stdio.h>
#include <stdlib.h>
//#include <mpi/mpi.h>
#include <mpi.h>

#include "Float2.h"
#include "Boid.h"
#include "IBoidRule.h"
#include "RuleCohesion.h"
#include "boidmodel.h"
//#include "boidview.h"
#include "test.h"
#include <time.h>

using namespace std;
BoidModel* model;
//BoidView* view;
clock_t timer;

field myField = {400, 225};

int tID;
int tCount;

long int actionsperminute = 0;
bool visual = false;

void init(){
    model->init();
//    if(tID == 0 && visual) view->init();
}

void update(){
    model->update();
//    if(tID == 0 && visual) view->update();
}

void close(bool &quit){
//    if(tID == 0 && visual) view->close(quit);
    if(quit){
        model->close();
    }
}

int main(int argc, char** argv)
{
    time_t start, t_init;
    double inittime;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD , &tCount);
    MPI_Comm_rank(MPI_COMM_WORLD, &tID);

    int timetorun = 10;
    int numboids;
    if(tID == 0){
    	printf("Anzahl an Boids: ");
    		scanf("%d", &numboids);
		printf("Wie lange soll gebenchmarkt werden: ");
					scanf("%d", &timetorun);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&numboids, 1, MPI_INT, 0, MPI_COMM_WORLD);
    model = new BoidModel(numboids);
//    if(tID == 0) view = new BoidView(model);
    time(&t_init);


    if(tID == 0){
        printf("processes: %d \n", tCount);
        time(&start);
    }
    init();

    //*
    bool quit = false;
    inittime = difftime(time(NULL), t_init);
    while(! quit){
    //for(int _r = 0; _r < 2; _r++){
        update();
        close(quit);
        int i = quit ? 1 : 0;
        if(tID == 0){
            double sec = difftime( time(NULL), start);
            if( (!visual && sec  >= timetorun) || quit){
                double d = actionsperminute * (60.0 / sec);
                printf("actions: \t\t\t %ld \n", actionsperminute);
                printf("seconds to init: \t\t %.3f \n", inittime);
                printf("seconds in update loop:\t\t %.3f \n", sec);
                printf("actions/min : \t\t\t %.f \n", d);
                i = 1;
            }
        }
        MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if(i == 1) quit = true;

    }
    //model->print();
    printf("%d: quit now\n", tID);
//    delete model;
//    model = NULL;
    //*/
    MPI_Finalize();
    return 0;
}
