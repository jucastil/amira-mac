/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_INDEX_LIST_FILTER_
#define  _PO_INDEX_LIST_FILTER_

#include <Inventor/fields/SoMFInt32.h>

#include <MeshViz/nodes/PoMesh1DFilter.h>

/**
 * @DTEXT  Node to define a index list filter.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current index list filter of all subsequent
 *    MeshViz representations inhering from PoChart.
 *    A list of points is selected by their indices from the geometry of the 
 *    current mesh 1D (PoRegularMesh1D or PoIrregularMesh1D) by all subsequent
 *    representations. For instance, if geometry of the current mesh 1D is
 *    0 0.5 4 6 and the index list is 0 3, only the points 0 and 6 will be used by 
 *    the representations.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoIndexListFilter {
 *    @TABLE_FILE_FORMAT
 *       @TR index @TD 0
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoIndexListFilter : public PoMesh1DFilter {
  
  SO_NODE_HEADER(PoIndexListFilter) ;


 public:

  /* Fields */

  /**
   * Defines the index list used to filter the mesh 1D geometry.
   */
  SoMFInt32 index ;

  /**
   * Constructor.
   */
  PoIndexListFilter() ;

  /*----------------------------------------------------------------------------*/  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoIndexListFilter() ;  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_INDEX_LIST_FILTER_ */

