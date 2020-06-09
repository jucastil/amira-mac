/*
*  File      : HxPortTimeCallback.h
*  Class     : HxPortTimeCallback
*  
*  Author(s) : Jerome Lague
*  Date      : 11/7/2007
* 
*  --------------------------------------------------------------------------
*  (c) Copyright 2007 VISUALIZATION SCIENCES GROUP S.A.S., all right reserved
*  --------------------------------------------------------------------------
* 
*  Description :
* 
* 
*/


#ifndef _HXPORTTIMECALLBACK_H_
#define _HXPORTTIMECALLBACK_H_

#ifdef None
#undef None
#endif

#include <mclib/McString.h>
#include <hxtime/QxPortTimeListener.h>

class HxPortTimeCallback: public QxPortTimeListener {
  Q_OBJECT

public :

  /// EvenType constants
  enum EventType {
    None = 1,

    NewTimeStep = 2,
    AnimationStateChanged = 4,
    ForwardFlagChanged = 8,
  };

  /// Returns the EvenType value according to its name
  static int getEventTypeByName(const McString & name);

  HxPortTimeCallback(HxPortTime &portTime);
  virtual ~HxPortTimeCallback();

  virtual void animationStateChanged(const HxPortTime &portTime);
  virtual void newTimeStep(const HxPortTime &portTime);
  virtual void forwardFlagChanged(const HxPortTime &portTime);
  virtual void portBeDeleted(const HxPortTime &portTime, bool ownerTo) {};

  void unsetCallback();
  void setCallback(const McString &callbackProc, int eventType);

protected:

  McString  timeCallbackProc;
  int       timeCallbackEventType;
};

#endif /* _HXPORTTIMECALLBACK_H_ */
