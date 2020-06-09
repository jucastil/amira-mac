/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GROUP_3_AXIS_3_
#define  _PO_GROUP_3_AXIS_3_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>

#include <MeshViz/graph/PoBaseAxis.h>

class PoCartesianAxis ;

/**
 * @DTEXT  Class to build a group of three axes.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a group of three axes. This group contains one X-axis, one Y-
 *    axis and one Z-axis which have the same start point and are orthogonal to 
 *    each other.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGroup3Axis3 {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1 1 1
 *       @TR verticalAxisName @TD Z_AXIS
 *       @TR xTitle @TD ""
 *       @TR yTitle @TD ""
 *       @TR zTitle @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogroup3axis3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoGroup3Axis3 : public PoBaseAxis {

  SO_KIT_HEADER(PoGroup3Axis3) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zAxis) ;


 public:

  /**
   *  Type of axis.
   */
  enum AxisType {
    /**
     *  Linear axis.
     */
    LINEAR,      
    /**
     *  Logarithmic axis.
     */
    LOGARITHMIC  
  } ;

  enum AxisName {
    X_AXIS,
    Y_AXIS,
    Z_AXIS
  } ;

  

  /**
   * Start point of the three axes.
   */
  SoSFVec3f   start ;

  /**
   * End coordinates of respectively the X, Y and Z axis.
   */
  SoSFVec3f   end ;

  /**
   * Name of the vertical axis.
   */
  SoSFEnum    verticalAxisName ;

  /**
   * Title of the X axis. Empty by default.
   */
  SoSFString  xTitle ;

  /**
   * Title of the Y axis. Empty by default.
   */
  SoSFString  yTitle ;

  /**
   * Title of the Z axis. Empty by default.
   */
  SoSFString  zTitle ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoGroup3Axis3()
    { init(SbVec3f(0., 0., 0.), SbVec3f(1., 1., 1.), LINEAR, LINEAR, LINEAR, 
           Z_AXIS, NULL, NULL, NULL) ; }

  /**
   * Constructor. (By default the 3 axes are linear).
   */
  PoGroup3Axis3(const SbVec3f &_start, const SbVec3f &_end, AxisType _xAxisType,
                AxisType _yAxisType, AxisType _zAxisType, AxisName vertAxis = Z_AXIS,
                const char *xTtle = NULL, const char *yTtle = NULL, 
                const char *zTtle = NULL)
    { init(_start, _end, _xAxisType, _yAxisType, _zAxisType, vertAxis, xTtle, yTtle, zTtle) ; }

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
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Destructor
  virtual ~PoGroup3Axis3() ;

 private:
  // Init method
  void init(const SbVec3f &start, const SbVec3f &end, AxisType xAxisType,
            AxisType yAxisType, AxisType zAxisType, AxisName vertAxis = Z_AXIS,
            const char *xTtle = NULL, const char *yTtle = NULL, 
            const char *zTtle = NULL) ;
  
  // Init axis
  void initAxis(PoCartesianAxis *xaxis, PoCartesianAxis *yaxis, 
                PoCartesianAxis *zaxis, AxisName vertAxis) ;

  SoSFEnum xAxisType, yAxisType, zAxisType ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
  
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_GROUP_3_AXIS_3_ */

