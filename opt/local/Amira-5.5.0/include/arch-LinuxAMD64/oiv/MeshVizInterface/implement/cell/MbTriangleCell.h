/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbTriangleCell_H
#define _MbTriangleCell_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiSurfaceCell.h>
#include <MeshVizInterface/extractors/MxTriangleCellExtract.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

/**
* @DTEXT Build a triangle cell.
* 
* @ingroup MeshIViz_Implement_Cell
*/
class MESHIVIZIMPL_API MbTriangleCell : virtual public MiSurfaceCell
{
public:

  /** 
  * Construct a triangle defined by its list of indices.
  */
  MbTriangleCell(size_t n0, size_t n1, size_t n2);

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const; 

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const; 

  /**
  * Gets a node id of this cell. For instance getNodeIndex(0) returns
  * the first node id of this cell.
  * @param nod must be in the interval [0-2]
  */
  virtual size_t getNodeIndex(size_t nod) const
  {
    return m_nodeIds[nod];
  }

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    return MxTriangleCellExtract::getLongestEdgeLength(*meshGeometry,this);
  }

  //Reimplemented from MiCell 
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const 
  {
    return MxTriangleCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
  }
  
protected:
  size_t m_nodeIds[3];

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


