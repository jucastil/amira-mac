/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
** Modified by : Paul Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ALARM_SENSOR_
#define  _SO_ALARM_SENSOR_

#include <Inventor/sensors/SoTimerQueueSensor.h>

/**
 * Triggers a delegate once sometime in the future.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   This type of sensor can be used to schedule a one-time delegate for some time in
 *   the future. The sensor is not guaranteed to be called at exactly that time, but
 *   will be called sometime after the specified time.
 * 
 * @SEE_ALSO
 *    SoOneShotSensor,
 *    SoTimerSensor,
 *    SoTimerQueueSensor,
 *    SbTime
 * 
 * 
 */ 

class INVENTOR_API SoAlarmSensor : public SoTimerQueueSensor {

 public:
  /**
   * Constructor.
   */
  SoAlarmSensor();

  /**
   * This constructor takes the callback function and data to be
   * called when the sensor is triggered.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoAlarmSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoAlarmSensor();

  /**
   * Sets the sensor to go off at the specified time. You @B must @b also call
   * schedule() for the sensor to be triggered. If the sensor is already
   * scheduled, it must be unscheduled and then rescheduled for the change in the
   * trigger time to take effect.
   */
  void                setTime(const SbTime &absTime);
  /**
   * Sets the sensor to go off the given amount of time from now. You @B must @b
   * also call schedule() for the sensor to be triggered. If the sensor is
   * already scheduled, it must be unscheduled and then rescheduled for the change in
   * the trigger time to take effect.
   */
  void                setTimeFromNow(const SbTime &relTime);

  /**
   * Returns the time at which the sensor is set to be triggered. This is similar to
   * the @B getTriggerTime @b method, but returns the time even if the sensor has
   * not yet been scheduled.
   */
  const SbTime &      getTime() const                 { return time; }

  // Overrides the regular schedule() method because we have to set
  // up the trigger time first.
  virtual void        schedule();

 private:
  SbTime              time;           // Time sensor is scheduled for
  SbBool              timeSet;        // Whether time value was set

};

#endif  /* _SO_ALARM_SENSOR_ */

