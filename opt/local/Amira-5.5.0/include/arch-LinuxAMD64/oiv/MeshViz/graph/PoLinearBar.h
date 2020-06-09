/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_LINEAR_BAR_
#define  _PO_LINEAR_BAR_

#include <MeshViz/graph/PoBar.h>

/**
 * @DTEXT  Class to build line bars.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Build line bars on 1D mesh (PoIrregularMesh1D or PoRegularMesh1D).
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
 *    PoLinearBar {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR orientation @TD VERTICAL
 *       @TR threshold @TD 0.
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE polinearbar.cat.html
 * 
 * 
 */

class MESHVIZ_API PoLinearBar : public PoBar {
  
  SO_KIT_HEADER(PoLinearBar) ;


 public:

  /**
   * Constructor.
   */
  PoLinearBar() ;

  /*----------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoLinearBar() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_LINEAR_BAR_ */

