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


#ifndef  _SO_V1_SHAPE_KIT_
#define  _SO_V1_SHAPE_KIT_

#include <Inventor/misc/upgraders/SoV1GroupKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1ShapeKit
//
//    New nodes in this subclass are:
//         materialBinding, normalBinding,                 
//         and textureCoordinateBinding
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |         |          |              |
//  "pickStyle" |    "transform"  |         |          |              | 
//     "appearance"  "texture2Transform"    |          |              |
//                                          |          |              |
//                                          |          |              |
//                                          |          |              |
//                                          |          |           "childList"
//                                          |       "shape"
//          ---------------------------------                   
//          |         |                  |  |                   
// "materialBinding"  |                  |  |                     
//            "normalBinding"            |  |                     
//           "textureCoordinateFunctionList"|                     
//                            "textureCoordinateBinding"          
//
////////////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoV1ShapeKit : public SoV1GroupKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1ShapeKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1ShapeKit);

 public:
  // constructor
  SoV1ShapeKit();

  virtual SoNode *createNewNode();
    
  // If tryToSetPartInNewNode fails, then this routine is called.
  // It will fail for the parts:
  // "textureCoordinateFunctionList".
  // This part has been changed to "textureCoordinateFunction" which is not
  // a list.  This routine will take the last function from the list
  // and set it as the part "textureCoordinateFunnction" in the new node.
  // It will also print a warning.
  virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
                                       SoNode *newPart, const SbName &newPartName );
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1ShapeKit();
};
#endif  /* _SO_V1_SHAPE_KIT_ */
