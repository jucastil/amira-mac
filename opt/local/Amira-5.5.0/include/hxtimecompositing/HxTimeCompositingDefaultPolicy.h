/*
*  File      : HxTimeCompositingDefaultPolicy.h
*  Class     : HxTimeCompositingDefaultPolicy
*  
*  Author(s) : Jerome Lague
*  Date      : 7/20/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXTIMECOMPOSITINGDEFAULTPOLICY_H_
#define _HXTIMECOMPOSITINGDEFAULTPOLICY_H_

#include <hxtimecompositing/HxTimeCompositingPolicy.h>

class HXTIMECOMPOSITING_API HxTimeCompositingDefaultPolicy: public HxTimeCompositingPolicy {

private :

	int m_numSlaves;

protected :

	int getNumSlaves();

public :

	HxTimeCompositingDefaultPolicy();
	virtual ~HxTimeCompositingDefaultPolicy();

	/**
	* Master side method
	* Returns id of slave responsible of given time step
	*/
	virtual int getSlaveID(int timeStep);

	/**
	* Slave side method
	* Returns the time increment
	*/
	virtual int getIncrement(const HxPortTime &portTime);

	/** 
	* Slave side method
	* When a new time step occurs, tells the slave which time 
	* step must be currently loaded. Returns the current time step
	* if no work should be done
	*/
	virtual int translateTimeStep(int slaveID, int timeStep);
};

#endif /* _HXTIMECOMPOSITINGDEFAULTPOLICY_H_ */
