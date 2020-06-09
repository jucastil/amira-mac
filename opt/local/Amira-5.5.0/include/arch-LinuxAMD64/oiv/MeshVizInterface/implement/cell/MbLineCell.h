/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbLineCell_H
#define _MbLineCell_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/cell/MiLineCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

/**
* @DTEXT Build a line cell.
* 
* @ingroup MeshIViz_Implement_Cell
*/
class MbLineCell : virtual public MiLineCell
{
public:

  /** 
  * Construct a triangle defined by its list of indices.
  */
  MbLineCell(size_t n0, size_t n1)
  {
    m_nodeIds[0] = n0;
    m_nodeIds[1] = n1;
  }

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const 
  {
    return 1;
  }

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const
  {
    return 2;
  }

  /**
  * Gets a node id of this cell. For instance getNodeIndex(0) returns
  * the first node id of this cell.
  * @param nod must be in the interval [0-1]
  */
  virtual size_t getNodeIndex(size_t nod) const
  {
    return m_nodeIds[nod];
  }

  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const 
  {
    MbVec3d point1(meshGeometry->getCoord(m_nodeIds[0]));
    MbVec3d point2(meshGeometry->getCoord(m_nodeIds[1]));
    return (point2-point1).length();
  }
  
protected:
  size_t m_nodeIds[2];

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


