/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_RIBBON_
#define  _PO_RIBBON_

#include <MeshViz/graph/PoCurveLine.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D ribbon curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Builds a 2D ribbon curve on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The abscissas of the ribbon are given by the geometry of the current mesh 1D,
 *    and the ordinates are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    The thickness of the ribbon is specified by the field thicknessIndex which is
 *    an index of a value-set of the current mesh 1D. These values are multiplied by
 *    the field width. If thicknessIndex == -1, the thickness of the ribbon is the 
 *    value of the field width.
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints).
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: The entire ribbon is colored with the same inherited color.
 * 
 *    - PER_PART : Each part of the ribbon is colored with the same color.
 *    A part is the ribbon between two abscissas defined by the current mesh 1D.
 * 
 *    - PER_VERTEX: A color is used at each vertex of the ribbon.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoRibbon {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR thicknessIndex @TD -1
 *       @TR thicknessBinding @TD PER_VERTEX_THICKNESS
 *       @TR thicknessFactor @TD 1.0
 *       @TR width @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poribbon.cat.html
 * 
 * 
 */

class MESHVIZ_API PoRibbon : public PoCurveLine {
  
  SO_KIT_HEADER(PoRibbon) ;


 public:

  /* Fields */

  /**
   * Defines the width of the ribbon. If the thicknessIndex is different from
   * -1, thickness values are multiplied to this value.
   */
  SoSFFloat width ;

  /**
   * Constructor.
   */
  PoRibbon() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoRibbon() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;

  // Methods
  virtual void   setDefaultOnNonWritingFields() ;
  virtual SbBool setUpConnections(SbBool onOff, SbBool doItAlways = FALSE) ;

 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_RIBBON_ */

