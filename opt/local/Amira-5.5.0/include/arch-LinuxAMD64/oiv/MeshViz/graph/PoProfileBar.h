/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PROFILE_BAR_
#define  _PO_PROFILE_BAR_

#include <MeshViz/graph/PoBar.h>

/**
 * @DTEXT  Class to build profile bars.
 * 
 * @ingroup GraphHistogram
 * 
 * @DESCRIPTION
 *    Build bars defined by a profile (PoProfile) on 1D mesh (PoIrregularMesh1D 
 *    or PoRegularMesh1D).
 *    The orientation of the bars can be horizontal or vertical.
 *    The abscissas (ordinates if HORIZONTAL orientation) of the bars are given 
 *    by the geometry of the current mesh 1D, and the height (width if HORIZONTAL
 *    orientation) are given by one of the value-set of the current mesh 1D 
 *    specified by the field yValuesIndex.
 *    A threshold defines the origin of the bars. This value is either
 *    an ordinate (VERTICAL orientation) or an abscissas (HORIZONTAL orientation).
 *    This class also takes into account of the current mesh 1D hints 
 *    (PoMesh1DHints) and the current mesh 1D filter (PoMesh1DFilter) 
 *    to filter the geometry of the current mesh 1D.
 *    The shape of the profile is given by the current profile (PoProfile and
 *    its derived nodes).
 *    The current complexity (SoComplexity) is used to determine the tessellation
 *    of the current profile.
 * 
 *    The interpretation of colorBinding is the following :
 * 
 *    - INHERITED: All bars are colored with the same inherited color.
 * 
 *    - PER_PART or PER_VERTEX : A color is used for each bar.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoProfileBar {
 *    @TABLE_FILE_FORMAT
 *       @TR colorBinding @TD INHERITED
 *       @TR yValuesIndex @TD 0
 *       @TR colorValuesIndex @TD 1
 *       @TR material @TD NULL
 *       @TR orientation @TD VERTICAL
 *       @TR threshold @TD 0.0
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE poprofilebar.cat.html
 * 
 * 
 */

class MESHVIZ_API PoProfileBar : public PoBar {
  
  SO_KIT_HEADER(PoProfileBar) ;


 public:

  /**
   * Constructor.
   */
  PoProfileBar() ;

  /*---------------------------------------------------------------------------*/


 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

 protected:
  virtual ~PoProfileBar() ;
  // Destructor.

  // Overloaded methods
  virtual void rebuild() ;
  virtual void addElementsAllCaches() ;
  virtual void preRebuild() ;
} ;

/*----------------------------------------------------------------------------*/

#endif /*  _PO_PROFILE_BAR_ */

