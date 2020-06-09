/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC_CTR_PT_ANGLE_
#define  _PO_CIRCLE_ARC_CTR_PT_ANGLE_

#include <MeshViz/graph/PoCircleArc.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a circle arc in the plane XY. The circle arc is defined by its center, 
 *    a start point and an angle.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArcCtrPtAngle {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR center @TD 0 0 
 *       @TR startPoint @TD 1 0
 *       @TR angle @TD 2PI
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearcctrptangle.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArcCtrPtAngle : public PoCircleArc {

  SO_KIT_HEADER(PoCircleArcCtrPtAngle) ;


 public:

  /* Fields */

  /**
   * Circle center. (0,0) by default.
   */
  SoSFVec2f center ;

  /**
   * Start point of the arc. (1,0) by default.
   */
  SoSFVec2f startPoint ;

  /**
   * Arc angle. 2PI by default.
   */
  SoSFFloat angle ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArcCtrPtAngle()
    { init(SbVec2f(0.0, 0.0), SbVec2f(1.0, 0.0), (float)PDEUXPI) ; }

  /**
   * Constructor.
   */
  PoCircleArcCtrPtAngle(const SbVec2f &_center, const SbVec2f &_startPoint,
                        float _angle)
    { init(_center, _startPoint, _angle) ; }

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
  virtual ~PoCircleArcCtrPtAngle() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(const SbVec2f &center, const SbVec2f &startPoint,
            float angle) ;

  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CIRCLE_ARC_CTR_PT_ANGLE_ */

