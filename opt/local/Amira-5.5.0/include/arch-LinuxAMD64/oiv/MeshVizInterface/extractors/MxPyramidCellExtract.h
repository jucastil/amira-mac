/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxPyramidCellExtract_h
#define  _MxPyramidCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>
#include <MeshVizInterface/extractors/MxHalfPyramidCell.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MxTabOfMarchingCase;
class MiVolumeCell;

/**
 * @DTEXT Utility class for pyramid cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   in a pyramid cell. This class is provided to make easier the 
 *   creation of a class in the application that implements the MiVolumeCell  
 *   interface for a pyramid cell. 
 *      - extraction of the topology of an isosurface in a pyramid.
 *        (see getIsosurfTopology())
 *      - value of iso parametric coordinates in a linear pyramid cell.
 *        (see getIsoParametricCoord())
 *      - value of the 5 weights (aka shape functions) in a pyramid cell.
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering and the faces numbering used by this class. 
 * The isosurface topology (see getIsosurfTopology()), weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 * @IMAGE LinearPyramid5.png "Nodes and faces numbering"
 */
class MESHIVIZ_API MxPyramidCellExtract 
{
public:

  /**
  * Returns the isosurface topology of the associated caseId.
  * This method can be used in the getIsosurfTopology(...) implementation of a pyramid cell interface to return
  * the information to the isosurface extraction module.
  */
  static void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList );

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given pyramidCell is assumed to contain 5 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(pyramidCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-4].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] pyramidCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell, const MbVec3d &point);
  
  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a pyramid cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given pyramidCell is 
  * assumed to contain 5 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(pyramidCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-4].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] pyramidCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 5 values weights[0-4]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 5 (at least) before calling this method, using for instance
  *    the weights.resize(5)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell, const MbVec3d &point, std::vector<double>& weights)
  {
    getWeight(getIsoParametricCoord(meshGeometry,pyramidCell,point),weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a pyramid cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 5 values weights[0-4].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 5 (at least) before calling this method, using for instance
  *    the weights::resize(5)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    double rm, sm, tm;

    rm = 1. - ipcoord[0];
    sm = 1. - ipcoord[1];
    tm = 1. - ipcoord[2];

    weights[0] = rm * sm * tm;
    weights[1] = ipcoord[0] * sm * tm;
    weights[2] = ipcoord[0] * ipcoord[1] * tm;
    weights[3] = ipcoord[1] * rm * tm;
    weights[4] = ipcoord[2];
  }

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 24 values derivs[0-23].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 24 (at least) before calling this method, using for instance
  *    the derivs::resize(24)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a pyramid cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a pyramid cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] pyramidCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 5 values weights[0-4] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 5 (at least) before calling this method, using for instance
  *    the weights::resize(5)
  * @return true if the point is inside the cell.
  */
  static bool isPointInsideCell(const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell, const MbVec3d &point, std::vector<double>& weights)
  {
    size_t n0 = pyramidCell->getNodeIndex(0);
    size_t n1 = pyramidCell->getNodeIndex(1);
    size_t n2 = pyramidCell->getNodeIndex(2);
    size_t n3 = pyramidCell->getNodeIndex(3);
    size_t n4 = pyramidCell->getNodeIndex(4);
    s_halfPyramid.setNodeIds(n0,n1,n2,n4);
    bool inside = s_halfPyramid.isPointInsideCell(meshGeometry,point,weights);
    if (!inside)
    {
      s_halfPyramid.setNodeIds(n0,n2,n3,n4);
      inside = s_halfPyramid.isPointInsideCell(meshGeometry,point,weights);
    }
    if(inside)
      getWeight(meshGeometry,pyramidCell,point,weights);
    return inside;
  }

  /**
  * Gets the volume of the cell.
  */
  static double getVolume(const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell);

  /**
  * Gets the normal of the given facet in a tetrahedron cell.
  */
  static MbVec3d getFacetNormal(size_t facetId, const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell);

  /**
  * Gets the longest edge of a pyramid cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

  /**
  * Gets the shortest edge of a pyramid cell
  */
  static double getShortestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

protected:

  static bool initClass();
  static void exitClass();

  static void initMarchingCase0();
  static void initMarchingCase1();
  static void initMarchingCase2();
  static void initMarchingCase3();
  static void initMarchingCase4();
  static void initMarchingCase5();


  static bool                 s_isInit;
  static MxTabOfMarchingCase* s_tabOfMarchingPyramid;
  static MxHalfPyramidCell    s_halfPyramid;
};

#endif 

