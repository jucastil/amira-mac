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


#ifndef  _SO_VRMLROUTE_
#define  _SO_VRMLROUTE_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLROUTE
//
//  VRMLROUTE source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLROUTE : public SoBase {

 public:

 SoINTERNAL public:

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  SoVRMLROUTE();

  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:

 protected:
  ~SoVRMLROUTE();

 private:
  // Reads stuff into instance of SoVRMLROUTE. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  // Returns new SoVRMLROUTE; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);
  static SoType      classTypeId;  

};

#endif /* _SO_VRMLROUTE_ */
