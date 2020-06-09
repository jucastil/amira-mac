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


#ifndef  _SO_V1_SCENE_KIT_
#define  _SO_V1_SCENE_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1SceneKit
//
//    New nodes in this subclass are:
//         cameraList, lightList, and childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//              -----------------
//              |               |
//           "label       "topSeparator"
//                              |
//           --------------------------------------------------
//           |               |              |                 |
//      "cameraList"    "lightList"   "childList"     "manipulatorList"
//
////////////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoV1SceneKit : public SoV1BaseKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1SceneKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1SceneKit);

 public:
  // constructor
  SoV1SceneKit();

  // sets the switch node in 'cameraList' to be the number given
  int  getCameraNumber();
  void setCameraNumber(int camNum );

  virtual SoNode *createNewNode();
    
  // If tryToSetPartInNewNode fails, then this routine is called.
  // It will fail for the parts:
  // "manipulatorList"
  // This routine will simply discard those parts with a warning, but
  // no error.
  virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
                                       SoNode *newPart, const SbName &newPartName );
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1SceneKit();
};
#endif  /* _SO_V1_SCENE_KIT_ */
