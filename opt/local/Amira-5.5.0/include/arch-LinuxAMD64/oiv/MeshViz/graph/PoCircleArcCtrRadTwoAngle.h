/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC_CTR_RAD_TWO_ANGLE_
#define  _PO_CIRCLE_ARC_CTR_RAD_TWO_ANGLE_

#include <MeshViz/graph/PoCircleArc.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    Class to build a circle arc in the plane XY. The circle arc is defined by  
 *    its center, its radius, the start angle and the end angle.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArcCtrRadTwoAngle {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR center @TD 0 0
 *       @TR radius @TD 1
 *       @TR startAngle @TD 0
 *       @TR endAngle @TD 2PI
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearcctrradtwoangle.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArcCtrRadTwoAngle : public PoCircleArc {

  SO_KIT_HEADER(PoCircleArcCtrRadTwoAngle) ;


 public:

  /* Fields */

  /**
   * Circle center. (0,0) by default.
   */
  SoSFVec2f center ;

  /**
   * Circle radius. 1 by default.
   */
  SoSFFloat radius ;

  /**
   * Start angle. 0.0 by default.
   */
  SoSFFloat startAngle ;

  /**
   * End angle. 2PI by default.
   */
  SoSFFloat endAngle ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArcCtrRadTwoAngle()
    { init(SbVec2f(0.0, 0.0), 1.0F, 0.0F, (float)PDEUXPI) ; }

  /**
   * Constructor.
   */
  PoCircleArcCtrRadTwoAngle(const SbVec2f &_center, float _radius,
                            float _startAngle, float _endAngle)
    { init(_center, _radius, _startAngle, _endAngle) ; }

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
  virtual ~PoCircleArcCtrRadTwoAngle() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(const SbVec2f &center, float radius,
            float startAngle, float endAngle) ;

  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_ARC_CTR_RAD_TWO_ANGLE_ */

