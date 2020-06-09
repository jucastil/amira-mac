/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CURVE_FILLING_
#define  _PO_CURVE_FILLING_

#include <MeshViz/graph/PoCurveLine.h>

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>

/**
 * @DTEXT  Class to build 3D filled curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Builds a 3D filled curve on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The abscissas of the filled curve are given by the geometry of the current 
 *    mesh 1D, and the ordinates are given by one of the value-set of the current 
 *    mesh 1D specified by the field yValuesIndex.
 *    A threshold defines the origin of the filled curve.
 *    This value is either an ordinate (VERTICAL orientation) or an abscissas
 *    (HORIZONTAL orientation).
 *    The thickness of the filled curve is specified by the field thicknessIndex 
 *    which is an index of a value-set of the current mesh 1D. These values are 
 *    multiplied by the field width. If thicknessIndex == -1, the thickness of the 
 *    filled curve is the value of the field width. thickness fields are ignored
 *    if the field width is equal to 0.
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints).
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: The entire filled curve is colored with the same inherited color.
 * 
 *    - PER_PART : Each part of the filled curve is colored with the same color.
 *    A part is the curve between two abscissas defined by the current mesh 1D.
 * 
 *    - PER_VERTEX: A color is used at each vertex of the filled curve.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCurveFilling {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR thicknessIndex @TD -1
 *       @TR thicknessBinding @TD PER_VERTEX_THICKNESS
 *       @TR thicknessFactor @TD 1.0
 *       @TR threshold @TD 0.0
 *       @TR width @TD 1.0
 *       @TR orientation @TD VERTICAL
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pocurvefilling.cat.html
 * 
 * 
 */

class MESHVIZ_API PoCurveFilling : public PoCurveLine {
  
  SO_KIT_HEADER(PoCurveFilling) ;


 public:

  /**
   *  Orientation of the filled bar.
   */
  enum Orientation {
    HORIZONTAL,
    VERTICAL
  } ;



  /* Fields */

  /**
   * Defines the threshold of the origin of the filled curve.
   * This value is either an ordinate (VERTICAL orientation) or an abscissas
   * (HORIZONTAL orientation).
   */
  SoSFFloat    threshold ;

  /**
   * Defines the width of the curve filled. If the thicknessIndex is different 
   * from -1, thickness values are multiplied to this value.
   * If this value is equal to 0, thicknessIndex, thicknessBinding and
   * thicknessFactor are ignored.
   */
  SoSFFloat    width ;

  /**
   * Defines the orientation of the filled curve.
   */
  SoSFEnum     orientation ;

  /**
   * Constructor.
   */
  PoCurveFilling() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoCurveFilling() ;
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

#endif /* _PO_CURVE_FILLING_ */

