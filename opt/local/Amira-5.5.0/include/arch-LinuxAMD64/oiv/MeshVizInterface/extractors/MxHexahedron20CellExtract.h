/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxHexahedron20CellExtract_h
#define  _MxHexahedron20CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiVolumeCell;

/**
 * @DTEXT Utility class for quadratic hexahedron cells with 20 nodes.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of MiVolumeCell's methods
 *   for a quadratic hexahedron of 20 nodes. This class is provided to make it easier to 
 *   create a class that implements the MiVolumeCell interface for a quadratic
 *   hexahedron of 20 nodes. 
 *      - value of iso parametric coordinates in an hexahedron of 20 nodes
 *        (see getIsoParametricCoord())
 *      - value of the weights (aka shape functions) in a hexahedron of 20 nodes
 *        (see getWeight())
 *      - decomposition of each face in sub triangles.
 *        (see getSubTriangleNodesIndex())
 *      - decomposition in sub tetrahedrons.
 *        (see getSubTetrahedronNodesIndex())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the node numbering and the face numbering used by this class. 
 * The weight (see getWeight()), parametric coordinates (see getIsoParametricCoord()), and
 * the decomposition into sub tetrahedrons (see getSubTetrahedronNodesIndex()) are defined 
 * according to this node numbering. The face decomposition (see getSubTriangleNodesIndex())
 * is defined according to this node and face numbering.
 *
 * @IMAGE QuadraticHexa20.png "Nodes and faces numbering"
 *
 */
class MESHIVIZ_API MxHexahedron20CellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given hexahedronCell is assumed to contain 20 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(hexahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-19].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinate of one of the 20 nodes of a quadratic hexahedron.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-19]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a quadratic hexahedron of 20 nodes. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given hexahedronCell is 
  * assumed to contain 20 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(hexahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-19].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 20 weight values [0-19]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 20 (at least) before calling this method, using for instance
  *    weights.resize(20)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,hexahedronCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a quadratic hexahedron of 20 nodes.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 20 weight values [0-19].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 20 (at least) before calling this method, using for instance
  *    weights.resize(20)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 60 derivs values [0-59].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 60 (at least) before calling this method, using for instance
  *    derivs.resize(60)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a quadratic hexahedron cell of 20 nodes.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a quadratic hexahedron of 20 nodes.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 20 weights values [0-19] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 20 (at least) before calling this method, using for instance
  *    the weights.resize(20)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,hexahedronCell,point);
    bool inside = ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 &&
                    -1.E-5 < pcoord[2] &&  pcoord[2] < 1 + 1.E-5 );
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

  /**
  * Gets the array of "linear" node indices belonging to a given facet.
  * @param[in] facet The index of the facet (where 0 <= facet < 6).
  * @param[out] facetNodes The array of "linear" local node indices of the facet. 
  * ( 0 <= facetNodes[i] < 20 for each i ).
  * @return The number of nodes added.
  */
  static size_t getNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes)
  {
    facetNodes.assign(s_facetNode[facet],s_facetNode[facet]+4);
    return 4;
  }

  /**
  * Gets a triangulation of the given facet of a quadratic hexahedron of 20 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTriangleNodesIndex() 
  * for a quadratic hexahedron of 20 nodes.
  * @param[in] face Number of the face. (where: 0 <= face < 6 ).
  * @param[out] triangleNodeIds Sub triangle node ids (where: 0 <= triangleNodeIds[i] < 20 for each i).
  * @return The number of sub triangles in the facet of the cell.
  */
  static size_t getSubTriangleNodesIndex(size_t face, std::vector<size_t>& triangleNodeIds)  
  {
    triangleNodeIds.assign(s_subFacetNode[face],s_subFacetNode[face]+18);
    return 6;
  }

  /**
  * Gets a decomposition in sub-tetrahedra of a quadratic hexahedron of 20 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTetrahedronNodesIndex() 
  * for a quadratic hexahedron of 20 nodes.
  * @param[out] tetrahedronNodeIds Sub tetrahedra node ids (where: 0 <= tetrahedronNodeIds[i] < 20 for each i).
  *             this method assign the 88 node ids tetrahedronNodeIds[0-87]
  * @return 22 (number of sub-tetrahedra in a quadratic hexahedron of 20 nodes)
  */
  static size_t getSubTetrahedronNodesIndex (std::vector<size_t>& tetrahedronNodeIds)
  {
    tetrahedronNodeIds.assign(s_subTetrahedronNodeIds,s_subTetrahedronNodeIds+88);
    return 22;
  }


SoINTERNAL public:
  /**
  * Computes the 20 first derivatives of shape function giving parametric coordinate in [-1,+1].
  * @param r,s,t [in] Parametric coordinates defined in the interval [-1,+1].
  * @param numNodes [in] Number of nodes in the cell : must be > 19
  * @param derivs [out] The resulting derivatives of the shape functions.
  */
  static void get20Derivs(double r, double s, double t, size_t numNodes, std::vector<double>& derivs);

protected:

  static bool initClass();
  static void exitClass();

  static bool   s_isInit;
  static double s_nodesIsoParametricCoords[20][3];
  static size_t s_subFacetNode[6][18];
  
  static size_t s_subTetrahedronNodeIds[22*4]; // an hexa20 is split into 22 tetras
  static size_t s_symetricByFace_16_17_18_19[20];

  static size_t s_facetNode[6][4];
};

#endif 

