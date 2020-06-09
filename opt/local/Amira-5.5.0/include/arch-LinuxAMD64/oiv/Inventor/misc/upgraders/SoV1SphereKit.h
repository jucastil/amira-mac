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


#ifndef  _SO_V1_SPHERE_KIT_
#define  _SO_V1_SPHERE_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1SphereKit
//
//    New nodes in this subclass are:
//         sphere
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |         |                     |  |
//  "pickStyle" |    "transform"  |         |                     |  |
//     "appearance"  "texture2Transform"    |                     |  |
//                                          |                     |  |
//          ---------------------------------                     |  |
//          |         |                  |  |                     |"childList"
// "materialBinding"  |                  |  |                     |
//            "normalBinding"            |  |                     |
//           "textureCoordinateFunctionList"|                     |
//                            "textureCoordinateBinding"          |
//                                                             "shape"
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1SphereKit : public SoV1ShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1SphereKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1SphereKit);

 public:
  // constructor
  SoV1SphereKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1SphereKit();
};
#endif  /* _SO_V1_SPHERE_KIT_ */
