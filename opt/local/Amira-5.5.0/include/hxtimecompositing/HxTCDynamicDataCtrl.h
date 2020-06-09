/*
*  File      : HxTCDynamicDataCtrl.h
*  Class     : HxTCDynamicDataCtrl
*  
*  Author(s) : Jerome Lague
*  Date      : 7/25/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXTCDYNAMICDATACTRL_H_
#define _HXTCDYNAMICDATACTRL_H_

#include <qdatetime.h>

#include <hxtime/HxDynamicDataCtrl.h>
#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>

class HXTIMECOMPOSITING_API HxTCDynamicDataCtrl: public HxDynamicDataCtrl {

protected:

	/**
     * Time to control duration of load + compute
	 */
	QTime		m_loadAndComputeTime;

	/**
	 * Translate a physical time to a time step
	 * Returns -1 if no conversion available.
	 * Default implementation returns -1
	 */
	virtual int physicalTimeToTimeStep(float physicalTime);

public :

	HxTCDynamicDataCtrl();
	virtual ~HxTCDynamicDataCtrl();

	/// This is called when a new time is chosen in time step mode.
	virtual void newTimeStep(int timeStep);

	/// Compute method.
	virtual void compute();
};

#endif /* _HXTCDYNAMICDATACTRL_H_ */
