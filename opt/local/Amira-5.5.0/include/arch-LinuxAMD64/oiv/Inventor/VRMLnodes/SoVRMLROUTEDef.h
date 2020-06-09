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



#ifndef  _SO_VRMLROUTEDEF_
#define  _SO_VRMLROUTEDEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLROUTEDef
//
//  This class stores the ROUTE definitions
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLROUTEDef : public SoBase {

 public:
                                         
  SbString      fromField;
  SbString      toField;
  SbString      fromNode;
  SbString      toNode;

  // Constructor
  SoVRMLROUTEDef();

  // Returns type identifier for VRMLROUTEDef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLROUTEDef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  ~SoVRMLROUTEDef();

 protected:

 private:
  // Returns new SoVRMLROUTEDef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  // Reads stuff into instance of SoVRMLROUTEDef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLROUTEDEF_ */
