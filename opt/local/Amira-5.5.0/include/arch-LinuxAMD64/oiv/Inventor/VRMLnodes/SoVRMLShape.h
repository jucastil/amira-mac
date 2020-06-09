/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLSHAPE_
#define  _SO_VRMLSHAPE_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoBoundingBoxCache;
class SoGLCacheList;
class SoPrimitiveCountCache;
class SoColorPacker;
class SoChildList;
class SoMFColor;
class SoMFFloat;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLShape
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Defines a shape by specifying its appearance and geometry.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLShape node has four fields: #appearance and #geometry which
 *   are used to create rendered objects in the world. The #appearance field
 *   specifies an SoVRMLAppearance node that specifies the visual attributes (e.g.
 *   material and texture) to be applied to the geometry. The #geometry field
 *   specifies a geometry node. The specified geometry node is rendered with the
 *   specified appearance nodes applied.
 *
 *   The #bboxCenter and #bboxSize fields specify a bounding box that
 *   encloses the SoVRMLShape node's geometry. This is a hint that may be used for
 *   optimization purposes. If the specified bounding box is smaller than the actual
 *   bounding box of the children at any time, then the results are undefined. A
 *   default #bboxSize value, (-1 -1 -1), implies that the bounding box is not
 *   specified and if needed must be calculated by the browser. See "Concepts -
 *   Bounding Boxes" for a description of the #bboxCenter and #bboxSize
 *   fields.
 *   
 *   See "Concepts - Lighting Model" for details of the VRML lighting model and the
 *   interaction between SoVRMLAppearance and geometry nodes.
 *   
 *   If the #geometry field is NULL the object is not drawn.
 *   
 *   Note: The following fields -- #renderCaching and #boundingBoxCaching --
 *   are specific to the VSG Open
 *   Inventor implementation and are not part of the VRML97 specification. These
 *   fields are very useful for performance tuning, but are not written out if the
 *   output file is specified as VRML97 format. See SoSeparator for a discussion of
 *   Open Inventor caching and culling. 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLShape {
 *    @TABLE_FILE_FORMAT
 *       @TR appearance         @TD NULL
 *       @TR geometry           @TD NULL
 *       @TR bboxCenter         @TD 0 0 0
 *       @TR bboxSize           @TD -1 -1 -1
 *       @TR metadata           @TD NULL
 *       @TR renderCaching      @TD AUTO
 *       @TR boundingBoxCaching @TD AUTO
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction  @BR
 *      Sets: SoCacheElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFNode   @TD   set_appearance      
 *       @TR   SoSFNode   @TD   set_geometry
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFNode   @TD   appearance_changed      
 *       @TR   SoSFNode   @TD   geometry_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLShape : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLShape);

 public:
    /** Possible values for caching */
  enum CacheEnabled {
    /**
     *  Never build a cache 
     */
    OFF,
    /**
     *  Always try to build a cache 
     */
    ON,
    /**
     *  Decide whether to cache based on some heuristic 
     */
    AUTO
  };

  /**
   * Specifies an SoVRMLAppearance node that defines the visual attributes.
   */
  SoSFNode      appearance;

  /**
   * A geometry node.
   */
  SoSFNode      geometry;

  /**
   * Center of a bounding box that encloses the children.
   * 
   */
  SoSFVec3f bboxCenter;

  /**
   * Size of a bounding box that encloses the children.
   * 
   */
  SoSFVec3f bboxSize;

  /**
   * Whether to cache during rendering traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   *
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum renderCaching;

  /**
   * Whether to cache during bounding box traversal.
   * Use enum #CacheEnabled. Default is AUTO.
   *
   * @B NOTE:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFEnum boundingBoxCaching;

  /**
   * Constructor.
   */
  SoVRMLShape();

  /**
   * Sets the maximum number of render caches [@B Deprecated @b].
   * SoDB::setNumRenderCaches is recommended instead of this method.
   */
  SoDEPRECATED static void setNumRenderCaches(int howMany);

  /**
   * Returns the current number of render caches [@B Deprecated @b].
   * SoDB::getNumRenderCaches is recommended instead of this method.
   */
  SoDEPRECATED static int getNumRenderCaches();

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:

  // Overrides default method on SoNode
  virtual SbBool     affectsState() const;

  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  // Implements picking along a ray by intersecting the ray with
  // each primitive generated by subclass. May be overridden in
  // subclass.
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


 SoINTERNAL public:
  virtual SoChildList *getChildren() const;
  virtual SoChildList *internalGetChildren() const;

  static void         initClass();
  static void         exitClass();

  SoSFBool override;

  virtual SbBool      validateNewFieldValue(SoField *pField,
                                            void *newValue);
  virtual void        notify(SoNotList *list);

  // Copies the contents of the given node into this instance. The
  // default implementation copies just field values and the name.
  virtual void        copyContents(const SoFieldContainer *fromFC,
                                   SbBool copyConnections);
 protected:
  virtual ~SoVRMLShape();
  SoColorPacker *colorPacker;

  SoBoundingBoxCache  *bboxCache;     // Cache for bounding boxes
  SoGLCacheList       *cacheList;     // Caches for GL rendering
  SoPrimitiveCountCache *primCountCache;      // Cache for primitive count:1


  // Hack to make paths work for VRML nodes that contain other nodes
  // in their fields...  Nov-96
  SoChildList *children;
  friend class SoPath;    // Need to access "children" in SoPath::truncate()

 private:
  void                rebuildChildrenList();
  // Temporary storage during traversal
  // (traversal state wants SoMF fields and we only have SoSF fields!)
  static SoMFColor    *m_diffuse;
  static SoMFColor    *m_emissive;
  static SoMFColor    *m_specular;
  static SoMFFloat    *m_transparency;
  static SoMFFloat    *m_shininess;
  static SoMFColor    *m_ambient;

  // Count instances of this type so we can clean up the temporary storage
  static int instanceCounter;

  int m_numRenderCaches;

};

#endif /* _SO_VRMLSHAPE_ */

