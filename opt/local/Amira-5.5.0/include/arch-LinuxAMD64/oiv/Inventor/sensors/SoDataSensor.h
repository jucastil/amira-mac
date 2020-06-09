/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
** Modified by : Paul Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DATA_SENSOR_
#define  _SO_DATA_SENSOR_

class SoBase;
class SoNode;
class SoPath;
class SoNotList;

#include <Inventor/sensors/SoDelayQueueSensor.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/threads/SbThreadSpinlock.h>

/**
 * Abstract base class for sensors attached to parts of a scene.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   Data sensors detect changes to scene graph objects (paths, nodes, or fields) and
 *   trigger their \oivnetdoc delegate \else callback \endoivnetdoc when the object changes.
 *   
 *   Data sensors provide a delete \oivnetdoc delegate \else callback \endoivnetdoc that is called just before the object the
 *   data sensor is attached to is deleted; note that the \oivnetdoc delegate \else callback \endoivnetdoc should not attempt
 *   to modify the object in any way, or core dumps may result.
 *   
 *   Priority zero data sensors also provide methods that can be called in the
 *   \oivnetdoc delegate \else callback \endoivnetdoc to determine exactly which node, field, or path caused the
 *   sensor to be triggered.
 * 
 * @SEE_ALSO
 *    SoNodeSensor,
 *    SoPathSensor,
 *    SoFieldSensor,
 *    SoDelayQueueSensor
 * 
 * 
 */ 


class INVENTOR_API SoDataSensor : public SoDelayQueueSensor {

 public:
   /** Change type */
  enum ChangeType {
    /** Unspecified */
    UNSPECIFIED,
    /** Group add child */
    GROUP_ADD_CHILD,
    /** Group insert child */
    GROUP_INSERT_CHILD,
    /** Group replace child */
    GROUP_REPLACE_CHILD,
    /** Group remove child */
    GROUP_REMOVE_CHILD,
    /** Group remove all children */
    GROUP_REMOVE_ALL_CHILDREN,
    /** Field multivalue */
    FIELD_MULTIVALUE
  };

  /**
   * Constructor.
   */
  SoDataSensor();
  /**
   * Constructor that takes standard callback function and data.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoDataSensor(SoSensorCB *func, void *data);

  // Destructor
#ifndef HIDDEN_FROM_DOC
  virtual ~SoDataSensor();
#endif // HIDDEN_FROM_DOC

  /**
   * Sets a callback that will be called when the object the sensor is sensing is
   * deleted.
   */
  void                setDeleteCallback(SoSensorCB *f, void *data = NULL)
    { deleteFunc = f; deleteData = data; }

  /**
   * If this is a priority 0 data sensor, returns the node that was modified
   * that caused this sensor to trigger. Returns NULL if the sensor was not triggered
   * because a node changed (for example, if schedule() is called on the
   * sensor) or if this sensor is not a priority 0 sensor. Note that because one
   * change to the scene graph may cause multiple nodes or fields to be modified
   * (because of field-to-field connections), the node returned may not be
   * the only one that changed.
   */
  SoNode *            getTriggerNode() const;

  /**
   * If this is a priority 0 data sensor, returns the field that was modified
   * that caused this sensor to trigger. Returns NULL if the sensor was not triggered
   * because a field changed (for example, if schedule() is called on the
   * sensor) or if this sensor is not a priority 0 sensor. Note that because one
   * change to the scene graph may cause multiple nodes or fields to be modified
   * (because of field-to-field connections), the field returned may not be
   * the only one that changed.
   */
  SoField *           getTriggerField() const;
    
  /**
   * If this is a priority 0 data sensor, returns a path to the node that caused this
   * sensor to trigger. Because recreating the path to the node that changed is
   * relatively expensive, @B setTriggerPathFlag(TRUE) @b must be called before the
   * sensor is scheduled. If it is not called, or if the sensor wasn't triggered
   * because a node changed, this returns NULL. NULL is also returned if this is not
   * a priority 0 sensor.
   */
  SoPath *            getTriggerPath() const;

  /**
   * Sets the flag that indicates whether the trigger path
   * (see getTriggerPath()) is available to callback methods. This
   * is FALSE by default. Note that setting this to TRUE will add a
   * little overhead when the sensor is notified.
   */
  void setTriggerPathFlag(SbBool flag) { m_notifyData->doTrigPath = flag; }
  /**
   * Queries the flag that indicates whether the trigger path
   * (see getTriggerPath()) is available to \oivnetdoc delegates \else callbacks \endoivnetdoc .
   */
  SbBool              getTriggerPathFlag() const      { return m_notifyData->doTrigPath; }

  /**
   * If this is a priority 0 data sensor, returns the type of change that occurred.
   * Returns UNSPECIFIED if the sensor was not triggered by a group children change
   * or a multi-value field change or if this sensor is not a priority 0 sensor.
   * A GROUP_* return value indicates that getTriggerChild and getTriggerChildIndex
   * will return valid data.  A FIELD_* return value indicates that the getTriggerMField*
   * methods will return valid data.
   */
  ChangeType getTriggerType() const;

  /**
   * If this is a priority 0 data sensor, and a change to a group node's
   * children caused this sensor to be triggered (getTriggerType returns
   * GROUP_ADD_CHILD, GROUP_INSERT_CHILD, or GROUP_REPLACE_CHILD), returns
   * the node that was added to the group, 
   * and NULL in all other cases.
   */
  SoNode* getTriggerChild() const;

  /**
   * If this is a priority 0 data sensor, and a change to a group node's
   * children caused this sensor to be triggered (getTriggerType returns
   * GROUP_ADD_CHILD, GROUP_INSERT_CHILD, or GROUP_REPLACE_CHILD), returns
   * the index of the node that was added or removed,
   * and -1 in all other cases.
   */
  int getTriggerChildIndex() const;

  /**
   * If this is a priority 0 data sensor, and a change in the data values 
   * of a multiple field (e.g., SoMFVec3f) caused this sensor to be 
   * triggered, returns the first index of the range of the potentially changed values. 
   * Otherwise, returns -1
   */
  int getTriggerMFieldStartIndex() const;

  /**
   * If this is a priority 0 data sensor, and a change in the data values 
   * of a multiple field (e.g., SoMFVec3f) caused this sensor to be 
   * triggered, returns the size of the range of the potentially changed values. 
   * Otherwise, returns -1
   */
  int getTriggerMFieldNumValues() const;

  // Override unschedule() to reset trigNode and trigPath.
  virtual void unschedule();

 SoINTERNAL public:
  // Override trigger to reset trigNode and trigPath, if
  // necessary.
  virtual void trigger();

  // Propagates modification notification through an instance. By
  // default, this schedules the sensor to be triggered and saves
  // some information from the notification list for use by the
  // callback function.  Called by SoBase.
  virtual void        notify(SoNotList *list);

  // This is called when the base (path, field, node, whatever) is
  // deleted. All subclasses must implement this to do the right
  // thing.
  virtual void        dyingReference() = 0;

 protected:
  // Invokes the delete callback
  void                invokeDeleteCallback();

 private:

   class SoDataSensorData
   {
   public:
     SoDataSensorData()
     {
       trigNode   = NULL;
       trigField  = NULL;
       trigPath   = NULL;
       doTrigPath = FALSE;

       trigChildIndex = -1;
       trigChild = NULL;
       trigMFieldStartIndex = -1;
       trigMFieldNumValues = -1;
       trigChangeType = UNSPECIFIED;
     }
     virtual void unref() {};
     virtual ~SoDataSensorData() {};

     SoNode* trigNode;      // Node that triggered sensor
     SoField* trigField;    // Field that triggered sensor
     SoPath* trigPath;      // Path to trigNode
     SbBool doTrigPath;     // Whether to compute trigger path

     ChangeType trigChangeType; // change type (if parent is SoGroup)
     SoNode* trigChild;        // changed child (if parent is SoGroup)
     int trigChildIndex;       // index of changed child in group (if parent is SoGroup)
     int trigMFieldStartIndex; // index of the first value which change in the MField
     int trigMFieldNumValues;  // num of values which change in the MField

   };
   SoDataSensorData* m_notifyData;

  SoSensorCB* deleteFunc;    // CB and data for when attached SoBase
  void* deleteData;    // is about to be deleted

  SbThreadSpinlock m_mutex;
};

#endif  /* _SO_DATA_SENSOR_ */

