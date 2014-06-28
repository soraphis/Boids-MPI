#ifndef BOIDMODEL_H
#define BOIDMODEL_H

#include "Boid.h"

class BoidModel
{
private:
    int s_SwarmSize;
    Boid*       home;
    IBoidRule** rules;
public:
    BoidModel();
    BoidModel(int swarmsize);
    ~BoidModel();
    Boid*       swarm;

    void print();
    void init();
    void update();
    void close();
    int getSwarmSize(){ return s_SwarmSize; }
};

#endif // BOIDMODEL_H
