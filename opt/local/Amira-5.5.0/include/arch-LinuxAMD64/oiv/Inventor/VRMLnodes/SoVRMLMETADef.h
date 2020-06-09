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



#ifndef  _SO_VRMLMETADEF_
#define  _SO_VRMLMETADEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMETADef
//
//  This class stores the META definitions
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLMETADef : public SoBase {

 public:
                                         
  SbString      key;
  SbString      value;

  // Constructor
  SoVRMLMETADef();

  // Returns type identifier for VRMLMETADef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLMETADef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 protected:
  ~SoVRMLMETADef();

 private:
  // Returns new SoVRMLMETADef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  // Reads stuff into instance of SoVRMLMETADef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLMETADEF_ */
