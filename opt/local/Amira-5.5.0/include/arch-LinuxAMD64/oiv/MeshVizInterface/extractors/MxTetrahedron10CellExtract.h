/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxTetrahedron10CellExtract_h
#define  _MxTetrahedron10CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiVolumeCell;

/**
 * @DTEXT Utility class for quadratic tetrahedron cells with 10 nodes.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of MiVolumeCell's methods
 *   for a quadratic tetrahedron of 10 nodes. This class is provided to make it easier 
 *   to create a class that implements the MiVolumeCell interface for a quadratic
*    tetrahedron of 10 nodes. 
 *      - value of iso parametric coordinates in an tetrahedron of 10 nodes
 *        (see getIsoParametricCoord())
 *      - value of the weights (aka shape functions) in a tetrahedron of 10 nodes
 *        (see getWeight())
 *      - decomposition of each face in sub triangles.
 *        (see getSubTriangleNodesIndex())
 *      - decomposition in sub tetrahedrons.
 *        (see getSubTetrahedronNodesIndex())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the node numbering and the face numbering used by this class. 
 * The weight (see getWeight()), parametric coordinates (see getIsoParametricCoord()), and
 * the decomposition in sub tetrahedrons (see getSubTetrahedronNodesIndex()) are defined 
 * according to this node numbering. The face decomposition (see getSubTriangleNodesIndex())
 * is defined according to this node and face numbering.
 *
 * @IMAGE QuadraticTetra10.png "Nodes and faces numbering"
 *
 */
class MESHIVIZ_API MxTetrahedron10CellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given tetrahedronCell is assumed to contain 10 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(tetrahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-9].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 10 nodes of a quadratic tetrahedron.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-9]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a quadratic tetrahedron of 10 nodes. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given tetrahedronCell is 
  * assumed to contain 10 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(tetrahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-9].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 10 values weights[0-9]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 10 (at least) before calling this method, using for instance
  *    the weights.resize(10)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,tetrahedronCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a quadratic tetrahedron of 10 nodes.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 10 values weights[0-9].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 10 (at least) before calling this method, using for instance
  *    the weights.resize(10)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 30 values derivs[0-29].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 30 (at least) before calling this method, using for instance
  *    the derivs.resize(30)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a quadratic tetrahedron cell of 10 nodes.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a quadratic tetrahedron of 10 nodes.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] tetrahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 10 values weights[0-9] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 10 (at least) before calling this method, using for instance
  *    the weights.resize(10)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* tetrahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,tetrahedronCell,point);
    bool inside = ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[2] &&  pcoord[2] < 1 + 1.E-5 &&
                    -1.E-5 < (pcoord[0]+pcoord[1]+pcoord[2]) &&  (pcoord[0]+pcoord[1]+pcoord[2]) < 1 + 1.E-5);
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

  /**
  * Gets the array of "linear" node indices belonging to a given facet.
  * @param[in] facet The index of the facet (where 0 <= facet < 4).
  * @param[out] facetNodes The array of "linear" local node indices of the facet. 
  * ( 0 <= facetNodes[i] < 10 for each i ).
  * @return The number of nodes added.
  */
  static size_t getNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes)
  {
    facetNodes.assign(s_facetNode[facet],s_facetNode[facet]+3);
    return 3;
  }

  /**
  * Gets a triangulation of the given facet of a quadratic tetrahedron of 10 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTriangleNodesIndex() 
  * for a quadratic tetrahedron of 10 nodes.
  * @param[in] face Number of the face. (where: 0 <= face < 4 ).
  * @param[out] triangleNodeIds Sub triangle node ids (where: 0 <= triangleNodeIds[i] < 10 for each i).
  * @return The number of sub triangles in the facet of the cell.
  */
  static size_t getSubTriangleNodesIndex(size_t face, std::vector<size_t>& triangleNodeIds)  
  {
    triangleNodeIds.assign(s_subFacetNode[face],s_subFacetNode[face]+12);
    return 4;
  }

  /**
  * Gets a decomposition in sub-tetrahedra of a quadratic tetrahedron of 10 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTetrahedronNodesIndex() 
  * for a quadratic tetrahedron of 10 nodes.
  * @param[out] tetrahedronNodeIds Sub tetrahedra node ids (where: 0 <= tetrahedronNodeIds[i] < 10 for each i).
  *             this method assign the 32 node ids tetrahedronNodeIds[0-31]
  * @return 8 (number of sub-tetrahedra in a quadratic tetrahedron of 10 nodes)
  */
  static size_t getSubTetrahedronNodesIndex (std::vector<size_t>& tetrahedronNodeIds)
  {
    tetrahedronNodeIds.assign(s_subTetrahedronNodeIds,s_subTetrahedronNodeIds+(8*4));
    return 8;
  }


SoINTERNAL public:
  friend std::ostream& operator << (std::ostream& s, const MxTetrahedron10CellExtract& cell);

protected:

  static bool initClass();
  static void exitClass();

  static bool   s_isInit;
  static double s_nodesIsoParametricCoords[10][3];
  static size_t s_subFacetNode[4][12]; // each face is split into 4 triangles
  
  static size_t s_subTetrahedronNodeIds[8*4]; // an tetra10 is split into 8 tetras
  static size_t s_facetNode[4][3];
};

#endif 

