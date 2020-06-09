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


#ifndef  _SO_WRAPPER_KIT_
#define  _SO_WRAPPER_KIT_

#include <Inventor/nodekits/SoSeparatorKit.h>


////////////////////////////////////////////////////////////
// Class: SoWrapperKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoWrapperKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoWrapperKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//  A grouping in which a programmer can shove whatever
//  subgraph (s)he wants
//
//    New nodes in this subclass are:
//         contents
//
//  Adds a node before the "childList"
//  from the SoSeparatorKit class.
//
// This results in the following structure:
//
//                            this
//              ----------------|
//              |          "topSeparator"
//          "callbackList"      |
//      ----------------------------------------------------------
//      |       |           |     |          |    |              |
//  "pickStyle" |    "transform"  |          |    |              |
//     "appearance"  "texture2Transform"     |    |              |
//                                           |    |              |
//                                           |    |              |
//                                           |    |          "contents"    
//                                           |  "localTransform"
//                                           |      
//                                        "childList"
//
////////////////////////////////////////////////////////////
/**
 * Wrapper nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   SoWrapperKit is derived from SoSeparatorKit. It adds the capability to wrap an
 *   arbitrary scene graph, (non-nodekit), within an SoSeparatorKit, so that it may
 *   be used along with other shape kits in a hierarchy. There are two additional
 *   parts included in SoWrapperKit: @B localTransform @b and @B contents @b.
 *   
 *   The part @B contents @b is an SoSeparator node beneath which any arbitrary scene
 *   graph can be added. This is especially useful for importing scene graphs of
 *   unknown structure (non-nodekits) into nodekit format.
 *   
 *   Since an SoWrapperKit is a class descended from SoSeparatorKit, it may be put
 *   into another SoSeparatorKit's @B childList @b.
 * 
 * @PARTS
 *   
 *    (SoTransform)  localTransform@BR
 *       This part is an SoTransform node that is used to affect the scene graph defined
 *       in contents part. This part is NULL by default and is automatically created if
 *       requested. 
 * 
 *    (SoSeparator)  contents@BR
 *       This part is an SoSeparator node that contains a user-supplied scene graph. This
 *       scene graph can contain any nodes. This part is NULL by default and an
 *       SoSeparator is automatically created if the user asks the nodekit to build the
 *       part. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    WrapperKit {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR callbackList         @TD NULL
 *       @TR pickStyle            @TD NULL
 *       @TR appearance           @TD NULL
 *       @TR units                @TD NULL
 *       @TR transform            @TD NULL
 *       @TR texture2Transform    @TD NULL
 *       @TR childList            @TD NULL
 *       @TR localTransform       @TD NULL
 *       @TR contents             @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList       @TD   NodeKitListPart    @TD    --      @TD   yes     
 *       @TR   pickStyle          @TD   PickStyle          @TD    --      @TD   yes     
 *       @TR   appearance         @TD   AppearanceKit      @TD    --      @TD   yes     
 *       @TR   units              @TD   Units              @TD    --      @TD   yes     
 *       @TR   transform          @TD   Transform          @TD    --      @TD   yes     
 *       @TR   texture2Transform  @TD   Texture2Transform  @TD    --      @TD   yes     
 *       @TR   childList          @TD   NodeKitListPart    @TD    --      @TD   yes     
 *       @TR   localTransform     @TD   Transform          @TD    --      @TD   yes     
 *       @TR   contents           @TD   Separator          @TD    --      @TD   yes     
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList       @TD   Separator          @TD   Callback, EventCallback
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
 *    SoSceneKit,
 *    SoSeparatorKit,
 *    SoShapeKit
 * 
 * 
 */ 

class INVENTOR_API SoWrapperKit : public SoSeparatorKit {

  SO_KIT_HEADER(SoWrapperKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(contents);

 public:
  /**
   * Constructor.
   */
  SoWrapperKit();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoWrapperKit();
};

#endif  /* _SO_WRAPPER_KIT_ */

