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


#ifndef  _SO_V1_INDEXED_NURB_CURVE_KIT_
#define  _SO_V1_INDEXED_NURB_CURVE_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1IndexedNurbsCurveKit
//
//    New nodes in this subclass are:
//         coordinate3, coordinate4, textureCoordinate2, and indexedNurbsCurve
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
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
//          ------------------------------------                    |
//          |            |                  |                       |
//     "coordinate3" "coordinate4"  "textureCoordinate2"         "shape"
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1IndexedNurbsCurveKit : public SoV1ShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1IndexedNurbsCurveKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1IndexedNurbsCurveKit);

 public:
  // constructor
  SoV1IndexedNurbsCurveKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1IndexedNurbsCurveKit();
};
#endif  /* _SO_V1_INDEXED_NURB_CURVE_KIT_ */
