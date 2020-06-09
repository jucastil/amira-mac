/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Sep 2007)
**=======================================================================*/


#ifndef  _SO_GEO_PROJECTION_
#define  _SO_GEO_PROJECTION_

#include <Inventor/nodes/SoProjection.h>
#include <Inventor/projection/SbProj4Projection.h>

class SbProj4Projection;

/**
* @VSGEXT Geospatial projection node
*
* @ingroup PropertyNodes
* 
* @DESCRIPTION
*   
* This property node defines a geospatial coordinate projection that will be applied 
* to all subsequent shapes in the scene graph.
*
* The projection used is either an instance of SbProj4Projection or an instance of 
* SbSphericalProjection.  To see the list of available projections, refer to SbProj4Projection.
*
* The SbSphericalProjection instance will be chosen if the projection field is set to SPHERICAL.
* All other projections are provided by SbProj4Projection.
*
* When an instance of SbProj4Projection is being used, you can set the 
* coordinateSystem and ellipsoid to be used in the projection.
* An ellispoid definition is a mathematical representation used to approximate the 
* earth when computing projections.
*
* Available coordinate systems are :
* 
* - GEODETIC :
*   - x coordinate : degrees longitudes from -180 to 180
*   - y coordinate : degrees latitudes from -90 to 90
*   - z coordinate : meters
* 
* - GEOCENTRIC :
*   - x, y and z coordinate : meters
*
* See SoProjection for limitations of coordinate projection nodes.
*
*  @FILE_FORMAT_DEFAULT
*    GeoProjection {
*    @TABLE_FILE_FORMAT
*       @TR parameters           @TD ""
*       @TR matrix               @TD identity
*       @TR isOn                 @TD true
*       @TR floatParameters      @TD 1
*       @TR projTypeId           @TD 0
*       @TR coordinateSystem     @TD GEODETIC
*       @TR ellipsoid            @TD WGS84
*       @TR projection           @TD CASSINI
*    @TABLE_END
*    }
*
*   @SEE_ALSO
*    
* SoProjection,
* SbProj4Projection
*
* 
*/ 

class INVENTOR_API SoGeoProjection : public SoProjection
{

  SO_NODE_HEADER(SoGeoProjection);

public:

  /** 
  * Constructor.
  */
  SoGeoProjection();

  /** 
  * Current ellipsoid.  
  * Use enum SbProj4Projection::PredefinedEllipsoid. Default is WGS84.
  */
  SoSFEnum ellipsoid;

  /** 
  * Current coordinate system.  
  * Use enum SbProj4Projection::CoordinateSystem. Default is GEODETIC.
  */
  SoSFEnum coordinateSystem;

  /** 
  * Current Projection.  
  * Use enum SbProj4Projection::Projection. Default is CASSINI.
  */
  SoSFEnum projection;

SoINTERNAL public:

  static void         initClass();
  static void         exitClass();

  /**
  * Transform the given coordinates from GEODETIC to GEOCENTRIC or the reverse.
  * Returns true if successful.
  */
  static bool changeCoordSys( SbProj4Projection::CoordinateSystem originCoordSys, SbProj4Projection::CoordinateSystem destCoordSys, SbVec3f &coord );

  // return static instance
  static SoGeoProjection* getInstance();

  void setProj( SbProj4Projection::Projection proj );

  void setEllipsoidIn( SbProj4Projection::PredefinedEllipsoid ellipsoid );

  void setProjIn( SbProj4Projection::Projection proj );

  void setUTMZone( int zone );

  void setUTMSouth( bool south );

  SbProj4Projection::PredefinedEllipsoid getEllipsoidIn();

  SbProj4Projection::Projection getProjIn();

  int getUTMZone();

  bool isUTMSouth();

  void setRevertCoord( bool revertCoordNeeded ) { m_proj4Projection->setRevertCoord( revertCoordNeeded ); };

  bool isRevertCoordNeeded() { return m_proj4Projection->isRevertCoordNeeded(); };

  /**
  * fields sensor Callbacks
  */
  static void ellipsoidChangedCB( void *data, SoSensor* );

  static void coordinateChangedCB( void *data, SoSensor* );

  static void projIdChangedCB( void *data, SoSensor* );

  static void projectionChangedCB( void *data, SoSensor* );

protected:

  //static instance for system coordinate change
  static SoGeoProjection* m_geoProjection;

  //Internal proj4 projection
  SbProj4Projection* m_proj4Projection;

  /**
  * Destructor
  */
  virtual ~SoGeoProjection();

  //Called if projection type id has changed
  SoFieldSensor* m_typeIdSensor;

  // Field sensors
  SoFieldSensor* m_projectionSensor;
  SoFieldSensor* m_ellipsoidSensor;
  SoFieldSensor* m_coordinateSensor;
};

#endif /* _SO_GEO_PROJECTION_ */

