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


#ifndef  _SO_V1_PERSPECTIVE_CAMERA_KIT_
#define  _SO_V1_PERSPECTIVE_CAMERA_KIT_

#include <Inventor/misc/upgraders/SoV1CameraKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1PerspectiveCameraKit
//
//    New nodes in this subclass are:
//         perspectiveCamera
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

SoEXTENDER class INVENTOR_API SoV1PerspectiveCameraKit : public SoV1CameraKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1PerspectiveCameraKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1PerspectiveCameraKit);

 public:
  // constructor
  SoV1PerspectiveCameraKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1PerspectiveCameraKit();
};
#endif  /* _SO_V1_PERSPECTIVE_CAMERA_KIT_ */
