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


#ifndef  _SO_VRMLTO_
#define  _SO_VRMLTO_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTO
//
//  VRMLTO source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLTO : public SoBase {

 public:

 SoINTERNAL public:

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  SoVRMLTO();

  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:

 protected:

  ~SoVRMLTO();

 private:
  // Reads stuff into instance of SoVRMLTO. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  // Returns new SoVRMLTO; called by SoType::createInstance()
  static void* createInstance(SoType* dynamicType = NULL);
  static SoType classTypeId;  

};

#endif /* _SO_VRMLTO_ */
