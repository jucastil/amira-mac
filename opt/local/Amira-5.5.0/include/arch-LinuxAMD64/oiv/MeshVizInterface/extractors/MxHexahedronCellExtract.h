/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxHexahedronCellExtract_h
#define  _MxHexahedronCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MxTabOfMarchingCase;
class MiVolumeCell;

/**
 * @DTEXT Utility class for hexahedron cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell interface methods
 *   for a hexahedron cell. This class is provided to make it easier to
 *   create a class that implements the MiVolumeCell interface for a hexahedron cell. 
 *      - Extraction of the topology of an isosurface in a hexahedron.
 *        (see getIsosurfTopology())
 *      - Value of iso parametric coordinates in a linear hexahedron cell.
 *        (see getIsoParametricCoord())
 *      - Value of the 8 weights (aka shape functions) in a hexahedron cell.
 *        (see getWeight())
 *      - Localization test (see isPointInsideCell())
 *
 * The following image shows the node numbering and the face numbering used by this class. 
 * The isosurface topology (see getIsosurfTopology()), weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
 *
 * @IMAGE LinearHexahedron8.png "Nodes and faces numbering"
 *
 */
class MESHIVIZ_API MxHexahedronCellExtract 
{
public:

  /**
  * Returns the isosurface topology of the associated caseId.
  * This method can be used in the getIsosurfTopology(...) implementation of an hexahedron cell interface to return
  * the information to the isosurface extraction module.
  */
  static void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList );

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given hexahedronCell is assumed to contain 8 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(hexahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-7].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 8 nodes of a hexahedron cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-7]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex);

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a hexahedron cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given hexahedronCell is 
  * assumed to contain 8 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(hexahedronCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-7].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 8 values weights[0-7]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights.resize(8)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,hexahedronCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a hexahedron cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 8 values weights[0-7].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights.resize(8)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    double rm, sm, tm;

    rm = 1. - ipcoord[0];
    sm = 1. - ipcoord[1];
    tm = 1. - ipcoord[2];

    weights[0] = rm*sm*tm;
    weights[1] = ipcoord[0] * sm * tm;
    weights[2] = ipcoord[0]*ipcoord[1] * tm;
    weights[3] = rm * ipcoord[1] * tm;
    weights[4] = rm * sm * ipcoord[2];
    weights[5] = ipcoord[0] * sm * ipcoord[2];
    weights[6] = ipcoord[0] * ipcoord[1] * ipcoord[2];
    weights[7] = rm * ipcoord[1] * ipcoord[2];
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
  *    the derivs.resize(24)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside an hexahedron cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a hexahedron cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] hexahedronCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 8 values weights[0-7] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 8 (at least) before calling this method, using for instance
  *    the weights.resize(8)
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
  * Gets the volume of the cell.
  */
  static double getVolume(const MiGeometryI& meshGeometry, const MiVolumeCell* hexahedronCell);

  /**
  * Gets the normal of the given facet in a tetrahedron cell.
  */
  static MbVec3d getFacetNormal(size_t facetId, const MiGeometryI& meshGeometry, const MiVolumeCell* pyramidCell);

  /**
  * Gets the longest edge of a hexahedron cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

  /**
  * Gets the shortest edge of a hexahedron cell
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
  static void initMarchingCase6();
  static void initMarchingCase7();
  static void initMarchingCase8();
  static void initMarchingCase9();
  static void initMarchingCase10();
  static void initMarchingCase11();
  static void initMarchingCase12();
  static void initMarchingCase13();
  static void initMarchingCase14();

  static bool            s_isInit;
  static MxTabOfMarchingCase* s_tabOfMarchingCube;
  static double s_nodesIsoParametricCoords[8][3];

};

#endif 

