/*
*  File      : QxPortTimeNotifier.h
*  Class     : QxPortTimeNotifier
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


#ifndef _QXPORTTIMENOTIFIER_H_
#define _QXPORTTIMENOTIFIER_H_

#include <qobject.h>
#include <hxtime/HxTimeWinDLLApi.h>

class HxPort;

class HXTIME_API QxPortTimeNotifier: public QObject {

	Q_OBJECT

public :

	QxPortTimeNotifier(HxPort* owner);
	virtual ~QxPortTimeNotifier();

	HxPort *getOwner() const { return theOwner; }

protected:

	HxPort		*theOwner;

signals:

	void play(int forward);
	void stop();
};

#endif /* _QXPORTTIMENOTIFIER_H_ */
