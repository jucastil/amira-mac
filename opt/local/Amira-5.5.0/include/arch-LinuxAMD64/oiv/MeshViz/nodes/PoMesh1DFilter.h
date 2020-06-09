/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH1D_FILTER_
#define  _PO_MESH1D_FILTER_

#include <MeshViz/nodes/PoNode.h>

/**
 * @DTEXT  Abstract base class for all filter nodes.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    This node is the abstract base class for filter nodes.
 *    Filter nodes allow geometry of mesh 1D (PoIrregularMesh1D or PoRegularMesh1D)
 *    to be filtered. Filtering consists on selecting particular points on the
 *    mesh 1D geometry. The way of selecting these points is determined by the
 *    derived classes. This is only these points which are used by the
 *    all the subsequent representations (heriting from PoChart) in a scene graph.
 *    If no filter node is present in the path used by a representation all the
 *    geometry points of the current mesh 1D are used by this representation.
 * 
 */

class MESHVIZ_API PoMesh1DFilter : public PoNode {
  
  SO_NODE_ABSTRACT_HEADER(PoMesh1DFilter) ;
  
  /*----------------------------------------------------------------------------*/  
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  PoMesh1DFilter() ;
  // Constructor.
  
  virtual ~PoMesh1DFilter() ;  
} ;
/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH1D_FILTER_  */

