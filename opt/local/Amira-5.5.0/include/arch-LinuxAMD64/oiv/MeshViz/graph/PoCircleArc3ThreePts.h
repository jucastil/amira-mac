/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_ARC3_THREE_PTS_
#define  _PO_CIRCLE_ARC3_THREE_PTS_

#include <MeshViz/graph/PoCircleArc3.h>
#include <Inventor/fields/SoSFVec3f.h>

/**
 * @DTEXT  Class to build a 3D circle arc. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    The circle arc is defined by three points, the start point, 
 *    a middle point and an end point.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleArc3ThreePts {
 *    @TABLE_FILE_FORMAT
 *       @TR arcType @TD OPENED
 *       @TR startPoint @TD 1 0 0
 *       @TR middlePoint @TD -1 0 0
 *       @TR endPoint @TD 1 0 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclearc3threepts.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleArc3ThreePts : public PoCircleArc3 {

  SO_KIT_HEADER(PoCircleArc3ThreePts) ;


 public:

  /* Fields */

  /**
   * Start point of the arc. (1,0,0) by default.
   */
  SoSFVec3f startPoint ;

  /**
   * Intermediate point of the arc. (-1,0,0) by default.
   */
  SoSFVec3f middlePoint ;

  /**
   * End point of the arc. (1,0,0) by default.
   */
  SoSFVec3f endPoint ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleArc3ThreePts()
    { init(TRUE, SbVec3f(1.0, 0.0, 0.0), SbVec3f(-1.0, 0.0, 0.0), SbVec3f(1.0, 0.0, 0.0)) ; }

  /**
   * Constructor.
   */
  PoCircleArc3ThreePts(const SbVec3f &_startPoint, const SbVec3f &_middlePoint, 
                       const SbVec3f &_endPoint)
    { init(FALSE, _startPoint, _middlePoint, _endPoint) ; }

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
  virtual ~PoCircleArc3ThreePts() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;

 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &_startPoint, const SbVec3f &_middlePoint, 
            const SbVec3f &_endPoint) ;

  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_ARC3_THREE_PTS_  */

