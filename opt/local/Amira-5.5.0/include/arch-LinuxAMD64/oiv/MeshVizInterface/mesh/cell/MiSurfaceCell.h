/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACECELL_H
#define _MISURFACECELL_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiCell.h>

/**
* @DTEXT  Defines an abstract cell of an unstructured surface mesh.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*    A surface cell is a polygonal element that connects adjacent nodes of a surface mesh.
*
*    This class defines the method getSubTriangleNodesIndex(), which is only useful for 
*    non linear 2D cells. For linear 2D cells, the application only needs to implement
*    the methods defined in MiCell without overriding getSubTriangleNodesIndex().
*    
*    When the result of getSubTriangleNodesIndex() is > 0, the cell is considered a 
*    non linear cell. In that case, the given sub triangulation is used by various 
*    extractors (for instance MiTessellatedSurfaceExtract) and mesh representation classes
*    (for instance MoMeshSurface, MoMeshCellShape). 
*    Furthermore if an MiTessellator is given, each sub triangle is tessellated by the method 
*    MiTessellator::tessellateSurfaceCell().
* 
*    The  utility classes MxXXXCellExtract can be used to help the 
*    application implement the various methods of MiCell and MiSurfaceCell.
*    These classes provide static implementations of the necessary methods
*    for the most common linear and quadratic surface cells.
*
*  @see MeXSurfaceCell
*  @see MiSurfaceTopologyExplicitI
*  @see MiTessellator
*  @see MxTriangleCellExtract, MxTriangle6CellExtract
*  @see MxQuadrangleCellExtract, MxQuadrangle8CellExtract, MxQuadrangle9CellExtract
*
*/
class MESHIVIZ_API MiSurfaceCell : public MiCell
{
public:
  /**
  * Get a decomposition of this surface cell into sub triangles.@BR
  *
  * This method must be overridden to correctly handle non-linear cells. 
  * For instance an implementation of this method for a quadratic 
  * triangle like the following one
  *   @IMAGE QuadraticTriangle6SubT.png Triangulation of a quadratic triangle.
  * should return 4, and triangleNodeIds = {0,3,5, 3,1,4, 3,4,5, 5,4,2}. 
  * (provided that getNodeIndex() follows this triangle node numbering).
  *
  * By default the method returns 0 and the argument triangleNodeIds is not modified.
  * It must not be overridden for a linear cell.
  *
  * @param[out] triangleNodeIds  sub-triangle node id (where: 0 <= triangleNodeIds[i] < getNumNodes() for each i).
  * @return the number of sub-triangles in this cell.
  */

  virtual size_t getSubTriangleNodesIndex(std::vector<size_t>& UNREF_PARAM(triangleNodeIds)) const 
  {
    return 0;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif

