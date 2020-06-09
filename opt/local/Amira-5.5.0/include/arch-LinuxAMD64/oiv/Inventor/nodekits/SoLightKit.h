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


#ifndef  _SO_LIGHT_KIT_
#define  _SO_LIGHT_KIT_

#include <Inventor/nodekits/SoBaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoLightKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoLightKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoLightKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//     --------------------------
//     |                        |         
//     |                    "transformGroup"
//"callbackList"                |
//               ---------------------------------
//               |               |               |
//              "transform"  "light"       "iconSeparator"
//                                               |
//                                            "icon"
//                                           
////////////////////////////////////////////////////////////////////

/**
 * Light nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This nodekit class is used to create light nodes that have a local
 *   transformation and a geometry icon to represent the light source. SoLightKit
 *   adds three public parts to the basic nodekit: @B transform @b, @B light @b,
 *   and @B icon @b.
 *   
 *   SoLightKit creates an SoDirectionalLight as the @B light @b part by default -
 *   all other parts are NULL at creation.
 *   
 *   You can move the light relative to the rest of the scene by creating and editing
 *   the @B transform @b part.
 *   
 *   You can add a geometrical representation for the light by setting the @B icon @b
 *   part to be any scene graph you like.
 *   
 *   SoLightKit also adds two private parts. An SoTransformSeparator contains the
 *   effect of @B transform @b to move only the @B light @b and @B icon @b, while
 *   allowing the @B light @b to illuminate the rest of the scene. The second
 *   private part is an SoSeparator, which keeps property nodes within the
 *   @B icon @b geometry from affecting the rest of the scene. It also serves to
 *   cache the @B icon @b even when the @B light @b or @B transform @b is
 *   changing.
 *   
 *   SoLightKit is derived from SoBaseKit and thus also includes a @B callbackList @b
 *   part for adding callback nodes.
 * 
 * @PARTS
 *   
 *    (SoTransform)  transform@BR
 *       This part positions and orients the light and icon relative to the rest of the
 *       scene. Its effect is kept local to this nodekit by a private part of type
 *       SoTransformSeparator. The transform part is NULL by default. If you ask for
 *       transform using getPart(), an SoTransform will be returned. But you may set the
 *       part to be any subclass of SoTransform. For example, set the transform to be an
 *       SoDragPointManip and the light to be an SoPointLight. Then you can move the
 *       light by dragging the manipulator with the mouse. 
 * 
 *    (SoLight)  light@BR
 *       The light node for this nodekit. This can be set to any node derived from
 *       SoLight. An SoDirectionalLight is created by default, and it is also the type of
 *       light returned when the you request that the nodekit build a light for you. 
 * 
 *    (SoNode)  icon@BR
 *       This part is a user-supplied scene graph that represents the light source. It is
 *       NULL by default - an SoCube is created by the lightkit when a method requires it
 *       to build the part itself. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    LightKit {
 *    @TABLE_FILE_FORMAT
 *       @TR callbackList   @TD NULL
 *       @TR transform      @TD NULL
 *       @TR light          @TD DirectionalLight {
 *       @TR                @TD }
 *       @TR icon           @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList  @TD   NodeKitListPart  @TD    --               @TD   yes     
 *       @TR   transform     @TD   Transform        @TD    --               @TD   yes     
 *       @TR   light         @TD   Light            @TD   DirectionalLight  @TD   no      
 *       @TR   icon          @TD   Node             @TD   Cube              @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList  @TD   Separator        @TD   Callback, EventCallback
 *    @TABLE_END
 * 
 * @SEE_ALSO
 *    SoAppearanceKit,
 *    SoBaseKit,
 *    SoCameraKit,
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

class INVENTOR_API SoLightKit : public SoBaseKit {

  SO_KIT_HEADER(SoLightKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(transformGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(light);
  SO_KIT_CATALOG_ENTRY_HEADER(iconSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(icon);

 public:
  /**
   * Constructor.
   */
  SoLightKit();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoLightKit();
};
#endif  /* _SO_LIGHT_KIT_ */

