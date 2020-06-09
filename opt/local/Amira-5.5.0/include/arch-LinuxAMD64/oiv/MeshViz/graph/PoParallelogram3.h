/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PARALLELOGRAM3_
#define  _PO_PARALLELOGRAM3_

#include <MeshViz/graph/PoGraphMaster.h>
#include <Inventor/fields/SoSFVec3f.h>

/**
 * @DTEXT  Class for a 3D parallelogram.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    Class to build a 3D parallelogram. A parallelogram is defined by three 
 *    points, p,q,r.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoParallelogram3 {
 *    @TABLE_FILE_FORMAT
 *       @TR p @TD 0 0 0
 *       @TR q @TD 1 0 0
 *       @TR r @TD 1 1 0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poparallelogram3.cat.html
 * 
 * 
 */
class MESHVIZ_API PoParallelogram3 : public PoGraphMaster {

  SO_KIT_HEADER(PoParallelogram3) ;

  SO_KIT_CATALOG_ENTRY_HEADER(parallelogram3) ;


 public:

  /* Fields */

  /**
   * First point of the parallelogram.
   */
  SoSFVec3f p ;

  /**
   * Second point of the parallelogram.
   */
  SoSFVec3f q ;

  /**
   * Third point of the parallelogram.
   */
  SoSFVec3f r ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoParallelogram3()
    { init(TRUE, SbVec3f(0.,0.,0.), SbVec3f(1.,0.,0.), SbVec3f(1.,1.,0.)) ; }

  /**
   * Constructor.
   */
  PoParallelogram3(const SbVec3f &_p, const SbVec3f &_q, const SbVec3f &_r) 
    { init(FALSE, _p, _q, _r) ;}   

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
  virtual ~PoParallelogram3() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Initialise
  void init(SbBool isDefault, const SbVec3f &_p, const SbVec3f &_q, const SbVec3f &_r) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_PARALLELOGRAM3_ */

