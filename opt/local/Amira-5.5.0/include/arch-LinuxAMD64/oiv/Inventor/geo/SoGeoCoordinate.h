/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Apr 2009)
**=======================================================================*/

#ifndef  _SO_GEOCOORDINATE_
#define  _SO_GEOCOORDINATE_

#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoCoordinate3.h>

/** 
 * @VSGEXT Geographic coordinates node.
 * 
 * @ingroup GeoNodes
 * 
 * @DESCRIPTION
 *    The SoGeoCoordinate node allows applications to build geometry using
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
 *    The SoGeoCoordinate node specifies a list of coordinates in a spatial
 *   reference frame. It can be used in place of an SoCoordinate3 node.
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
 * @FILE_FORMAT_DEFAULT
 *    GeoCoordinate {
 *    @TABLE_FILE_FORMAT
 *       @TR point        @TD []
 *       @TR geoOrigin    @TD NULL
 *       @TR geoSystem    @TD ["GD","WE"]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoGetBoundingBoxAction, SoCallbackAction  @BR
 * 
 */
class INVENTOR_API SoGeoCoordinate : public SoCoordinate3 {

  SO_NODE_HEADER(SoGeoCoordinate);

 public:
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
  SoGeoCoordinate();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoGeoCoordinate();
};

#endif /* _SO_GEOCOORDINATE_ */
