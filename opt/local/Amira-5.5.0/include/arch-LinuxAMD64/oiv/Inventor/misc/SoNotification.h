/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NOTIFICATION_
#define  _SO_NOTIFICATION_

#include <Inventor/SbBasic.h>

class SoBase;
class SoField;
class SoEngineOutput;
class SoVRMLInterpOutput;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNotRec
//
//  Records one step in the path taken by notification. Instances of
//  this class are typically allocated on the stack as automatic
//  variables.
//
//  There is an SoBase pointer in the record that points to the base
//  (node, path, engine, interpolator) from which the notification is being
//  propagated. The contents of this pointer depend on the type of
//  the notification. The type also indicates the nature of the
//  notification. These are the possible types:
//
//      CONTAINER:  A field has changed value and is notifying its
//                  container node or engine. The base is the container.
//
//      PARENT:     A child of a group has changed and is notifying
//                  its parent. The base is the child.
//
//      SENSOR:     A node or path is notifying a sensor of a change.
//                  The base is the thing to which the sensor is attached.
//
//      FIELD:      A field in a node or engine is notifying the
//                  field to which it is connected. The base is the
//                  container of the source field.
//
//      ENGINE:     An engine is notifying a field to which it is
//                  connected. The base is the engine.
//
//      INTERP:     A VRMLInterpolator is notifying a field to which it is
//                  connected. The base is the SoVRMLInterpolator.
//
//      UNDEFINED:  None or undefined notification type.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoNotRec {

 public:

  // Notification types (what receives notification). Note that
  // these are also used for maintaining lists of auditors in
  // SoBase instances. Each auditor uses one of these types to
  // indicate how it is auditing the instance. This is then
  // propagated to the auditors in the notification records.
  enum Type {
    CONTAINER,              // Field notifying container
    PARENT,                 // Child node notifying parent
    SENSOR,                 // Some base notifying sensor
    FIELD,                  // Field notifying connected field
    ENGINE,                 // Engine notifying connected field
    INTERP,                 // VRMLInterpolator notifying connected field
    UNDEFINED               // none or undefined
  };

  // Constructor - passed the base pointer
  SoNotRec(SoBase *b)                 { base = b; }

  // Sets notification type
  void                setType(SoNotRec::Type t)       { type = t;     }

  // Returns base pointer, type, or previous record in list
  SoBase *            getBase() const                 { return base;  }
  SoNotRec::Type      getType() const                 { return type;  }
  const SoNotRec *    getPrevious() const             { return previous; }

  // Sets previous record pointer
  void                setPrevious(SoNotRec *prev)     { previous = prev; }

  // Prints a notification record for debugging
  void                print(FILE *fp) const;

 private:

  SoBase              *base;          // Base that changed
  Type                type;           // Type of record
  const SoNotRec      *previous;      // Pointer to previous record
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNotList
//
//  Holds a list of SoNotRec notification records. Points to the first
//  and last records in the list. The records are linked backwards by
//  "previous" pointers.
//
//  The list also points to the first notification record that
//  involves a node. This info is used to determine which node
//  actually notified sensors. There is also a pointer to the last
//  field that changed, which is needed by field-specific sensors.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoNotList {

 public:
  // Constructor
  SoNotList();

  // Copy constructor
  SoNotList(const SoNotList *copyFrom)                { *this = *copyFrom; }

  // Appends given non-field record to end of list.
  void                append(SoNotRec *rec);

  // Appends given (container) field record to end of list. We
  // assume the base in the record is a node.
  void                append(SoNotRec *rec, SoField *field);

  // Appends given (container) engineOutput record to end of list. We
  // assume the base in the record is a node.
  void                append(SoNotRec *rec, SoEngineOutput *engineOutput);

  // Appends given (container) interpOutput record to end of list. We
  // assume the base in the record is a node.
  void                append(SoNotRec *rec, SoVRMLInterpOutput *interpOutput);

  // Sets the type of the last (current) record in the list
  void                setLastType(SoNotRec::Type t)
    {
      last->setType(t);
      // Reset firstAtNode pointer if we're going through
      // field-to-field or engine-to-field connections.
      if (t == SoNotRec::FIELD || 
          t == SoNotRec::ENGINE ||
          t == SoNotRec::INTERP)
        firstAtNode = NULL;
    }

  // Returns first and last records in list
  SoNotRec *          getFirstRec() const             { return first; }
  SoNotRec *          getLastRec() const              { return last;  }

  // Returns first record in list that has a node base in the
  // current chain of node-to-node notification. This information is
  // passed to sensor callbacks to indicate which node initiated
  // notification in the graph.
  SoNotRec *          getFirstRecAtNode() const       { return firstAtNode; }

  // Returns last field set by notification (or NULL if notification
  // did not originate at or propagate through a field)
  SoField *           getLastField() const            { return lastField; }

  // Returns last Interpolator Output set by notification
  // (or NULL if notification did not originate at or propagate
  //through a field)
  SoVRMLInterpOutput *  getLastInterpOutput() const
    { return lastInterpOutput; }

  // Returns last Engine Output set by notification
  // (or NULL if notification did not originate at or propagate
  //through a field)
  SoEngineOutput *  getLastEngineOutput() const  { return lastEngineOutput; }


  // Returns the time stamp so nodes can check if notification has
  // already been handled
  uint64_t getTimeStamp() const { return timeStamp; }

  // Prints a notification list for debugging
  void                print(FILE *fp) const;

 private:
  SoNotRec            *first, *last;  // First and last records in list
  SoNotRec            *firstAtNode;   // First record that has a node base
  SoField             *lastField;     // Last field that changed
  SoVRMLInterpOutput  *lastInterpOutput;      // Last field that changed
  SoEngineOutput      *lastEngineOutput;      // Last field that changed
  uint64_t            timeStamp;      // Time stamp of notification
};

#endif /* _SO_NOTIFICATION_ */
