/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SENSOR_MANAGER_
#define  _SO_SENSOR_MANAGER_

#include <Inventor/misc/SoBasic.h>
#include <Inventor/SbTime.h>

class SoSensor;
class SoDelayQueueSensor;
class SoTimerQueueSensor;
class SoTimerSensor;
class SoAlarmSensor;
class SoSensorManagerThread;
class SbDict;

SoINTERNAL class INVENTOR_API SoSensorManager {

 public:
  // Constructor, destructor
  SoSensorManager();
  virtual ~SoSensorManager();

  // Set up a function to call when either queue has a sensor added
  // or removed
  virtual void                setChangedCallback(void (*func)(void *), void *data);

  // Insert/remove an delay or timer event into/from the appropriate queue
  virtual void                insertDelaySensor(SoDelayQueueSensor *s);
  virtual void                insertTimerSensor(SoTimerQueueSensor *s);
  virtual void                removeDelaySensor(SoDelayQueueSensor *s);
  virtual void                removeTimerSensor(SoTimerQueueSensor *s);

  // Timers are all rescheduled at the same time, after they have
  // been triggered.  This avoids timer queue saturation.
  virtual void                rescheduleTimer(SoTimerSensor *s);
  virtual void                removeRescheduledTimer(SoTimerQueueSensor *s);

  // Set/get delay queue sensors (OneShot, Node, Path, etc)
  // timeout value.  Delay sensor go off whenever there is idle time
  // or when the timeout expires.
  virtual void                setDelaySensorTimeout(const SbTime &t);
  virtual const SbTime        &getDelaySensorTimeout();

  // Process all sensors in the delay queue.  The isIdle flag should
  // be TRUE if the delay queue is being processed because there is
  // idle time; it should be false if it is being processed because
  // the delay sensor timeout has expired.
  virtual void                processDelayQueue(SbBool isIdle);

  // Process all immediate (priority 0) sensors in the delay queue
  virtual void                processImmediateQueue();

  // Process appropriate sensors in the timer queue based on current time
  virtual void                processTimerQueue();

  // Returns TRUE if there is at least one sensor in the delay queue
  virtual SbBool              isDelaySensorPending();

  // Returns TRUE if there is at least one sensor in the timer
  // queue. If there is one, the time of the first sensor is placed
  // in tm.
  virtual SbBool              isTimerSensorPending(SbTime &tm);

  // Just like UNIX select() call, but checks sensor queues while
  // waiting for events.
  virtual int                 doSelect(int nfds, fd_set *readfds, fd_set *writefds,
                                       fd_set *exceptfds,
                                       struct timeval *userTimeOut);

  // 
  static void init();
  static void finish();

  // return true if IV_DEBUG_SENSORS was set at startup
  static bool isIvDebugSensorsSet()
  {return s_ivDebugSensors;}

#ifdef _WIN32
 protected:
#else
 private:
#endif
  SoSensor            *delayQueue;    // Head of delay sensor queue
  SoSensor            *timerQueue;    // Head of timer sensor queue
  SoSensor            *rescheduleQueue;// Timers ready to be rescheduled

  // These are used to process the delay queue every once in a
  // while:
  SbTime              delayQTimeout;
  SoAlarmSensor       *delayQTimeoutSensor;
  static void         delayQTimeoutCB(void *, SoSensor *);

  // Non-zero when processing a queue.  The changedCallback will not
  // be called when we are in the middle of processing a queue, and
  // the immediate queue uses this to avoid recursion.  Because a
  // timer sensor might decide to process the delay queue in its
  // trigger method, this is an integer instead of a simple Boolean.
  int                 processingQueue;

  uint32_t            delayQCount;    // Avoids loops processing delay queue

  // Insert/remove an entry into/from the queue with the given head
  void                insert(SoSensor *s, SoSensor *&head);
  void                remove(SoSensor *s, SoSensor *&head);

  // Callback which is called whenever a sensor is inserted or removed
  void                (*changedFunc)(void *);
  void                *changedFuncData;

  // Calls the changed callback, if there is one
  void                notifyChanged();

private:
#ifdef _WIN32
  // IMPORTANT: see header doc of SoInventorBase::isMultiThreadApplication.
  // Note to implementer : to manage isMultiThreadApplication mode without breaking
  // standard multiThread mode we must alway use m_pThreadSensorMgr
  // constructor and destructor or init/finish will do the job to correctly init it.
  SoSensorManagerThread* m_pThreadSensorMgr;
  static SoSensorManagerThread* s_pThreadSensorMgr;

#endif
  static bool s_ivDebugSensors;

};

#endif /* _SO_SENSOR_MANAGER_ */

