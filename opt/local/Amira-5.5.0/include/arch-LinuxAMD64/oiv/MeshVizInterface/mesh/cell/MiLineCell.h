/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MILINECELL_H
#define _MILINECELL_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiCell.h>

/**
* @DTEXT  Defines an abstract cell of a line mesh.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*    A line cell is an edge element that connects adjacent nodes of a line mesh.
*    This class defines the method getSubEdgeNodesIndex() that is only useful for 
*    non linear 1D cells. For linear 1D cells, the application must just provide
*    the implementation of the methods defined in MiCell without overriding
*    getSubEdgeNodesIndex().
*    
*    When the result of getSubEdgeNodesIndex() is > 0, the cell is considered as a 
*    non linear cell. In that case, the given sub segments are used by the miscellaneous 
*    extractors (for instance MiTessellatedLineExtract). Furthermore if a 
*    MiTessellator is given, each sub segment is tessellated by the method 
*    MiTessellator::tessellateLineCell().
* 
*  @see MiTessellator, MbLineCell, MeXLineCell
*/

class MiLineCell : public MiCell
{
public:
  /**
  * Get a decomposition of this cell into sub linear segments. @BR
  *
  * This method must be overridden to correctly handle 
  * non-linear cells. For instance an implementation of this method for a quadratic 
  * bar like the following one
  *   @IMAGE QuadraticBar3.png Quadratic bar
  * should return 2, and edgeNodeIds = {0,2,2,1}. 
  * (provided that getNodeIndex(2) corresponds to the middle point of this bar).@BR
  *
  * By default it returns 0 and the argument edgeNodeIds is not modified.
  * @param[out] edgeNodeIds  sub edge node id (where: 0 <= edgeNodeIds[i] < getNumNodes() for each i).
  * @return the number of sub linear segments in this cell.
  */
  virtual size_t getSubEdgeNodesIndex(std::vector<size_t>& UNREF_PARAM(edgeNodeIds)) const 
  {
    return 0;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif

