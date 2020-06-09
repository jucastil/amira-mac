/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxWedge18CellExtract_h
#define  _MxWedge18CellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MiVolumeCell;

/**
 * @DTEXT Utility class for quadratic wedge cells with 18 nodes.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   for a quadratic wedge of 18 nodes. This class is provided to make easier the 
 *   creation of a class that implements the MiVolumeCell interface for a quadratic
*    wedge of 18 nodes. 
 *      - value of iso parametric coordinates in a wedge of 18 nodes
 *        (see getIsoParametricCoord())
 *      - value of the weights (aka shape functions) in a wedge of 18 nodes
 *        (see getWeight())
 *      - decomposition of each face in sub triangles.
 *        (see getSubTriangleNodesIndex())
 *      - decomposition in sub tetrahedrons.
 *        (see getSubTetrahedronNodesIndex())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering and the faces numbering used by this class. 
 * The weight (see getWeight()), parametric coordinates (see getIsoParametricCoord()), and
 * the decomposition in sub tetrahedrons (see getSubTetrahedronNodesIndex()) are defined 
 * according to this node numbering. The face decomposition (see getSubTriangleNodesIndex())
 * is defined according to this node and face numbering.
 *
 * @IMAGE QuadraticWedge18.png "Nodes and faces numbering"
 *
 */
class MESHIVIZ_API MxWedge18CellExtract 
{
public:

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given wedgeCell is assumed to contain 18 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(wedgeCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-17].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 18 nodes of a quadratic wedge.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-17]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a quadratic wedge of 18 nodes. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given wedgeCell is 
  * assumed to contain 18 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(wedgeCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-17].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 18 values weights[0-17]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 18 (at least) before calling this method, using for instance
  *    the weights.resize(18)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,wedgeCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a quadratic wedge of 18 nodes.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 18 values weights[0-17].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 18 (at least) before calling this method, using for instance
  *    the weights.resize(18)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights);

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 54 values derivs[0-53].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 54 (at least) before calling this method, using for instance
  *    the derivs.resize(54)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a quadratic wedge cell of 18 nodes.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a quadratic wedge of 18 nodes.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 18 values weights[0-17] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 18 (at least) before calling this method, using for instance
  *    the weights.resize(18)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d pcoord = getIsoParametricCoord(meshGeometry,wedgeCell,point);
    bool inside =  ( -1.E-5 < pcoord[0] &&  pcoord[0] < 1 + 1.E-5 &&
      -1.E-5 < pcoord[1] &&  pcoord[1] < 1 + 1.E-5 &&
      -1.E-5 < pcoord[2] &&  pcoord[2] < 1 + 1.E-5 &&
      -1.E-5 < (pcoord[0]+pcoord[1]) &&  (pcoord[0]+pcoord[1]) < 1 + 1.E-5);
    if (inside)
      getWeight(pcoord,weights);
    return inside;
  }

  /**
  * Gets the array of "linear" node indices belonging to a given facet.
  * @param[in] facet The index of the facet (where 0 <= facet < 5).
  * @param[out] facetNodes The array of "linear" local node indices of the facet. 
  * ( 0 <= facetNodes[i] < 18 for each i ).
  * @return The number of nodes added.
  */
  static size_t getNodesIndexOfFacet (size_t facet, std::vector<size_t>& facetNodes)
  {
    facetNodes.assign(s_linearNodesPerFacet[facet],s_linearNodesPerFacet[facet]+s_numLinearNodesPerFacet[facet]);
    return s_numLinearNodesPerFacet[facet];
  }

  /**
  * Gets a triangulation of the given facet of a quadratic wedge of 18 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTriangleNodesIndex() 
  * for a quadratic wedge of 18 nodes.
  * @param[in] face Number of the face. (where: 0 <= face < 5 ).
  * @param[out] triangleNodeIds Sub triangle node ids (where: 0 <= triangleNodeIds[i] < 18 for each i).
  * @return The number of sub triangles in the facet of the cell.
  */
  static size_t getSubTriangleNodesIndex(size_t face, std::vector<size_t>& triangleNodeIds)  
  {
    triangleNodeIds.assign(s_subTrianglePerFacet[face],s_subTrianglePerFacet[face]+(3*s_numSubTrianglePerFacet[face]));
    return s_numSubTrianglePerFacet[face];
  }

  /**
  * Gets a decomposition in sub-tetrahedra of a quadratic wedge of 18 nodes.
  * This static method helps to implement the method MiVolumeCell::getSubTetrahedronNodesIndex() 
  * for a quadratic wedge of 18 nodes.
  * @param[out] tetrahedronNodeIds Sub tetrahedra node ids (where: 0 <= tetrahedronNodeIds[i] < 18 for each i).
  *             this method assign the 96 node ids tetrahedronNodeIds[0-95]
  * @return 24 (number of sub-tetrahedra in a quadratic wedge of 18 nodes)
  */
  static size_t getSubTetrahedronNodesIndex (std::vector<size_t>& tetrahedronNodeIds)
  {
    tetrahedronNodeIds.assign(s_subTetrahedronNodeIds,s_subTetrahedronNodeIds+(24*4));
    return 24;
  }


SoINTERNAL public:
  /**
  * Computes the 18 first derivatives of shape function giving parametric coordinate in [-1,+1].
  * @param r,s,t [in] Parametric coordinates defined in the interval [-1,+1].
  * @param numNodes [in] Number of nodes in the cell : must be > 17
  * @param derivs [out] The resulting derivatives of the shape functions.
  */
  static void get18Derivs(double r, double s, double t, size_t numNodes, std::vector<double>& derivs);

  friend std::ostream& operator << (std::ostream& s, const MxWedge18CellExtract& cell);
protected:

  static bool initClass();
  static void exitClass();

  static void computeSubTetrahedronNodesIndex();
  static void addSubWedge(size_t n0,size_t n1,size_t n2, size_t n3,size_t n4,size_t n5, size_t orient, std::vector<size_t>& wedgeNodeIds);

  template <typename _F>
  static void addSymetricWedgesByPlane(_F& symetricByPlane, std::vector<size_t>& wedgeNodeIds);
  static void decomposeWedge(size_t orient, size_t n0,size_t n1,size_t n2, size_t n3,size_t n4,size_t n5, std::vector<size_t>& tetraNodeIds);

  static void computeSubTriangleNodesIndex();
  template <typename _F>
  static std::vector<size_t> getSymetricTriangles(_F& symetricFunctor, const std::vector<size_t>& triangleNodeIds);
  template <typename _F>
  static std::vector<size_t> getRotateTriangles(_F& rotateFunctor, const std::vector<size_t>& triangleNodeIds);
  static void addTriangle(size_t n0, size_t n1, size_t n2, std::vector<size_t>& triangleNodeIds);

  static bool            s_isInit;

  static double s_nodesIsoParametricCoords[18][3];

  static size_t s_linearNodesPerFacet[5][4];
  static size_t s_numLinearNodesPerFacet[5];

  static size_t s_numSubTrianglePerFacet[5];
  static size_t s_subTrianglePerFacet[5][24]; 

  static size_t s_subTetrahedronNodeIds[24*4]; 

  static int s_imat0[36];
  static int s_imat1[24];
  static int s_imat2[24];
  static int s_imat3[18];
  static int s_iperm[24];
};

#endif 
