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


#ifndef  _SO_V1_TEXT2_KIT_
#define  _SO_V1_TEXT2_KIT_

#include <Inventor/misc/upgraders/SoV1ShapeKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1Text2Kit
//
//    New nodes in this subclass are:
//         text2
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
SoEXTENDER class INVENTOR_API SoV1Text2Kit : public SoV1ShapeKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1Text2Kit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1Text2Kit);

 public:
  // constructor
  SoV1Text2Kit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1Text2Kit();
};
#endif  /* _SO_V1_TEXT2_KIT_ */
