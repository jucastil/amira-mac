/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_LISTS_
#define  _SO_LISTS_

#include <Inventor/SbPList.h>
#include <Inventor/SoType.h>
#include <Inventor/STL/iostream>

#include <Inventor/misc/SoNotification.h>
#include <Inventor/sensors/SoListSensor.h>

class SoAuditorList;
class SoBase;
class SoDetail;
class SoEngine;
class SoEngineOutput;
class SoField;
class SoNode;
class SoSensor;
class SoPath;
class SoPickedPoint;
class SoVRMLInterpolator;
class SoVRMLInterpOutput;
class SoVRMLPROTOField;
class SoVRMLEXTERNPROTOField;

//////////////////////////////////////////////////////////////////////////////
//
// Subclasses of the SbPList class which hold lists of pointers of a
// specific type.
//
// Each contains:
//      A default constructor
//      A constructor taking an initial number of items in the list
//      An "append" function that adds a pointer to the end of the list
//      The index ([]) operator that returns the nth pointer in the list
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Maintains a list of pointers to instances of the SoBase classes.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to instances of classes derived
 *   from SoBase (an abstract class). A flag indicates whether adding an instance
 *   pointer to the list should add a reference to the instance. If this flag is
 *   TRUE, then adding and removing pointers from the list updates reference counts
 *   in the corresponding instances.
 *
 * @SEE_ALSO
 *    SoBase,
 *    SoNodeList,
 *    SoPathList
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoBaseList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoBaseList();
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoBaseList(int size);
  /**
   * Constructor that copies the contents of another list.
   */
  SoBaseList(const SoBaseList &l);
  /**
   * Destructor.
   */
  ~SoBaseList();

  /**
   * Adds a pointer to the end of the list.
   */
  void                append(SoBase * ptr);

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void                insert(SoBase *ptr, int addBefore);

  /**
   * Removes pointer with given index.
   */
  void                remove(int which);

  /**
   * Removes all pointers after one with given index, inclusive.
   */
  void                truncate(int start);

  /**
   * Copies a list, keeping all reference counts correct.
   */
  void                copy(const SoBaseList &l);

  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoBaseList &        operator =(const SoBaseList &l)
  { copy(l) ; return *this; }

  /**
   * Accesses an element of a list.
   */
  SoBase *            operator [](int i) const
    { return ( static_cast<SoBase *> ( (*static_cast<const SbPList *>(this) ) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoBase *ptr);

  /**
   * Indicates whether to call ref() and unref() for bases in the list
   * when adding/removing them. The default value is TRUE.
   */
  void                addReferences(SbBool flag)
    { addRefs = flag; }

  /** 
   * Forces each attached SoListSensor to be notified.
   * Attached sensor will be notified using the passed index
   * as the trigger index.
   * If index is greater than the number of elements in the list,
   * index is set to the last element.
   * If the list is empty, index is set to -1.
   */
  void touch( int index = -1 );

  /**
   * Add an auditor to the list.
   */
   void addAuditor(void *auditor, SoNotRec::Type type);

   /**
    * Remove an auditor to the list.
    */
   void removeAuditor(void *auditor, SoNotRec::Type type);

   /**
    * Get current auditor list.
    */
   const SoAuditorList* getAuditors() const
   { 
     if (m_notificationInfo)
       return m_notificationInfo->m_auditors;
     return NULL;
   }

   /**
    * Get last changed index element of the list.
    */
   int getChangedIndex() const 
   { 
     if (m_notificationInfo)
       return m_notificationInfo->m_changedIndex;
     return -1;
   }

   /**
    * Get last changed type of the list.
    */ 
   SoListSensor::ChangeType getChangedType() const
   {
     if (m_notificationInfo)
       return m_notificationInfo->m_changedType;
     return SoListSensor::UNSPECIFIED;
   }
 
   /**
    * setup notification info for auditor mechanism.
    */
  void setNotificationInfo(const int changedIndex, const SoListSensor::ChangeType changedType)
  {
    if (m_notificationInfo)
    {
      m_notificationInfo->m_changedIndex = changedIndex;
      m_notificationInfo->m_changedType  = changedType;
    }
  }

protected:
  // Inner class that handle auditors notification infos.
  class SoNotificationInfo
  {
  public:
    // Constructor.
    SoNotificationInfo();
    // Destructor.
    ~SoNotificationInfo();
    // List of auditors: objects to pass notification to
    SoAuditorList *m_auditors;
    // changed element index
    int m_changedIndex;
    // type of change
    SoListSensor::ChangeType m_changedType;
  };

 private:
  // If TRUE (the default), this refs and unrefs things in the list
  SbBool              addRefs;

  // start notification.
  void startNotify();

  // Auditor notification infos
  SoNotificationInfo *m_notificationInfo;

};

/**
 * Maintains a list of pointers to nodes.
 *
 * @ingroup nodes
 *
 * @DESCRIPTION
 *   This subclass of SoBaseList holds lists of pointers to SoNodes. It updates
 *   reference counts to nodes in the list whenever adding or removing pointers.
 *
 * @SEE_ALSO
 *    SoNode
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoNodeList : public SoBaseList {
 public:
  /**
   * Constructor.
   */
  SoNodeList() : SoBaseList() {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoNodeList(int size) : SoBaseList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoNodeList(const SoNodeList &l) : SoBaseList(l) {}
  /**
   * Destructor.
   */
  ~SoNodeList() {}

  /**
   * Adds a pointer to the end of the list.
   */
  void append(SoNode * ptr);
  /**
   * Accesses an element of a list.
   */
  SoNode * operator [](int i) const;
  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoNodeList &operator =(const SoNodeList &l)
  { SoBaseList::copy(l) ; return *this; }
};

/**
 * Maintains a list of pointers to paths.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This subclass of SoBaseList holds lists of pointers to SoPaths. It updates
 *   reference counts to paths in the list whenever adding or removing pointers.
 *
 * @SEE_ALSO
 *    SoPath
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoPathList : public SoBaseList {
 public:
  /**
   * Constructor.
   */
  SoPathList()                        : SoBaseList()  {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoPathList(int size)                : SoBaseList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoPathList(const SoPathList &l)     : SoBaseList(l) {}
  /**
   * Destructor.
   */
  ~SoPathList()                       { }

  /**
  * Remove a path from the list and return TRUE if removed
  */
  SbBool removePath( const SoPath &path );

  /**
   * Adds a path to the end of the list.
   */
  void                append(SoPath * ptr);
  /**
   * Accesses an element of a list.
   */
  SoPath *            operator [](int i) const;

  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoPathList &        operator =(const SoPathList &l)
  { SoBaseList::copy(l) ; return *this; }


  /**
   * Returns the index of the matching path in the list, or -1 if not found.
   */
# ifdef __osf__
  int                 findPath(const SoPath &path) const ;
# else
  int                 findPath(const SoPath &path);
# endif

  /**
   * Sorts list in place based on (1) increasing address of head node, then (2)
   * increasing indices of children.
   */
  void                sort();

  /**
   * Given a sorted list, removes any path that (1) is a duplicate, or (2) goes
   * through a node that is the tail of another path.
   */
  void                uniquify();

 private:
  // Comparison method for path list sorting.
  static int          comparePaths(const void *p1Ptr, const void *p2Ptr);

  ///////////////////////EXCEPTION METHODS/////////////////////////////////////
  //
  // #duplicated findPath(SoPath & path)
  //
  /////////////////////////////////////////////////////////////////////////////

};

 /**
  * Writes the list to the specified output stream.
  */
std::ostream& operator << (std::ostream& os, const SoPathList& pathList);

/**
 * Maintains a list of pointers to engines.
 *
 * @ingroup engines
 *
 * @DESCRIPTION
 *   This subclass of SoBaseList holds lists of pointers to SoEngines. It updates
 *   reference counts to engines in the list whenever adding or removing pointers.
 *
 * @SEE_ALSO
 *    SoEngine
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoEngineList : public SoBaseList {
 public:
  /**
   * Constructor.
   */
  SoEngineList()                      : SoBaseList()  {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoEngineList(int size)              : SoBaseList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoEngineList(const SoEngineList &l) : SoBaseList(l) {}
  /**
   * Destructor.
   */
  ~SoEngineList()                     { }

  /**
   * Adds an engine to the end of the list.
   */
  void                append(SoEngine * ptr);
  /**
   * Accesses an element of a list.
   */
  SoEngine *          operator [](int i) const;
  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoEngineList &      operator =(const SoEngineList &l)
  { SoBaseList::copy(l) ; return *this; }
};

/**
 * Maintains a list of SoSensor.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of SoSensor type identifiers.
 *
 * @SEE_ALSO
 *    SoSensor
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoSensorList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoSensorList();
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoSensorList(int size);
  /**
   * Constructor that copies the contents of another list.
   */
  SoSensorList(const SoSensorList &l);
  /**
   * Destructor.
   */
  ~SoSensorList()
    { truncate(0); }

  /**
   * Adds a pointer to the end of the list.
   */
  void                append(SoSensor * ptr);

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void                insert(SoSensor *ptr, int addBefore);

  /**
   * Removes pointer with given index.
   */
  void                remove(int which);

  /**
   * Removes all pointers after one with given index, inclusive.
   */
  void                truncate(int start);

  /**
   * Copies a list, keeping all reference counts correct.
   */
  void                copy(const SoSensorList &l);

  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoSensorList &        operator =(const SoSensorList &l)
  { copy(l) ; return *this; }

  /**
   * Accesses an element of a list.
   */
  SoSensor *            operator [](int i) const
    { return ( static_cast<SoSensor *> ( (*static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoSensor *ptr);

};

/**
 * Maintains a list of pointers to VRML interpolators.
 *
 * @ingroup OtherVRML2
 *
 * @DESCRIPTION
 *   This subclass of SoBaseList holds lists of pointers to SoVRMLInterpolators. It updates
 *   reference counts to nodes in the list whenever adding or removing pointers.
 *
 * @SEE_ALSO
 *    SoVRMLInterpolator
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoVRMLInterpList : public SoBaseList {
 public:
  /**
   * Constructor.
   */
  SoVRMLInterpList()                      : SoBaseList()  {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoVRMLInterpList(int size)              : SoBaseList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoVRMLInterpList(const SoVRMLInterpList &l) : SoBaseList(l) {}
  /**
   * Destructor.
   */
  ~SoVRMLInterpList()                     { }

  /**
   * Adds a VRML interpolator to the end of the list.
   */
  void                    append(SoVRMLInterpolator * ptr);
  /**
   * Accesses an element of a list.
   */
  SoVRMLInterpolator *    operator [](int i) const;
  /**
   * Copies a list, keeping all reference counts correct.
   */
  SoVRMLInterpList &      operator =(const SoVRMLInterpList &l)
  { SoBaseList::copy(l) ; return *this; }
};

/**
 * Maintains a list of instances of details.
 *
 * @ingroup details
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of instances of classes derived from
 *   SoDetail.
 *
 * @SEE_ALSO
 *    SoDetail
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoDetailList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoDetailList()                      : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoDetailList(int size)              : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoDetailList(const SoDetailList &l);
  /**
   * Destructor.
   */
  ~SoDetailList()                     { truncate(0); }

  /**
   * Adds a detail to the end of the list.
   */
  void                append(SoDetail *detail)
    { SbPList::append(static_cast<void *>(detail) ); }

  /**
   * Inserts given detail in list before detail with given index.
   */
  void                insert(SoDetail *detail, int addBefore)
    { SbPList::insert(static_cast<void *>(detail), addBefore); }

  /**
   * Removes all details after one with given index, inclusive. Removed detail
   * instances are deleted.
   */
  void                truncate(int start);

  /**
   * Copies a list, making a copy of each detail instance in the list.
   */
  void                copy(const SoDetailList &l);
  /**
   * Copies a list, making a copy of each detail instance in the list.
   */
  SoDetailList &      operator =(const SoDetailList &l)
  { copy(l) ; return *this; }

  /**
   * Accesses an element of a list.
   */
  SoDetail *          operator [](int i) const
    { return ( static_cast<SoDetail*> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list, deleting the old entry first.
   */
  void                set(int i, SoDetail *detail);
};

/**
 * Maintains a list of pointers to SoPickedPoint instances.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to instances of classes derived
 *   from SoPickedPoint. It is used primarily to return information from picking with
 *   the SoRayPickAction class.
 *
 * @SEE_ALSO
 *    SoPickedPoint,
 *    SoRayPickAction
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoPickedPointList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoPickedPointList()                 : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoPickedPointList(int size)         : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoPickedPointList(const SoPickedPointList &l);
  /**
   * Destructor.
   */
  ~SoPickedPointList()                                { truncate(0); }

  /**
   * Adds a pointer to the end of the list.
   */
  void                append(SoPickedPoint *pickedPoint)
    { SbPList::append(static_cast<void *>(pickedPoint) ); }

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void                insert(SoPickedPoint *pickedPoint, int addBefore)
    { SbPList::insert(static_cast<void*>(pickedPoint), addBefore); }

  /**
   * Removes all pointers after one with given index, inclusive, deleting all
   * instances removed from the list.
   */
  void                truncate(int start);

  /**
   * Accesses an element of a list.
   */
  SoPickedPoint *     operator [](int i) const
    { return ( static_cast<SoPickedPoint *> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoPickedPoint *pickedPoint);
};

/**
 * Maintains a list of pointers to fields.
 *
 * @ingroup fields
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to instances of classes derived
 *   from SoField.
 *
 * @SEE_ALSO
 *    SoField
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoFieldList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoFieldList()                       : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoFieldList(int size)               : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoFieldList(const SoFieldList &l)   : SbPList(l)    {}
  /**
   * Destructor.
   */
  ~SoFieldList()                      { truncate(0); }

  /**
   * Adds a pointer to the end of the list.
   */
  void                append(SoField *field)
    { SbPList::append(static_cast<void*>(field)); }

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void                insert(SoField *field, int addBefore)
    { SbPList::insert(static_cast<void*>(field), addBefore); }

  /**
   * Accesses an element of a list.
   */
  SoField *           operator [](int i) const
    { return ( static_cast<SoField *> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoField *Field)
  { SbPList::set( i, Field); }

  // Internal versions of [] that do not check for bounds:
 SoINTERNAL public:
  SoField *           get(int i) const
    { return static_cast<SoField *>(SbPList::get(i)); }
};

/**
 * Maintains a list of pointers to engine outputs.
 *
 * @ingroup engines
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to SoEngineOutputs. It updates
 *   reference counts to engine outputs in the list whenever adding or removing
 *   pointers.
 *
 * @SEE_ALSO
 *    SoEngineOutput
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoEngineOutputList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoEngineOutputList()                        : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoEngineOutputList(int size)                : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoEngineOutputList(const SoEngineOutputList &l)     : SbPList(l)    {}
  /**
   * Destructor.
   */
  ~SoEngineOutputList()                       { truncate(0); }

  /**
   * Adds an engine output to the end of the list.
   */
  void                append(SoEngineOutput *engineOutput)
    { SbPList::append(static_cast<void*>(engineOutput)); }

  /**
   * Inserts the given engine output in the list before the element of the given
   * index.
   */
  void                insert(SoEngineOutput *engineOutput, int addBefore)
    { SbPList::insert(static_cast<void*>(engineOutput), addBefore); }

  /**
   * Accesses an element of a list.
   */
  SoEngineOutput *            operator [](int i) const
    { return ( static_cast<SoEngineOutput *> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoEngineOutput *engineOutput)
    { SbPList::set( i, engineOutput); }
};

/**
 * Maintains a list of pointers to the field definitions of a prototype.
 *
 * @ingroup OtherVRML2
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to instances of class
 *   SoVRMLPROTOField.
 *
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML
 *   2.0 browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *
 *   This section may reference portions of the VRML 2.0 specification that are not
 *   present in this help file. The complete VRML 2.0 spec is available at
 *   @B http://www.web3d.org @b.
 *
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoVRMLPROTOFieldList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoVRMLPROTOFieldList()                       : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoVRMLPROTOFieldList(int size)               : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoVRMLPROTOFieldList(const SoVRMLPROTOFieldList &l)   : SbPList(l)    {}
  /**
   * Destructor.
   */
  ~SoVRMLPROTOFieldList()                      { truncate(0); }

  /**
   * Accesses an element of a list.
   */
  SoVRMLPROTOField *           operator [](int i) const
    { return ( static_cast<SoVRMLPROTOField *> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  // Internal versions of [] that do not check for bounds:
 SoINTERNAL public:
  SoVRMLPROTOField *           get(int i) const
    { return static_cast<SoVRMLPROTOField *>(SbPList::get(i)); }
  // Add a VRMLPROTOField to the end of the list
  void                append(SoVRMLPROTOField *protoField)
    { SbPList::append(static_cast<void*>(protoField) ); }
};

/**
 * Maintains a list of pointers to the field definitions of an externprototype.
 *
 * @ingroup OtherVRML2
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to instances of class
 *   SoVRMLEXTERNPROTOField.
 *
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML
 *   2.0 browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *
 *   This section may reference portions of the VRML 2.0 specification that are not
 *   present in this help file. The complete VRML 2.0 spec is available at
 *   @B http://www.web3d.org @b.
 *
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoVRMLEXTERNPROTOFieldList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoVRMLEXTERNPROTOFieldList()                       : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoVRMLEXTERNPROTOFieldList(int size)               : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoVRMLEXTERNPROTOFieldList(const SoVRMLEXTERNPROTOFieldList &l)   : SbPList(l)    {}
  /**
   * Destructor.
   */
  ~SoVRMLEXTERNPROTOFieldList()                      { truncate(0); }

  /**
   * Accesses an element of a list.
   */
  SoVRMLEXTERNPROTOField *           operator [](int i) const
    { return ( static_cast<SoVRMLEXTERNPROTOField *>( (* static_cast<const SbPList *>(this)) [i] ) ); }

  // Internal versions of [] that do not check for bounds:
 SoINTERNAL public:
  SoVRMLEXTERNPROTOField *           get(int i) const
    { return static_cast<SoVRMLEXTERNPROTOField *>(SbPList::get(i)); }
  // Add a VRMLEXTERNPROTOField to the end of the list
  void                append(SoVRMLEXTERNPROTOField *externprotoField)
    { SbPList::append(static_cast<void*>(externprotoField)); }
};

/**
 * Maintains a list of pointers to VRML interpolator outputs.
 *
 * @ingroup OtherVRML2
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of pointers to SoVRMLInterpOutputs. It
 *   updates reference counts to VRML interpolator outputs in the list whenever
 *   adding or removing pointers.
 *
 * @SEE_ALSO
 *    SoVRMLInterpOutput
 *
 *
 * [OIV-WRAPPER-CUSTOM-CODE]
 */

class INVENTOR_API SoVRMLInterpOutputList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoVRMLInterpOutputList()                        : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b pointers.
   */
  SoVRMLInterpOutputList(int size)                : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoVRMLInterpOutputList(const SoVRMLInterpOutputList &l)     : SbPList(l) {}
  /**
   * Destructor.
   */
  ~SoVRMLInterpOutputList()                       { truncate(0); }

  /**
   * Adds a VRML interpolator output to the end of the list.
   */
  void                append(SoVRMLInterpOutput *interpOutput)
    { SbPList::append(static_cast<void*>(interpOutput)); }

  /**
   * Inserts the given VRML interpolator output in the list before the element of the
   * given index.
   */
  void                insert(SoVRMLInterpOutput *interpOutput, int addBefore)
    { SbPList::insert(static_cast<void*>(interpOutput), addBefore); }

  /**
   * Accesses an element of a list.
   */
  SoVRMLInterpOutput *            operator [](int i) const
    { return ( static_cast<SoVRMLInterpOutput *> ( (* static_cast<const SbPList *>(this)) [i] ) ); }

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoVRMLInterpOutput *interpOutput)
    { SbPList::set( i, interpOutput); }
};

#ifndef HIDDEN_FROM_DOC
/**
 * [OIV-WRAPPER-NO-WRAP]
 */
class INVENTOR_API SoNodeStack : public SoNodeList {
 public:
  // duplicates the top of the stack
  void push();
  // removes the top of the stack
  void pop();
  // replaces the top of the stack
  void load(const SoNode* node);
  // returns the top of the stack
  const SoNode *get() const;
};
#endif // HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////

#endif /* _SO_LISTS_ */












