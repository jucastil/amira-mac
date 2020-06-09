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


#ifndef  _SO_V1_VERTEX_SHAPE_KIT_
#define  _SO_V1_VERTEX_SHAPE_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1VertexShapeKit
//
//    New nodes in this subclass are:
//         shapeHints, coordinate3, normal, and textureCoordinate2
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |      |     |         |            |
//  "pickStyle" |    "transform"  |      |     |         |            |
//     "appearance"  "texture2Transform" |     |         |            | 
//                                       |     |         |            |
//                                       |     |         |            |
//       ---------------------------------     |         |            |
//       |         |                  |  |     |         |         "childList"
//"materialBinding"|                  |  |     |         |       
//            "normalBinding"         |  |     |         |
//       "textureCoordinateFunctionList" |     |      "shape" 
//                   "textureCoordinateBinding"|      
//                                             |
//        --------------------------------------
//        |            |               |       |
//  "shapeHints" "coordinate3"   "normal" "textureCoordinate2"
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1VertexShapeKit : public SoV1ShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1VertexShapeKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1VertexShapeKit);

 public:
  // constructor
  SoV1VertexShapeKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1VertexShapeKit();
};
#endif  /* _SO_V1_VERTEX_SHAPE_KIT_ */
