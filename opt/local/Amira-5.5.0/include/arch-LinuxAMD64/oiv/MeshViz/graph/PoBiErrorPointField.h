/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
                                                                              
#ifndef  _PO_BI_ERROR_POINT_FIELD_
#define  _PO_BI_ERROR_POINT_FIELD_

#include <MeshViz/graph/PoGraphMaster.h>


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoSFBool.h>


/**
 * @DTEXT  Builds a bi-error point field.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Class to build in the plane XY, a point field with two X and two Y margin 
 *    errors. A shape and/or skeleton represent the error of each points.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoBiErrorPointField {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0
 *       @TR lowX @TD 0
 *       @TR lowY @TD 0
 *       @TR highX @TD 0
 *       @TR highY @TD 0
 *       @TR variationType @TD REL_VARIATION
 *       @TR isShapeVisible @TD TRUE
 *       @TR isSkeletonVisible @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pobierrorpointfield.cat.html
 * 
 * 
 */
class MESHVIZ_API PoBiErrorPointField : public PoGraphMaster {
  
  SO_KIT_HEADER(PoBiErrorPointField) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(shapeSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(shapeApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(shape)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(skeletonSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeleton)    ;


 public:

  /**
   *  Type of interpretation of the fields lowX,lowY and highX,highY.
   */
  enum VariationType {
    FIXED_VARIATION,
    REL_VARIATION,
    PERCENT_FIXED_VARIATION,
    PERCENT_REL_VARIATION
  } ;

  /* Fields */

  /**
   * List of coordinates of the point field.
   */
  SoMFVec2f point ;

  /**
   * List of abscissas low errors. The number of abscissas must be equal to the 
   * number of points of point.
   */
  SoMFFloat lowX ;

  /**
   * List of ordinates low errors. The number of ordinates must be equal to the 
   * number of points of point.
   */
  SoMFFloat lowY ;

  /**
   * List of abscissas high errors. The number of abscissas must be equal to the 
   * number of points of point.
   */
  SoMFFloat highX ;

  /**
   * List of ordinates high errors. The number of ordinates must be equal to the 
   * number of points of point.
   */
  SoMFFloat highY ;

  /**
   * Defines the interpretation of the values lowX, lowY, highX, highY.
   * The low abscissa xl of the i-th point depends on the value of this field:
   *    - FIXED_VARIATION:              xl = lowY[i]
   *    - REL_VARIATION:                        xl = point[i][0] - lowY[i]
   *    - PERCENT_FIXED_VARIATION:      xl = point[i][0] * lowY[i]
   *    - PERCENT_REL_VARIATION:                xl = point[i][0] - (lowY[i] * point[i][0])
   *
   * The same method is used to compute the high abscissa xh, low ordinate yl and 
   * high ordinate yh.
   */
  SoSFEnum  variationType ;

  /**
   * Defines the visibility of the shape.
   */
  SoSFBool  isShapeVisible ;

  /**
   * Defines the visibility of the skeleton.
   */
  SoSFBool  isSkeletonVisible ;

  

  /* Methods */

  /**
   * Default constructor.
   */
  PoBiErrorPointField()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,ARRAY,ARRAY,ARRAY,IN,IN,IN]
   */
  PoBiErrorPointField(int numPoints, const SbVec2f *_point, const float *_lowX, 
                      const float *_lowY, const float *_highX, const float *_highY, 
                      VariationType type = REL_VARIATION, SbBool _isShapeVisible = TRUE,
                      SbBool _isSkeletonVisible = TRUE)
    { init(FALSE, numPoints, _point, _lowX, _lowY, _highX, _highY, type, 
           _isShapeVisible, _isSkeletonVisible) ; } 

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
  virtual ~PoBiErrorPointField() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec2f *_point=NULL, 
            const float *_lowX=NULL, const float *_lowY=NULL, 
            const float *_highX=NULL, const float *_highY=NULL, 
            VariationType type = REL_VARIATION, SbBool _isShapeVisible = TRUE,
            SbBool _isSkeletonVisible = TRUE) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_BI_ERROR_POINT_FIELD_  */

