/*
*  File      : HxTimeCompositingController.h
*  Class     : HxTimeCompositingController
*  
*  Author(s) : Jerome Lague
*  Date      : 7/11/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXTIMECOMPOSITINGCONTROLLER_H_
#define _HXTIMECOMPOSITINGCONTROLLER_H_

#include <mclib/McHandle.h>

#include <hxcore/HxVRSessionController.h>
#include <hxtime/HxPortTime.h>
#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>
#include <hxtimecompositing/SoVRTimeComposer.h>
#include <hxtimecompositing/HxTimeCompositingPolicy.h>
#include <hxtimecompositing/HxTimeCompositingPolicyFactory.h>

class HxTCDynamicDataCtrl;

class HXTIMECOMPOSITING_API HxTimeCompositingController: public HxVRSessionController
{
	Q_OBJECT

public:

	HxTimeCompositingController(SoVRTimeComposer *timeComposer);
	virtual ~HxTimeCompositingController();

	virtual bool isMaster() const;
	virtual bool isSlave() const;

	virtual void render();

	virtual bool handleDelayedMessage(const McString& msg);
	virtual void initConnection(HxRemoteSessionController* ctrl, int remoteID) {}

	int getSlaveID() const;
	int getFrameSlaveID() const;

	void resetMaster();

	HxTimeCompositingPolicy * getPolicy() const { return m_policy; }

	//
	bool isCurrent(HxTCDynamicDataCtrl *control) const;

SoINTERNAL public:

	/** Returns the current time step.
	* If offsetIt is true, the return time step is relative to
	* the time step loaded when animation starts.
	* Return value can be negative.
	*/
	int getCurrentTimeStep(bool offsetIt = true) const;

	/**
	 * Slave side method
	 */
	// Called by HxTCDynamicDataCtrl::compute()
	int getNextTimeStep(const HxPortTime &portTime);
	int getNextTimeStep(const HxPortTime &portTime, int timeStep);
	int getNextTimeStep(const HxPortTime &portTime, int timeStep, int &forward);
	int getNextTimeStep(const HxPortTime &portTime, int timeStep, int &forward, bool &frameMayBeRequestTwoTimes);

	int getSlaveID(int timeStep);

	/**
	 *
	 */
	void setLoadedTimeStep(int timeStep, int elapsedTime = -1);
	bool loadedTimeStepFrameRequested() const;

protected slots:

	void animationStateChanged(const HxPortTime &portTime);
	void newTimeStep(const HxPortTime &portTime);
	//void forwardFlagChanged(const HxPortTime &portTime);
	//void portBeDeleted(const HxPortTime &portTime, bool ownerTo);

protected:

	virtual Q3Socket* mainSocket() { return NULL; }

	// Time step loaded before animation starts
	int	 m_timeStepOffset;
	bool m_grabbOffset;

	// Current time step
	int	 m_currentTimeStep;

	// Slave id responsible of current time step
	int	 m_frameSlaveID;

	// Current loaded time step by slave
	int		m_loadedTimeStep;

	// Flag to indicate if the frame
	// of loaded time step has already 
	// been requested by the master
	int		m_loadedTimeStepFrameRequestCount;

	// 
	bool	m_frameMayBeRequestTwoTimes;

	//
	bool	m_loadForced;

	// Time to load and compute loaded time step
	int		m_loadedTimeStepComputeTime;

	//
	const HxPortTime		*m_portTime;

	//
	HxTimeCompositingPolicy *m_policy;

	//
	McHandle<SoVRTimeComposer> m_timeComposer;
};

#endif // _HXTIMECOMPOSITINGCONTROLLER_H_
