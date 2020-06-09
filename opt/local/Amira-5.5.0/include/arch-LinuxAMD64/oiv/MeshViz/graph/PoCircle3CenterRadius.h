/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CIRCLE3_CENTER_RADIUS_
#define  _PO_CIRCLE3_CENTER_RADIUS_

#include <MeshViz/graph/PoCircle3.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 3D circle. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    The circle is given by its center, its radius and a normal vector to the 
 *    circle plane.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCircle3CenterRadius {
 *    @TABLE_FILE_FORMAT
 *       @TR center @TD 0 0 0
 *       @TR radius @TD 1
 *       @TR normal @TD 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocircle3centerradius.cat.html
 * 
 * 
 */
class MESHVIZ_API PoCircle3CenterRadius : public PoCircle3 {

  SO_KIT_HEADER(PoCircle3CenterRadius) ;


 public:

  /* Fields */

  /**
   * Circle center.
   */
  SoSFVec3f center ;

  /**
   * Circle radius.
   */
  SoSFFloat radius ;

  /**
   * Normal to the plane of circle.
   */
  SoSFVec3f normal ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoCircle3CenterRadius()
    { init(TRUE, SbVec3f(0.,0.,0.), 1.0, SbVec3f(0.,0.,1.)) ; }

  /**
   * Constructor.
   */
  PoCircle3CenterRadius(const SbVec3f &_center, float _radius, const SbVec3f &_normal)
    { init(FALSE, _center, _radius, _normal) ; }

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
  virtual ~PoCircle3CenterRadius() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Init method
  void init(SbBool isDefault, const SbVec3f &center,float radius, const SbVec3f &_normal) ;
  
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;


} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_CIRCLE3_CENTER_RADIUS_ */

