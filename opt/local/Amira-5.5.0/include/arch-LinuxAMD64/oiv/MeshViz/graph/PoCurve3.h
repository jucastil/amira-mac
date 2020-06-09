/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CURVE3_
#define  _PO_CURVE3_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFVec3f.h>

/**
 * @DTEXT  Builds a 3D curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Class to build a 3D curve. The curve is defined by a set of points. Different 
 *    representations of the curve can be obtained such as a polyline curve or a smooth 
 *    curve.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCurve3 {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0 0
 *       @TR curveRep @TD CURVE_POLYLINE
 *       @TR isMarkerVisible @TD FALSE
 *       @TR markerString @TD "."
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocurve3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCurve3 : public PoGraphMaster {
  
  SO_KIT_HEADER(PoCurve3) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(curvePointSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curvePointApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(curvePoint)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(markerSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(markerApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(marker)    ;


 public:

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
    CURVE_SMOOTH    
  } ;





  /* Fields */

  /**
   * Point list of the curve.
   */
  SoMFVec3f  point ;

  /**
   * Defines the curve representation (polyline, smooth or none). CURVE_POLYLINE by default.
   */
  SoSFEnum   curveRep ;

  /**
   * Indicates if a marker is generated on each curve point.
   */
  SoSFBool   isMarkerVisible ;

  /**
   * The markers are defined by a string. If this field is equal to ".", the markers are 
   * SoPointSet shapes, otherwise SoText2 shapes. To change the font of text 
   * markers, set the catalog part markerApp.font.name . Be careful, for the 
   * moment, text markers are not vertically aligned.
   */
  SoSFString markerString ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCurve3()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,IN]
   */
  PoCurve3(int numPoints, const SbVec3f *_point, CurveRep _curveRep = CURVE_POLYLINE)
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
  virtual ~PoCurve3() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec3f *_point=NULL, 
            CurveRep _curveRep = CURVE_POLYLINE) ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CURVE3_ */

