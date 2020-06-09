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


#ifndef  _SO_CAMERA_KIT_
#define  _SO_CAMERA_KIT_

#include <Inventor/nodekits/SoBaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoCameraKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoCameraKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoCameraKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//        ------------------------
//        |                      |               
//     "callbackList"       "transformGroup"
//                               |
//                      ----------------
//                      |              |
//                    "transform" "camera"
//                                           
////////////////////////////////////////////////////////////////////

/**
 * Camera nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This nodekit class is used to create camera nodes that have a local
 *   transformation. SoCameraKit adds two public parts to the basic nodekit:
 *   @B transform @b and @B camera @b.
 *   
 *   The @B camera @b part is created by default as an SoPerspectiveCamera node, but
 *   may later be changed to any subclass of SoCamera.
 *   
 *   You can move the camera relative to the rest of the scene by creating and editing
 *   the @B transform @b part.
 *   
 *   SoCameraKit also adds a private part, @B transformGroup @b, which is of type
 *   SoTransformSeparator. The kit uses this part to contain the effect of
 *   @B transform @b to move only the @B camera @b, while allowing the
 *   @B camera @b to affect the rest of the scene.
 *   
 *   SoCameraKit is derived from SoBaseKit and thus also includes a
 *   @B callbackList @b part for adding callback nodes.
 * 
 * @PARTS
 *   
 *    (SoTransform)  transform@BR
 *       A transform that positions and orients the camera relative to the rest of the
 *       scene. Private parts keep the effect of the transform part localized. This part
 *       is NULL by default, but may be set to any subclass of SoTransform 
 * 
 *    (SoCamera)  camera@BR
 *       The camera node for this nodekit. The camera part is created by default as an
 *       SoPerspectiveCamera node, but may later be changed to any subclass of SoCamera.
 *       (e.g., SoPerspectiveCamera, SoOrthographicCamera). 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    CameraKit {
 *    @TABLE_FILE_FORMAT
 *       @TR callbackList   @TD NULL
 *       @TR transform      @TD NULL
 *       @TR camera         @TD PerspectiveCamera {
 *       @TR      }         @TD 
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList  @TD   NodeKitListPart  @TD    --                @TD   yes     
 *       @TR   transform     @TD   Transform        @TD    --                @TD   yes     
 *       @TR   camera        @TD   Camera           @TD   PerspectiveCamera  @TD   no      
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

class INVENTOR_API SoCameraKit : public SoBaseKit {

  SO_KIT_HEADER(SoCameraKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(transformGroup);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(camera);

 public:
  /**
   * Constructor.
   */
  SoCameraKit();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoCameraKit();
};
#endif  /* _SO_CAMERA_KIT_ */

