/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PERIOD_INDEX_FILTER_
#define  _PO_PERIOD_INDEX_FILTER_

#include <Inventor/fields/SoSFInt32.h>


#include <MeshViz/nodes/PoMesh1DFilter.h>

/**
 * @DTEXT  Node to define a period index filter.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current period index filter of all subsequent
 *    MeshViz representations inhering from PoChart.
 *    One point every index period is selected from the geometry of the current
 *    mesh 1D (PoRegularMesh1D or PoIrregularMesh1D) by all subsequent
 *    representations. For instance, if geometry of the current mesh 1D is
 *    0 0.5 4 6 and the period is 2, only the points 0 and 4 will be used by the
 *    representations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPeriodIndexFilter {
 *    @TABLE_FILE_FORMAT
 *       @TR period @TD 1
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoPeriodIndexFilter : public PoMesh1DFilter {
  
  SO_NODE_HEADER(PoPeriodIndexFilter) ;


 public:

  /* Fields */

  /**
   * Defines the period used to filter the mesh 1D geometry.
   */
  SoSFInt32 period ;

  /**
   * Constructor.
   */
  PoPeriodIndexFilter() ;

  /*----------------------------------------------------------------------------*/  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoPeriodIndexFilter() ;  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_PERIOD_INDEX_FILTER_ */

