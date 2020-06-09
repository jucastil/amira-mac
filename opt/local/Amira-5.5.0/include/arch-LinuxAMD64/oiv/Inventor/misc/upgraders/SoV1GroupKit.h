/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_V1_GROUP_KIT_
#define  _SO_V1_GROUP_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>
#include <Inventor/misc/upgraders/SoV1AppearanceKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1GroupKit
//
//    New nodes in this subclass are:
//         callbackList, topSeparator, pickStyle, appearance,                 
//          transform, texture2Transform, 
//          childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ---------------------------------------------------------------
//      |       |           |     |                                   |
//  "pickStyle" |    "transform"  |                                   |
//     "appearance"  "texture2Transform"                              |
//                                                                    |
//                                                                    | 
//                                                              "childList"
//
////////////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoV1GroupKit : public SoV1BaseKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1GroupKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1GroupKit);

 public:
  // constructor
  SoV1GroupKit();

  virtual SoNode *createNewNode();

  // Overload this function. After SoV1BaseKit is done, see if there
  // is information we need in the nodelist:
  // SoV1AppearanceKit::unusedTextureXfs.
  // If so, move this into our "texture2Transform" part.
  // Need to do this because Inventor 1.0 texture had fields for 
  // texture transforms, but new one does not. So SoV1AppearanceKit just
  // stores this info. We retrieve it and make use of it.
  virtual void setUpNewNode(SoNode *newNode);
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1GroupKit();
};
#endif  /* _SO_V1_GROUP_KIT_ */
