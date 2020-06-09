/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PARALLELOGRAM_
#define  _PO_PARALLELOGRAM_

#include <MeshViz/graph/PoGraphMaster.h>
#include <Inventor/fields/SoSFVec2f.h>

/**
 * @DTEXT  Class for a 2D parallelogram. 
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    Class to build a parallelogram in the plane XY. A parallelogram is defined 
 *    by three points, p,q,r where the segment PR defines a diagonal of the parallelogram.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoParallelogram {
 *    @TABLE_FILE_FORMAT
 *       @TR p @TD 0 0
 *       @TR q @TD 1 0
 *       @TR r @TD 1 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poparallelogram.cat.html
 * 
 * 
 */
class MESHVIZ_API PoParallelogram : public PoGraphMaster {

  SO_KIT_HEADER(PoParallelogram) ;

  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(parallelogram) ;


 public:

  /* Fields */

  /**
   * First point of the parallelogram.
   */
  SoSFVec2f p ;

  /**
   * Second point of the parallelogram.
   */
  SoSFVec2f q ;

  /**
   * Third point of the parallelogram.
   */
  SoSFVec2f r ;

  /* Methods */

  /**
   * Default constructor.
   */
  PoParallelogram()
    { init(SbVec2f(0.0, 0.0), SbVec2f(1.0, 0.0), SbVec2f(1.0, 1.0)) ; }

  /**
   * Constructor.
   */
  PoParallelogram(const SbVec2f &_p, const SbVec2f &_q, const SbVec2f &_r) 
    { init(_p, _q, _r) ;}   

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Destructor
  virtual ~PoParallelogram() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Initialise
  void init(const SbVec2f &_p, const SbVec2f &_q, const SbVec2f &_r) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_PARALLELOGRAM_ */

