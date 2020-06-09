/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_V1_LIGHT_KIT_
#define  _SO_V1_LIGHT_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1LightKit
//
//    New nodes in this subclass are:
//         icon, which can be any shape node.
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//     ------------------------------------------------------------------
//     |     |         |               |       |                       |
// "label"   |     "appearance"   "transform"  |                       |
//      "callbackList"                         |                   "childList"
//                                          "light"
//                                           
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1LightKit : public SoV1BaseKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1LightKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1LightKit);

 public:
  // constructor
  SoV1LightKit();

  virtual SoNode *createNewNode();
    
  // If tryToSetPartInNewNode fails, then this routine is called.
  // It will fail for the parts:
  // "appearance" and "childList."
  // This routine will simply discard those parts with a warning, but
  // no error.
  virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
                                       SoNode *newPart, const SbName &newPartName );

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1LightKit();
};
#endif  /* _SO_V1_LIGHT_KIT_ */
