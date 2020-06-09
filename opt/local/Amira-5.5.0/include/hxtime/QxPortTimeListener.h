/*
*  File      : QxPortListener.h
*  Class     : QxPortListener
*  
*  Author(s) : Jerome Lague
*  Date      : 2/23/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _QXPORTLISTENER_H_
#define _QXPORTLISTENER_H_

#include <qobject.h>
#include <hxtime/HxTimeWinDLLApi.h>

class HxPortTime;
class QxPortNotifier;

class HXTIME_API QxPortTimeListener: public QObject {

	Q_OBJECT

public :

	QxPortTimeListener(HxPortTime &portTime);
	virtual ~QxPortTimeListener();

	virtual void animationStateChanged(const HxPortTime &portTime) = 0;
	virtual void newTimeStep(const HxPortTime &portTime) = 0;
	virtual void forwardFlagChanged(const HxPortTime &portTime) = 0;
	virtual void portBeDeleted(const HxPortTime &portTime, bool ownerTo) = 0;

public slots:

	void valueChanged(unsigned int mask=0xffffffff);
	void toBeDeleted(bool ownerTo);

protected:

	HxPortTime &portTime;
};

#endif /* _QXPORTLISTENER_H_ */
