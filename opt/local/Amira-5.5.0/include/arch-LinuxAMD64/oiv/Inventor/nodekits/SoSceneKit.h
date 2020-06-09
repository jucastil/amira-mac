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


#ifndef  _SO_SCENE_KIT_
#define  _SO_SCENE_KIT_

#include <Inventor/nodekits/SoBaseKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoSceneKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoSceneKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoSceneKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         cameraList, lightList, and childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//                              |
//              -----------------
//              |               |
//           "callbackList" "topSeparator"
//                              |
//           --------------------------------
//           |               |              |        
//      "cameraList"    "lightList"   "childList"     
//
////////////////////////////////////////////////////////////////////
/**
 * Scene nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   This nodekit is used to organize camera, (SoCameraKit), light, (SoLightKit), and
 *   object, (SoShapeKit, SoSeparatorKit, and SoWrapperKit) nodekits into a scene. A
 *   scene is composed of a list of cameras, a list of lights, and a list of
 *   children. There are three parts created by this nodekit: @B cameraList @b,
 *   @B lightList @b, and @B childList @b.
 *   
 *   The @B cameraList @b part is a @B list part @b of SoCameraKit nodes. The list
 *   itself is an SoNodeKitListPart, and since only one camera can be active at a
 *   time, the @B container @b of the @B list part @b is an SoSwitch node. Use
 *   setCameraNumber(), and the scene kit will set the switch to make that
 *   camera active.
 *   
 *   The @B lightList @b part is a list of SoLightKit nodes. The @B lightList @b is
 *   used to illuminate the objects contained in the @B childList @b part.
 *   
 *   The @B childList @b part contains a set of SoSeparatorKit nodes. You can add any
 *   kind of SoSeparatorKit to this list, including SoShapeKit and SoWrapperKit.
 *   Since each SoSeparatorKit in turn contains a @B childList @b, this part is used
 *   to describe a hierarchical scene. (See the reference page for SoSeparatorKit).
 *   All members of @B childList @b are lit by the lights in @B lightList @b and
 *   rendered by the active camera in @B cameraList @b.
 * 
 * @PARTS
 *   
 *    (SoNodeKitListPart)  cameraList@BR
 *       This part is an SoNodeKitListPart It has a container that is an SoSwitch node.
 *       The list may contain only SoCameraKit nodekits. The active child of the SoSwitch
 *       is the active camera. This part is NULL by default, but is automatically created
 *       whenever you add a camera, as with setPart("cameraList[0]", myNewCamera) . 
 * 
 *    (SoNodeKitListPart)  lightList@BR
 *       This part is an SoNodeKitListPart that uses an defines an SoGroup as its
 *       container The list may contain only SoLightKit nodekits. Add SoLightKits to this
 *       list and they will light the members of the childList of this SoSceneKit. This
 *       part is NULL by default, but is automatically created when you add a light. 
 * 
 *    (SoNodeKitListPart)  childList@BR
 *       This part is an SoNodeKitListPart that uses an SoGroup for its container. The
 *       list may contain only SoSeparatorKit nodekits or nodekits derived from
 *       SoSeparatorKit (e.g., SoShapeKit and SoWrapperKit). These children represent the
 *       objects in the scene. This part is NULL by default, but is automatically created
 *       whenever you add a child to the childList. Also, when asked to build a member of
 *       the childList, the scenekit will build an SoShapeKit by default. So if the
 *       childList part is NULL, and you call: getPart("childList[0]", TRUE) . the scene
 *       kit will create the childList and add an SoShapeKit as the new element in the
 *       list. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    SceneKit {
 *    @TABLE_FILE_FORMAT
 *       @TR callbackList @TD NULL
 *       @TR cameraList NodeKitListPart {
 *       @TR                               @TD containerTypeName     @TD "Switch"
 *       @TR                               @TD childTypeNames        @TD "CameraKit"
 *       @TR                               @TD containerNode         @TD Switch {
 *       @TR                               @TD                       @TD       @TD whichChild 0 
 *       @TR                               @TD                       @TD       @TD CameraKit {
 *       @TR                               @TD                       @TD       @TD    @TD camera       PerspectiveCamera {}
 *       @TR                               @TD                       @TD       @TD }
 *       @TR                               @TD                       @TD }
 *       @TR }                     
 *       @TR lightList    @TD NULL
 *       @TR childList    @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList  @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   cameraList    @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   lightList     @TD   NodeKitListPart  @TD    --      @TD   yes     
 *       @TR   childList     @TD   NodeKitListPart  @TD    --      @TD   yes     
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
 *    SoLightKit,
 *    SoNodeKit,
 *    SoNodeKitDetail,
 *    SoNodeKitListPart,
 *    SoNodeKitPath,
 *    SoNodekitCatalog,
 *    SoSeparatorKit,
 *    SoShapeKit,
 *    SoWrapperKit
 * 
 * 
 */ 

class INVENTOR_API SoSceneKit : public SoBaseKit {

  SO_KIT_HEADER(SoSceneKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(cameraList);
  SO_KIT_CATALOG_ENTRY_HEADER(lightList);
  SO_KIT_CATALOG_ENTRY_HEADER(childList);

 public:
  /**
   * Constructor.
   */
  SoSceneKit();

  /**
   * Gets current camera index. This index refers to which child is active
   * in the @B cameraList @b part (SoSwitch node).
   */
  int  getCameraNumber();
  /**
   * Sets current camera index. This index refers to which child is active
   * in the @B cameraList @b part (SoSwitch node).
   */
  void setCameraNumber(int camNum );

  // Overrides default method on SoNode
  virtual SbBool affectsState() const;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoSceneKit();

};
#endif  /* _SO_SCENE_KIT_ */

