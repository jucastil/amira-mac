/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Apr 2009)
**=======================================================================*/

#ifndef  _SO_GEOLOCATION_
#define  _SO_GEOLOCATION_

#include <Inventor/fields/SoSFVec3d.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoTransformation.h>

/** 
 * @VSGEXT Used to georeference models.
 * 
 * @ingroup GeoNodes
 * 
 * @DESCRIPTION
 *    The SoGeoLocation allows to place a non-georeferenced model at its 
 *   correct location in geospatial coordinates.
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
 *    The SoGeoLocation node provides the ability to geo-reference any models.
 *   That is, to take an ordinary model, and to specify its geospatial location.
 *   This node is a grouping node that can be thought of as a Transform node.
 *   However, the GeoLocation node specifies an absolute location, not a relative
 *   one, so content developers should not nest GeoLocation nodes within each other.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #geoCoords field should be provided in the format described in
 *   25.2.3 Specifying a spatial reference frame.
 *   The #geoCoords field can be used to dynamically update the geospatial
 *   location of the model.
 * 
 * @FILE_FORMAT_DEFAULT
 *    GeoLocation {
 *    @TABLE_FILE_FORMAT
 *       @TR geoCoords      @TD 0 0 0
 *       @TR geoSystem      @TD ["GD","WE"]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction, SoRayPickAction,  SoGetBoundingBoxAction,  SoCallbackAction,
 *      SoGetMatrixAction, SoGetPrimitiveCount  @BR
 * 
 */
class INVENTOR_API SoGeoLocation : public SoTransformation {

  SO_NODE_HEADER(SoGeoLocation);

 public:
  // Fields
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
   *   specify the zone number (1..60). This is given in the form "Zn", where
   *   n is the zone number. An optional argument of "S" may be supplied in 
   *   order to specify that the coordinates are in the southern hemisphere
   *  (otherwise, northern hemisphere will be assumed).
   */
  SoMFString         geoSystem;

  /**
   * Creates a geoLocation node with default settings.
   */
  SoGeoLocation();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoGeoLocation();

 private:
  SbVec3f             m_geoCoords;

};

#endif /* _SO_GEOLOCATION_ */
