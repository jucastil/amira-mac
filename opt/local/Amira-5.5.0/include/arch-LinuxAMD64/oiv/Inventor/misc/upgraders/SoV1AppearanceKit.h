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


#ifndef  _SO_V1_APPEARANCE_KIT_
#define  _SO_V1_APPEARANCE_KIT_

#include <Inventor/misc/upgraders/SoV1BaseKit.h>
#include <Inventor/SoLists.h>


////////////////////////////////////////////////////////////////////
//    Class: SoV1AppearanceKit 
//
//      A parent node that manages a collection of child nodes
//      for complete description of the graphical appearance.
//
//    New nodes in this subclass are:
//         lightModel, drawStyle, material, complexity, texture2, and font
//
//    The structure of the catalog for this class is:
//
//                       this
//                         |
//   -----------------------------------------------------------------------
//   |         |           |      |        |        |             |        |
//  "label"    |    "environment" |"material" "complexity"        |     "font"
//             |                  |                    "texture2list"
//        "lightModel"     "drawStyle"        
//
//
////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTOR_API SoV1AppearanceKit : public SoV1BaseKit {

  // Define typeId and name stuff
  SO_NODE_HEADER(SoV1AppearanceKit);

  // Define catalog for children
  SO_V1_SUBKIT_CATALOG_HEADER(SoV1AppearanceKit);

 public:
  // constructor
  SoV1AppearanceKit();

  virtual SoNode *createNewNode();

  // If tryToSetPartInNewNode fails, then this routine is called.
  // It will fail if the part read from file was called "texture2List"
  // This part has been changed to a single noded part, "texture2"
  // We will use just the first child of the list and set it as the "texture2"
  // It will also print a warning.
  virtual SbBool dealWithUpgradedPart( SoBaseKit *newNode,
                                       SoNode *newPart, const SbName &newPartName );
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  static SoNodeList *getKitsWithUnusedTextureXfs();
  static SoNodeList *getUnusedTextureXfs();

 protected:

  // In the case where an SoV1Texture2 node has the translation rotation
  // scaleFactor or center field set, it will return a group containing
  // an SoTexture2Transform and an SoTexture2 node.
  // The SoV1AppearanceKit can not have a group part, so it pulls out the
  // SoTexture2 node and sets it as "transform."
  // Instead of just throwing away the SoTexture2Transform, it puts it in
  // this static variable so that other nodes can get at it.
  // For example, the SoV1GroupKit overloads the virtual function 
  // setUpNewNode to get this texture2Transform and copy its
  // values into its "texture2Transform" part.
  static SoNodeList *kitsWithUnusedTextureXfs;
  static SoNodeList *unusedTextureXfs;

  virtual ~SoV1AppearanceKit();
};

#endif  /* _SO_V1_APPEARANCE_KIT_ */
