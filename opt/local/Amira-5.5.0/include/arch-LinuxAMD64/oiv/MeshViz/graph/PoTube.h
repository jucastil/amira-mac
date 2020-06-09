/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_TUBE_
#define  _PO_TUBE_

#include <MeshViz/graph/PoCurveLine.h>

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>

/**
 * @DTEXT  Class to build a 2D tube curve.
 * 
 * @ingroup GraphCurves
 * 
 * @DESCRIPTION
 *    Builds a 2D tube curve on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
 *    The abscissas of the tube are given by the geometry of the current mesh 1D,
 *    and the ordinates are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    The thickness of the tube is specified by the field thicknessIndex which is
 *    an index of a value-set of the current mesh 1D. These values are multiplied by
 *    the field width. If thicknessIndex == -1, the thickness of the tube is the 
 *    value of the field width.
 *    The shape of the profile is given by the current profile (PoProfile and its 
 *    derived nodes). The profile must be defined in the plane ZY.
 *    Profiles can be beveled according to the current beveled edge values 
 *    (PoBeveledEdge).
 *    The current complexity (SoComplexity) is used to determine the tessellation
 *    of the current profile.
 * 
 *    This class also takes into account of the current mesh 1D hints (PoMesh1DHints).
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: The entire tube is colored with the same inherited color.
 * 
 *    - PER_PART : Each part of the tube is colored with the same color.
 *    A part is the tube between two abscissas defined by the current mesh 1D.
 * 
 *    - PER_VERTEX: A color is used at each vertex of the tube.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoTube {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR thicknessIndex @TD -1
 *       @TR thicknessBinding @TD PER_VERTEX_THICKNESS
 *       @TR thicknessFactor @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE potube.cat.html
 * 
 * 
 */

class MESHVIZ_API PoTube : public PoCurveLine {
  
  SO_KIT_HEADER(PoTube) ;


 public:

  /* Fields */

  /**
   * Constructor.
   */
  PoTube() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoTube() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;

 private:
  // Sensors
  FieldSensorList fieldSensorList ;
  
  // List of fields defined in this class
  SoFieldList     fieldList ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_TUBE_ */

