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



#ifndef  _SO_VRMLISREF_
#define  _SO_VRMLISREF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLISRef
//
//  This class stores the IS relationships for the fields
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLISRef : public SoBase {

 public:

  // Constructor
  SoVRMLISRef();

  // Returns type identifier for VRMLISRef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLISRef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:

  int              ISIndex;
  SbString         interfaceName;
  SbBool           isField;

  static void         initClass();
  static void         exitClass();

  // Returns new SoVRMLISRef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  SbBool    isInFieldList() { return isField; }
  // Reads stuff into instance of SoVRMLISRef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

 protected:
  virtual ~SoVRMLISRef();

 private:


  static SoType      classTypeId;    // TypeId 
};

#endif /* _SO_VRMLISREF_ */
