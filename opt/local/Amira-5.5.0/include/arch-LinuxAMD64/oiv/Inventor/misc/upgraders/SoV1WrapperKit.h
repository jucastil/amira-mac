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


#ifndef  _SO_V1_WRAPPER_KIT_
#define  _SO_V1_WRAPPER_KIT_

#include <Inventor/misc/upgraders/SoV1GroupKit.h>


////////////////////////////////////////////////////////////
// Class: Wrapper
//
//  A grouping in which a programmer can shove whatever
//  subgraph (s)he wants
//
//    New nodes in this subclass are:
//         contents
//
//  Adds a node before the "childList"
//  from the SoV1GroupKit class.
//
// This results in the following structure:
//
//                            this
//        |---------------------|
//     "label"     |      "topSeparator"
//            "callbackList"    |
//      ----------------------------------------------------------
//      |       |           |     |                         |    |
//  "pickStyle" |    "transform"  |                         |    |
//     "appearance"  "texture2Transform"                    |    |
//                                                          |    |
//                                                          |    |
//                                                          |    |
//                                                          |  "childList"
//                                                          |      
//                                                       "contents"
//
////////////////////////////////////////////////////////////
SoEXTENDER class INVENTOR_API SoV1WrapperKit : public SoV1GroupKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1WrapperKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1WrapperKit);

 public:
  // constructor
  SoV1WrapperKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1WrapperKit();
};

#endif  /* _SO_V1_WRAPPER_KIT_ */
