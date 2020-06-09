/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_AUDITOR_LIST_
#define _SO_AUDITOR_LIST_

#include <Inventor/SbPList.h>
#include <Inventor/misc/SoNotification.h>

class SbDict;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAuditorList
//
//  SoAuditorList class. This class maintains a list of instances that
//  audit (receive notification from) an SoBase or SoField. Each entry
//  in the list consists of a pointer to the auditor (base or field)
//  instance and a type code of type SoNotRec::Type.
//
//  The type of the auditor object pointer depends on the type code,
//  as follows:
//
//      Type code:      Auditor object pointer:
//
//      CONTAINER       The SoFieldContainer containing the field
//      PARENT          The parent node
//      SENSOR          The SoDataSensor instance
//      FIELD           The destination field instance
//      ENGINE          The destination field instance
//      INTERP          The destination field instance(VRML2 only)
//      UNDEFINED       null
//
//  Since there are two entries in the underlying SbPList for each
//  auditor, some of these methods have to do some fancy footwork.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoAuditorList : private SbPList {
 public:

  // Constructor and destructor.
  SoAuditorList();
  virtual ~SoAuditorList();

  // Adds an auditor of the given type to the list
  void append(void *auditor, SoNotRec::Type type);

  // Sets auditor and type for given index
  void set(int index, void *auditor, SoNotRec::Type type);

  // Finds an auditor in the list, returning the index or -1 if not found
  int find(void *auditor, SoNotRec::Type type) const;

  // Returns object or type for given index
  void* getObject(int index) const;
  SoNotRec::Type getType(int index) const;

  // Removes an auditor from the list
  void remove(int index);
  void remove(void *auditor, SoNotRec::Type type)
    { remove(find(auditor, type)); }

  // Returns number of auditors in list
  int getLength() const;

  // Propagates notification to all auditors in list
  void notify(SoNotList *list);

 private:
  // Propagates notification to indexed auditor
  void notify1(SoNotList *list, int index);

  // Provides fast lookup for large auditor lists
  SbDict* m_fastFindDict;
  
  int numAuds;
};

#endif /* _SO_AUDITOR_LIST_ */
