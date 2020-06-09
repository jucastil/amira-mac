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


#ifndef  _SO_V1_SPOT_LIGHT_KIT_
#define  _SO_V1_SPOT_LIGHT_KIT_

#include <Inventor/misc/upgraders/SoV1LightKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoV1SpotLightKit
//
//    New nodes in this subclass are:
//         spotLight
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                               |
//     ------------------------------------------------------------------
//     |     |         |               |       |                       |
// "label"   |     "appearance"   "transform"  |                       |
//      "callbackList"                         |                   "childList"
//                                          "light"
//                                           
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1SpotLightKit : public SoV1LightKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1SpotLightKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1SpotLightKit);

 public:
  // constructor
  SoV1SpotLightKit();

  virtual SoNode *createNewNode();
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoV1SpotLightKit();
};
#endif  /* _SO_V1_SPOT_LIGHT_KIT_ */
