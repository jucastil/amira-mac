/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC3_CTR_TWO_PTS_
#define  _PO_CIRCLE_ARC3_CTR_TWO_PTS_

#include <MeshViz/graph/PoCircleArc3.h>
#include <Inventor/fields/SoSFVec3f.h>

/**
 * @DTEXT  Class to build a 3D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    The circle arc is defined by its center, a start point and 
 *    an end point.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArc3CtrTwoPts {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR center @TD 0 0 0
 *       @TR startPoint @TD 1 0 0
 *       @TR endPoint @TD 1 0 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearc3ctrtwopts.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArc3CtrTwoPts : public PoCircleArc3 {

  SO_KIT_HEADER(PoCircleArc3CtrTwoPts) ;


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
   * End point of the arc. (1,0,0) by default.
   */
  SoSFVec3f endPoint ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArc3CtrTwoPts()
    { init(TRUE, SbVec3f(0., 0., 0.), SbVec3f(1., 0., 0.), SbVec3f(1., 0., 0.)) ; }

  /**
   * Constructor.
   */
  PoCircleArc3CtrTwoPts(const SbVec3f &_center, const SbVec3f &_startPoint,
                        const SbVec3f &_endPoint)
    { init(FALSE, _center, _startPoint, _endPoint) ; }

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
  virtual ~PoCircleArc3CtrTwoPts() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &_center, const SbVec3f &_startPoint, 
            const SbVec3f &_endPoint) ;


  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_ARC3_CTR_TWO_PTS_  */

