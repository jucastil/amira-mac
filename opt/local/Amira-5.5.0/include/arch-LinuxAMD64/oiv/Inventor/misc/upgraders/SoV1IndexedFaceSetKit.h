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


#ifndef  _SO_V1_INDEXED_FACE_SET_KIT_
#define  _SO_V1_INDEXED_FACE_SET_KIT_

#include <Inventor/misc/upgraders/SoV1VertexShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1IndexedFaceSetKit
//
//    New nodes in this subclass are:
//         indexedFaceSet
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ----------------------------------------------------------------
//      |       |           |     |      |     |                    |  |
//  "pickStyle" |    "transform"  |      |     |                    |  |
//     "appearance"  "texture2Transform" |     |                    |  |
//                                       |     |                    |  |
//       ---------------------------------     |                    |  |
//       |         |                  |  |     |                    |  |
//"materialBinding"|                  |  |     |                    |"childList"
//            "normalBinding"         |  |     |                    |
//       "textureCoordinateFunctionList" |     |                    |
//                   "textureCoordinateBinding"|                    |
//                                             |                    |
//        --------------------------------------                    |
//        |            |               |       |                    |
//  "shapeHints" "coordinate3"   "normal" "textureCoordinate2"      |
//                                                               "shape"
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1IndexedFaceSetKit : public SoV1VertexShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1IndexedFaceSetKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1IndexedFaceSetKit);

 public:
  // constructor
  SoV1IndexedFaceSetKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1IndexedFaceSetKit();
};
#endif  /* _SO_V1_INDEXED_FACE_SET_KIT_ */
