/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CURVE_
#define  _PO_CURVE_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFString.h>


/**
 * @DTEXT  Builds a 2D curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Class to build a curve in the plane XY. The curve is defined by a set of points. 
 *    Different representations of the curve can be obtained, such as polyline curve, 
 *    smooth curve, stair curve or double stair curve. The curve can be filled. 
 *    Furthermore, some filters control the appearance of markers (on the curve) and 
 *    raise points (vertical lines from the curve to a threshold).
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCurve {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *       @TR curveRep @TD CURVE_POLYLINE
 *       @TR fillingThreshold @TD 0.0
 *       @TR isCurveFilled @TD FALSE
 *       @TR markerFilterType @TD INACTIVE
 *       @TR markerIndexPeriod @TD 0
 *       @TR markerIndexList @TD 0
 *       @TR markerXPeriod @TD 0
 *       @TR markerXList @TD 0
 *       @TR markerString @TD "."
 *       @TR raiseFilterType @TD INACTIVE
 *       @TR raiseIndexPeriod @TD 0
 *       @TR raiseIndexList @TD 0
 *       @TR raiseXPeriod @TD 0
 *       @TR raiseXList @TD 0
 *       @TR raiseThreshold @TD 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocurve.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCurve : public PoGraphMaster {
  
  SO_KIT_HEADER(PoCurve) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(curveFillingSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curveFillingApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curveFilling)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(curvePointSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curvePointApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curvePoint)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(markerSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(markerApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(marker)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(raisePointSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(raisePointApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(raisePoint)    ;


 public:

  /**
   *  Filter type.
   */
  enum FilterType {
    /**
     *  Filter is inactive
     */
    INACTIVE,     
    /**
     *  All points of point are selected.
     */
    ALL_POINTS,   
    /**
     *  One point of point in every indexPeriod is selected.
     */
    INDEX_PERIOD, 
    /**
     *  A list of points of point is selected by their indices.
     */
    INDEX_LIST,   
    /**
     *  One point of computed curve points is selected in every xPeriod.
     */
    X_PERIOD,     
    /**
     *  A list of points of computed curve points are selected by a list of abscises.
     */
    X_LIST        
  } ;



  /**
   *  Curve representation.
   */
  enum CurveRep {
    /**
     *  No curve is built.
     */
    CURVE_NONE,       
    /**
     *  The curve is a sequence of straight lines linking all points.
     */
    CURVE_POLYLINE,   
    /**
     *  The curve is a smoothing passing through all points.
     */
    CURVE_SMOOTH,     
    /**
     *  Stair curve passing through all points.
     */
    CURVE_STAIRS_X,   
    /**
     *  Stair curve passing through all points.
     */
    CURVE_STAIRS_Y,   
    /**
     *  Stair curve no necessarily passing through all points
     */
    CURVE_HISTO_X,    
    /**
     *  Stair curve no necessarily passing through all points
     */
    CURVE_HISTO_Y,    
    /**
     *  Double stair curve.
     */
    CURVE_STAIRS_2X,  
    /**
     *  Double stair curve.
     */
    CURVE_STAIRS_2Y   
  } ;





  /* Fields */

  /**
   * Point list of the curve.
   */
  SoMFVec2f point ;

  /**
   * Defines the curve representation (polyline, smooth, stair, ...)
   */
  SoSFEnum  curveRep ;

  /**
   * Indicates if the curve is filled or not.
   */
  SoSFBool  isCurveFilled ;

  /**
   * Defines the threshold to fill the curve.
   */
  SoSFFloat fillingThreshold ;

  /**
   * Defines the type of marker filter. This value 
   * determines which filter is active (markerIndexPeriod or 
   * markerIndexList,...)
   */
  SoSFEnum   markerFilterType ;

  /**
   * One point (of point) in every consecutive 
   * markerIndexPeriod is selected.
   */
  SoSFInt32  markerIndexPeriod ;

  /**
   * A list of points (of point) is selected by their 
   * indices.
   */
  SoMFInt32  markerIndexList ;

  /**
   * One point (of the computed curve points) in 
   * every markerXPeriod is selected.
   */
  SoSFFloat  markerXPeriod ;

  /**
   * A list of points (of the computed curve points) 
   * is selected by their abscises.
   */
  SoMFFloat  markerXList ;

  /**
   * The markers are defined by a string. If this 
   * field is equal to ".", the markers are 
   * SoPointSet shapes, otherwise SoText2 shapes. 
   * To change the font of text markers, set the 
   * catalog part markerApp.font.name. Be careful, 
   * in this version, text markers are not vertically 
   * aligned.
   */
  SoSFString markerString ;

  /**
   * Defines the type of raise filter. This value 
   * determines which filter is active (raiseIndexPeriod or 
   * raiseIndexList,...)
   */
  SoSFEnum  raiseFilterType ;

  /**
   * One point (of point) in every consecutive 
   * raiseIndexPeriod is selected.
   */
  SoSFInt32 raiseIndexPeriod ;

  /**
   * A list of points (of point) is selected by their 
   * indices.
   */
  SoMFInt32 raiseIndexList ;

  /**
   * One point (of the computed curve points) in 
   * every raiseXPeriod is selected.
   */
  SoSFFloat raiseXPeriod ;

  /**
   * A list of points (of the computed curve points) 
   * is selected by their abscises.
   */
  SoMFFloat raiseXList ;

  /**
   * Raise points are vertical lines joining the curve 
   * points and the specified threshold.
   */
  SoSFFloat raiseThreshold ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCurve()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,IN]
   */
  PoCurve(int numPoints, const SbVec2f *_point, CurveRep _curveRep = CURVE_POLYLINE)
    { init(FALSE, numPoints, _point, _curveRep) ; } 

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoCurve() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec2f *_point=NULL, 
            CurveRep _curveRep = CURVE_POLYLINE) ;
  
  // Build raise points
  void drawRaisePoints(int numPoints, const SbVec3f *pointList) ;

  // Build markers
  void drawMarkers(int numPoints, const SbVec3f *pointList) ;

  // Compute interpolation
  static void calculateInterpolation(const SbVec2f &a, const SbVec2f &b, float x, 
                                     float &y) ;
  static void calculateInterpolation2(const SbVec2f &a, const SbVec2f &b, float y, 
                                      float &x) ;
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CURVE_ */

