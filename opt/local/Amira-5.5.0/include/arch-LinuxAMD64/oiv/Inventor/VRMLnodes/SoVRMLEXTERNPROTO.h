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


#ifndef  _SO_VRMLEXTERNPROTO_
#define  _SO_VRMLEXTERNPROTO_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLEXTERNPROTO
//
//  VRMLEXTERNPROTO source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLEXTERNPROTO : public SoNode {

  SO_NODE_HEADER(SoVRMLEXTERNPROTO);

 public:

 SoINTERNAL public:

  SoVRMLPROTODef      *protoDef;

  SoVRMLEXTERNPROTO();

  static void         initClass();
  static void         exitClass();

 SoEXTENDER public:

 protected:

  ~SoVRMLEXTERNPROTO();

 private:
  // Reads stuff into instance of SoVRMLEXTERNPROTO. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

};

#endif /* _SO_VRMLEXTERNPROTO_ */
