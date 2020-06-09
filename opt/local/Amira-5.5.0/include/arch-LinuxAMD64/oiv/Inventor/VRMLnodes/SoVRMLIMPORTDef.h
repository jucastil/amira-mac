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



#ifndef  _SO_VRMLIMPORTDEF_
#define  _SO_VRMLIMPORTDEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIMPORTDef
//
//  This class stores the IMPORT definitions
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLIMPORTDef : public SoBase {

 public:
                                         
  SbString      fromField;
  SbString      fromNode;
  SbString      asNode;

  // Constructor
  SoVRMLIMPORTDef();

  // Returns type identifier for VRMLIMPORTDef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLIMPORTDef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
 protected:
  ~SoVRMLIMPORTDef();

 private:
  // Returns new SoVRMLIMPORTDef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  // Reads stuff into instance of SoVRMLIMPORTDef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLIMPORTDEF_ */
