/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ERROR_CURVE_
#define  _PO_ERROR_CURVE_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>

/**
 * @DTEXT  Class to build an error curve represention.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Class to build an error curve in the plane XY. An error curve is a curve 
 *    (defined by a point list) with a low curve and a high curve which represent 
 *    the error.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoErrorCurve {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *       @TR lowY @TD 0
 *       @TR highY @TD 0
 *       @TR variationType @TD REL_VARIATION
 *       @TR errorCurveRep @TD HIGH_LOW_CLOSE
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poerrorcurve.cat.html
 * 
 * 
 */
class MESHVIZ_API PoErrorCurve : public PoGraphMaster {
  
  SO_KIT_HEADER(PoErrorCurve) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve1Sep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve1App) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve1)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve2Sep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve2App) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve2)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve3Sep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve3App) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve3)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve4Sep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve4App) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve4)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve5Sep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve5App) ;
  SO_KIT_CATALOG_ENTRY_HEADER(errorCurve5)    ;


 public:

  /**
   *  Type of interpretation of the fields lowY and highY.
   */
  enum VariationType {
    FIXED_VARIATION,
    REL_VARIATION,
    PERCENT_FIXED_VARIATION,
    PERCENT_REL_VARIATION
  } ;

  /**
   *  Type of error curve representation.
   */
  enum ErrorCurveRep {
    /**
     *  The error curve is a high low close representation.
     */
    HIGH_LOW_CLOSE, 
    /**
     *  The error curve is a line bar representation.
     */
    LINE_BAR,       
    /**
     *  The error curve is a filled representation.
     */
    FILLED          
  } ;



  /* Fields */

  /**
   * List of coordinates of the error curve.
   */
  SoMFVec2f point ;

  /**
   * List of the low ordinates for the low curve. The number of low ordinates must 
   * be equal to the number of points of point.
   */
  SoMFFloat lowY ;

  /**
   * List of the high ordinates for the high curve. The number of high ordinates 
   * must be equal to the number of points of point.
   */
  SoMFFloat highY ;

  /**
   * Defines the interpretation of the values lowY and highY.
   * The ordinate yl of the i-th point of the low curve depends on the value of this 
   * field:
   *     - FIXED_VARIATION:             yl = lowY[i]
   *    - REL_VARIATION:                        yl = point[i][1] - lowY[i]
   *    - PERCENT_FIXED_VARIATION:      yl = point[i][1] * lowY[i]
   *    - PERCENT_REL_VARIATION:        yl = point[i][1] - (lowY[i] * point[i][1])
   *
   * The same method is used to compute yh, the ordinate of the i-th point of the 
   * high curve.
   */
  SoSFEnum  variationType ;

  /**
   * Defines the error curve representation. There are three types of representations: 
   * high low close representation (HIGH_LOW_CLOSE), line bar representation 
   * (LINE_BAR) and filling representation (FILLED).
   */
  SoSFEnum  errorCurveRep ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoErrorCurve()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,ARRAY,IN,IN]
   */
  PoErrorCurve(int numPoints, const SbVec2f *_point, const float *_lowY, 
               const float *_highY, VariationType type = REL_VARIATION, 
               ErrorCurveRep rep = HIGH_LOW_CLOSE)
    { init(FALSE, numPoints, _point, _lowY, _highY, type, rep) ; } 

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
  virtual ~PoErrorCurve() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec2f *_point=NULL, 
            const float *_lowY=NULL, const float *_highY=NULL, 
            VariationType type = REL_VARIATION, ErrorCurveRep rep = HIGH_LOW_CLOSE) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_ERROR_CURVE_ */

