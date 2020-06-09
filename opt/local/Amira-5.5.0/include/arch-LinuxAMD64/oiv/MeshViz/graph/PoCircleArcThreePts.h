/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC_THREE_PTS_
#define  _PO_CIRCLE_ARC_THREE_PTS_

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
 *    by three points: the start point, the middle point and the end point.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArcThreePts {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR startPoint @TD 1 0
 *       @TR middlePoint @TD -1 0
 *       @TR endPoint @TD 1 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearcthreepts.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArcThreePts : public PoCircleArc {

  SO_KIT_HEADER(PoCircleArcThreePts) ;


 public:

  /* Fields */

  /**
   * Start point of the arc. (1,0) by default.
   */
  SoSFVec2f startPoint ;

  /**
   * Intermediate point of the arc. (-1,0) by default.
   */
  SoSFVec2f middlePoint ;

  /**
   * End point of the arc. (1,0) by default.
   */
  SoSFVec2f endPoint ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArcThreePts()
    { init(SbVec2f(1.0, 0.0), SbVec2f(-1.0, 0.0), SbVec2f(1.0, 0.0)) ; }

  /**
   * Constructor.
   */
  PoCircleArcThreePts(const SbVec2f &_startPoint, const SbVec2f &_middlePoint, 
                      const SbVec2f &_endPoint)
    { init(_startPoint, _middlePoint, _endPoint) ; }

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
  virtual ~PoCircleArcThreePts() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(const SbVec2f &_startPoint, const SbVec2f &_middlePoint, 
            const SbVec2f &_endPoint) ;


  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_ARC_THREE_PTS_  */

