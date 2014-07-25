#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include "Float2.h"
#include "IModel.h"
#include "BoidModel.h"
#include "FieldModel.h"
#include "boidview.h"
#include "test.h"

BoidView* view;

//* either
	FieldModel* model;
/*/// or
	BoidModel* model;
//*/

field myField = {250, 150};

int tID;
int tCount;
long int actionsperminute = 0;
bool visual = true;

void output_data(double* sec_init, double* sec_output);
void input_data(int* numboids, int* timetorun);

void init(){
    model->init();
    if(visual) view->init();
}

void update(){
    model->update();
    if(visual) view->update();
}

void close(bool &quit){
    if(visual) view->close(quit);
//    if(quit){
//        model->close();
//    }
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

    input_data(&numboids, &timetorun);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&numboids, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //* either
    	model = new FieldModel(numboids);
    /*/// or
    	model = new BoidModel(numboids);
    //*/

//    if(tID == 0)
	view = new BoidView(model);

    time(&t_init);


    if(tID == 0){
        printf("processes: %d \n", tCount);
        time(&start);
    }
    init();

    bool quit = false;
    inittime = difftime(time(NULL), t_init);
    while(! quit){
        update();
        close(quit);
        int i = quit ? 1 : 0;
        if(tID == 0){
            double sec = difftime( time(NULL), start);
            if( (!visual && sec  >= timetorun) || quit){
                // * snip *
            	output_data(&sec, &inittime);
                i = 1;
            }
        }
        MPI_Bcast(&i, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if(i == 1) quit = true;
    }
//    model->print();		// DEBUG
    printf("%d: quit now\n", tID);
//  delete model; model = NULL; → throws segmentation fault, but does not matter cause program ends now

    MPI_Finalize();
    return 0;
}

void input_data(int* numboids, int* timetorun){
	if(tID == 0){
	printf("Anzahl an Boids: ");
		scanf("%d", numboids);
	printf("Wie lange soll gebenchmarkt werden: ");
		scanf("%d", timetorun);
	}
}

void output_data(double* sec_update, double* sec_init){
	double d = actionsperminute * (60.0 / *sec_update);
	printf("actions: \t\t\t %ld \n", actionsperminute);
	printf("seconds to init: \t\t %.3f \n", *sec_init);
	printf("seconds in update loop:\t\t %.3f \n", *sec_update);
	printf("actions/min : \t\t\t %.f \n", d);
}
