/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Mar 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOCOORDINATE_
#define  _SO_VRMLGEOCOORDINATE_


#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoGeoProjection.h>
#include <Inventor/VRMLnodes/SoVRMLCoordinate.h>

/** 
 * @VSGEXT Geographic coordinates node.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *    The SoVRMLGeoCoordinate node allows applications to build geometry using
 *   geographic coordinates
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
 *    The SoVRMLGeoCoordinate node specifies a list of coordinates in a spatial
 *   reference frame. It is used in the #coord field of vertex-based geometry nodes
 *   including SoVRMLIndexedFaceSet, SoVRMLIndexedLineSet, and SoVRMLPointSet.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #point array is used to contain the actual geospatial coordinates and should
 *   be provided in a format consistent with that specified for the particular
 *   #geoSystem (see above). The geospatial coordinates are transparently transformed
 *   into a geocentric, curved-earth representation. For example, this would allow a
 *   geographer to create a X3D world where all coordinates are specified in terms of
 *   latitude, longitude, and elevation.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoCoordiante {
 *    @TABLE_FILE_FORMAT
 *       @TR metadata     @TD NULL
 *       @TR point        @TD []
 *       @TR geoOrigin    @TD NULL
 *       @TR geoSystem    @TD ["GD","WE"]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoGetBoundingBoxAction, SoCallbackAction  @BR
 * 
 * 
 * @EVENTS 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFVec3d    @TD   set_point
 *       @TR   SoSFNode     @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoMFVec3d    @TD   point_changed
 *       @TR   SoSFNode     @TD   metadata_changed
 *    @TABLE_END
 * 
 */
class INVENTOR_API SoVRMLGeoCoordinate : public SoVRMLCoordinate {

  SO_NODE_HEADER(SoVRMLGeoCoordinate);

 public:
  // Fields
  /**
   * An SoVRMLGeoOrigin node specifying the origin of the local coordinate system.
   */
  SoSFNode           geoOrigin;
  
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
  SoVRMLGeoCoordinate();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLGeoCoordinate();
};

#endif /* _SO_VRMLGEOCOORDINATE_ */
