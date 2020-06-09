/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2007)
**=======================================================================*/


#ifndef  _SO_LIST_SENSOR_
#define  _SO_LIST_SENSOR_

class SoBaseList;
class SoNotList;

#include <Inventor/sensors/SoSensor.h>

/** 
 * Sensor class that can be attached to Open Inventor base lists.
 * 
 * @ingroup sensors
 * 
 * @DESCRIPTION
 *   List sensors detect changes to SoBaseList derived lists (field list, engine list, ...) and
 *   trigger their \oivnetdoc delegate \else callback \endoivnetdoc when the list changes.
 *   
 *   List sensors provide a delete \oivnetdoc delegate \else callback \endoivnetdoc that is called just before the list the
 *   list sensor is attached to is deleted; note that the \oivnetdoc delegate \else callback \endoivnetdoc should not attempt
 *   to modify the list in any way, or core dumps may result.
 *   
 *   List sensors also provide methods that can be called in the
 *   \oivnetdoc delegate \else callback \endoivnetdoc to determine exactly which item of the list caused the
 *   sensor to be triggered.
 * 
 * @SEE_ALSO
 *    SbPList,
 *    SoSensor
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 


class INVENTOR_API SoListSensor : public SoSensor
{
 public:
   /** Change type */
  enum ChangeType
  {
    /** Unspecified change. */
    UNSPECIFIED,
    /** An item has been appended to the list. */
    APPEND,
    /** An item has been inserted. */
    INSERT,
    /** A previously existing item has been replaced. */
    SET,
    /** An item has been deleted. */
    REMOVE,
    /** The list has been cleared. */
    TRUNCATE,
    /** The list is resulting of a list copy. */
    COPY,
    /** A touch() call has been done on list. */
    TOUCH
  };

  /**
   * Constructor.
   */
  SoListSensor();

  /**
   * Constructor that takes standard callback function and data.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  SoListSensor(SoSensorCB* func, void* data);

  /**
   * Destructor.
   */
  virtual ~SoListSensor();

  /**
   * Makes this sensor detect changes to the given list.
   */
  void attach(SoBaseList* list);

  /**
   * Unschedules this sensor (if it is scheduled) and makes it ignore changes to the list. 
   */
  void detach();

  /**
   * Returns the list that this sensor is sensing, or NULL if it is not attached to
   * any list.
   */
  SoBaseList* getAttachedList() const { return m_list; }

  /**
   * Sets a callback that will be called when the object the sensor is sensing is
   * deleted.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setDeleteCallback( SoSensorCB *f, void *data = NULL )
  {
    m_deleteFunc = f;
    m_deleteData = data;
  }

  /**
   * Returns the type of change that occurred.
   */
  ChangeType getTriggerType() const;

  /**
   * Returns the index of the item that was added, removed, inserted, set, ...
   */
  int getTriggerIndex() const;

 SoINTERNAL public:

  // Override trigger to reset trigNode and trigPath, if
  // necessary.
  virtual void trigger();

  // Called by the attached list when it is about to be deleted
  virtual void dyingReference();

    // Schedules the sensor for triggering at the appropriate time
  virtual void schedule() {};

  // Unschedules sensor to keep it from being triggered
  virtual void unschedule() {};

  // Returns whether the sensor is scheduled
  virtual SbBool isScheduled() const { return true; }

  // This returns TRUE if this sensor should precede sensor s in
  // whichever queue this sensor would be in.
  virtual SbBool isBefore(const SoSensor*) const { return false; }

 protected:
  // Invokes the delete callback
  void invokeDeleteCallback();

 private:

  SoSensorCB *m_deleteFunc;    // CB and data for when attached
  void *m_deleteData;          // is about to be deleted
  ChangeType m_trigType;
  int m_trigIndex;
  SoBaseList* m_list;
};

#endif  // _SO_LIST_SENSOR_

/**/
