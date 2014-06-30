#ifndef BOIDMODEL_H
#define BOIDMODEL_H

#include "Boid.h"
#include "IModel.h"
#include <vector>

class BoidModel : public IModel
{
private:
    int s_SwarmSize;
    //Boid*       home;
    IBoidRule** rules;
public:
    BoidModel();
    BoidModel(int swarmsize);
    virtual ~BoidModel();
    //Boid*       swarm;
    std::vector<Boid> swarm;

    void print();
    virtual void init();
    virtual void update();
    void close();
    int getSwarmSize(){ return s_SwarmSize; }
};

#endif // BOIDMODEL_H
