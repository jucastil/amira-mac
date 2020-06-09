/*
*  File      : QxTCSessionControllerNotifier.h
*  Class     : QxTCSessionControllerNotifier
*  
*  Author(s) : Jerome Lague
*  Date      : 7/12/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _QxTCSessionControllerNotifier_H_
#define _QxTCSessionControllerNotifier_H_

#include <hxtime/QxPortTimeListener.h>
#include <hxtimecompositing/HxTimeCompositingWinDLLApi.h>

class HxTimeCompositingController;

class HXTIMECOMPOSITING_API QxTCSessionControllerNotifier: public QxPortTimeListener {

	Q_OBJECT

public :

	QxTCSessionControllerNotifier(HxPortTime &portTime);
	virtual ~QxTCSessionControllerNotifier();

	virtual void animationStateChanged(const HxPortTime &portTime);
	virtual void newTimeStep(const HxPortTime &portTime);
	virtual void forwardFlagChanged(const HxPortTime &portTime) {};
	virtual void portBeDeleted(const HxPortTime &portTime, bool ownerTo);

signals:

	virtual void sig_animationStateChanged(const HxPortTime &portTime);
	virtual void sig_newTimeStep(const HxPortTime &portTime);
	virtual void sig_forwardFlagChanged(const HxPortTime &portTime);
	virtual void sig_portBeDeleted(const HxPortTime &portTime, bool ownerTo);

};

#endif /* _QxTCSessionControllerNotifier_H_ */
