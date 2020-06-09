/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CARTESIAN_AXIS_
#define  _PO_CARTESIAN_AXIS_

#include <MeshViz/graph/PoAxis.h>
#include <MeshViz/graph/PbDomain.h>


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>


class SoTransform ;

/**
 * @DTEXT  Abstract class for cartesian axes.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class handles the start, end, and the type of 
 *    the cartesian axis.
 * 
 */
class MESHVIZ_API PoCartesianAxis : public PoAxis {

  SO_KIT_HEADER(PoCartesianAxis) ;


 public:



  /* Fields */

  /**
   * Defines the start of the axis.
   */
  SoSFVec3f start ;

  /**
   * Defines the end of the axis.
   */
  SoSFFloat end ;

  /**
   * Type of the axis (XY, XZ, YX, ... axis).
   * For instance if the type is XY, it means an X-Axis in the plane XY.
   */
  SoSFEnum  type ;

  /**
   *  Type of axis orientation.
   */
  enum Type {
    /**
     *  X-Axis in the plane XY
     */
    XY,       
    /**
     *  X-Axis in the plane XZ
     */
    XZ,       
    /**
     *  Y-Axis in the plane YX
     */
    YX,       
    /**
     *  Y-Axis in the plane YZ
     */
    YZ,       
    /**
     *  Z-Axis in the plane ZX
     */
    ZX,       
    /**
     *  Z-Axis in the plane ZY
     */
    ZY        
  } ;



  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  PoCartesianAxis() ;
  // Constructor

  virtual ~PoCartesianAxis() ;
  // Destructor

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Compute axis tranformation
  void computeTransfo(const SbVec3f &refPoint, SoMatrixTransform *transfo, 
                      float &deltaX, float &deltaY) ;
  
 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CARTESIAN_AXIS_ */

