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


#ifndef  _SO_V1_NURB_SURFACE_KIT_
#define  _SO_V1_NURB_SURFACE_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1NurbsSurfaceKit
//
//    New nodes in this subclass are:
//        coordinate3 
//        coordinate4 
//        textureCoordinate2 
//        profileCoordinate2 
//        profileCoordinate3 
//        profileList ( a list composed of SoProfile nodes )
//        nurbsSurface 
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      -----------------------------------------------------------------
//      |       |           |     |         |                   |   |    |
//  "pickStyle" |    "transform"  |         |                   |   |    |
//     "appearance"  "texture2Transform"    |                   |   |    |
//                                          |                   |   |    |
//          ---------------------------------                   |   |    |
//          |         |                  |  |                   |   |    |
// "materialBinding"  |                  |  |                   |   |    |
//            "normalBinding"            |  |                   |   |    |
//           "textureCoordinateFunctionList"|                   |   |    |
//                            "textureCoordinateBinding"        |   |    |
//                                                              |   |    |
//      ---------------------------------------------------------   |    |
//      |        |         |          |      |      |               |    |
// "coordinate3" |         |          |      |      |               |    |
//         "coordinate4"   |          |      |      |               |"childList"
//              "textureCoordinate2"  |      |      |               |
//                       "profileCoordinate2"|      |               |
//                              "profileCoordinate3"|               |
//                                        "profileList"             |
//                                                               "shape"
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1NurbsSurfaceKit : public SoV1ShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1NurbsSurfaceKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1NurbsSurfaceKit);

 public:
  // constructor
  SoV1NurbsSurfaceKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1NurbsSurfaceKit();
};
#endif  /* _SO_V1_NURB_SURFACE_KIT_ */