/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GROUP_2_AXIS_
#define  _PO_GROUP_2_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFString.h>

#include <MeshViz/graph/PoBaseAxis.h>

class PoCartesianAxis ;

/**
 * @DTEXT  Class to build a group of two axes.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a group of two axes in the plane XY. This group contains one 
 *    horizontal axis (X-axis) and one vertical axis (Y-axis).
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGroup2Axis {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0
 *       @TR end @TD 1 1
 *       @TR xTitle @TD ""
 *       @TR yTitle @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogroup2axis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoGroup2Axis : public PoBaseAxis {

  SO_KIT_HEADER(PoGroup2Axis) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(xAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yAxis) ;


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
   * Start point of the both axis. (0,0) by default.
   */
  SoSFVec2f   start ;

  /**
   * Defines the end point of the both axis. 
   * The X-axis is generated from the point "start" to the point (end[0], start[1]).
   * The Y-axis is generated from the point start to the point (start[0], end[1]).
   * (1,1) by default.
   */
  SoSFVec2f   end ;

  /**
   * Title of the horizontal axis. Empty by default.
   */
  SoSFString  xTitle ;

  /**
   * Title of the vertical axis. Empty by default.
   */
  SoSFString  yTitle ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoGroup2Axis()
    { init(SbVec2f(0., 0.), SbVec2f(1., 1.), LINEAR, LINEAR, NULL, NULL) ; }

  /**
   * Constructor.
   */
  PoGroup2Axis(const SbVec2f &_start, const SbVec2f &_end, AxisType _xAxisType,
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
  virtual ~PoGroup2Axis() ;

 private:
  // Init method
  void init(const SbVec2f &start, const SbVec2f &end, AxisType xAxisType,
            AxisType yAxisType, const char *xTtle = NULL, const char *yTtle = NULL) ;
  
  // Init axis
  void initAxis(PoCartesianAxis *xAxis, PoCartesianAxis *yAxis) ;

  SoSFEnum xAxisType, yAxisType ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
  
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_GROUP_2_AXIS_ */

