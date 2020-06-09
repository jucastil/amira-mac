/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GROUP_4_AXIS_
#define  _PO_GROUP_4_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFString.h>

#include <MeshViz/graph/PoBaseAxis.h>

class PoCartesianAxis ;

/**
 * @DTEXT  Class to build a group of four axes.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a group of four axes in the plane XY. This group contains two 
 *    parallel horizontal axes (X-axis) and two parallel vertical axes (Y-axis) which 
 *    define a rectangle of axes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGroup4Axis {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0
 *       @TR end @TD 1 1
 *       @TR xTitle @TD ""
 *       @TR yTitle @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogroup4axis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoGroup4Axis : public PoBaseAxis {

  SO_KIT_HEADER(PoGroup4Axis) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(xUpAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xDownAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yLeftAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yRightAxis) ;


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



  /* Fields */

  /**
   * Start point of the bottom horizontal axis and of the left vertical axis.
   * The first X-axis is generated from the point "start" to the point (end[0], start[1]).
   * The second X-axis is generated from the point (start[0], end[1]) to the point "end".
   * The first Y-axis is generated from the point "start" to the point (start[0], end[1]).
   * The second Y-axis is generated from the point (end[0], start[1]) to the point "end".
   */
  SoSFVec2f   start ;

  /**
   * End point of the top horizontal axis and of the right vertical axis.
   */
  SoSFVec2f   end ;

  /**
   * Title of the horizontal axes. Empty by default.
   */
  SoSFString  xTitle ;

  /**
   * Title of the vertical axes. Empty by default.
   */
  SoSFString  yTitle ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoGroup4Axis()
    { init(SbVec2f(0., 0.), SbVec2f(1., 1.), LINEAR, LINEAR, NULL, NULL) ; }

  /**
   * Constructor. (By default the 4 axes are linear axes).
   */
  PoGroup4Axis(const SbVec2f &_start, const SbVec2f &_end, AxisType _xAxisType,
               AxisType _yAxisType, const char *xTtle = NULL, const char *yTtle = NULL)
    { init(_start, _end, _xAxisType, _yAxisType, xTtle, yTtle) ; }

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
  virtual ~PoGroup4Axis() ;

 private:
  // Init method
  void init(const SbVec2f &start, const SbVec2f &end, AxisType xAxisType,
            AxisType yAxisType, const char *xTtle = NULL, const char *yTtle = NULL) ;

  // Init axis
  void initAxis(PoCartesianAxis *xDownAxis, PoCartesianAxis *xUpAxis, 
                PoCartesianAxis *yLeftAxis, PoCartesianAxis *yRightAxis) ;

  SoSFEnum xAxisType, yAxisType ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
  
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_GROUP_4_AXIS_ */

