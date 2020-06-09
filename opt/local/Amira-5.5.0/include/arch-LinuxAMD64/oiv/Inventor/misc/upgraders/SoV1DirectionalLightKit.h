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


#ifndef  _SO_V1_DIRECTIONAL_LIGHT_KIT_
#define  _SO_V1_DIRECTIONAL_LIGHT_KIT_

#include <Inventor/misc/upgraders/SoV1LightKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1DirectionalLightKit
//
//    New nodes in this subclass are:
//         directionalLight
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//     ------------------------------------------------------------------
//     |     |         |               |       |                       |
// "label"   |     "appearance"   "transform"  |                       |
//      "callbackList"                         |                   "childList"
//                                          "light"
//                                           
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1DirectionalLightKit : public SoV1LightKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1DirectionalLightKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1DirectionalLightKit);

 public:
  // constructor
  SoV1DirectionalLightKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1DirectionalLightKit();
};
#endif  /* _SO_V1_DIRECTIONAL_LIGHT_KIT_ */
