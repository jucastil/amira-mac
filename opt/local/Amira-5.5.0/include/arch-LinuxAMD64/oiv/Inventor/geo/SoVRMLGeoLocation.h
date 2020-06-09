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
** Modified by : Julien SALLANNE (May 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOLOCATION_
#define  _SO_VRMLGEOLOCATION_


#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLTransform.h>

/** 
 * @VSGEXT Used to georeference models.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *    The SoVRMLGeoLocation allows to place a non-georeferenced model at its 
 *   correct geospatial location.
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
 *    The SoVRMLGeoLocation node provides the ability to geo-reference any
 *   standard X3D model. That is, to take an ordinary X3D model, contained
 *   within the children field of the node, and to specify its geospatial location.
 *   This node is a grouping node that can be thought of as a Transform node.
 *   However, the GeoLocation node specifies an absolute location, not a relative
 *   one, so content developers should not nest GeoLocation nodes within each other.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The geometry of the nodes in #children is to be specified in units of meters
 *   in X3D coordinates relative to the location specified by the #geoCoords field.
 *   The #geoCoords field should be provided in the format described in
 *   25.2.3 Specifying a spatial reference frame.
 *   The #geoCoords field can be used to dynamically update the geospatial
 *   location of the model.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoLocation {
 *    @TABLE_FILE_FORMAT
 *       @TR children       @TD []
 *       @TR geoCoords      @TD 0 0 0
 *       @TR metadata       @TD NULL
 *       @TR geoOrigin      @TD NULL
 *       @TR geoSystem      @TD ["GD","WE"]
 *       @TR bboxCenter     @TD 0 0 0
 *       @TR bboxSize       @TD -1 -1 -1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction, SoRayPickAction, SoGetBoundingBoxAction, SoCallbackAction,
 *      SoGetMatrixAction, SoGetPrimitiveCount  @BR
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
 *    @TABLE_END
 * 
 */
class INVENTOR_API SoVRMLGeoLocation : public SoVRMLGroup {

  SO_NODE_HEADER(SoVRMLGeoLocation);

 public:
  // Fields
  /**
   * An SoVRMLGeoOrigin node specifying the origin of the local coordinate system.
   */
  SoSFNode           geoOrigin;

  /**
   * Geospatial coordinate used for translation
   */
  SoSFVec3d          geoCoords;

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
  SoMFString         geoSystem;

  /**
   * Constructor.
   */
  SoVRMLGeoLocation();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

    // These methods make render traversal faster by implementing
  // different rendering paths corresponding to different action
  // path codes.
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  virtual void        notify(SoNotList *list);

 protected:
  virtual ~SoVRMLGeoLocation();

 private:
  void                 setupModelMatrixElement(SoState *state);
};

#endif /* _SO_VRMLGEOLOCATION_ */
