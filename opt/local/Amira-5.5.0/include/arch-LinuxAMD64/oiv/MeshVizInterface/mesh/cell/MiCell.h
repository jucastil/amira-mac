/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiCell_H
#define _MiCell_H

#include <MeshVizInterface/mesh/geometry/MiGeometryI.h>
#include <MeshVizInterface/MxMeshIViz.h>
#include <MeshVizInterface/MiAbstractMethodError.h>

#include <MeshVizInterface/MbVec3.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/ostream>

/**
* @DTEXT  Defines an abstract cell of a mesh.
* 
* @ingroup MeshIViz_Mesh_Cell
* 
* @DESCRIPTION
*    A cell is a basic volume, surface or edge element that 
*    connects adjacent nodes of a mesh. The MiCell interface 
*    is necessary to define the topology of unstructured 1D, 2D or 3D meshes.
*    
*    MiCell is the base class that defines topological characteristics
*    of a cell (characteristics not depending on the cell dimension). 
*      - the number of edges: see getNumEdges()
*      - the number of nodes: see getNumNodes()
*      - the node index: see getNodeIndex().

*    These methods must be overridden by the appplication as they are 
*    pure virtual.
*    The characteristics that depend on the cell dimension are
*    defined in the derived interfaces MiLineCell for 1D cells,
*    MiSurfaceCell for 2D cells, and MiVolumeCell for 3D cells.
*
*   MiCell also defines additional methods with a default implementation.
*   A default implementation is provided in 2 cases:
*      - A default behavior is defined. The application should
*        override the method if this default behavior is not satisfying.
*        getRelativeSize() is an example of such a method.
*      - The method throws an exception as it is only used by some
*        extractors. When an application uses such extractors the method
*        must be overridden. getWeight() is an example of such a method.
*
*  @see MiLineCell, MiSurfaceCell, MiVolumeCell
*  @see MiTopologyExplicitI, MiVolumeTopologyExplicitI, MiSurfaceTopologyExplicitI, MiLineTopologyExplicitI
*
*/
class MESHIVIZ_API MiCell
{
public:

  /**
   * Virtual destructor
   */
  virtual ~MiCell() {}

  /**
  * Gets the number of edges. @BR For non linear cell, the number of edges is independent
  * of the order of the cell. For instance, getNumEdges must always return 3 for
  * a linear triangle cell, a quadratic triangle cell, a cubic triangle cell etc...
  */
  virtual size_t getNumEdges() const = 0; 

  /**
  * Gets the number of nodes. @BR This number must include the additional nodes
  * of non linear cells. For instance getNumNodes() for a quadratic triangle
  * cell should return 6.
  */
  virtual size_t getNumNodes() const = 0; 

  /**
  * Gets the index (in the mesh) of a node.
  * @param[in] node Node number (where: 0 <= node < getNumNodes()).
  */
  virtual size_t getNodeIndex(size_t node) const = 0;

  /**
  * Gets the relative size of the cell. @BR
  *
  * This method is used only by the MoMeshCellShape to display node names
  * if using the relative offset feature and
  * the streamline extraction to adapt the step integration to the size 
  * of the cell. getRelativeSize() should return a value depending on 
  * the size of the cell even if the default implementation returns 1. 
  * For instance, getRelativeSize() can return the length of the longest 
  * edge of this cell, or the length of its diagonal.
  *
  * If getRelativeSize() returns a constant value for 
  * any cell, the stream line extraction uses a constant number of 
  * step integration anywhere in the mesh. Returning a constant
  * implies that all the cells are supposed to have the same size.
  * getRelativeSize() must not return 0.
  *
  * @param[in] meshGeometry the geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  * @return 1 by default.
  *
  */
  virtual double getRelativeSize(const MiGeometryI* UNREF_PARAM(meshGeometry)) const 
  {
    return 1;
  }

  /**
  * Gets the weights of a point defined by its iso parametric coordinates.@BR
  * Only classes defining non linear cells must implement this method.
  *
  * A weight value (aka shape function) must be given for each node of the cell.
  * The weight must respect the following rules:
  *   - The sums of the weights must be equal to 1. 
  *   - When ipcoord matches the i-th node of the cell,
  *     weight[i] must be 1 and weight[j] must be 0 for any j!=i.
  *   - The weight depends only on pcoord[0] for all types of 1D cells.
  *   - The weight depends only on pcoord[0] and pcoord[1] for all types of 2D cells.
  *
  * See chapter "Properties of shape functions" in the User's Guide for more details.
  * This method is not pure virtual because it is not used by all 
  * extraction classes. However using an extraction class that uses this
  * method will generate an exception. An application
  * does not need to override this method if no such extraction class is used.
  *
  * 
  * @param[in] ipcoord iso parametric coordinates of the points where the weights must be evaluated. 
  * @param[out] weight Must contain at least as many elements as the number of nodes in this cell.
  * @note For extraction purpose only, it is not nessessary to resize the weight vector array since 
  *     extraction classes are optimized such as weight vectors passed to this method are
  *     already allocated and large enough to retrieve all the computed weights.
  *     Thus the following assignment is then sufficient:
  * @verbatim
  weight[i] = wi
  @endverbatim
  *  for each i with 0 <= i < getNumNodes() 
  *      
  */
  virtual void getWeight(const MbVec3d& UNREF_PARAM(ipcoord), std::vector<double>& UNREF_PARAM(weight)) const 
  {
    throw MiAbstractMethodError("MiCell::getWeight(const MbVec3d &, std::vector<double>&)");
  }

  /**
  * Gets the iso parametric coordinates of a cell's node.@BR
  * Only classes defining non linear cells must implement this method.
  *
  * The interval value of parametric coordinates are usually [0,1] or [-1,+1].
  * If the application uses interval [0,1], the parametric coordinates returned
  * by this method for linear cell must be either 0 or 1. For quadratic cell, the
  * parametric coordinates must be either 0, 0.5 or 1. (0.5 for intermediate nodes).
  * 
  * See the following image as example of parametric coordinates values for linear 
  * and quadratic quadrangle.
  * 
  * @IMAGE ParamCoordCenter.png parametric coordinates in [-1,+1]
  * @IMAGE ParamCoordUncenter.png parametric coordinates in [0,1]
  *
  * @note 1D cells use only 1 parametric coordinate (MbVec3d[0]); 2D cells use only 
  * 2 parametric coordinates (MbVec3d[0-1]); 3D cells use 3 parametric coordinates.
  *
  * This method is not pure virtual because it is not used by all 
  * extraction classes. However using an extraction class that uses this
  * method will generate an exception. An application
  * does not need to override this method if no such extraction class is used.
  * 
  * 
  * @param[in] nodeIndex The index of the node.
  */
  virtual MbVec3d getIsoParametricCoord(size_t UNREF_PARAM(nodeIndex)) const 
  {
    throw MiAbstractMethodError("MiCell::getIsoParametricCoord(size_t nodeIndex)");
  }

  /**
  * Gets the center of the cell.@BR
  *
  * This method is not pure virtual because it is not used by all 
  * extraction classes. The default implementation provided computes
  * the average of the coordinates of each cell's node.
  * @param[in] geometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  * @return The center of the cell.
  */
  virtual MbVec3d getCenter(const MiGeometryI& geometry) const;


  /**
  * Checks if a point is inside or outside a cell.@BR
  *
  * This method is not pure virtual because it is not used by all 
  * extraction classes. However using an extraction class that uses this
  * method (i.e. streamline) will generate an exception. An application
  * does not need to override this method if no such extraction class is used.
  *
  * @param[in] meshGeometry The geometry of the mesh. Used to retrieve the node coordinates
  * of this cell.
  * @param[in] point The point to be checked.
  * @param[out] weights Must contain at least  as many elements as the number of 
  * nodes in this cell (see getWeight()).
  * @return True if the point is inside the cell.
  * @note For extraction purpose only, it is not nessessary to resize the weight vector array since 
  *     extraction classes are optimized such as weight vectors passed to this method are
  *     already allocated and large enough to retrieve all the computed weights.
  *     Thus the following assignment is then sufficient:
  * @verbatim
  weight[i] = wi
  @endverbatim
  *  for each i with 0 <= i < getNumNodes() 
  */
  virtual bool isPointInsideCell(const MiGeometryI& UNREF_PARAM(meshGeometry), 
                                 const MbVec3d& UNREF_PARAM(point), 
                                 std::vector<double>& UNREF_PARAM(weights)) const
  {
    throw MiAbstractMethodError("MiCell::isPointInsideCell(const MbVec3d &point)");
  }

  /**
  * @copydoc MiMesh::operator <<()
  */
  friend std::ostream& operator << (std::ostream& s, const MiCell& cell);

protected: //PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const;

};

//-----------------------------------------------------------------------------
inline MbVec3d
MiCell::getCenter(const MiGeometryI& geometry) const
{
  MbVec3d center(0);
  for (size_t i=0; i<getNumNodes(); ++i) 
    center += geometry.getCoord(getNodeIndex(i));
  return ( center / (double) getNumNodes() );
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MiCell::toStream(std::ostream& s) const
{
  s << "# num cell's nodes" << std::endl;
  s << getNumNodes() << std::endl;
  s << "[";
  for (size_t i=0; i<getNumNodes(); ++i)
    s << getNodeIndex(i) << " ";
  s << "]";

  return s;
}

//-----------------------------------------------------------------------------
inline std::ostream& 
operator << (std::ostream& s, const MiCell& cell)
{
  return cell.toStream(s);
}


#endif 







