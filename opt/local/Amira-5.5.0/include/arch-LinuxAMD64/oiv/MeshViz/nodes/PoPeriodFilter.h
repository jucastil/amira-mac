/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PERIOD_FILTER_
#define  _PO_PERIOD_FILTER_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>

#include <MeshViz/nodes/PoMesh1DFilter.h>

/**
 * @DTEXT  Node to define a period filter.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node defines the current period filter of all subsequent
 *    MeshViz representations inhering from PoChart.
 *    One point every period is selected from the geometry of the 
 *    current mesh 1D (PoRegularMesh1D or PoIrregularMesh1D) by all subsequent
 *    representations. Nevertheless, if a PoMesh1DHints node with the field
 *    geomInterpretation different from AS_IS is found in the path to the
 *    representation, the filter is not applied to the mesh 1D geometry
 *    but to the computed points (these points are differently computed
 *    according to the field geomInterpretation of the class PoMesh1DHints).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    PoPeriodFilter {
 *    @TABLE_FILE_FORMAT
 *       @TR period @TD 1
 *       @TR axis @TD X
 *    @TABLE_END
 *    }
 * 
 * 
 */

class MESHVIZ_API PoPeriodFilter : public PoMesh1DFilter {
  
  SO_NODE_HEADER(PoPeriodFilter) ;


 public:

  /**
   *  Axis of the period.
   */
  enum Axis {
    X,
    Y
  } ;

  /* Fields */

  /**
   * Defines the period used to filter the mesh 1D geometry.
   */
  SoSFFloat period ;

  /**
   * Defines the axis of the period.
   */
  SoSFEnum axis ;

  /**
   * Constructor.
   */
  PoPeriodFilter() ;

  /*--------------------------------------------------------------------------*/  
 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  virtual ~PoPeriodFilter() ;  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_PERIOD_FILTER_  */

