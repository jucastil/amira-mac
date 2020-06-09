/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_RECTANGLE_
#define  _PO_RECTANGLE_

#include <MeshViz/graph/PoGraphMaster.h>
#include <Inventor/fields/SoSFVec2f.h>

/**
 * @DTEXT  Class for a 2D rectangle.
 * 
 * @ingroup GraphMisc
 * 
 * @DESCRIPTION
 *    Class to build a rectangle in the plane XY. A rectangle is defined by two points, p 
 *    and q, representing one of its diagonals.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoRectangle {
 *    @TABLE_FILE_FORMAT
 *       @TR p @TD 0 0
 *       @TR q @TD 1 1
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE porectangle.cat.html
 * 
 * 
 */
class MESHVIZ_API PoRectangle : public PoGraphMaster {

  SO_KIT_HEADER(PoRectangle) ;
  
  /* Define fields for new parts */
  SO_KIT_CATALOG_ENTRY_HEADER(rectangle) ;


 public:

  /* Fields */

  /**
   * First point of one of the diagonals of the rectangle.
   */
  SoSFVec2f p ;

  /**
   * Second point of the same diagonal.
   */
  SoSFVec2f q ;



  /* Methods */

  /**
   * Default constructor.
   */
  PoRectangle() ; 

  /**
   * Constructor.
   */
  PoRectangle(const SbVec2f &p1, const SbVec2f &p2) { init(p1,p2) ;}   

  /**
   * Forces node-kit rebuilding. See PoBase.
   */
  virtual void   rebuild() ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  // Methods
  // Destructor
  virtual ~PoRectangle() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;
  virtual void   setDefaultOnNonWritingFields() ;
  
 private:
  // Initialise
  void init(const SbVec2f &p1, const SbVec2f &p2) ;

  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_RECTANGLE_  */

