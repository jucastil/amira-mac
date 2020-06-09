/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MxWedgeCellExtract_h
#define  _MxWedgeCellExtract_h

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/utility>

class MxTabOfMarchingCase;
class MiVolumeCell;

/**
 * @DTEXT Utility class for wedge cells.
 * 
 * @ingroup MeshIViz_Extract_Cell
 * 
 * @DESCRIPTION
 *   Utility class that provides a static implementation of the MiVolumeCell's methods
 *   in a wedge cell. This class is provided to make easier the 
 *   creation of a class in the application that implements the MiVolumeCell  
 *   interface for a wedge cell. 
 *      - extraction of the topology of an isosurface in a wedge.
 *        (see getIsosurfTopology())
 *      - value of iso parametric coordinates in a linear wedge cell.
 *        (see getIsoParametricCoord())
 *      - value of the 6 weights (aka shape functions) in a wedge cell.
 *        (see getWeight())
 *      - localization test (see isPointInsideCell())
 *
 * The following image shows the nodes numbering and the faces numbering used by this class. 
 * The isosurface topology (see getIsosurfTopology()), weights (see getWeight()), 
 * and parametric coordinates (see getIsoParametricCoord()) are 
 * defined according to this node numbering. 
*
 * @IMAGE LinearWedge6.png "Nodes and faces numbering"
 */
class MESHIVIZ_API MxWedgeCellExtract 
{
public:

  /**
  * Returns the isosurface topology of the associated caseId.
  * This method can be used in the getIsosurfTopology(...) implementation of a wedge cell interface to return
  * the information to the isosurface extraction module.
  */
  static void getIsosurfTopology(unsigned char caseId, std::vector< std::pair<size_t,size_t> >& edgeList );

  /**
  * Computes the iso parametric coordinates of the given point in the given cell with the given geometry.
  * As computing the iso parametric coordinates of a point needs the coordinates of the cell's nodes, 
  * the given wedgeCell is assumed to contain 6 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(wedgeCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-5].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  */
  static MbVec3d getIsoParametricCoord(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point);
  
  /**
  * Returns the iso parametric coordinates of one of the 6 nodes of a wedge cell.
  * This static method helps to implement the method MiCell::getIsoParametricCoord().
  * @param [in] nodeIndex Must be defined in the range [0-5]
  */
  static MbVec3d getIsoParametricCoord(size_t nodeIndex)
  {
    return MbVec3d(s_nodesIsoParametricCoords[nodeIndex]);
  }

  /**
  * Gets the weights in the given cell of the given point. This static method 
  * helps to implement the method MiCell::getWeight(meshGeometry,point,weights) 
  * for a wedge cell. As computing the weights of a point
  * needs the coordinates of the cell's nodes, the given wedgeCell is 
  * assumed to contain 6 nodes. 
  * @note Each node coordinate of the given cell is retrieved in the following way:
  * @verbatim
     meshGeometry.getCoord(wedgeCell->getNodeIndex(i)) 
    @endverbatim
  * for each i in the range [0-5].
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 6 values weights[0-5]. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 6 (at least) before calling this method, using for instance
  *    the weights.resize(6)
  */
  static void getWeight(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell, const MbVec3d &point, std::vector<double>& weights)
  {
    MbVec3d ipcoord = getIsoParametricCoord(meshGeometry,wedgeCell,point);
    getWeight(ipcoord,weights);
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates. This 
  * static method helps to implement the method MiCell::getWeight(ipcoord,weights) 
  * for a wedge cell.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] weights This method computes the 6 values weights[0-5].           
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 6 (at least) before calling this method, using for instance
  *    the weights::resize(6)
  */
  static void getWeight(const MbVec3d &ipcoord, std::vector<double>& weights)
  {
    double um, tm;

    um = 1. - ipcoord[0] - ipcoord[1];
    tm = 1. - ipcoord[2];

    weights[0] = um * tm;
    weights[1] = ipcoord[0] * tm;
    weights[2] = ipcoord[1] * tm;

    weights[3] = um * ipcoord[2];
    weights[4] = ipcoord[0] * ipcoord[2];
    weights[5] = ipcoord[1] * ipcoord[2];
  }

  /**
  * Gets the value of the derivatives of the shape functions (aka weights) at the point given by 
  * its iso parametric coordinates.
  * @param[in] ipcoord The iso parametric coordinates of the input point. The reference
  *            space for the iso parametric coordinates is assumed to be [0-1]. Thus any
  *            point inside the cell has iso parametric coordinates in the interval [0-1].
  * @param[out] derivs This method computes the 18 values derivs[0-17].   
  *    It assumes the derivs vector array has been already allocated.
  *    Its size must be set to 18 (at least) before calling this method, using for instance
  *    the derivs::resize(18)
  */
  static void getDerivs(const MbVec3d &ipcoord, std::vector<double>& derivs);

  /**
  * Checks if a point is inside or outside a wedge cell.
  * This static method helps to implement the method 
  * MiCell::isPointInsideCell(meshGeometry,point,weights) for a wedge cell.
  * @param[in] meshGeometry The geometry of the mesh.
  * @param[in] wedgeCell The input cell.
  * @param[in] point The input point given in the same space coordinate as meshGeometry.
  * @param[out] weights This method computes the 6 values weights[0-5] if the point is inside the cell. 
  *    It assumes the weights vector array has been already allocated.
  *    Its size must be set to 6 (at least) before calling this method, using for instance
  *    the weights::resize(6)
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
  * Gets the volume of a wedge cell.
  */
  static double getVolume(const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell);

  /**
  * Gets the facet normal of a wedge cell.
  */
  static MbVec3d getFacetNormal(size_t facet, const MiGeometryI& meshGeometry, const MiVolumeCell* wedgeCell);

  /**
  * Gets the longest edge of a wedge cell
  */
  static double getLongestEdgeLength(const MiGeometryI& meshGeometry, const MiVolumeCell* cell);

  /**
  * Gets the shortest edge of a wedge cell
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

  static bool                 s_isInit;
  static MxTabOfMarchingCase* s_tabOfMarchingWedge;
  static double               s_nodesIsoParametricCoords[6][3];
};

#endif 

