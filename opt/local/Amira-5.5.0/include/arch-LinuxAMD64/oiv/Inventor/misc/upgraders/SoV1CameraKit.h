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


#ifndef  _SO_V1_CAMERA_KIT_
#define  _SO_V1_CAMERA_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1CameraKit
//
//    New nodes in this subclass are:
//         icon
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//        -------------------------------------------------------------
//        |        |           |       |    |                         |
//     "label"     |      "appearance" |"transform"                   |
//            "callbackList"           |                            "childList"
//                                  "camera"
//                                           
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1CameraKit : public SoV1BaseKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1CameraKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1CameraKit);

 public:
  // constructor
  SoV1CameraKit();

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
  virtual ~SoV1CameraKit();
};
#endif  /* _SO_V1_CAMERA_KIT_ */
