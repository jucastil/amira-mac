/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (May 2007)
**=======================================================================*/

#ifndef _SB_PROJ4PROJECTION_
#define _SB_PROJ4PROJECTION_

#include <Inventor/projection/SbProjection.h>
#include <Inventor/SbLinear.h>

// WARNING: dumb workaround for symbol conflict with winreg.h on Win32
#define PVALUE PROJ_PVALUE

#define PROJECTION_PARAM_ID 0
#define ELLIPSOID_PARAM_ID 1
#define UTM_ZONE 2
#define UTM_SOUTH 3

class SoProjection;

/**
 * Cartographic (PROJ4) projection class.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 * 
 *  This class performs a cartographic projection using the PROJ.4 Cartographic Projections Library 
 *  ( see http://proj.maptools.org/ )
 *
 *  To use this class as a projection, refer to the documentation of SbProjection class.
 *
 *  By default, input points must be defined in the geodetic coordinate system :
 *
 *    - x coordinate : longitudes degrees from -180 to 180
 *    - y coordinate : latitudes degrees from -90 to 90
 *    - z coordinate : meters
 * 
 *  It is possible to define the input data in the geocentric coordinate system by calling
 *  setCoordinateSystem(GEOCENTRIC).  The geocentric coordinate system is the earth 
 *  coordinate system, where x, y and z coordinate are expressed in meters. 
 *
 *  The PROJ.4 library parameters are stored as SbProjection string parameters:
 *
 *    - parameter 0 : projection name
 *    - parameter 1 : ellipsoid
 *    - parameter 2 : units
 *    - parameter 3 : longitude zero
 *
 *  The first SbProjection float parameter is used to specify the z coordinate 
 *  scaleRatio applied to the projected shapes.
 *
 *  The enumeration PredefinedEllipsoid defines the list of available ellipsoid. 
 *  An ellispoid definition is a mathematical representation used to approximate the 
 *  earth when computing projections.
 *  Calling setEllipsoid() sets the current ellipsoid used to compute projections.
 *
 *  Only projections with an inverse function defined are available.
 *  
 *  The available projections are defined with the Projection enumeration.
 *  When using an SbProj4Projection object with an SoProjection node, those projections are
 *  automatically added in the order above, and you can choose the desired projection by using
 *  the corresponding id (refer to SoProjection node).
 *
 *  LIMITATIONS
 *
 *  It can happen that vertices of a projected shape cross other ones, depending on the chosen 
 *  projection.  Visually it results in a flipping effect.
 *
 * @SEE_ALSO
 * 
 *  SbProjection,
 *  SoProjection,
 *  SoGeoProjection
 *  
 * 
 */

class INVENTOR_API SbProj4Projection : public SbProjection
{

public:

  /** 
  * Available coordinate systems 
  */
  enum CoordinateSystem
  {
    GEOCENTRIC = 0,
    GEODETIC,
    NUM_COORDINATE_SYSTEMS
  };

  /** 
  * Available ellipsoids
  */
  enum PredefinedEllipsoid 
  {
    SPHERE = 0,	// Normal Sphere (r=6370997)
    AIRY		  ,	// Airy 183
    AIRYM	    ,	// Modified Airy
    ANDRAE	  ,	// Andrae 1876 (Den., Iclnd.)
    APL		    ,	// Appl. Physics. 1965
    AUST_SA	  ,	// Australian Natl & S. Amer. 1969
    BESSEL	  ,	// Bessel 1841
    BESS_NAM  ,	// Bessel 1841 (Namibia)
    CLRK66	  ,	// Clarke 1866
    CLRK80	  ,	// Clarke 1880
    CPM		    ,	// Comm. des Poids et Mesures 1799
    DELMBR	  ,	// Delambre 1810 (Belgium)
    ENGELIS	  ,	// Engelis 1985
    EVRST30	  ,	// Everest 1830
    EVRST48	  ,	// Everest 1948
    EVRST56	  ,	// Everest 1956
    EVRST69	  ,	// Everest 1969
    EVRSTSS	  ,	// Everest (Sabah & Sarawak)
    FSCHR60	  ,	// Fischer (Mercury Datum) 1960
    FSCHR60M	,	// Modified Fischer 1960
    FSCHR68	  ,	// Fischer 1968
    GRS67	    ,	// GRS 67(IUGG 1967)
    GRS80	    ,	// GRS 1980(IUGG, 1980
    HELMERT	  ,	// Helmert 1906
    HOUGH	    ,	// Hough
    IAU76	    ,	// IAU 1976
    INTL		  ,	// International 1909 (Hayford)
    KAULA	    ,	// Kaula 1961
    KRASS	    ,	// Krassovsky, 1942
    LERCH	    ,	// Lerch 1979
    MERIT	    ,	// MERIT 1983
    MPRTS	    ,	// Maupertius 1738
    NEW_INTL	,	// New International 1967
    NWL9D	    ,	// Naval Weapons Lab., 1965
    PLESSIS	  ,	// Plessis 1817 (France)
    SE_ASIA	  ,	// Southeast Asia
    SGS85	    ,	// Soviet Geodetic System 85 
    WALBECK	  ,	// Walbeck
    WGS60	    ,	// WGS 60
    WGS66	    ,	// WGS 66
    WGS72	    ,	// WGS 72
    WGS84	 	, // WGS 84
    NUM_ELLIPSOIDS
  };

  /** 
  * Available projections
  */
  enum Projection
  {
    CASSINI,                              // Cassini
    EQUAL_AREA_CYLINDRICAL,               //Equal Area Cylindrical
    COLLIGNON,                            //Collignon
    CRASTER_PARABOLIC,                    //Craster Parabolic (Putnins P4)
    ECKERT_I,                             //Eckert I
    ECKERT_II,                            //Eckert II
    ECKERT_III,                           //Eckert III
    ECKERT_IV,                            //Eckert IV
    ECKERT_V,                             //Eckert V
    ECKERT_VI,                            //Eckert VI
    EQUIDISTANT_CYLINDRICAL,              //Equidistant Cylindrical (Plate Caree)
    FAHEY,                                //Fahey
    FOUCAUT_SINUSOIDAL,                   //Foucaut Sinusoidal
    GALL,                                 //Gall (Gall Stereographic)
    GEOCENTRIC_PROJ,                      //Geocentric
    HATANO_ASYMMETRICAL_EQUAL_AREA,       //Hatano Asymmetrical Equal Area
    KAVRAISKY_VII,                        //Kavraisky VII
    KROVAK,                               //Krovak
    LAMBERT_AZIMUTHAL_EQUAL_AREA,         //Lambert Azimuthal Equal Area
    LAT_LONG ,                            //Lat/long (Geodetic)
    LONG_LAT ,                            //Long/lat (Geodetic)
    LAMBERT_EQUAL_AREA_CONIC,             //Lambert Equal Area Conic
    LOXIMUTHAL,                           //Loximuthal
    MCBRYDE_THOMAS_FLAT_POLE_SINE,        //McBryde-Thomas Flat-Pole Sine (No. 2)
    MCBRYDE_THOMAS_FLAT_POLAR_PARABOLIC,  //McBride-Thomas Flat-Polar Parabolic
    MCBRYDE_THOMAS_FLAT_POLAR_QUARTIC,    //McBryde-Thomas Flat-Polar Quartic
    MCBRYDE_THOMAS_FLAT_POLAR_SINUSOIDAL, //McBryde-Thomas Flat-Polar Sinusoidal
    MERCATOR,                             //Mercator
    MILLER_CYLINDRICAL,                   //Miller Cylindrical
    MOLLWEIDE,                            //Mollweide
    NELL,                                 //Nell
    NELL_HAMMER,                          //Nell-Hammer
    OBLIQUE_CYLINDRICAL_EQUAL_AREA,       //Oblique Cylindrical Equal Area
    POLYCONIC,                            //Polyconic (American)
    PUTNINS_P1,                           //Putnins P1
    PUTNINS_P2,                           //Putnins P2
    PUTNINS_P3_2,                         //Putnins P3'
    PUTNINS_P4_2,                         //Putnins P4'
    PUTNINS_P5,                           //Putnins P5
    PUTNINS_P5_2,                         //Putnins P5'
    PUTNINS_P6,                           //Putnins P6
    PUTNINS_P6_2,                         //Putnins P6'
    ROBINSON,                             //Robinson
    SINUSOIDAL,                           //Sinusoidal (Sanson-Flamsteed)
    SWISS_OBL_MERCATOR,                   //Swiss. Obl. Mercator
    OBLIQUE_STEREOGRAPHIC_ALTERNATIVE,    //Oblique Stereographic Alternative
    TRANSVERSE_CYLINDRICAL_EQUAL_AREA,    //Transverse Cylindrical Equal Area
    TRANSVERSE_MERCATOR,                  //Transverse Mercator
    UNIVERSAL_POLAR_STEREOGRAPHIC,        //Universal Polar Stereographic
    UNIVERSAL_TRANSVERSE_MERCATOR,        //Universal Transverse Mercator (UTM)
    VAN_DER_GRINTEN_I,                    //van der Grinten (I)
    WAGNER_I,                             //Wagner I (Kavraisky VI)
    WAGNER_II,                            //Wagner II
    WAGNER_III,                           //Wagner III
    WAGNER_IV,                            //Wagner IV
    WAGNER_V,                             //Wagner V
    WAGNER_VI,                            //Wagner VI
    WERENSKIOLD_I,                        //Werenskiold I
    WINKEL_I,                             //Winkel I
    WINKEL_TRIPEL,                        //Winkel Tripel
    NUM_PROJ4_PROJECTIONS
  };

  /**
  * Constructor
  */
  SbProj4Projection();

  /**
  * Constructor.
  */
  SbProj4Projection( SoProjection *node );

  /**
  * Copy constructor.
  */
  SbProj4Projection( const SbProj4Projection &proj );

  /**
  * Destructor.
  */
  virtual ~SbProj4Projection();

  /**
  * Set current ellipsoid.
  */
  void setEllipsoid( SbProj4Projection::PredefinedEllipsoid ellipsoid );
  
  /**
  * Get current ellipsoid.
  */
  SbProj4Projection::PredefinedEllipsoid getEllipsoid();

  /**
  * Set current input ellipsoid.
  */
  void setEllipsoidIn( SbProj4Projection::PredefinedEllipsoid ellipsoid );
  
  /**
  * Get current input ellipsoid.
  */
  SbProj4Projection::PredefinedEllipsoid getEllipsoidIn();
  
  /**
  * Get PROJ.4 ellipsoid string.
  */
  static SbString getEllipsoidString( SbProj4Projection::PredefinedEllipsoid ellipsoid );

  /**
  * Set current coordinate system.
  */
  void setCoordinateSystem( SbProj4Projection::CoordinateSystem coordinateSystem );

  /**
  * Get current coordinate system.
  */
  SbProj4Projection::CoordinateSystem getCoordinateSystem();

  /**
  * Set current projection.
  */
  void setProjection( SbProj4Projection::Projection proj );
  
  /**
  * Get current projection .
  */
  SbProj4Projection::Projection getProjection( );

  /**
  * Set current input projection.
  */
  void setProjectionIn( SbProj4Projection::Projection proj );

  /**
  * Get current input projection .
  */
  SbProj4Projection::Projection getProjectionIn();

  /**
  * Set current UTM zone.
  */
  void setUTMZone( int zone );

  /**
  * Get current UTM zone.
  */
  int getUTMZone();

  /**
  * Set m_south (UTM)
  */
  void setUTMSouth( bool south );

  /**
  * Get m_south (UTM)
  */
  bool isUTMSouth();

  /**
  * Set revertCoordNeeded
  */
  void setRevertCoord( bool revertCoordNeeded ) { m_revertCoordNeeded = revertCoordNeeded; };

  /**
  * Get revertCoordNeeded.
  */
  bool isRevertCoordNeeded() { return m_revertCoordNeeded; };

  /**
  * Get internal PROJ.4 projection string.
  */
  static SbString getProjectionString( SbProj4Projection::Projection proj );

  /**
  * Get projection name description.
  */
  static SbString getProjectionName( SbProj4Projection::Projection proj );

  /**
  * Initialisation.
  */
  virtual void init();

  /**
  * Exit function.
  */
  virtual void exit();

  /**
  * Inverse projection of one point.
  */
  virtual void inverse( SbVec3f &point );

  /**
  * Transform the given coordinates from Geocentric coordinate system to Geodetic coordinate system .
  */
  void toGeodetic( SbVec3f &point );

  /**
  * Transform the given coordinates from Geodetic coordinate system to Geocentric coordinate system .
  */
  void toGeocentric( SbVec3f &point );

SoEXTENDER_Documented protected:
  /**
  * @copydoc SbProjection::apply
  */
  virtual void apply( SbVec3f &point );

  SoINTERNAL public:

  //Special case for lon_0 parameter
  virtual void internalSetParameter( int parameterId, const SbString &parameterString, SbBool notifyNode = TRUE, SbBool callInit = TRUE);

  // just here to avoid warning on SUN
  virtual void internalSetParameter( int parameterId, const float &parameterString, SbBool notifyNode = TRUE, SbBool callInit = TRUE)
  { SbProjection::internalSetParameter( parameterId, parameterString, notifyNode , callInit ); }

protected:

  void internalInit();

  /**
  * initialisation of PROJ.4 parameters
  */
  void initProj4Params();

  // ellipsoid
  SbProj4Projection::PredefinedEllipsoid m_ellipsoid;

  // ellipsoid
  SbProj4Projection::PredefinedEllipsoid m_ellipsoidIn;

  // CoordinateSystem
  SbProj4Projection::CoordinateSystem m_coordinateSystem;

  // hint about first initialisation
  bool m_firstInit;

  // lon_0 if set to workaround linux Proj4 crash
  // lon_0 is not sent to Proj4, but auto computed in project() function
  double m_lon0;

  // zone (UTM)
  int m_zone;

  // south hemisphere (UTM)
  bool m_south;

  bool m_revertCoordNeeded;

  // number of internal projection
  int m_numProjections;

  //Current proj id
  int m_projID;

  //Current proj in id
  int m_projInID;

  // type of projection
  void *m_projType;

  // type of projection
  void *m_projTypeIn;
};

#endif /* _SB_PROJ4PROJECTION_ */

