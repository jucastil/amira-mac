/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GROUP_6_AXIS_3_
#define  _PO_GROUP_6_AXIS_3_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFString.h>

#include <MeshViz/graph/PoBaseAxis.h>

class PoCartesianAxis ;

/**
 * @DTEXT  Class to build a group of six axes.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a group of six axes. This group contains two parallel X-axes, 
 *    two parallel Y-axes and two parallel Z-axes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGroup6Axis3 {
 *    @TABLE_FILE_FORMAT
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1 1 1
 *       @TR xTitle @TD ""
 *       @TR yTitle @TD ""
 *       @TR zTitle @TD ""
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogroup6axis3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoGroup6Axis3 : public PoBaseAxis {

  SO_KIT_HEADER(PoGroup6Axis3) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(xUpAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(xDownAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yLeftAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(yRightAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zUpAxis) ;
  SO_KIT_CATALOG_ENTRY_HEADER(zDownAxis) ;


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
   * Start point of the cube.
   */
  SoSFVec3f   start ;

  /**
   * End point of the cube.
   */
  SoSFVec3f   end ;

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
  PoGroup6Axis3()
    { init(SbVec3f(0., 0., 0.), SbVec3f(1., 1., 1.), LINEAR, LINEAR, LINEAR, 
           NULL, NULL, NULL) ; }

  /**
   * Constructor. (By default the 6 axes are linear).
   */
  PoGroup6Axis3(const SbVec3f &_start, const SbVec3f &_end, AxisType _xAxisType,
                AxisType _yAxisType, AxisType _zAxisType,
                const char *xTtle = NULL, const char *yTtle = NULL,
                const char *zTtle = NULL)
    { init(_start, _end, _xAxisType, _yAxisType, _zAxisType, xTtle, yTtle, zTtle) ; }

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
  virtual ~PoGroup6Axis3() ;

 private:
  // Init method
  void init(const SbVec3f &start, const SbVec3f &end, AxisType xAxisType,
            AxisType yAxisType, AxisType zAxisType,
            const char *xTtle = NULL, const char *yTtle = NULL,
            const char *zTtle = NULL) ;
  
  // Init axis
  void initAxis(PoCartesianAxis *xDownAxis, PoCartesianAxis *xUpAxis, 
                PoCartesianAxis *yLeftAxis, PoCartesianAxis *yRightAxis,
                PoCartesianAxis *zDownAxis, PoCartesianAxis *zUpAxis) ;
  
  SoSFEnum xAxisType, yAxisType, zAxisType ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
  
} ; 
/*----------------------------------------------------------------------------*/

#endif /* _PO_GROUP_6_AXIS_3_ */

