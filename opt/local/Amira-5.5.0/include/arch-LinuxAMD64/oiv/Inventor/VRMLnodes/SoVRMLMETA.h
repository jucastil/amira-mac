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


#ifndef  _SO_VRMLMETA_
#define  _SO_VRMLMETA_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMETA
//
//  VRMLMETA source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLMETA : public SoBase {

 public:

 SoINTERNAL public:

  // Returns type identifier for SoPath class
  static SoType       getClassTypeId();

  // Returns type identifier for path instance
  virtual SoType      getTypeId() const;

  SoVRMLMETA();

  static void         initClass();
  static void         exitClass();
 SoEXTENDER public:

 protected:
  ~SoVRMLMETA();

 private:
  // Reads stuff into instance of SoVRMLMETA. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);
  // Returns new SoVRMLMETA; called by SoType::createInstance()
  static void *       createInstance(SoType* dynamicType = NULL);
  static SoType      classTypeId;  

};

#endif /* _SO_VRMLMETA_ */
