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


#ifndef  _SO_VRMLCOMPONENT_
#define  _SO_VRMLCOMPONENT_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLCOMPONENT
//
//  VRMLCOMPONENT source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLCOMPONENT : public SoBase {

 public:

 SoINTERNAL public:

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  SoVRMLCOMPONENT();

  static void         initClass();
  static void         exitClass();


 SoEXTENDER public:

 protected:
  ~SoVRMLCOMPONENT();

 private:
  // Reads stuff into instance of SoVRMLCOMPONENT. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  // Returns new SoVRMLCOMPONENT; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);
  static SoType      classTypeId;  

};

#endif /* _SO_VRMLCOMPONENT_ */
