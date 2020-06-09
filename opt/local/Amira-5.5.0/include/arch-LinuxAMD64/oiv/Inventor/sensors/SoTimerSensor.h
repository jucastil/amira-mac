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


#ifndef  _SO_TIMER_SENSOR_
#define  _SO_TIMER_SENSOR_

#include <Inventor/sensors/SoTimerQueueSensor.h>

/**
 * Sensor that triggers \oivnetdoc delegate \else callback \endoivnetdoc repeatedly at regular intervals.
 *
 * @ingroup sensors
 *
 * @DESCRIPTION
 *   Timer sensors trigger their \oivnetdoc delegate \else callback \endoivnetdoc function at regular intervals. For example,
 *   a timer might be set up to call its \oivnetdoc delegate \else callback \endoivnetdoc function every second on the second
 *   by setting the base time to SbTime@B (0.0) @b and the interval to
 *   SbTime@B (1.0) @b. Timers are guaranteed to be triggered only once when the
 *   timer queue is processed, so if the application only processes the timer queue
 *   once every 5 seconds (because it is busy doing something else) the once-a-second
 *   sensor's \oivnetdoc delegate \else callback \endoivnetdoc will be called only once every 5 seconds.
 *
 *   Note also that SoTimers always schedule themselves to be triggered the next even
 *   multiple of the interval time after the base time; so, for example, if the
 *   once-a-second sensor is triggered at time 2.9 (because the application way busy
 *   doing something at time 2.0 and didn't get around to processing the sensor queue
 *   for a while) it will reschedule itself to go off at time 3.0, not at time 3.9.
 *   If the base time was never set, the sensor would be scheduled for time 3.9.
 *
 * @SEE_ALSO
 *    SoOneShotSensor,
 *    SoAlarmSensor,
 *    SoTimerQueueSensor,
 *    SbTime
 *
 *
 */

class INVENTOR_API SoTimerSensor : public SoTimerQueueSensor {

 public:
  /**
   * Default constructor.
   */
  SoTimerSensor();
  /**
   * Constructor that takes the callback function and data to be
   * called when the sensor is triggered.
   */
  SoTimerSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoTimerSensor();

  /**
   * Sets the base time. The default base time is the time when
   * the sensor is scheduled or rescheduled.
   */
  void                setBaseTime(const SbTime &base)  { baseTime = base;
  baseTimeSet = TRUE;}
  /**
   * Sets the interval. The default interval is 1/30th of a
   * second.
   */
  void                setInterval(const SbTime &intvl) { interval = intvl; }
  /**
   * Gets the base time.
   */
  const SbTime &      getBaseTime() const              { return baseTime; }
  /**
   * Gets the interval.
   */
  const SbTime &      getInterval() const              { return interval;  }

  // Overrides the regular schedule() method because we have to set
  // up the trigger time first.
  virtual void        schedule();

  // Overrides the regular unschedule() because the timer could be
  // in either the timer queue or the waiting-to-be-rescheduled
  // queue, depending on the state of the 'triggering' flag.
  virtual void        unschedule();

 SoINTERNAL public:

  // Reschedule this timer relative to the given time
  void                reschedule(const SbTime &);

protected:
  // Triggers the sensor, calling its callback function. This
  // overrides the method in SoSensor because it has to reschedule
  // itself for the next interval after triggering.
  virtual void        trigger();

  SbBool              triggering;     // True if in trigger() code

 private:
  SbTime              baseTime;       // Base time for scheduling triggering
  SbTime              interval;       // Interval between triggering
  SbBool              baseTimeSet;    // Whether base time was set by user

};

#endif  /* _SO_TIMER_SENSOR_ */

