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


#ifndef  _SO_VRMLPROFILE_
#define  _SO_VRMLPROFILE_

#include <Inventor/misc/SoBase.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoLists.h>

class SoVRMLPROFILEDef;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPROFILE
//
//  VRMLPROFILE source node.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTOR_API SoVRMLPROFILE : public SoNode {

  SO_NODE_HEADER(SoVRMLPROFILE);

 public:

 SoINTERNAL public:

  SoVRMLPROFILE();

  static void         initClass();
  static void         exitClass();
 SoEXTENDER public:
 
 protected:

  ~SoVRMLPROFILE();

 private:
};

#endif /* _SO_VRMLPROFILE_ */
