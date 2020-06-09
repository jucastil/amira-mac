/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_COORDINATE_LIST_FILTER_
#define  _PO_COORDINATE_LIST_FILTER_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFEnum.h>

#include <MeshViz/nodes/PoMesh1DFilter.h>

/**
 * @DTEXT  Node to define a coordinate list filter.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current coordinate list filter of all subsequent
 *    MeshViz representations inhering from PoChart.
 *    A list of points is selected by their coordinates from the geometry of the 
 *    current mesh 1D (PoRegularMesh1D or PoIrregularMesh1D) by all subsequent
 *    representations. Nevertheless, if a PoMesh1DHints node with the field
 *    geomInterpretation different from AS_IS is found in the path to the
 *    representation, the filter is not applied to the mesh 1D geometry
 *    but to the computed points (these points are differently computed
 *    according to the field geomInterpretation of the class PoMesh1DHints).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoCoordinateListFilter {
 *    @TABLE_FILE_FORMAT
 *       @TR coord @TD 0
 *       @TR axis @TD X
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoCoordinateListFilter : public PoMesh1DFilter {
  
  SO_NODE_HEADER(PoCoordinateListFilter) ;


 public:

  /**
   *  Axis of the coordinates.
   */
  enum Axis {
    X,
    Y
  } ;

  /* Fields */

  /**
   * Defines the list of coordinates used to filter the mesh 1D geometry.
   */
  SoMFFloat coord ;

  /**
   * Defines the axis of the coordinates.
   */
  SoSFEnum axis ;

  /**
   * Constructor.
   */
  PoCoordinateListFilter() ;

  /*--------------------------------------------------------------------------*/  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoCoordinateListFilter() ;  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_COORDINATE_LIST_FILTER_  */

