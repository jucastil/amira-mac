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


#ifndef  _SO_PATH_SENSOR_
#define  _SO_PATH_SENSOR_

#include <Inventor/SoPath.h>
#include <Inventor/sensors/SoDataSensor.h>

/**
 * Sensor class that can be attached to Open Inventor paths.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Path sensors detect changes to paths, calling a \oivnetdoc delegate \else callback \endoivnetdoc function whenever the
 *   path or any node in the path changes. The definition of "in the path" is the
 *   same as the definition used when applying an action to the path - any node that
 *   can possibly affect the node at the end of the path chain is considered in the
 *   path. See the SoPath manual page for more information on paths.
 * 
 * @SEE_ALSO
 *    SoNodeSensor,
 *    SoPathSensor,
 *    SoDataSensor
 * 
 * 
 */ 

class INVENTOR_API SoPathSensor : public SoDataSensor {

 public:
  /**
   * Default constructor.
   */
  SoPathSensor();
  /**
   * Constructor that takes the callback function and data to be
   * called when the sensor is triggered.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoPathSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoPathSensor();

  /**
   * Makes this sensor detect changes to the given path.
   */
  void                attach(SoPath *path);

  /**
   * Unschedules this sensor (if it is scheduled) and
   * makes it ignore changes to the scene graph. 
   */
  void                detach();

  /**
   * Returns the path that this sensor is sensing, or NULL if it is not attached to
   * any path.
   */
  SoPath *            getAttachedPath() const         { return path; }

 protected:
  void                notify(SoNotList *list);

 private:
  SoFullPath *        path;           // Path sensor is attached to
  SoNode *            head;           // Head of that path

  // Called by the attached path when it (the path) is about to be deleted
  virtual void        dyingReference();

};

#endif  /* _SO_PATH_SENSOR_ */

