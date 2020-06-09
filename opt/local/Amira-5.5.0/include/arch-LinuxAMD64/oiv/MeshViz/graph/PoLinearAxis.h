/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LINEAR_AXIS_
#define  _PO_LINEAR_AXIS_


#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>


#include <MeshViz/graph/PoCartesianAxis.h>
#include <MeshViz/graph/PiNumericFormat.h>
#include <MeshViz/graph/PbNumericDisplayFormat.h>

/**
 * @DTEXT  Class to build a linear axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds a linear axis. This axis will be generated between the  
 *    point start to the point end. The graduations will be in the plane given 
 *    by the user (cf field PoCartesianAxis::type).
 * 
 *    Graduations format depends on the current numerical display format.
 *    If the method setFormat(format) is called, the current numerical display 
 *    format is "format". Otherwise the current numerical display format 
 *    is specified in the current inherited state (cf property node 
 *    PoNumericDisplayFormat).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoLinearAxis {
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
 *       @TR start @TD 0 0 0
 *       @TR end @TD 1
 *       @TR type @TD XY
 *       @TR step @TD 0
 *       @TR gradFit @TD GRAD_UNFIT
 *       @TR multFactorPosition @TD MULT_FACTOR_END
 *       @TR multFactorDistAxis @TD 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE polinearaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoLinearAxis : public PoCartesianAxis {

  SO_KIT_HEADER(PoLinearAxis) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorSep) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactorApp) ;
  SO_KIT_CATALOG_ENTRY_HEADER(multFactor) ;


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
   * Defines the step for the axis. If this value is <= 0, the step is automatically 
   * calculated.
   */
  SoSFFloat step ;

  /**
   * This flag indicates if the first graduation is rounded or not.
   */
  SoSFEnum  gradFit ;

  /* Ten power attributes */

  /**
   * Position of the multiplicative factor.
   */
  SoSFEnum  multFactorPosition ;

  /**
   * Distance from the multiplicative factor to the axis. 
   * This value is a percentage of the current domain 
   * (cf PoBase description). If this value is <= 
   * 0, the distance is automatically calculated.
   */
  SoSFFloat multFactorDistAxis ;

  /* Methods */

  /**
   * Default constructor.
   */
  PoLinearAxis()
    { init(SbVec3f(0.,0.,0.), 1., XY, 0.) ; }

  /**
   * Constructor.
   */
  PoLinearAxis(const SbVec3f &_start, float _end, PoCartesianAxis::Type _type, float _step = 0.0) 
    { init(_start, _end, _type, _step) ; }

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
   * Returns the current step attribute (the step computed can be different from the 
   * associated field).
   */
  float getStep() const ;

  /**
   * Returns the current multiplicative factor attributes (those computed can be 
   * different from the associated field).
   * [OIVJAVA-WRAPPER PACK{MultFactor}]
   */
  void  getMultFactor(MultFactorPosition &position, float &distAxis) const ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:

  static void initClass() ;
	static void exitClass() ;

  // Compute step for linear graduations.
  // If requestStep <= 0., a step is automatically compute thanks
  // to deltaValue
  static void getLinGradStep(float deltaValue, float &requestStep) ;

  // Determine the firstGrad and the number of graduations for a linear axis
  // from graduation fit, the origin and and the extremity of the axis, and
  // the step between graduations requested.
  static void getLinGradFirstGrad(GradFit fit, float firstVal,
                                  float lastVal, float step, float &firstGrad,
                                  int &numGrad) ;

  // This method combines the two previous methods
  static void getLinGrads(GradFit fit, float firstVal, float lastVal,
                          float &requestStep, float &firstGrad, int &numGrad) ;

  struct MultFactor {
    MultFactorPosition position ;
    float              distAxis ;
  } ;

 protected:

  // Linear axis attr
  struct LinAxisAttr {
    MultFactor      multFactor ;
    PiNumericFormat numericFormat ;
    float           step ;
    float           firstVal ;
  } ;

  // Methods
  // Destructor
  virtual ~PoLinearAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Manage the connection with PbBase objects
  virtual void basicObjectChange(PbBase *basicObj) ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

  // overloaded methods
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

 private:
  // Init method
  void init(const SbVec3f &start, float end, Type typeAxis, float s = 0.0) ;

  // Numeric Display format
  PbNumericDisplayFormat *m_numericDisplayFormat, m_defaultNumericDisplayFormat ;

  // Computed linear axis attributes
  LinAxisAttr  linAxisAttr ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_LINEAR_AXIS_ */


