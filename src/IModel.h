/*
 * IModel.h
 *
 *  Created on: 29.06.2014
 *      Author: oliver
 */

#ifndef IMODEL_H_
#define IMODEL_H_


class IModel{

public:
	//IModel();
	virtual ~IModel();
	virtual void update() = 0;
	virtual void init() = 0;
};




#endif /* IMODEL_H_ */
