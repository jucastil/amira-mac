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



#ifndef  _SO_VRMLCOMPONENTDEF_
#define  _SO_VRMLCOMPONENTDEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCOMPONENTDef
//
//  This class stores the COMPONENT definitions
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLCOMPONENTDef : public SoBase {

 public:
                                         
  SbString      name;
  int32_t       level;

  // Constructor
  SoVRMLCOMPONENTDef();

  // Returns type identifier for VRMLCOMPONENTDef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLCOMPONENTDef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();


 protected:
  ~SoVRMLCOMPONENTDef();

 private:
  // Returns new SoVRMLCOMPONENTDef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  // Reads stuff into instance of SoVRMLCOMPONENTDef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLCOMPONENTDEF_ */
