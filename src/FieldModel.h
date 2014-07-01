/*
 * fieldmodel.h
 *
 *  Created on: 29.06.2014
 *      Author: oliver
 */

#ifndef FIELDMODEL_H_
#define FIELDMODEL_H_

#include "IModel.h"
#include "Boid.h"
#include "IBoidRule.h"

class FieldModel : public IModel{
private:
    int s_SwarmSize;
    //Boid*       home;
    IBoidRule** rules;
public:
	FieldModel();
	FieldModel(int swarmsize);
	virtual ~FieldModel();
	virtual void init();
	virtual void update();
	Boid*		swarm;
};

#endif /* FIELDMODEL_H_ */
