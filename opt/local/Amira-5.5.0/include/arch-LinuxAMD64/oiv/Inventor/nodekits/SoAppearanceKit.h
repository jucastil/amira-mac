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


#ifndef  _SO_APPEARANCE_KIT_
#define  _SO_APPEARANCE_KIT_

#include <Inventor/nodekits/SoBaseKit.h>


////////////////////////////////////////////////////////////////////
//    Class: SoAppearanceKit 
//
//      A parent node that manages a collection of child nodes
//      for complete description of the graphical appearance.
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoAppearanceKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoAppearanceKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    The structure of the catalog for this class is:
//
//                       this
//                         |
//   -----------------------------------------------------------------------
//   |            |             |      |        |        |             |
//  "callbackList"|"environment"|"material" "complexity" |           "font"
//                |             |                      "texture2" 
//        "lightModel"     "drawStyle"                            
//
////////////////////////////////////////////////////////////////////

/**
 * Appearance nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   The SoAppearanceKit is used to create a group of property nodes that will be
 *   used to affect subsequent @B shape @b nodes or nodekits in the scene graph.
 *   
 *   This nodekit defines seven new parts: @B lightModel @b, @B environment @b,
 *   @B drawStyle @b, @B material @b, @B complexity @b, @B texture2 @b, and
 *   @B font @b. Note that it does not include @B binding @b nodes such as
 *   SoMaterialBinding.
 *   
 *   SoAppearanceKit is derived from SoBaseKit and thus also includes a
 *   @B callbackList @b part for adding callback nodes.
 * 
 * @PARTS
 *   
 *    (SoLightModel)  lightModel@BR
 *       An SoLightModel node that affects any shapes that follow this nodekit in the
 *       scene graph. This part is NULL by default. 
 * 
 *    (SoEnvironment)  environment@BR
 *       An SoEnvironment node that affects any nodes that follow this nodekit in the
 *       scene graph. This part is NULL by default. 
 * 
 *    (SoDrawStyle)  drawStyle@BR
 *       An SoDrawStyle node that affects any shapes that follow this nodekit in the
 *       scene graph. This part is NULL by default. 
 * 
 *    (SoMaterial)  material@BR
 *       An SoMaterial node that affects any shapes that follow this nodekit in the scene
 *       graph. This part is NULL by default. 
 * 
 *    (SoComplexity)  complexity@BR
 *       An SoComplexity node that affects any shapes that follow this nodekit in the
 *       scene graph. This part is NULL by default. 
 * 
 *    (SoTexture2)  texture2@BR
 *       An SoTexture2 node that affects any shapes that follow this nodekit in the scene
 *       graph. This part is NULL by default. 
 * 
 *    (SoFont)  font@BR
 *       An SoFont node that affects any text nodes that follow this nodekit in the scene
 *       graph. This part is NULL by default. 
 * 
 * 
 * @NOTES
 *    Note that SoSeparatorKit includes an SoAppearanceKit as a part.
 * 
 * @FILE_FORMAT_DEFAULT
 *    AppearanceKit {
 *    @TABLE_FILE_FORMAT
 *       @TR callbackList   @TD NULL
 *       @TR lightModel     @TD NULL
 *       @TR environment    @TD NULL
 *       @TR drawStyle      @TD NULL
 *       @TR material       @TD NULL
 *       @TR complexity     @TD NULL
 *       @TR texture2       @TD NULL
 *       @TR font           @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   lightModel    @TD   LightModel       @TD    --      @TD   yes     
 *       @TR   environment   @TD   Environment      @TD    --      @TD   yes     
 *       @TR   drawStyle     @TD   DrawStyle        @TD    --      @TD   yes     
 *       @TR   material      @TD   Material         @TD    --      @TD   yes     
 *       @TR   complexity    @TD   Complexity       @TD    --      @TD   yes     
 *       @TR   texture2      @TD   Texture2         @TD    --      @TD   yes     
 *       @TR   font          @TD   Font             @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoBaseKit,
 *    SoCameraKit,
 *    SoLightKit,
 *    SoNodeKit,
 *    SoNodeKitDetail,
 *    SoNodeKitListPart,
 *    SoNodeKitPath,
 *    SoNodekitCatalog,
 *    SoSceneKit,
 *    SoSeparatorKit,
 *    SoShapeKit,
 *    SoWrapperKit
 * 
 * 
 */ 

class INVENTOR_API SoAppearanceKit : public SoBaseKit {

  SO_KIT_HEADER(SoAppearanceKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(lightModel);
  SO_KIT_CATALOG_ENTRY_HEADER(environment);
  SO_KIT_CATALOG_ENTRY_HEADER(drawStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(material);
  SO_KIT_CATALOG_ENTRY_HEADER(complexity);
  SO_KIT_CATALOG_ENTRY_HEADER(texture2);
  SO_KIT_CATALOG_ENTRY_HEADER(font);

 public:
  /**
   * Constructor.
   */
  SoAppearanceKit();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoAppearanceKit();
};

#endif  /* _SO_APPEARANCE_KIT_ */

