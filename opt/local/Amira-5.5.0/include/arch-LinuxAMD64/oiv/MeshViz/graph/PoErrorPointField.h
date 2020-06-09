/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ERROR_POINT_FIELD_
#define  _PO_ERROR_POINT_FIELD_

#include <MeshViz/graph/PoGraphMaster.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFVec2f.h>

/**
 * @DTEXT  Builds points field with X and Y margin error.
 * 
 * @ingroup GraphScatter
 * 
 * @DESCRIPTION
 *    Class to build in the plane XY, a points field with X and Y margin error. 
 *    A shape and/or skeleton represents the error of each points.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoErrorPointField {
 *    @TABLE_FILE_FORMAT
 *       @TR point @TD 0 0 0
 *       @TR errorX @TD 0
 *       @TR errorY @TD 0
 *       @TR shapeType @TD RECTANGLE_SHAPE
 *       @TR skeletonType @TD CROSS1_SKELETON
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poerrorpointfield.cat.html
 * 
 * 
 */
class MESHVIZ_API PoErrorPointField : public PoGraphMaster {
  
  SO_KIT_HEADER(PoErrorPointField) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(shapeSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(shapeApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(shape)    ;

  SO_KIT_CATALOG_ENTRY_HEADER(skeletonSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeletonApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(skeleton)    ;


 public:

  /**
   *  Type of shape used to represent each point.
   */
  enum ShapeType {
    /**
     *  No shape for the point field.
     */
    NO_SHAPE,         
    /**
     *  Rectangle shape for the point field.
     */
    RECTANGLE_SHAPE,  
    /**
     *  Quadrangle shape for the point field.
     */
    QUADRANGLE_SHAPE, 
    /**
     *  Ellipse shape for the point field.
     */
    ELLIPSE_SHAPE     
  } ;

  /**
   *  Type of skeleton used to represent each point.
   */
  enum SkeletonType {
    /**
     *  No skeleton for the point field.
     */
    NO_SKELETON,     
    /**
     *  x skeleton for the point field.
     */
    CROSS1_SKELETON, 
    /**
     *  + skeleton for the point field.
     */
    CROSS2_SKELETON, 
    /**
     *  * skeleton for the point field.
     */
    CROSS3_SKELETON, 
    /**
     *  Bar skeleton for the point field.
     */
    BAR_SKELETON     
  } ;



  /* Fields */

  /**
   * List of coordinates of the point field.
   */
  SoMFVec2f point ;

  /**
   * List of abscissas errors. The number of abscissas must be equal to the number 
   * of points.
   */
  SoMFFloat errorX ;

  /**
   * List of ordinates errors. The number of ordinates must be equal to the number 
   * of points.
   */
  SoMFFloat errorY ;

  /**
   * Defines the shape associated to errors. The shape can be a rectangle, a 
   * quadrangle, an ellipse or no shape.
   */
  SoSFEnum  shapeType ;

  /**
   * Defines the skeleton associated to errors. The skeleton can be a cross, a bar or 
   * no skeleton.
   */
  SoSFEnum  skeletonType ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoErrorPointField()
    { init(TRUE) ; }

  /**
   * Constructor.
   * [OIV-WRAPPER-ARG NO_WRAP{_point->Length},ARRAY,ARRAY,ARRAY,IN,IN]
   */
  PoErrorPointField(int numPoints, const SbVec2f *_point, const float *_errorX,
                    const float *_errorY, ShapeType _shapeType = RECTANGLE_SHAPE,
                    SkeletonType _skeletonType = CROSS1_SKELETON)
    { init(FALSE, numPoints, _point, _errorX, _errorY, _shapeType, _skeletonType) ; } 

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
  virtual ~PoErrorPointField() ;
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Init method
  void init(SbBool isDefault, int numPoints=0, const SbVec2f *_point=NULL, 
            const float *_errorX=NULL, const float *_errorY=NULL, ShapeType 
            _shapeType = RECTANGLE_SHAPE, SkeletonType _skeletonType = 
            CROSS1_SKELETON) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_ERROR_POINT_FIELD_  */

