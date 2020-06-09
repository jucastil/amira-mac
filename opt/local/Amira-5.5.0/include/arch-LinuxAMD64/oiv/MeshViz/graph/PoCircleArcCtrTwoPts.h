/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC_CTR_TWO_PTS_
#define  _PO_CIRCLE_ARC_CTR_TWO_PTS_

#include <MeshViz/graph/PoCircleArc.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a circle arc in the plane XY. The circle arc is defined 
 *    by its center, the start point and the end point.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArcCtrTwoPts {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR center @TD 0 0 
 *       @TR startPoint @TD 1 0
 *       @TR endPoint @TD 1 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearcctrtwopts.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArcCtrTwoPts : public PoCircleArc {

  SO_KIT_HEADER(PoCircleArcCtrTwoPts) ;


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
   * End point of the arc. (1,0) by default.
   */
  SoSFVec2f endPoint ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArcCtrTwoPts()
    { init(SbVec2f(0.0, 0.0), SbVec2f(1.0, 0.0), SbVec2f(1.0, 0.0)) ; }

  /**
   * Constructor.
   */
  PoCircleArcCtrTwoPts(const SbVec2f &_center, const SbVec2f &_startPoint,
                       const SbVec2f &_endPoint)
    { init(_center, _startPoint, _endPoint) ; }

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
  virtual ~PoCircleArcCtrTwoPts() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(const SbVec2f &_center, const SbVec2f &_startPoint,
            const SbVec2f &_endPoint) ;

  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_ARC_CTR_TWO_PTS_  */

