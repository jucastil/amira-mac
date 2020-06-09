/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_NON_LINEAR_VALUE_LEGEND2_
#define  _PO_NON_LINEAR_VALUE_LEGEND2_

#include <MeshViz/graph/PoAutoValueLegend.h>

/**
 * @DTEXT  Class to build a non linear legend (second representation).
 * 
 * @ingroup GraphLegend
 * 
 * @DESCRIPTION
 *    Each box represents the color associated to a value of a data mapping
 *    object or an isovalue list object.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoNonLinearValueLegend2 {
 *    @TABLE_FILE_FORMAT
 *       @TR titleVisibility @TD VISIBILITY_OFF
 *       @TR titlePosition @TD POS_BOTTOM
 *       @TR titlePath @TD RIGHT_PATH
 *       @TR titleFontSize @TD 0
 *       @TR titleFontName @TD ""
 *       @TR titleString @TD ""
 *       @TR valueVisibility @TD VISIBILITY_ON
 *       @TR valuePosition @TD POS_RIGHT
 *       @TR valueFontName @TD ""
 *       @TR valueAddStringVisibility @TD FALSE
 *       @TR valueAddString @TD ""
 *       @TR marginType @TD REL_MARGIN
 *       @TR marginLeft @TD 0.05
 *       @TR marginRight @TD 0.05
 *       @TR marginBottom @TD 0.05
 *       @TR marginTop @TD 0.05
 *       @TR incrementType @TD VERTICAL_INCREMENT
 *       @TR numColumns @TD 1
 *       @TR boxRatio @TD 1
 *       @TR periodValue @TD 1
 *       @TR firstValue @TD 1
 *       @TR lastValue @TD 32767
 *       @TR start @TD 0 0
 *       @TR end @TD 1 1
 *       @TR lowerUndefString @TD "UNDEF>"
 *       @TR upperUndefString @TD "UNDEF>"
 *    @TABLE_END
 *    }
 * 
 * @CATALOG_PARTS_INCLUDE pononlinearvaluelegend2.cat.html
 * 
 * 
 */
class MESHVIZ_API PoNonLinearValueLegend2 : public PoAutoValueLegend {

  SO_KIT_HEADER(PoNonLinearValueLegend2) ;


 public:

  /* Methods */

  /**
   * Default constructor.
   */
  PoNonLinearValueLegend2() ; 

  /**
   * Constructor.
   */
  PoNonLinearValueLegend2(const SbVec2f &_start, const SbVec2f &_end) ;

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
  virtual ~PoNonLinearValueLegend2() ;

 private:
  // Init method
  void init() ;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_NON_LINEAR_VALUE_LEGEND2_ */



