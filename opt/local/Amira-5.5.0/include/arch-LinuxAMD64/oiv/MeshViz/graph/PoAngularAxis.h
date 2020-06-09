/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_ANGULAR_AXIS_
#define  _PO_ANGULAR_AXIS_

#include <MeshViz/graph/PoAxis.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

#define PATH_HOR      PATH_RIGHT
#define PATH_RADIAL   PATH_LEFT
#define PATH_TANGENT  PATH_UP

#define GRAD_INSIDE   GRAD_ABOVE
#define GRAD_OUTSIDE  GRAD_BELOW

/**
 * @DTEXT  Class to build an angular axis.
 * 
 * @ingroup GraphAxis
 * 
 * @DESCRIPTION
 *    This class builds an angular axis in the plane XY. The axis is generated between 
 *    (startAngle + offset) and (endEngle + offset) in counter-clockwise. It is centered at 
 *    (0,0). An angle step defines the angular distance between two graduations. 
 *    Graduations are displayed in degrees. 
 *    The inherited field reverseFlag is not used.
 * @CATALOG_PARTS_INCLUDE poangularaxis.cat.html
 * 
 * 
 */
class MESHVIZ_API PoAngularAxis : public PoAxis {

  SO_KIT_HEADER(PoAngularAxis) ;


 public:

  /**
   * Enumerations
   */

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
   * Offset for the axis in radians. (However the graduations begin at startAngle to 
   * endAngle).
   */
  SoSFFloat offset ;

  /**
   * Angle in radians of the origin of the axis.
   */
  SoSFFloat startAngle ;

  /**
   * Angle in radians of the end of the axis.
   */
  SoSFFloat endAngle ;

  /**
   * Radius of the axis.
   */
  SoSFFloat radius ;

  /**
   * Angular distance in radians between two graduations. If this value is <= 0, the 
   * angle step is automatically calculated according to the ratio radius and the 
   * current domain (see PoBase description).
   */
  SoSFFloat angleStep ;

  /**
   * This flag indicates if the first graduation is rounded or not. (GRAD_UNFIT by 
   * default).
   */
  SoSFEnum  gradFit ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoAngularAxis() ;

  /**
   * Constructor.
   */
  PoAngularAxis(float _offset, float _startAngle, float _endAngle, float _radius, 
                float _angleStep)
    { init(_offset, _startAngle, _endAngle, _radius, _angleStep) ; } 

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /**
   * Returns the current angle step (the step computed can be different from the 
   * associated field).
   */
  float getAngleStep() const ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  struct AngularAxisAttr {
    float angleStep ;
    float startAngle ;
  } ;
  // Angular axis attr

  // Methods
  // Destructor
  ~PoAngularAxis() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

  // Save all axis attributes which can be modified by MeshViz.
  virtual void saveAxisAttr() ;

 private:
  // Compute limit coordinate for display graduation
  virtual void computeGradLimit(float sAngle, float eAngle, 
                                float &smAngle, float &emAngle) ;

  // Compute tick length
  virtual void computeAngularTickLen(int numGrad, float theta, 
                                     float &mainTickLen, float &secdTickLen) ;

  // Set Default attributes
  virtual void setDefaultAttr(Plane plane = XY) ;

  // Build arrow - The arrow is built under the node "group"
  virtual void buildArrow(float radius, float angle, SoGroup *group) ;
  
  // Build title - The title is built under the node "group"
  void buildTitle(float start_angle, float theta, SoGroup *group) ;

  // Build tick - The ticks are built under the node "group"
  virtual void buildTick(int numGrad, const float *gradAngleList, 
                         float tickLen, SoGroup *group) ;

  // Build grid lines - The grid lines are built under the node "group"
  virtual void buildGridLines(int numGrad, const float *gradAngleList, 
                              SoGroup *group) ;

  // Compute the step
  void computeGradStep(float _radius, float theta, float &step) ;

  // Compute grad list str
  void computeGradListStr(float theta_m, float start_angle_m, float s_angle_m, 
                          float angle_step, int &num_grad, float *grad_angle_list, 
                          char **grad_str) ;

  // Build graduations - The graduations are built under the node "group"
  // (used only by generalised, linear and polar linear axis)
  virtual void buildGrads(int numGrad, const float *gradAngleList, 
                          const char **gradStr, SoGroup *group) ;

  // Draw an angular text in polar coordinate
  void drawAngularText(PiText *text, TextPath path, GradPosition pos,
                       float rad, float angle, const SbString& str) ;

  // Init method
  void init(float offset, float startAngle, float endAngle, float radius, 
            float angleStep) ;

  // Computed axis attributes
  AngularAxisAttr angularAxisAttr ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_ANGULAR_AXIS_ */

