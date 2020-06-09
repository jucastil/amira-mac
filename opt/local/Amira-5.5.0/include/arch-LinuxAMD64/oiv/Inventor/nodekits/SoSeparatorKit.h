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


#ifndef  _SO_SEPARATOR_KIT_
#define  _SO_SEPARATOR_KIT_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoFieldSensor.h>

////////////////////////////////////////////////////////////////////
//    Class: SoSeparatorKit
//
// NOTE TO DEVELOPERS:
//     For info about the structure of SoSeparatorKit:
//     [1] compile: /usr/share/src/Inventor/samples/ivNodeKitStructure
//     [2] type:    ivNodeKitStructure SoSeparatorKit.
//     [3] The program prints a diagram of the scene graph and a table with 
//         information about each part.
//
//    New nodes in this subclass are:
//         callbackList, topSeparator, pickStyle, appearance,                 
//          transform, texture2Transform, 
//          childList
//
//      A parent node that manages a collection of child nodes 
//      into a unit with the following structure:
//
//                            this
//            ------------------|
//            |          "topSeparator"
//         "callbackList"       |
//      ---------------------------------------------------------------
//      |       |       |           |     |                           |
//  "pickStyle" |    "units" "transform"  |                           |
//     "appearance"  "texture2Transform"                              |
//                                                                    |
//                                                                    | 
//                                                              "childList"
//
////////////////////////////////////////////////////////////////////

#ifdef OIV_NET_DOC
/**
* Separator nodekit class.
* 
* @ingroup nodekits
* 
* @DESCRIPTION
*   A nodekit that is used for creating nodekit hierarchies. SoSeparatorKit contains
*   a @B transform @b part, a @B childList @b part, and a few others in its
*   catalog. The @B transform @b part (an SoTransform node) affects all of the
*   children in the childList. Each of these children must be an SoSeparatorKit or
*   from a class that is derived from SoSeparatorKit (e.g., SoShapeKit and
*   SoWrapperKit). Since all members of the @B childList @b are in turn
*   SoSeparatorKits, and each contains a @B transform @b, these nested lists allow
*   you to create a hierarchy of motion, in which each @B transform @b affects an
*   entire subgraph of nodekits.
*   
*   The other parts added to the catalog for the SoSeparatorKit are @B pickStyle @b,
*   @B appearance @b, @B units @b and @B texture2Transform @b. Furthermore, since
*   SoSeparator is derived from SoBaseKit, it inherits the @B callbackList @b part.
*   This is a list of SoCallback and/or SoEventCallback nodes which enable the
*   SoSeparatorKit to perform special callbacks whenever an action is applied to
*   it.
*   
*   By creating the @B pickStyle @b part, a user can alter the pick style for the
*   entire nodekit hierarchy. The @B appearance @b part is an SoAppearanceKit
*   nodekit. Note that all parts contained in the SoAppearanceKit catalog can be
*   accessed as if they were part of the SoSeparatorKit. 
*  
*   See SoBaseKit for further explanation.
* 
* @PARTS
*   
*    (SoPickStyle)  pickStyle@BR
*       An SoPickStyle property node that can be used to set the picking style of its
*       children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoAppearanceKit)  appearance@BR
*       An SoAppearanceKit nodekit which can be used to set the appearance properties of
*       its children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoUnits)  units@BR
*       An SoUnits node which can be used to set the types of units, (e.g., feet), of
*       its children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoTransform)  transform@BR
*       An SoTransform node which can be used to set the overall position, orientation,
*       and scale of its children. This part is NULL by default, but is created
*       automatically if necessary. 
* 
*    (SoTexture2Transform)  texture2Transform@BR
*       An SoTexture2Transform node which can be used to apply a transformation to any
*       textures used by its children. This part is NULL by default, but is created
*       automatically if necessary. 
* 
*    (SoNodeKitListPart)  childList@BR
*       This part contains the children nodekits of this SoSeparatorKit. This part is a
*       list part and can have multiple children. This part is NULL by default, but is
*       created automatically when the first child is added to the childList. Also, when
*       asked to build a member of the childList, the separatorKit will build an
*       SoShapeKit by default. So if the childList part is NULL, and you call:
*       getPart("childList[0]", true), the separator kit will create the childList and
*       add an SoShapeKit as the new element in the list. 
* 
* 
* @FILE_FORMAT_DEFAULT
*    SeparatorKit {
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
*    SoShapeKit,
*    SoWrapperKit
* 
* 
*/ 
#else
/**
* Separator nodekit class.
* 
* @ingroup nodekits
* 
* @DESCRIPTION
*   A nodekit that is used for creating nodekit hierarchies. SoSeparatorKit contains
*   a @B transform @b part, a @B childList @b part, and a few others in its
*   catalog. The @B transform @b part (an SoTransform node) affects all of the
*   children in the childList. Each of these children must be an SoSeparatorKit or
*   from a class that is derived from SoSeparatorKit (e.g., SoShapeKit and
*   SoWrapperKit). Since all members of the @B childList @b are in turn
*   SoSeparatorKits, and each contains a @B transform @b, these nested lists allow
*   you to create a hierarchy of motion, in which each @B transform @b affects an
*   entire subgraph of nodekits.
*   
*   The other parts added to the catalog for the SoSeparatorKit are @B pickStyle @b,
*   @B appearance @b, @B units @b and @B texture2Transform @b. Furthermore, since
*   SoSeparator is derived from SoBaseKit, it inherits the @B callbackList @b part.
*   This is a list of SoCallback and/or SoEventCallback nodes which enable the
*   SoSeparatorKit to perform special callbacks whenever an action is applied to
*   it.
*   
*   By creating the @B pickStyle @b part, a user can alter the pick style for the
*   entire nodekit hierarchy. The @B appearance @b part is an SoAppearanceKit
*   nodekit. Note that all parts contained in the SoAppearanceKit catalog can be
*   accessed as if they were part of the SoSeparatorKit. 
* 
* 
* For example:
*   
*   <PRE> 
*    myMtl = mySepKit->getPart("material",TRUE)
*    </PRE>
*    and
*   
*   <PRE> 
*    mySepKit->setPart("material",myMtl)
*    </PRE>
*    See SoBaseKit for further explanation.
* 
* @PARTS
*   
*    (SoPickStyle)  pickStyle@BR
*       An SoPickStyle property node that can be used to set the picking style of its
*       children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoAppearanceKit)  appearance@BR
*       An SoAppearanceKit nodekit which can be used to set the appearance properties of
*       its children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoUnits)  units@BR
*       An SoUnits node which can be used to set the types of units, (e.g., feet), of
*       its children. This part is NULL by default, but is created automatically if
*       necessary. 
* 
*    (SoTransform)  transform@BR
*       An SoTransform node which can be used to set the overall position, orientation,
*       and scale of its children. This part is NULL by default, but is created
*       automatically if necessary. 
* 
*    (SoTexture2Transform)  texture2Transform@BR
*       An SoTexture2Transform node which can be used to apply a transformation to any
*       textures used by its children. This part is NULL by default, but is created
*       automatically if necessary. 
* 
*    (SoNodeKitListPart)  childList@BR
*       This part contains the children nodekits of this SoSeparatorKit. This part is a
*       list part and can have multiple children. This part is NULL by default, but is
*       created automatically when the first child is added to the childList. Also, when
*       asked to build a member of the childList, the separatorKit will build an
*       SoShapeKit by default. So if the childList part is NULL, and you call:
*       getPart("childList[0]", TRUE), the separator kit will create the childList and
*       add an SoShapeKit as the new element in the list. 
* 
* 
* @FILE_FORMAT_DEFAULT
*    SeparatorKit {
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
*    SoShapeKit,
*    SoWrapperKit
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SoSeparatorKit : public SoBaseKit {

  SO_KIT_HEADER(SoSeparatorKit);

  // defines fields for the new parts in the catalog
  SO_KIT_CATALOG_ENTRY_HEADER(topSeparator);
  SO_KIT_CATALOG_ENTRY_HEADER(pickStyle);
  SO_KIT_CATALOG_ENTRY_HEADER(appearance);
  SO_KIT_CATALOG_ENTRY_HEADER(units);
  SO_KIT_CATALOG_ENTRY_HEADER(transform);
  SO_KIT_CATALOG_ENTRY_HEADER(texture2Transform);
  SO_KIT_CATALOG_ENTRY_HEADER(childList);

 public:

   /** Possible values for caching. */
  enum CacheEnabled
  {
    /**
     *  Never build or use a cache 
     */
    OFF,
    /**
     *  Always try to build a cache 
     */
    ON,
    /**
     *  Automatic caching 
     */
    AUTO
  };

  // Fields
  /**
   * Set render caching mode. Default is AUTO.
   * 
   */
  SoSFEnum renderCaching;
  /**
   * Set bounding box caching mode. 
   * Use enum #CacheEnabled. Default is ON. Setting this value to AUTO is
   * equivalent to ON - automatic culling is not implemented.
   * 
   */
  SoSFEnum boundingBoxCaching;
  /**
   * Set render culling mode. 
   * Use enum #CacheEnabled. Default is OFF. Setting this value to AUTO is
   * equivalent to ON - automatic culling is not implemented.
   * 
   */
  SoSFEnum renderCulling;
  /**
   * Set pick culling mode. 
   * Use enum #CacheEnabled. Default is AUTO.
   * 
   */
  SoSFEnum pickCulling;

  /**
   * Constructor.
   */
  SoSeparatorKit();

  // Overrides default method on SoNode
  virtual SbBool affectsState() const;

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // Copies the contents of the given nodekit into this instance
  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

  // detach/attach any sensors, callbacks, and/or field connections.
  // Called by:            start/end of SoBaseKit::readInstance
  // and on new copy by:   start/end of SoBaseKit::copy.
  // Classes that redefine must call setUpConnections(TRUE,TRUE) 
  // at end of constructor.
  // Returns the state of the node when this was called.
  virtual SbBool setUpConnections( SbBool onOff, SbBool doItAlways = FALSE );

  // Called by the SoBaseKit::write() method. Calls setDefault(TRUE)
  // on the topSeparator. Note that this may be overriden later by basekit
  // if, for example, topSeparator lies on a path that is being written out.
  virtual void setDefaultOnNonWritingFields();

  // This sensor will watch the topSeparator part.  If the part changes to a 
  // new node,  then the fields of the old part will be disconnected and
  // the fields of the new part will be connected.
  // Connections are made from/to the renderCaching, boundingBoxCaching,
  // renderCulling and pickCulling fields. This way, the SoSeparatorKit
  // can be treated from the outside just like a regular SoSeparator node.
  // Setting the fields will affect caching and culling, even though the
  // topSeparator takes care of it.
  // oldTopSep keeps track of the part for comparison.
  SoFieldSensor *fieldSensor;
  static void fieldSensorCB( void *, SoSensor *);
  SoSeparator *oldTopSep;

  void connectSeparatorFields( SoSeparator *dest, SbBool onOff );

 protected:
  virtual ~SoSeparatorKit();

};
#endif  /* _SO_SEPARATOR_KIT_ */

