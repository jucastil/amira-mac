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


#ifndef  _SO_ONE_SHOT_SENSOR_
#define  _SO_ONE_SHOT_SENSOR_

#include <Inventor/sensors/SoDelayQueueSensor.h>

/**
 * Sensor for one-time only callbacks.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   A one-shot sensor is triggered once after it is scheduled, when the delay queue
 *   is processed. Like all delay queue sensors, one-shot sensors with a non-zero
 *   priority are just added to the delay queue when scheduled; if they are scheduled
 *   again before the delay queue is processed nothing happens, and they are
 *   guaranteed to be called only once when the delay queue is processed. For
 *   example, a one-shot sensor whose \oivnetdoc delegate \else callback \endoivnetdoc redraws the scene might be
 *   scheduled whenever the scene graph changes and whenever a window-system event
 *   reporting that the window changed size occurs. By using a one-shot, the scene
 *   will only be redrawn once even if a window-changed-size event occurs just after
 *   the scene graph is modified (or if several window-changed-size events occur in a
 *   row).
 *   
 *   Calling schedule() in the \oivnetdoc delegate \else callback \endoivnetdoc is a useful way of getting
 *   something to happen repeatedly as often as possible, while still handling events
 *   and timeouts.
 *   
 *   A priority 0 one-shot sensor isn't very useful, since scheduling it is exactly
 *   the same as directly calling its \oivnetdoc delegate \else callback \endoivnetdoc.
 * 
 * @SEE_ALSO
 *    SoIdleSensor,
 *    SoDelayQueueSensor
 * 
 * 
 */ 

class INVENTOR_API SoOneShotSensor : public SoDelayQueueSensor {

 public:
  /**
   * Default constructor.
   */
  SoOneShotSensor();
  /**
   * Constructor that takes the \oivnetdoc delegate \else callback \endoivnetdoc function and data to be
   * called when the sensor is triggered.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoOneShotSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoOneShotSensor();

};

#endif  /* _SO_ONE_SHOT_SENSOR_ */

