/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_POLAR_LIN_AXIS_
#define  _PO_POLAR_LIN_AXIS_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

#include <MeshViz/graph/PoPolarAxis.h>
#include <MeshViz/graph/PiNumericFormat.h>
#include <MeshViz/graph/PbNumericDisplayFormat.h>

/**
 * @DTEXT  Class to build a polar linear axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a polar linear axis in the plane XY. This axis will be generated 
 *    from the point in polar coordinate (startRadius + offset, theta) to the point 
 *    (endRadius + offset, theta), however the graduations start at startRadius and finish 
 *    at endRadius.
 * 
 *    Graduations format depends on the current numerical display format.
 *    If the method setFormat(format) is called, the current numerical display 
 *    format is "format". Otherwise the current numerical display format 
 *    is specified in the current inherited state (cf property node 
 *    PoNumericDisplayFormat).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPolarLinAxis {
 *    @TABLE_FILE_FORMAT
 *       @TR gradVisibility @TD VISILITY_DEPEND
 *       @TR gradPosition @TD GRAD_DEPEND
 *       @TR gradPath @TD PATH_DEPEND
 *       @TR gradFontName @TD ""
 *       @TR gradFontSize @TD 0
 *       @TR gradDistAxis @TD 0
 *       @TR gradAddStringVisibility @TD FALSE
 *       @TR gradAddString @TD ""
 *       @TR marginType @TD REL_MARGIN
 *       @TR marginStart @TD 0
 *       @TR marginEnd @TD 0
 *       @TR titleVisibility @TD VISILITY_DEPEND
 *       @TR titlePosition @TD TITLE_DEPEND
 *       @TR titlePath @TD PATH_DEPEND
 *       @TR titleFontName @TD ""
 *       @TR titleFontSize @TD 0
 *       @TR titleDistAxis @TD 0
 *       @TR titleString @TD ""
 *       @TR gridVisibility @TD VISILITY_DEPEND
 *       @TR gridLengthGradSide @TD 0
 *       @TR gridLengthGradOtherSide @TD 1
 *       @TR arrowVisibility @TD VISIBILITY_DEPEND
 *       @TR arrowHeight @TD 0.03
 *       @TR arrowLength @TD 0.05
 *       @TR tickVisibility @TD VISIBILITY_DEPEND
 *       @TR tickPosition @TD TICK_GRAD_SIDE
 *       @TR tickMainLength @TD 0
 *       @TR tickSubLength @TD 0
 *       @TR tickSubDef @TD PERIOD_MAIN_TICK
 *       @TR tickNumOrPeriod @TD 1
 *       @TR tickFirstGrad @TD 1
 *       @TR tickLastGrad @TD 1
 *       @TR reverseFlag @TD AXIS_REVERSE_DEPEND
 *       @TR offset @TD 0
 *       @TR startRadius @TD 0
 *       @TR endRadius @TD 1
 *       @TR theta @TD 0
 *       @TR multFactorPosition @TD MULT_FACTOR_END
 *       @TR multFactorDistAxis @TD 0
 *       @TR step @TD 0
 *       @TR gradFit @TD GRAD_UNFIT
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE popolarlinaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoPolarLinAxis : public PoPolarAxis {

  SO_KIT_HEADER(PoPolarLinAxis) ;


 public:

  /**
   *  First graduation rounded or not.
   */
  enum GradFit {
    /**
     *  The first graduation is rounded.
     */
    GRAD_FIT,   
    /**
     *  The first graduation is not rounded.
     */
    GRAD_UNFIT  
  } ;

  /* Fields */

  /**
   * Defines the step for the axis. If this value is <= 0, the step is automatically 
   * calculated.
   */
  SoSFFloat step ;

  /**
   * This flag indicates if the first graduation is rounded or not.
   */
  SoSFEnum  gradFit ;

  /**
   * Default constructor.
   */
  PoPolarLinAxis() ;

  /**
   * Constructor.
   */
  PoPolarLinAxis(float offset, float startRadius, float endRadius, float theta, 
                 float step = 0.0) ;



  /* Methods */

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /**
   * Sets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format for the graduations. If this method is not called
   * (or called passing NULL as argument), this is the numerical display format 
   * defined in the current inherited state (defined with the property node 
   * PoNumericDisplayFormat) which is used.
   */
  void setFormat(PbNumericDisplayFormat *format) ;

  /**
   * Gets a reference to a PbNumericDisplayFormat object for the numerical 
   * display format for the graduations. 
   */
  const PbNumericDisplayFormat *getFormat() const ;

  /**
   * Returns the step (the step computed can be different from the associated field).
   */
  float getStep() const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  struct PolarLinAxisAttr {
    float           step ;
    float           firstVal ;
    PiNumericFormat numericFormat ;
  } ;
  // Polar axis attr

  // Methods
  // Destructor
  virtual ~PoPolarLinAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

 private:
  // Init method
  void init(float step = 0.0) ;

  // Sensors
  FieldSensorList fieldSensorList ;

  // Computed polar linear axis attributes
  PolarLinAxisAttr  polLinAxisAttr ;

  // Numeric Display format
  PbNumericDisplayFormat *m_numericDisplayFormat, m_defaultNumericDisplayFormat ;

  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_POLAR_LIN_AXIS_ */

