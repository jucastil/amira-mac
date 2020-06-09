/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_THREE_POINTS_
#define  _PO_CIRCLE_THREE_POINTS_

#include <MeshViz/graph/PoCircle.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D circle. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a circle in the plane XY. The circle is defined by three 
 *    points, p, q, r.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleThreePoints {
 *    @TABLE_FILE_FORMAT
 *       @TR p @TD 1 0
 *       @TR q @TD 0 1
 *       @TR r @TD -1 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclethreepoints.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleThreePoints : public PoCircle {

  SO_KIT_HEADER(PoCircleThreePoints) ;


 public:

  /* Fields */

  /**
   * First point of the circle.
   */
  SoSFVec2f p ;

  /**
   * Second point of the circle.
   */
  SoSFVec2f q ;

  /**
   * Third point of the circle.
   */
  SoSFVec2f r ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleThreePoints()
    { init(SbVec2f(1.0, 0.0), SbVec2f(0.0, 1.0), SbVec2f(-1, 0.)) ; }

  /**
   * Constructor.
   */
  PoCircleThreePoints(const SbVec2f &_p, const SbVec2f &_q, const SbVec2f &_r)
    { init(_p, _q, _r) ; }

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
  virtual ~PoCircleThreePoints() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Init method

  void init(const SbVec2f &p, const SbVec2f &q, const SbVec2f &r) ;

  // Compute circle center from three points p1, p2 and p3
  SbBool computeCircleCenter(const SbVec2f &p1, const SbVec2f &p2,
                             const SbVec2f &p3, SbVec2f &center) ;
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_THREE_POINTS_  */

