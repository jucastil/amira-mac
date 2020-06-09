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


#ifndef  _SO_SHAPE_KIT_
#define  _SO_SHAPE_KIT_

#include <Inventor/nodekits/SoSeparatorKit.h>

////////////////////////////////////////////////////////////////////
//    Class: SoShapeKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoShapeKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoShapeKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         materialBinding, normalBinding,                 
//         and textureCoordinateBinding
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//              ----------------|
//              |        "topSeparator"
//         "callbackList"       |
//      ---------------------------------------------------------------
//      |       |           |     |         |    |   |               |
//  "pickStyle" |    "transform"  |         |    |   |               | 
//     "appearance"  "texture2Transform"    |    |   |               |
//                                          |    |  "localTransform" |
//                                          |    |                   |
//                                          |    |            "shapeSeparator"
//                                          |    |                   |
//                                          |    |                "shape"
//                                          |  "childList"
//          ---------------------------------                   
//          |        
// "materialBinding" "normalBinding"  
//  "textureCoordinateBinding" "shapeHints"
//  "coordinate3" "coordinate4" "normal"
//  "textureCoordinate2" "textureCoordinateFunction"
// "profileCoordinate2" "profileCoordinate3"
// "profileList" 
//

////////////////////////////////////////////////////////////////////
/**
 * Shape nodekit class.
 * 
 * @ingroup nodekits
 * 
 * @DESCRIPTION
 *   A nodekit that is used for creating a shape (i.e. geometry). SoShapeKit is
 *   derived from SoSeparatorKit and SoBaseKit, and thus inherits all the parts
 *   defined by these classes.
 *   
 *   Furthermore, SoShapeKit adds numerous parts that can be used to define a variety
 *   of @B shape @b objects, a @B localTransform @b part, and of course a
 *   @B shape @b part.
 *   
 *   All of the property nodes requires to define any of the Open Inventor shapes are
 *   included as parts in this class. Not all of these parts (nodes) are needed for
 *   any one type of shape. For example, if you set the @B shape @b part to be an
 *   SoSphere node, then it is not necessary to create a @B profileCoordinate3 @b
 *   part since it will be ignored in drawing the sphere. (And the unneeded parts
 *   will not be created, so there is no performance penalty for using this class of
 *   node.
 *   
 *   This class contains two private parts. They are both SoSeparator nodes. One of
 *   them sits just below the nodekit itself, and serves to contain all properties
 *   within this nodekit from affecting nodes that come after this nodekit. The
 *   second separator sits above the @B shape @b part, and serves to cache the shape
 *   even when the @B transform @b, @B localTransform @b, or @B appearance @b
 *   parts are changing.
 * 
 * @PARTS
 *   
 *    (SoSeparator)  shapeSeparator@BR
 *       This is a private part. The parent node of the actual shape part. It is an
 *       SoSeparator and is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoMaterialBinding)  materialBinding@BR
 *       An SoMaterialBinding node that can be used to set the material binding for the
 *       shape. This part is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoNormalBinding)  normalBinding@BR
 *       An SoNormalBinding node that can be used to set the normal binding for the
 *       shape. This part is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoTextureCoordinateBinding)  textureCoordinateBinding@BR
 *       An SoTextureCoordinateBinding node that can be used to set the texture
 *       coordinate binding for the shape. This part is NULL by default, but is created
 *       automatically if necessary. 
 * 
 *    (SoShapeHints)  shapeHints@BR
 *       An SoShapeHints node that can be used to set the shape hints for the shape. This
 *       part is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoCoordinate3)  coordinate3@BR
 *       An SoCoordinate3 node that can be used to set the 3D coordinates for a
 *       vertex-based shape. This part is NULL by default, but is created automatically
 *       if necessary. 
 * 
 *    (SoCoordinate4)  coordinate4@BR
 *       An SoCoordinate4 node that can be used to set the 4D coordinates for a NURBS
 *       shapes. This part is NULL by default, but is created automatically if necessary.
 * 
 *    (SoNormal)  normal@BR
 *       An SoNormal node that can be used to set the normal vectors for a vertex-based
 *       shape. This part is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoTextureCoordinate2)  textureCoordinate2@BR
 *       An SoTextureCoordinate2 node that can be used to set the texture coordinates for
 *       a vertex-based shape. This part is NULL by default, but is created automatically
 *       if necessary. 
 * 
 *    (SoTextureCoordinateFunction)  textureCoordinateFunction@BR
 *       An SoTextureCoordinateFunction node that can be used to set the a procedural
 *       texture coordinates function for a vertex-based shape. This part is NULL by
 *       default, but is created automatically if necessary. 
 * 
 *    (SoProfileCoordinate2)  profileCoordinate2@BR
 *       An SoProfileCoordinate2 node that can be used to set the 2D profile coordinates
 *       for a shape that uses them, (e.g., SoText3). This part is NULL by default, but
 *       is created automatically if necessary. 
 * 
 *    (SoProfileCoordinate3)  profileCoordinate3@BR
 *       An SoProfileCoordinate3 node that can be used to set the 3D profile coordinates
 *       for a shape that uses them, (e.g., SoNurbsCurve). This part is NULL by default,
 *       but is created automatically if necessary. 
 * 
 *    (SoNodeKitListPart)  profileList@BR
 *       An SoProfileList node that can be used to set the profile curve for a shape that
 *       uses them, (e.g., SoNurbsCurve). This part is NULL by default, but is created
 *       automatically if necessary. 
 * 
 *    (SoTransform)  localTransform@BR
 *       An SoTransform node that can be used to set a local transformation on the shape.
 *       This part is NULL by default, but is created automatically if necessary. 
 * 
 *    (SoShape)  shape@BR
 *       This is the part which specifies the actual shape node. This can be any node
 *       derived from SoShape By default, an SoCube is created. It is important to set
 *       all of the appropriate parts within this nodekit to suit the type of SoShape
 *       that is used. For example, if the shape part is set to an SoFaceSet, then the
 *       coordinate3 shape and probably the normal shape would be set as well. See the
 *       reference page of the shape used for details on which other nodes are necessary.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShapeKit {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching               @TD AUTO
 *       @TR boundingBoxCaching          @TD AUTO
 *       @TR renderCulling               @TD AUTO
 *       @TR pickCulling                 @TD AUTO
 *       @TR callbackList                @TD NULL
 *       @TR pickStyle                   @TD NULL
 *       @TR appearance                  @TD NULL
 *       @TR units                       @TD NULL
 *       @TR transform                   @TD NULL
 *       @TR texture2Transform           @TD NULL
 *       @TR childList                   @TD NULL
 *       @TR materialBinding             @TD NULL
 *       @TR normalBinding               @TD NULL
 *       @TR textureCoordinateBinding    @TD NULL
 *       @TR shapeHints                  @TD NULL
 *       @TR coordinate3                 @TD NULL
 *       @TR coordinate4                 @TD NULL
 *       @TR normal                      @TD NULL
 *       @TR textureCoordinate2          @TD NULL
 *       @TR textureCoordinateFunction   @TD NULL
 *       @TR profileCoordinate2          @TD NULL
 *       @TR profileCoordinate3          @TD NULL
 *       @TR profileList                 @TD NULL
 *       @TR localTransform              @TD NULL
 *       @TR shape                       @TD Cube {
 *       @TR      }                      @TD 
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS
 *    All Parts
 *    @TABLE_CATALOG_PART
 *       @TR   callbackList                  @TD   NodeKitListPart            @TD    --                           @TD   yes     
 *       @TR   pickStyle                     @TD   PickStyle                  @TD    --                           @TD   yes     
 *       @TR   appearance                    @TD   AppearanceKit              @TD    --                           @TD   yes     
 *       @TR   units                         @TD   Units                      @TD    --                           @TD   yes     
 *       @TR   transform                     @TD   Transform                  @TD    --                           @TD   yes     
 *       @TR   texture2Transform             @TD   Texture2Transform          @TD    --                           @TD   yes     
 *       @TR   childList                     @TD   NodeKitListPart            @TD    --                           @TD   yes     
 *       @TR   materialBinding               @TD   MaterialBinding            @TD    --                           @TD   yes     
 *       @TR   normalBinding                 @TD   NormalBinding              @TD    --                           @TD   yes     
 *       @TR   textureCoordinate-  Binding   @TD   TextureCoordinateBinding   @TD    --                           @TD   yes     
 *       @TR   shapeHints                    @TD   ShapeHints                 @TD    --                           @TD   yes     
 *       @TR   coordinate3                   @TD   Coordinate3                @TD    --                           @TD   yes     
 *       @TR   coordinate4                   @TD   Coordinate4                @TD    --                           @TD   yes     
 *       @TR   normal                        @TD   Normal                     @TD    --                           @TD   yes     
 *       @TR   textureCoordinate2            @TD   TextureCoordinate2         @TD    --                           @TD   yes     
 *       @TR   textureCoordinate-  Function  @TD   TextureCoordinateFunction  @TD   Texture  Coordinate  Default  @TD   yes     
 *       @TR   profileCoordinate2            @TD   ProfileCoordinate2         @TD    --                           @TD   yes     
 *       @TR   profileCoordinate3            @TD   ProfileCoordinate3         @TD    --                           @TD   yes     
 *       @TR   profileList                   @TD   NodeKitListPart            @TD    --                           @TD   yes     
 *       @TR   localTransform                @TD   Transform                  @TD    --                           @TD   yes     
 *       @TR   shape                         @TD   Shape                      @TD   Cube                          @TD   no      
 *    @TABLE_END
 * 
 *    Extra Information for List Parts from Above Table
 *    @TABLE_LIST_PART
 *       @TR   callbackList                  @TD   Separator                  @TD   Callback, EventCallback      
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
 *    SoWrapperKit,
 *    SoCone,
 *    SoCube,
 *    SoCylinder,
 *    SoIndexedNurbsCurve,
 *    SoIndexedNurbsSurface,
 *    SoNurbsCurve,
 *    SoNurbsSurface,
 *    SoShapeHints,
 *    SoSphere,
 *    SoText2,
 *    SoText3,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoShapeKit : public SoSeparatorKit {

  SO_KIT_HEADER(SoShapeKit);

  // defines fields for the new parts in the catalog
  // Binding nodes
  SO_KIT_CATALOG_ENTRY_HEADER(materialBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(normalBinding);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateBinding);

  // Shapehints
  SO_KIT_CATALOG_ENTRY_HEADER(shapeHints);

  // Coordinate and normal nodes
  SO_KIT_CATALOG_ENTRY_HEADER(coordinate3);
  SO_KIT_CATALOG_ENTRY_HEADER(coordinate4);
  SO_KIT_CATALOG_ENTRY_HEADER(normal);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinate2);
  SO_KIT_CATALOG_ENTRY_HEADER(textureCoordinateFunction);

  // Profile Stuff (for text and for nurbs)
  SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate2);
  SO_KIT_CATALOG_ENTRY_HEADER(profileCoordinate3);
  SO_KIT_CATALOG_ENTRY_HEADER(profileList);

  // Shape
  SO_KIT_CATALOG_ENTRY_HEADER(localTransform);
  SO_KIT_CATALOG_ENTRY_HEADER(shapeSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(shape);

 public:
  /**
   * Constructor.
   */
  SoShapeKit();

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:

  // Copies the contents of the given nodekit into this instance
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);

  // Called by the SoBaseKit::write() method. Calls setDefault(TRUE)
  // on the shapeSeparator. Note that this may be overriden later by basekit
  // if, for example, topSeparator lies on a path that is being written out.
  virtual void setDefaultOnNonWritingFields();

  virtual ~SoShapeKit();
};
#endif  /* _SO_SHAPE_KIT_ */

