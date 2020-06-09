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


#ifndef  _SO_VRMLIMPORT_
#define  _SO_VRMLIMPORT_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLIMPORT
//
//  VRMLIMPORT source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLIMPORT : public SoBase {

 public:

 SoINTERNAL public:

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  SoVRMLIMPORT();

  static void         initClass();
  static void         exitClass();
 SoEXTENDER public:

 protected:
  ~SoVRMLIMPORT();

 private:
  // Reads stuff into instance of SoVRMLIMPORT. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  // Returns new SoVRMLIMPORT; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);
  static SoType      classTypeId;  

};

#endif /* _SO_VRMLIMPORT_ */
