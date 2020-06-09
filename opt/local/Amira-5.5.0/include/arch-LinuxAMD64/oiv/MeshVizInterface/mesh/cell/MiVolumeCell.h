/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiVolumeCell_H
#define _MiVolumeCell_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiCell.h>
#include <MeshVizInterface/mesh/data/MiDataSet.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

/**
* @DTEXT  Defines an abstract cell of an unstructured volume mesh.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*    A volume cell is a polyhedron element that connects adjacent nodes of a volume mesh.
*
*    This class defines additional methods beyond MiCell to gives a complete description of a volume 
*    cell.
*         - Definition of the facet numbering.@BR
*           See getNumFacets(), appendNodesIndexOfFacet(), appendLocalNodesIndexOfFacet().
*         - Definition of the isosurface topology in this cell.@BR
*           See getIsosurfTopology() and getMarchingCaseId().
*         - Definition of a sub triangulation for each facet of the cell.@BR
*           See getSubTriangleNodesIndex().
*         - Definition of sub tetrahedra of the cell.@BR
*           See getSubTetrahedronNodesIndex().
*  
*    The methods getSubTriangleNodesIndex() and getSubTetrahedronNodesIndex() are
*    only useful for non linear volume cells and generic polyhedron cells. 
*    For the most usual basic volume cells (tetrahedron, hexahedron, wedge, pyramid), 
*    the application only needs to implement facet numbering, the isosurface topology, 
*    and the methods defined in MiCell.
*    
*    When the result of getSubTetrahedronNodesIndex() is > 0, the cell is considered to be a
*    non linear cell, or a generic polyhedron cell. In that case, the given sub triangles 
*    and sub tetrahedra are used by various extractors (for instance 
*    MiSkinExtractUnstructured) and mesh representation classes (for instance MoMeshSkin, 
*    MoMeshCellShape).  Furthermore if an MiTessellator is given, each sub triangle is 
*    tessellated by the method MiTessellator::tessellateSurfaceCell().
* 
*    The  utility classes MxXXXCellExtract can be used to help the 
*    application implement the various methods of MiCell and MiVolumeCell.
*    These classes provide static implementations of the necessary methods
*    for the most common linear and quadratic volume cells.
*
*  @see MeXVolumeCell
*  @see MiVolumeTopologyExplicitI
*  @see MiTessellator
*  @see MxTetrahedronCellExtract
*  @see MxHexahedronCellExtract, MxHexahedron20CellExtract, MxHexahedron27CellExtract
*  @see MxWedgeCellExtract, MxWedge18CellExtract
*  @see MxPyramidCellExtract
*
*/
class MESHIVIZ_API MiVolumeCell : public MiCell
{
public:

  /**
  * Gets the number of facets.
  */
  virtual size_t getNumFacets() const = 0; 

  /**
  * Appends the array of node indices belonging to a given facet to facetNode.@BR
  * 
  * The method must not include the additional nodes of the non linear cell. For instance 
  * an implementation of this method for a linear or quadratic tetrahedron cell
  * like the following one
  *   @IMAGE TetrahedronFaceNodes.png facetNodes of the pink face of these tetrahedra.
  * should return 3, and facetNodes should be appended by = {node0,node2,node1} if the facet argument 
  * corresponds to the pink one. (Provided that getNodeIndex() follows this tetrahedron 
  * node numbering.)
  * 
  * @param[in] facet The index of the facet (where 0 <= facet < getNumFacets()).
  * @param facetNodes A vector in which the node indices of the facet will be appended. 
  * The given vector should not be cleared by this method.
  * The implementation must use the push_back() method to add elements to the vector.
  * @return the number of nodes appended in facetNodes.
  */
  virtual size_t appendNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes) const = 0;

  /**
  * Get a triangulation of the given facet of a non linear volume cell.@BR
  *
  * This method must be overridden to correctly handle non-linear cells. 
  * For instance an implementation of this method for a quadratic 
  * tetrahedron like the following one
  *   @IMAGE QuadraticTetrahedron10SubT.png Triangulation of the pink face of this quadratic tetrahedron.
  * should return 4, and triangleNodeIds = {3,7,9, 7,0,6, 9,7,6, 9,6,2}. 
  * (provided that getNodeIndex() follows this tetrahedron node numbering).
  *
  * By default the method returns 0 and the argument triangleNodeIds is not modified.
  * It must not be overridden for linear cell.
  *
  * @param[in] facet number of the given facet. (where: 0 <= face < getNumFacets() ).
  * @param[out] triangleNodeIds  sub triangle node id (where: 0 <= triangleNodeIds[i] < getNumNodes() for each i).
  * @return the number of sub triangles in the facet of the cell.
  */
  virtual size_t getSubTriangleNodesIndex(size_t UNREF_PARAM(facet), std::vector<size_t>& UNREF_PARAM(triangleNodeIds)) const 
  {
    return 0;
  }

  /**
  * Get a decomposition in sub-tetrahedra of this volume cell.@BR
  *
  * This method must be overridden to correctly handle  
  * non-linear cells. By default it returns 0 and the argument tetrahedronNodeIds is not modified.
  * This method must not be overridden for linear cells.
  * @param[out] tetrahedronNodeIds sub tetrahedra node id (where: 0 <= tetrahedronNodeIds[i] < getNumNodes() for each i).
  *  If the cell is not linear, tetrahedronNodeIds must contain 4 times the number of sub-tetrahedra.
  * @return the number of sub-tetrahedra in this cell. 0 by default.
  */
  virtual size_t getSubTetrahedronNodesIndex (std::vector<size_t>& UNREF_PARAM(tetrahedronNodeIds)) const 
  {
    return 0;
  }

  /**
  * Appends the array of local node indices belonging to a given facet to facetNodes.@BR
  *
  * This method is similar to appendNodesIndexOfFacet() but facetNodes must be filled 
  * only with local node ids (i.e. node ids relative to the number of nodes in the cell): 
  * 0 <= facetNodes[i] < getNumNodes() for each i.
  *
  * The method must not include the additional nodes of a non linear cell. For instance 
  * an implementation of this method for a linear or quadratic tetrahedron cell
  * like the following one
  *   @IMAGE TetrahedronFaceNodesLocal.png facetNodes of the pink face of these tetrahedra.
  * should return 3, and facetNodes should be appended by {0,2,1} if the facet argument 
  * corresponds to the pink one. (Provided that getNodeIndex() follows this tetrahedron 
  * node numbering.)
  * 
  * @param[in] facet The index of the facet (where 0 <= facet < getNumFacets()).
  * @param facetNodes A vector in which the local node indices of the facet will be appended. 
  * The given vector should not be cleared by this method.
  * The implementation must use the push_back() method to add elements to the vector.
  * @return the number of nodes added.
  */
  virtual size_t appendLocalNodesIndexOfFacet (size_t UNREF_PARAM(facet), std::vector<size_t>& UNREF_PARAM(facetNodes)) const
  {
    throw MiAbstractMethodError("MiVolumeCell::appendLocalNodesIndexOfFacet(size_t facet, std::vector<size_t>& facetNodes)");
  }

  /**
  * Gets the list of topological polygons defining the part of the isosurface topology in this cell.@BR
  *
  * This method is used during isosurface and slice extraction on an unstructured mesh 
  * (for instance MoMeshPlaneSlice, MoMeshIsosurface, MiIsosurfExtractUnstructured). 
  * Static implementations are provided for the most common basic volume cells:
  *   - See MxHexahedronCellExtract::getIsosurfTopology()
  *   - See MxTetrahedronCellExtract::getIsosurfTopology()
  *   - See MxWedgeCellExtract::getIsosurfTopology()
  *   - See MxPyramidCellExtract::getIsosurfTopology()
  *
  * For polyhedral cells and non linear cells (for which no static implementation is available), returning 
  * an empty list can produce a hole in the isosurface. To avoid such a hole, this kind of cell must provide
  * a decomposition into sub tetrahedra by the method getSubTetrahedronNodesIndex(). 
  * To summary:
  *    - For basic cell shape (hexahedron, tetrahedron, wedge, pyramid),
  *      implement this method for example by calling MxXXXXCellExtract::getIsosurfTopology() 
  *      and do not override getSubTetrahedronNodesIndex().
  *    - Otherwise, implement this method by giving an empty edgeList and implement
  *      getSubTetrahedronNodesIndex() to provide a sub tetrahedra decomposition.
  * 
  * @param caseId the isosurf "marching cube" entry for this cell. This is the value returned by getMarchingCaseId
  *
  * @param edgeList the list of pair of nodes defining the isosurf topology in this cell. 
  * The given vector should not be cleared by this method. New pairs of node ids are appended to 
  * this vector. Each pair of nodes must correspond to an edge of
  * the cell which is cut by the isosurface. An edge is cut by the isosurface when the two nodes of the edge have different signs.
  * The pair of nodes must be correctly ordered to define a non manifold polygon.
  * When the isosurface part is made up of several polygons, each polygon must be separated by a
  * pair of identical nodes (for instance <0,0>).
  */
  virtual void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList ) const = 0;

  /**
  * Gets the isosurface "marching cube" entry according to the sign of each node in the cell.
  * The return entry corresponds to the first argument of getIsosurfTopology().
  * This method is used during isosurface and slice extraction on an unstructured mesh 
  * (for instance MoMeshPlaneSlice, MoMeshIsosurface, MiIsosurfExtractUnstructured). 
  * 
  * @param nodesSign A vector containing as many booleans as the number of nodes in the mesh.
  * nodesSign[i] is relative to the sign of the (isovalue-i-th node's value) .
  * @param beginNodeId is the first node id used by the mesh topology. @see MiVolumeTopologyExplicitI#getBeginNodeId.
  * @return a binary word containing as many bits as the number of nodes in the cell.
  * the i-th bit in the returned word equals nodesSign[getNodeIndex(i)].
  * @note MeshViz interface assumes that the cell does not contain any part of an isosurf if and only if the 
  * "marching cube" entry equals 0. Thus if all the bits in this word are 1, the method returns 0.
  */
  virtual unsigned char getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId=0) const;

  /**
  * Gets the center of the specified cell facet.@BR
  *
  * This method is not pure virtual because it is not used by all 
  * extraction classes. The default implementation provided computes
  * the average of the coordinates of each facet's node.
  * @param[in] geometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  * @return The center of the specified facet.
  */
  virtual MbVec3d getFacetCenter(size_t UNREF_PARAM(facet), const MiGeometryI& UNREF_PARAM(geometry)) const;

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */  
  virtual std::ostream& toStream(std::ostream& s) const;

};

//-----------------------------------------------------------------------------
inline unsigned char 
MiVolumeCell::getMarchingCaseId(std::vector<bool> &nodesSign, size_t beginNodeId) const
{
  unsigned char caseId = 0;
  unsigned char maxId = 0;
  size_t i;
  for (i=0; i<getNumNodes(); ++i)
  {
    if (nodesSign[getNodeIndex(i)-beginNodeId]) caseId |= (1<<i);
    maxId |= (1<<i);
  }
  if (caseId == maxId) 
    caseId = 0;
  return caseId;
}

//-----------------------------------------------------------------------------
inline MbVec3d
MiVolumeCell::getFacetCenter(size_t facet, const MiGeometryI& geometry) const
{
  std::vector<size_t> facetNodes;
  MbVec3d facetCenter(0);
  size_t numFacetNodes = this->appendNodesIndexOfFacet(facet,facetNodes);
  for ( size_t n = 0; n < numFacetNodes; ++n) 
    facetCenter += geometry.getCoord(facetNodes[n]);
  return ( facetCenter / (double) numFacetNodes );
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MiVolumeCell::toStream(std::ostream& s) const
{
  s << "# num cell's facets" << std::endl;
  s << getNumFacets() << std::endl;

  s << "# num cell's edges" << std::endl;
  s << getNumEdges() << std::endl;

  s << "# num cell's nodes" << std::endl;
  s << getNumNodes();

  std::vector<size_t> facetNodes;
  for (size_t i=0; i<getNumFacets(); ++i)
  {
    facetNodes.clear();
    s << std::endl << "[";
    appendNodesIndexOfFacet(i,facetNodes);
    for (size_t j=0; j<facetNodes.size(); ++j)
      s << facetNodes[j] << " ";
    s << "]";
  }

  return s;
}



#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
