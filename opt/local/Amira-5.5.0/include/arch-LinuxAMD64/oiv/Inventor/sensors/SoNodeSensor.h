/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Paul Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NODE_SENSOR_
#define  _SO_NODE_SENSOR_

#include <Inventor/sensors/SoDataSensor.h>

/**
 * Sensor class that can be attached to Open Inventor nodes.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Node sensors detect changes to nodes, calling a \oivnetdoc delegate \else callback \endoivnetdoc whenever any
 *   field of the node or, if the node is a group node, any children of the node
 *   change.
 * 
 * @SEE_ALSO
 *    SoFieldSensor,
 *    SoPathSensor,
 *    SoDataSensor
 * 
 * 
 */ 

class INVENTOR_API SoNodeSensor : public SoDataSensor {

 public:
  /**
   * Default constructor.
   */
  SoNodeSensor();
  /**
   * Constructor that takes the callback function and data to be
   * called when the sensor is triggered.
   */
  SoNodeSensor(SoSensorCB *func, void *data);

  /**
   * Destroys the sensor, freeing up any memory associated with it after unscheduling
   * it.
   */
  virtual ~SoNodeSensor();

  /**
   * Makes this sensor detect changes to the given node.
   */
  void attach(SoNode *node);

  /**
   * Unschedules this sensor (if it is scheduled) and
   * makes it ignore changes to the scene graph. 
   */
  void detach();

  /**
   * Returns the node that this sensor is
   * sensing, or NULL if it is not attached to any node.
   */
  SoNode *getAttachedNode() const { return node; }

 private:
  SoNode *node;               // Node sensor is attached to

  // Called by the attached node when it (the node) is about to be deleted
  virtual void dyingReference();

};

#endif  /* _SO_NODE_SENSOR_ */

