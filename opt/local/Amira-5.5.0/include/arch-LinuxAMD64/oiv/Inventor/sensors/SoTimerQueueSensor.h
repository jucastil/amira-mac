/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Paul Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TIMER_QUEUE_SENSOR_
#define  _SO_TIMER_QUEUE_SENSOR_

#include <Inventor/sensors/SoSensor.h>
#include <Inventor/SbTime.h>

/**
 * Abstract base class for sensors dependent on time.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Timer queue sensors are sensors that trigger themselves at specific times. The
 *   timer queue is normally processed as part of a program's main loop when the
 *   program is not busy doing something else. Note that processing the timer queue
 *   is not asynchronous - the program must re-enter its main loop for timers to be
 *   triggered. When the timer queue is processed, all timers scheduled to go off at
 *   or before the current time are triggered once, in order from earliest to latest.
 * 
 * @SEE_ALSO
 *    SoTimerSensor,
 *    SoAlarmSensor,
 *    SoIdleSensor,
 *    SoOneShotSensor,
 *    SoDataSensor
 * 
 * 
 */ 

class INVENTOR_API SoTimerQueueSensor : public SoSensor {

 public:
  /**
   * Constructor.
   */
  SoTimerQueueSensor();
  /**
   * Constructor that takes standard callback function and data.
   */
  SoTimerQueueSensor(SoSensorCB *func, void *data);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoTimerQueueSensor();
#endif // HIDDEN_FROM_DOC

  /**
   * Returns the time at which this sensor is scheduled to be triggered. If the
   * sensor is not scheduled the results are undefined.
   */
  const SbTime &      getTriggerTime() const          { return trigTime; }

  /**
   * Adds this sensor to the timer queue. Subclasses provide methods for setting when
   * the sensor will be triggered.
   */
  virtual void        schedule();
  /**
   * If this sensor is scheduled, removes it from the timer queue so that it will not
   * be triggered.
   */
  virtual void        unschedule();
  /**
   * Returns TRUE if this sensor has been scheduled and is waiting in the timer queue
   * to be triggered.
   */
  virtual SbBool      isScheduled() const;

 protected:
  // Used by subclasses to set the time at which the sensor is to be
  // triggered.
  void                setTriggerTime(const SbTime &time);

  // Triggers the sensor, calling its callback function. This
  // overrides the method in SoSensor because it has to reset the
  // schedule flag before triggering.
  virtual void        trigger();

  SbBool              scheduled;      // Whether sensor is scheduled

 private:
  SbTime              trigTime;       // Time when sensor is to be triggered

  // Returns TRUE if this sensor should precede sensor s in the delay
  // queue: it must have a lower priority number than s.
  virtual SbBool      isBefore(const SoSensor *s) const;
};

#endif  /* _SO_TIMER_SENSOR_ */

