/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_GENERALIZED_BAR_
#define  _PO_GENERALIZED_BAR_

#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFVec3f.h>

#include <MeshViz/graph/PoBar.h>

/**
 * @DTEXT  Class to build generalized bars.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Build bars on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D), 
 *    where each bar is defined by a sub-scene graph.
 *    The field bars is used to define the sub-scene graph of each bar. If the
 *    number of sub-scene graphs is inferior to the number of bars to draw, they
 *    are cyclically used.
 *    The field scaleFactor specifies a possibly non uniform scale applied to each bar.
 *    The orientation of the bars can be horizontal or vertical.
 *    The abscissas (ordinates if HORIZONTAL orientation) of the bars are given 
 *    by the geometry of the current mesh 1D, and the height (width if HORIZONTAL
 *    orientation) are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    A threshold defines the origin of the bars. This value is either
 *    an ordinate (VERTICAL orientation) or an abscissas (HORIZONTAL orientation).
 *    This class also takes into account of the current mesh 1D hints 
 *    (PoMesh1DHints) and the current mesh 1D filter (PoMesh1DFilter) 
 *    to filter the geometry of the current mesh 1D .
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: All bars are colored with the same inherited color.
 * 
 *    - PER_PART or PER_VERTEX : A color is used for each bar.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoGeneralizedBar {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR bars @TD NULL
 *       @TR scaleFactor @TD 1 1 1
 *       @TR orientation @TD VERTICAL
 *       @TR threshold @TD 0.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pogeneralizedbar.cat.html
 * 
 * 
 */

class MESHVIZ_API PoGeneralizedBar : public PoBar {
  
  SO_KIT_HEADER(PoGeneralizedBar) ;


 public:

  /**
   * Constructor.
   */
  PoGeneralizedBar() ;

  /* Fields */

  /**
   * Defines the sub-scene graphs used for each bar. If the number of 
   * sub-scene graphs is inferior to the number of bars to draw, they
   * are cyclically used.
   * Each sub-scene graph defining each bar is considered to be specified
   * vertically in the plane XY.
   */
  SoMFNode  bars ;

  /**
   * Specifies a possibly non uniform scale applied to each bar.
   * If the orientation is VERTICAL, only the X and Z components are used,
   * and if the orientation is HORIZONTAL, only the Y and Z components are used.
   * If a component has a negative value, the scale in the component direction is
   * relative to the height (resp. width) of the histogram, otherwise this
   * an absolute scale.
   */
  SoSFVec3f scaleFactor ;

  /*---------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoGeneralizedBar() ;
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

#endif /*  _PO_GENERALIZED_BAR_ */

