/*
*  File      : HxTimeCompositingPolicy.h
*  Class     : HxTimeCompositingPolicy
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


#ifndef _HXTIMECOMPOSITINGPOLICY_H_
#define _HXTIMECOMPOSITINGPOLICY_H_

#include <hxtime/HxPortTime.h>
#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>

class HXTIMECOMPOSITING_API HxTimeCompositingPolicy {

protected :

	HxTimeCompositingPolicy();

public :

	virtual ~HxTimeCompositingPolicy();

	/**
	* Master side method
	* Returns id of slave responsible of given time step
	*/
	virtual int getSlaveID(int timeStep) = 0;

	/**
	* Slave side method
	* Returns the time increment
	*/
	virtual int getIncrement(const HxPortTime &portTime) = 0;

	/** 
	* Slave side method
	* When a new time step occurs, tells the slave which time 
	* step must be currently loaded. Returns the current time step
	* if no work should be done
	*/
	virtual int translateTimeStep(int slaveID, int timeStep) = 0;
};

#endif /* _HXTIMECOMPOSITINGPOLICY_H_ */
