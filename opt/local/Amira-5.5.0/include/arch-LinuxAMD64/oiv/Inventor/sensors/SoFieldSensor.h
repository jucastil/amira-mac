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


#ifndef  _SO_FIELD_SENSOR_
#define  _SO_FIELD_SENSOR_

#include <Inventor/sensors/SoDataSensor.h>

class SoFieldContainer;

/**
 * Sensor class that can be attached to Open Inventor fields.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Field sensors detect changes to fields, calling a \oivnetdoc delegate \else callback \endoivnetdoc function whenever the
 *   field changes. The field may be part of a node, an input of an engine, or a
 *   global field.
 * 
 * @SEE_ALSO
 *    SoNodeSensor,
 *    SoPathSensor,
 *    SoDataSensor
 * 
 * 
 */ 

class INVENTOR_API SoFieldSensor : public SoDataSensor {

 public:
  /**
   * Constructor
   */
  SoFieldSensor();

  /**
   * This constructor takes the callback function and data to be
   * called when the sensor is triggered.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoFieldSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoFieldSensor();

  /**
   * The attach() method makes this sensor detect changes to the given field.
   * See also detach(), getAttachedField()
   */
  void                attach(SoField *field);

  /**
   * The detach() method unschedules this sensor (if it is scheduled) and
   * makes it ignore changes to the scene graph. 
   * See also attach(), getAttachedField()
   */
  void                detach();

  /**
   * The getAttachedField() method returns the field that this sensor is 
   * sensing, or NULL if it is not attached to any field.
   * See also attach(), detach() 
   */
  SoField *           getAttachedField() const        { return field; }

 SoINTERNAL public:
  // Override trigger to evaluate the field we're connected to, just
  // in case the trigger method doesn't get the value.
  virtual void trigger();

 private:
  SoField *           field;          // Field sensor is attached to

  // Propagates modification notification through an instance. This
  // checks to see if the field that triggered notification matches
  // the field we are attached to. (It also checks indices if necessary.)
  virtual void        notify(SoNotList *list);

  // Called by the attached path when it (the path) is about to be deleted
  virtual void        dyingReference();

};

#endif  /* _SO_FIELD_SENSOR_ */

