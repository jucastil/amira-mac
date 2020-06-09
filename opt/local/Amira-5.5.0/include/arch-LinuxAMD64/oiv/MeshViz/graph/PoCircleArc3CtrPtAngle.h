/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC3_CTR_PT_ANGLE_
#define  _PO_CIRCLE_ARC3_CTR_PT_ANGLE_

#include <MeshViz/graph/PoCircleArc3.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 3D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    The circle arc is defined by its center, a start point , an 
 *    angle and a normal vector to the circle plane.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArc3CtrPtAngle {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR center @TD 0 0 0
 *       @TR startPoint @TD 1 0 0
 *       @TR angle @TD 2PI
 *       @TR normal @TD 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearc3ctrptangle.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArc3CtrPtAngle : public PoCircleArc3 {

  SO_KIT_HEADER(PoCircleArc3CtrPtAngle) ;


 public:

  /* Fields */

  /**
   * Circle center. (0,0,0) by default.
   */
  SoSFVec3f center ;

  /**
   * Start point of the arc. (1,0,0) by default.
   */
  SoSFVec3f startPoint ;

  /**
   * Arc angle. 2PI by default.
   */
  SoSFFloat angle ;

  /**
   * Normal to the plane of circle. (0,0,1) by default.
   */
  SoSFVec3f normal ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArc3CtrPtAngle()
    { init(TRUE, SbVec3f(0., 0., 0.), SbVec3f(0., 0., 0.), (float)PDEUXPI, SbVec3f(0., 0., 1.)) ; }

  /**
   * Constructor.
   */
  PoCircleArc3CtrPtAngle(const SbVec3f &_center, const SbVec3f &_startPoint,
                         float _angle, const SbVec3f &_normal)
    { init(FALSE, _center, _startPoint, _angle, _normal) ; }

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
  virtual ~PoCircleArc3CtrPtAngle() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &_center, const SbVec3f &_startPoint, 
            float _angle, const SbVec3f &_normal) ;

  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_CIRCLE_ARC3_CTR_PT_ANGLE_ */

