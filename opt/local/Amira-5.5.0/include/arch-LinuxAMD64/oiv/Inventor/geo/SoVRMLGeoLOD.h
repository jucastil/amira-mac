/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Julien SALLANNE (Jun 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOLOD_
#define  _SO_VRMLGEOLOD_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/nodes/SoGeoProjection.h>
#include <Inventor/VRMLnodes/SoVRMLParent.h>
#include <Inventor/VRMLnodes/SoVRMLInline.h>

/** 
 * @VSGEXT Level-of-detail management for multi-resolution terrains.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *    The SoVRMLGeoLOD node allows applications to build massive tiled,
 *   multi-resolution terrain models where the viewer progressively loads higher
 *   resolution detail as you fly into the terrain.
 * 
 * @VRMLX3D_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming X3D / VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *    This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *    The SoVRMLGeoLOD node provides a terrain-specialized form of the LOD node.
 *   It is a grouping node that specifies two different levels of detail for an
 *   object using a tree structure, where 0 to 4 children can be specified, and
 *   also efficiently manages the loading and unloading of these levels of detail.
 *   The level of detail is switched depending upon whether the user is closer
 *   or further than #range meters from the geospatial coordinate #center.
 *   The #center field should be specified as described in 25.2.4 Specifying geospatial coordinates.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   When the user is outside the specified range, only the geometry for #rootUrl
 *   or #rootNode are displayed. When the viewer enters the specified range,
 *   this geometry is replaced with the contents of the four children files
 *   defined by #child1Url through #child4Url. The four children files are loaded
 *   into memory only when the user is within the specified range.
 *   Similarly, these are unloaded from memory when the user leaves this range.
 *   Figure below illustrates this process. The child URLs shall be arranged in
 *   the same order as in the figure; i.e., #child1Url represents the bottom-left
 *   quadtree child. It is valid to specify less than four child URLs;
 *   in which case, the SoVRMLGeoLOD should switch to the children nodes when all of
 *   the specified URLs have been loaded. This latter feature can support tree
 *   structures other than quadtrees, such as binary trees.
 *
 *   @IMAGE geolod.gif
 *
 *   The #rootUrl and #rootNode fields provide two different ways to specify the
 *   geometry of the root tile. You may use one or the other. The #rootNode field
 *   lets you include the geometry for the root tile directly within the X3D file;
 *   whereas the #rootUrl field lets you specify a URL for a file that contains the
 *   geometry. The result of specifying a value for both of these fields is undefined.
 *   The #children field is used to expose a portion of the scene graph for the
 *   currently loaded set of nodes. The value returned as an event is an MFNode
 *   containing the currently selected tile. This will either be the node specified
 *   by the #rootNode field or the nodes specified by the #child1Url, #child2Url,
 *   #child3Url, and #child4Url fields. The SoVRMLGeoLOD node shall generate a new
 *   #children output event each time the scene graph is changed
 *   (EXAMPLE whenever nodes are loaded or unloaded). When the new children event
 *   is generated, the SoVRMLGeoLOD node shall also generate a #level_changed event 
 *   with value 0 or 1, where 0 indicates the #rootNode field and 1 indicates the
 *   nodes specified by the #child1Url, #child2Url, #child3Url, and #child4Url fields.
 *   The SoVRMLGeoLOD node may optionally be implemented with support for a cache of
 *   the most recent nodes that have been loaded. This cache should be global
 *   across all SoVRMLGeoLOD instances in a scene. This will improve performance when
 *   navigating large terrain models by avoiding excessive loading and unloading
 *   when a user makes small changes in viewpoint.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoLOD {
 *    @TABLE_FILE_FORMAT
 *       @TR metadata         @TD NULL
 *       @TR children         @TD []
 *       @TR center           @TD 0 0 0
 *       @TR child1Url        @TD []
 *       @TR child2Url        @TD []
 *       @TR child3Url        @TD []
 *       @TR child4Url        @TD []
 *       @TR geoOrigin        @TD NULL
 *       @TR geoSystem        @TD ["GD","WE"]
 *       @TR range            @TD 10
 *       @TR rootUrl          @TD []
 *       @TR rootNode         @TD []
 *       @TR bboxCenter       @TD 0 0 0
 *       @TR bboxSize         @TD -1 -1 -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction 
 *      SoGetPrimitiveCountAction @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN
 *       @TR   SoMFNode   @TD   addChildren
 *       @TR   SoMFNode   @TD   removeChildren
 *       @TR   SoMFNode   @TD   set_children
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT
 *       @TR   SoMFNode   @TD   children_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *       @TR   SoSFNode   @TD   level_changed
 *    @TABLE_END
 * 
 */
class INVENTOR_API SoVRMLGeoLOD : public SoVRMLParent {

  SO_NODE_HEADER(SoVRMLGeoLOD);

 public:
  // Fields
  /**
   * Defines the spatial reference frame. @BR
   * Valid values are:
   * - GC: Earth-fixed Geocentric with respect to the WGS84 ellipsoid.
   * - GD: Geodetic spatial reference frame. @BR
   *   An optional second string may be used to specify the ellipsoid using
   *   one of the ellipsoid codes that are defined in X3D. If no ellipsoid is 
   *   specified, then "WE" is assumed (the WGS84 ellipsoid).
   * - UTM: Universal Transverse Mercator @BR
   *   One further required argument must be supplied for UTM in order to
   *   specify the zone number (1..60). This is given in the form "Z<n>", where
   *   <n> is the zone number. An optional argument of "S" may be supplied in 
   *   order to specify that the coordinates are in the southern hemisphere
   *  (otherwise, northern hemisphere will be assumed).
   */
  SoMFString        geoSystem;

  /**
   * First child url : bottom-left quadtree child
   */
  SoMFString        child1Url;

  /**
   * Second child url : up-left quadtree child
   */
  SoMFString        child2Url;

  /**
   * Third child url : up-right quadtree child
   */
  SoMFString        child3Url;

  /**
   * Fourth child url : bottom-right quadtree child
   */
  SoMFString        child4Url;

  /**
   * Url of the file that contains the root tile geometry
   */
  SoMFString        rootUrl;

  /**
   * World-space distance to use as switching criteria.
   */
  SoSFFloat         range;

  /**
   * Object-space center of the model.
   */
  SoSFVec3d         center;

  /**
   * An SoVRMLGeoOrigin node specifying the origin of the local coordinate system.
   */
  SoSFNode          geoOrigin;

  /**
   * The root tile of the hierarchy.
   */
  SoMFNode          rootNode;

  /**
   * Constructor.
   */
  SoVRMLGeoLOD();
  /**
   * Constructor that takes approximate number of levels/children.
   */
  SoVRMLGeoLOD(int nChildren);

 SoEXTENDER public:
  // Implements actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
                                               
 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  //virtual void        notify(SoNotList *list);

 protected:
  virtual             ~SoVRMLGeoLOD();

 private:
  void                addVRMLInlineChild();
  void                addVRMLInlineRoot();
  bool                isInside(SoAction *action);
  int                 getNumInlineChild();

  SoVRMLInline *m_vrmlInlineRoot;
  SoVRMLInline *m_vrmlInline1;
  SoVRMLInline *m_vrmlInline2;
  SoVRMLInline *m_vrmlInline3;
  SoVRMLInline *m_vrmlInline4;

  SbVec3f m_geoCenter;

  bool m_needLoad;
};

#endif /* _SO_VRMLGEOLOD_ */
