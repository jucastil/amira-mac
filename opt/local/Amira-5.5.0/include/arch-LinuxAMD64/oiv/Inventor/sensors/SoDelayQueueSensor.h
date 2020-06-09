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


#ifndef  _SO_DELAY_QUEUE_SENSOR_
#define  _SO_DELAY_QUEUE_SENSOR_

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDelayQueueSensor
//
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/sensors/SoSensor.h>

/**
 * Abstract base class for sensors not dependent on time.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Delay queue sensors are separate from timer queue sensors (see
 *   SoTimerQueueSensor) and provide methods for setting the relative priorities of
 *   the sensors in the delay queue (sensors with higher priorities will be triggered
 *   first).
 *   
 *   Sensors with non-zero priorities are added to the delay queue when scheduled, and
 *   are all processed once, in order, when the delay queue is processed, which
 *   normally happens as part of your program's main loop (see
 *   SoWin::mainLoop() or SoDB::doSelect()). Typically, the delay queue
 *   is processed whenever there are no events waiting to be distributed and there
 *   are no timer queue sensors waiting to be triggered. The delay queue also has a
 *   timeout to ensure that delay queue sensors are triggered even if there are
 *   always events or timer sensors waiting; see
 *   SoDB::setDelaySensorTimeout().
 *   
 *   Sensors with priority 0 are treated specially. Priority 0 sensors are triggered
 *   almost immediately after they are scheduled, before the program returns to the
 *   main loop. Priority 0 sensors are not necessarily triggered immediately when
 *   they are scheduled, however; if they are scheduled as part of the evaluation of
 *   a field connection network they may not be triggered until the evaluation of the
 *   network is complete. Also, if a priority 0 sensor is scheduled within the
 *   \oivnetdoc delegate \else callback \endoivnetdoc method of another priority 0 sensor, it will not be triggered until the
 *   \oivnetdoc delegate \else callback \endoivnetdoc method is complete (also note that if more than one priority 0 sensor
 *   is scheduled, the order in which they fire is undefined).
 * 
 * @SEE_ALSO
 *    SoTimerQueueSensor,
 *    SoDataSensor,
 *    SoFieldSensor,
 *    SoIdleSensor,
 *    SoOneShotSensor,
 *    SoNodeSensor,
 *    SoPathSensor
 * 
 * 
 */ 

class INVENTOR_API SoDelayQueueSensor : public SoSensor {

 public:
  /**
   * Constructor.
   */
  SoDelayQueueSensor();
  /**
   * Constructor that takes standard \oivnetdoc delegate \else callback \endoivnetdoc and data.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoDelayQueueSensor(SoSensorCB *func, void *data);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoDelayQueueSensor();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets the priority of the sensor. Priorities can be changed at any time; if
   * the priority is changed to zero and it is already scheduled, the sensor is
   * immediately triggered and removed from the queue.
   */
  void                setPriority(uint32_t pri);
  /**
   * Gets the priority of the sensor.
   */
  uint32_t            getPriority() const             { return priority; }

  /**
   * Returns the default delay queue sensor priority, which is 100.
   */
  static uint32_t getDefaultPriority()                { return 100; }

  /**
   * If this sensor's priority is non-zero, adds this sensor to the list of delay
   * queue sensors ready to be triggered. This is a way of making a sensor fire
   * without changing the thing it is sensing.
   * 
   * Calling schedule() within the \oivnetdoc delegate \else callback \endoivnetdoc function causes the sensor to be
   * called repeatedly. Because sensors are processed only once every time the delay
   * queue is processed (even if they reschedule themselves), timers and events will
   * still be processed. This should not be done with a priority zero sensor because
   * an infinite loop will result.
   */
  virtual void        schedule();
  /**
   * If this sensor is scheduled, removes it from the delay queue so that it will not
   * be triggered.
   */
  virtual void        unschedule();
  /**
   * Returns TRUE if this sensor has been scheduled and is waiting in the delay queue
   * to be triggered. Sensors are removed from the queue before their \oivnetdoc delegate \else callback \endoivnetdoc
   * function is triggered.
   */
  virtual SbBool      isScheduled() const;

  // This method is overriden by IdleSensors to tell sensor manager
  // that they should only be processed when there really is idle
  // time (and not when the delay queue timeout expires).
  virtual SbBool      isIdleOnly() const;
 SoINTERNAL public:
  // Set/inquire counter when sensor was last triggered. This allows
  // the sensor manager to avoid triggering a sensor more than once
  // during the same call to processDelayQueue().
  void                setCounter(uint32_t c)          { counter = c;  }
  uint32_t            getCounter() const              { return counter; }

 protected:
  // Triggers the sensor, calling its callback function. This
  // overrides the method in SoSensor because it has to reset the
  // schedule flag before triggering.
  virtual void        trigger();

  SbBool              scheduled;      // Whether sensor is scheduled

 private:
  uint32_t            priority;       // Sensor priority
  uint32_t            counter;        // Used by sensor manager

  // Returns TRUE if this sensor should precede sensor s in the delay
  // queue: it must have a lower priority number than s.
  virtual SbBool      isBefore(const SoSensor *s) const;
};

#endif  /* _SO_DELAY_QUEUE_SENSOR_ */

