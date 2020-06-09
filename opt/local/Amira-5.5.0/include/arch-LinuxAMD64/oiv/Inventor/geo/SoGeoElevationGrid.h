/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Apr 2009)
**=======================================================================*/

#ifndef  _SO_GEOELEVATIONGRID_
#define  _SO_GEOELEVATIONGRID_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoGeoProjection.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>

/** 
 * @VSGEXT Specifies a uniform grid of elevation values within some spatial 
 *         reference frame.
 * 
 * @ingroup GeoNodes
 * 
 * @DESCRIPTION
 *    The SoGeoElevationGrid allows to create terrain models for local or large
 *   areas (automatically introduces correct degree of earth curvature).
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
 *    The SoGeoElevationGrid node specifies a uniform grid of elevation values 
 *   within some spatial reference frame. These are then transparently transformed 
 *   into a geocentric, curved-earth representation. For example, this would allow 
 *   a geographer to create a height field where all coordinates are specified in 
 *   terms of latitude, longitude, and elevation.
 *   The #geoSystem field is used to define the spatial reference frame and is 
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #geoGridOrigin field specifies the geographic coordinate for the south-west
 *   corner (bottom-left) of the dataset. This value should be specified as described
 *   in 25.2.4 Specifying geospatial coordinates.
 *   The #height array contains #xDimension #zDimension floating point values that
 *   represent elevation above the ellipsoid or the geoid, as appropriate. These
 *   values are given in row-major order from west to east, south to north. When 
 *   the #geoSystem is "GD", #xSpacing refers to the number of degrees of longitude
 *   between adjacent height values and #zSpacing refers to the number of degrees
 *   of latitude between vertical height values. When the geoSystem is "UTM",
 *   #xSpacing refers to the number of eastings (meters) between adjacent height
 *   values and #zSpacing refers to the number of northings (meters) between
 *   vertical height values.
 *   EXAMPLE  If xDimension = n and the grid spans d units horizontally, 
 *   the xSpacing value should be set to: d / (n-1).
 *   The #yScale value can be used to produce a vertical exaggeration of the data
 *   when it is displayed. By default, this value is 1.0 (no exaggeration).
 *   If this value is set greater than 1.0, all heights will appear larger than actual.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    GeoElevationGrid {
 *    @TABLE_FILE_FORMAT
 *       @TR yScale           @TD 1.0
 *       @TR geoGridOrigin    @TD 0 0 0
 *       @TR geoSystem        @TD ["GD","WE"]
 *       @TR height           @TD []
 *       @TR xDimension       @TD 0
 *       @TR xSpacing         @TD 1.0
 *       @TR zDimension       @TD 0
 *       @TR zSpacing         @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 * 
 */
class INVENTOR_API SoGeoElevationGrid : public SoIndexedFaceSet {

  SO_NODE_HEADER(SoGeoElevationGrid);

 public:
  // Fields
  /**
   * The yScale value can be used to produce a vertical exaggeration of the data
   * when it is displayed. By default, this value is 1.0 (no exaggeration).
   * If this value is set greater than 1.0, all heights will appear larger than actual. 
   */
  SoSFFloat         yScale;
  
  /**
   * Specifies the geographic coordinate for the south-west
   * corner (bottom-left) of the dataset.
   */
  SoSFVec3f         geoGridOrigin;
  
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
  SoMFString        geoSystem;
  
  /**
   * The #height array contains #xDimension * #zDimension floating point values that
   * represent elevation above the ellipsoid or the geoid, as appropriate. These
   * values are given in row-major order from west to east, south to north.
   */
  SoMFFloat         height;
  
  /**
   * Number of X values in the grid.
   */
  SoSFInt32         xDimension;
  
  /**
   * Spacing between X values. @BR
   * When the #geoSystem is "GD", xSpacing refers to the number of degrees of longitude
   * between adjacent height values. When the geoSystem is "UTM", xSpacing refers to the 
   * number of eastings (meters) between adjacent height values.
   */
  SoSFFloat         xSpacing;
  
  /**
   * Number of Z values in the grid.
   */
  SoSFInt32         zDimension;
  
  /**
   * Spacing between Z values. @BR
   * When the #geoSystem is "GD", zSpacing refers to the number of degrees
   * of latitude between vertical height values. When the geoSystem is "UTM",
   * zSpacing refers to the number of northings (meters) between
   * vertical height values.
   */
  SoSFFloat         zSpacing;

  /**
   * Constructor.
   */
  SoGeoElevationGrid();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

  // Computes bounding box
  virtual void        computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected: 

  virtual ~SoGeoElevationGrid();

private:

  void                buildGrid( SoAction *action );
  float               computeHeight(int index);



};

#endif /* _SO_GEOELEVATIONGRID_ */
