/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE_CENTER_RADIUS_
#define  _PO_CIRCLE_CENTER_RADIUS_

#include <MeshViz/graph/PoCircle.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D circle. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    This class builds a circle in the plane XY. The circle is defined by its  
 *    center and its radius.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircleCenterRadius {
 *    @TABLE_FILE_FORMAT
 *       @TR center @TD 0 0
 *       @TR radius @TD 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocirclecenterradius.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircleCenterRadius : public PoCircle {

  SO_KIT_HEADER(PoCircleCenterRadius) ;


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



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircleCenterRadius()
    { init(SbVec2f(0.0, 0.0), 1.0) ; }

  /**
   * Constructor.
   */
  PoCircleCenterRadius(const SbVec2f &_center, float _radius)
    { init(_center, _radius) ; }

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
  virtual ~PoCircleCenterRadius() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Init method
  void init(const SbVec2f &center, float radius) ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE_CENTER_RADIUS_ */

