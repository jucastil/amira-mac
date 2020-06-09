/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_IDLE_SENSOR_
#define  _SO_IDLE_SENSOR_

#include <Inventor/sensors/SoDelayQueueSensor.h>

/**
 * Sensor for one-time only callbacks when the application is idle.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   An idle sensor is almost exactly like an SoOneShotSensor, except that it is only
 *   triggered when there are no timer queue sensors waiting to be triggered and
 *   there are no events waiting to be processed; that is, idle sensors will not be
 *   triggered if the delay queue is processed because the delay queue timeout
 *   expires. If the delay queue timeout is disabled (see
 *   SoDB::setDelaySensorTimeout().), idle and one-shot sensors are exactly
 *   the same.
 *   
 *   Note that idle sensors do not reschedule themselves. Inventor 1 idle sensors were
 *   always scheduled; call schedule() in the \oivnetdoc delegate \else callback \endoivnetdoc to duplicate
 *   that behavior.
 *   
 *   See the SoOneShotSensor manual page for more information.
 * 
 * @SEE_ALSO
 *    SoOneShotSensor,
 *    SoDelayQueueSensor
 * 
 * 
 */ 

class INVENTOR_API SoIdleSensor : public SoDelayQueueSensor {

 public:
  /**
   * Default constructor.
   */
  SoIdleSensor();
  /**
   * Constructor that takes the callback function and data to be
   * called when the sensor is triggered.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoIdleSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoIdleSensor();

 private:
  // Let sensor manager know this class should only be processed
  // when there is really idle time.
  virtual SbBool      isIdleOnly() const;

};

#endif  /* _SO_IDLE_SENSOR_ */

