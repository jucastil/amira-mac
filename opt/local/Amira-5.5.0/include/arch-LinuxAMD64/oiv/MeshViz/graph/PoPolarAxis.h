/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_POLAR_AXIS_
#define  _PO_POLAR_AXIS_

#include <MeshViz/graph/PoAxis.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Abstract class for polar axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    Abstract class for polar axes. This class handles the offset, start radius, end radius 
 *    and the rotation angle theta of polar axis. The inherited fields 
 *    gridLengthGradSide and gridLengthGradOtherSide are expressed in radians (grid 
 *    lines are arcs of circle).
 * 
 */
class MESHVIZ_API PoPolarAxis : public PoAxis {

  SO_KIT_HEADER(PoPolarAxis) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactor) ;



 public:

  /**
   *  Type of position of the multiplicative factor.
   */
  enum MultFactorPosition {
    /**
     *  The multiplicative factor is at the start of the axis.
     */
    MULT_FACTOR_START,  
    /**
     *  The multiplicative factor is at the end of the axis.
     */
    MULT_FACTOR_END,    
    /**
     *  The multiplicative factor is at the start and at the end of the axis.
     */
    MULT_FACTOR_EXTR,   
    /**
     *  The multiplicative factor is at the graduations of the axis.
     */
    MULT_FACTOR_GRAD    
  } ;

  /* Fields */

  /**
   * Offset for the axis.
   */
  SoSFFloat offset ;

  /**
   * Radius at the start of the axis.
   */
  SoSFFloat startRadius ;

  /**
   * Radius at the end of the axis.
   */
  SoSFFloat endRadius ;

  /**
   * Rotation angle of the axis in radians.
   */
  SoSFFloat theta ;

  /* Ten power attributes */

  /**
   * Position of the multiplicative factor.
   */
  SoSFEnum  multFactorPosition ;

  /**
   * Distance from the mutiplicative factor to the axis. 
   * This value is a percentage of the current domain 
   * (cf PoBase description). If this value is <= 0,
   * the distance is automatically calculated.
   */
  SoSFFloat multFactorDistAxis ;

  /**
   * Returns the current multiplicative factor attributes (those computed can be 
   * different from the associated fields).
   * [OIVJAVA-WRAPPER PACK{MultFactor}]
   */
  void  getMultFactor(MultFactorPosition &position, float &distAxis) const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  struct MultFactor {
    MultFactorPosition position ;
    float              distAxis ;
  } ;

 protected:
  struct PolarAxisAttr {
    MultFactor     multFactor ;
  } ;
  // Polar axis attr

  // Constructor
  PoPolarAxis(float offset = 0., float startRadius = 0., float endRadius = 1.,
              float theta = 0.) ;
  // Destructor
  virtual ~PoPolarAxis() ;

  // Methods
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Build tick - The ticks are built under the node "group"
  virtual void buildGridLines(int numGrad, const float *xGrad, SoGroup *group) ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

  // Computed polar axis attributes
  PolarAxisAttr  polAxisAttr ;

 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_POLAR_AXIS_ */

