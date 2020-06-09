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


#ifndef  _SO_VRMLPROTO_
#define  _SO_VRMLPROTO_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>

class SoVRMLPROTODef;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPROTO
//
//  VRMLPROTO source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLPROTO : public SoNode {

  SO_NODE_HEADER(SoVRMLPROTO);

 public:
  SoVRMLPROTODef      *protoDef;

 SoINTERNAL public:

  SoVRMLPROTO();

  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:
 
  SoVRMLPROTODef *    getPROTODef() { return protoDef; }

 protected:

  ~SoVRMLPROTO();

 private:
  // Reads stuff into instance of SoVRMLPROTO. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

};

#endif /* _SO_VRMLPROTO_ */
