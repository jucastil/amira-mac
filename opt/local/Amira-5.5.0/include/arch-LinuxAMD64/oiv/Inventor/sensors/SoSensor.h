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


#ifndef  _SO_SENSOR_
#define  _SO_SENSOR_

#include <Inventor/SbBasic.h>

class SoField;
class SoMField;
class SoSensor;

/** This typedef defines the calling sequence for all callbacks from sensors
 * [OIV-WRAPPER NAME{SensorCB}]
 */
typedef void SoSensorCB(void *data, SoSensor *sensor);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSensor
//
//  Abstract base class for all sensors. Defines basic callback
//  definition (explicit or in constructor) and scheduling and
//  triggering methods.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * Abstract base class for Open Inventor sensors.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Sensors detect changes either to time or to Open Inventor objects in a scene
 *   graph, and call a user-defined \oivnetdoc delegate \else callback \endoivnetdoc function. Sensors are @B scheduled @b
 *   when the thing they are attached to changes, and sometime after they are
 *   scheduled they are @B triggered @b, calling the user's \oivnetdoc delegate \else callback \endoivnetdoc function.
 * 
 * @SEE_ALSO
 *    SoAlarmSensor,
 *    SoDataSensor,
 *    SoFieldSensor,
 *    SoIdleSensor,
 *    SoNodeSensor,
 *    SoPathSensor
 * 
 * 
 */ 

class INVENTOR_API SoSensor {

 public:

  /**
   * Constructor.
   */
  SoSensor()
    {
      func = NULL;
      funcData = NULL;
#ifdef _WIN32
      dwThreadId=GetCurrentThreadId();
#endif
    }
  /**
   * Constructor that takes standard \oivnetdoc delegate \else callback \endoivnetdoc function and data.
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoSensor(SoSensorCB *f, void *d)
    {
      func = f;
      funcData = d;
#ifdef _WIN32
      dwThreadId=GetCurrentThreadId();
#endif
    }

  // Virtual destructor so that subclasses are deleted properly
#ifndef HIDDEN_FROM_DOC
  virtual ~SoSensor();
#endif // HIDDEN_FROM_DOC

  /**
   * [OIV-WRAPPER EVENT_NAME{Action}]
   */
  inline void setFunction(SoSensorCB *f, void *userData);

  /**
   * Sets the callback function that is called when the sensor is triggered. The
   * function must take two arguments - user-supplied callback data (of type void *)
   * and a pointer to the sensor that is triggering the function (of type SoSensor
   * *).
   * [OIV-WRAPPER-NO-WRAP]
   */
  void                setFunction(SoSensorCB *f)
    {
      func = f;
#ifdef _WIN32
      dwThreadId=GetCurrentThreadId();
#endif
      
    }
    
  /**
   * Sets the callback data passed to the callback function.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void                setData(void *d)                { funcData = d; }

  /**
   * Returns the callback that will be called when the sensor is triggered.
   * [OIV-WRAPPER-NO-WRAP]
   */
  SoSensorCB *        getFunction() const             { return func; }
    
  /**
   * Returns the user-supplied pointer that will be passed to the callback function.
   * [OIV-WRAPPER-NO-WRAP]
   */
  void *              getData() const                 { return funcData; }

  // Schedules the sensor for triggering at the appropriate time
  virtual void        schedule() = 0;

  // Unschedules sensor to keep it from being triggered
  virtual void        unschedule() = 0;

  // Returns whether the sensor is scheduled
  virtual SbBool      isScheduled() const = 0;

 SoINTERNAL public:
#ifdef _WIN32
  DWORD getThreadId() { return dwThreadId;};
  void setThreadId(DWORD id) { dwThreadId=id;};
#endif

  // Initialize static members, etc.
  static void         initClass();

  // Triggers the sensor, calling its callback function
  virtual void        trigger();

  // This returns TRUE if this sensor should precede sensor s in
  // whichever queue this sensor would be in.
  virtual SbBool      isBefore(const SoSensor *s) const = 0;

  // Sets/returns the next sensor in whichever queue the sensor is in
  void                setNextInQueue(SoSensor *next) { nextInQueue = next; }
  SoSensor *          getNextInQueue() const         { return nextInQueue; }

 protected:
  SoSensorCB *        func;           // Callback function
  void *              funcData;       // Data to pass to callback

#ifdef _WIN32
  DWORD           dwThreadId; // thread to which this sensor belongs

 protected:
#else
 private:
#endif
  SoSensor            *nextInQueue;   // Next sensor in queue
};

void SoSensor::setFunction(SoSensorCB *f, void *userData)
{ 
  setFunction(f);
  setData(userData);
}

#endif /* _SO_SENSOR_ */


