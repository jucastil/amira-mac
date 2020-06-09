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



#ifndef  _SO_VRMLEXPORTDEF_
#define  _SO_VRMLEXPORTDEF_

#include <Inventor/misc/SoBase.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLEXPORTDef
//
//  This class stores the EXPORT definitions
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLEXPORTDef : public SoBase {

 public:
                                         
  SbString      fromNode;
  SbString      asNode;

  // Constructor
  SoVRMLEXPORTDef();

  // Returns type identifier for VRMLEXPORTDef instance
  virtual SoType      getTypeId() const;

  // Returns type identifier for SoVRMLEXPORTDef class
  static SoType       getClassTypeId();

 SoEXTENDER public:

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();


 protected:
  ~SoVRMLEXPORTDef();

 private:
  // Returns new SoVRMLEXPORTDef; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);

  // Reads stuff into instance of SoVRMLEXPORTDef. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  static SoType      classTypeId;    // TypeId of paths

};

#endif /* _SO_VRMLEXPORTDEF_ */
