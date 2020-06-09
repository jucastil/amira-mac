/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE3_THREE_POINTS_
#define  _PO_CIRCLE3_THREE_POINTS_

#include <MeshViz/graph/PoCircle3.h>
#include <Inventor/fields/SoSFVec3f.h>


/**
 * @DTEXT  Class to build a 3D circle. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a 3D circle. The circle is given by three points p, q, r.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircle3ThreePoints {
 *    @TABLE_FILE_FORMAT
 *       @TR p @TD 1 0 0
 *       @TR q @TD 0 1 0
 *       @TR r @TD -1 0 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocircle3threepoints.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircle3ThreePoints : public PoCircle3 {

  SO_KIT_HEADER(PoCircle3ThreePoints) ;


 public:

  /* Fields */

  /**
   * First point of the circle.
   */
  SoSFVec3f p ;

  /**
   * Second point of the circle.
   */
  SoSFVec3f q ;

  /**
   * Third point of the circle.
   */
  SoSFVec3f r ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircle3ThreePoints()
    { init(TRUE, SbVec3f(1., 0., 0.), SbVec3f(0., 1., 0.), SbVec3f(-1, 0., 0.)) ; }

  /**
   * Constructor.
   */
  PoCircle3ThreePoints(const SbVec3f &_p, const SbVec3f &_q, const SbVec3f &_r)
    { init(FALSE, _p, _q, _r) ; }

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
  virtual ~PoCircle3ThreePoints() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &p, const SbVec3f &q, const SbVec3f &r) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;


} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE3_THREE_POINTS_  */

