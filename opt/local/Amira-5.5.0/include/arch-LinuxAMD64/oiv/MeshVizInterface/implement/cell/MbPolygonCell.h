/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBPOLYGONCELL_H
#define _MBPOLYGONCELL_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#endif

#include <MeshVizInterface/extractors/MxPolygonCellExtract.h>
#include <MeshVizInterface/mesh/cell/MiSurfaceCell.h>
#include <MeshVizInterface/implement/MbMeshVizImpl.h>

/**
* @DTEXT Build a polygonal cell.
* 
* @ingroup MeshIViz_Implement_Cell
*/
class MbPolygonCell : virtual public MiSurfaceCell
{
public:

  /** 
  * Construct a polygon defined by its list of indices.
  */
  template <typename _NodeIdIter>
  MbPolygonCell(_NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Gets the surface of the polygon. 
  */
  double getArea(const MiGeometryI* meshGeometry) const;

  /**
  * Gets the number of edges.
  */
  virtual size_t getNumEdges() const; 

  /**
  * Gets the number of nodes.
  */
  virtual size_t getNumNodes() const; 

  virtual size_t getNodeIndex(size_t nod) const;

  /**
  * Checks if a point is inside or outside a cell.
  */
  virtual bool isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const;

  /**
  * Gets the relative size of the cell
  */
  virtual double getRelativeSize(const MiGeometryI* meshGeometry) const;


protected:
  /**
  * Defines a specialized output on stream for MbPolygonCell
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  std::vector<size_t> m_nodeIds;

};

//-----------------------------------------------------------------------------
template <typename _NodeIdIter>
inline
MbPolygonCell::MbPolygonCell(_NodeIdIter beginId, _NodeIdIter endId)
{
  m_nodeIds.assign(beginId,endId);
}

//-----------------------------------------------------------------------------
inline bool 
MbPolygonCell::isPointInsideCell(const MiGeometryI& meshGeometry, const MbVec3d &point, std::vector<double>& weights) const
{
  return MxPolygonCellExtract::isPointInsideCell(meshGeometry,this,point,weights);
}

//-----------------------------------------------------------------------------
inline double 
MbPolygonCell::getRelativeSize(const MiGeometryI* meshGeometry) const
{
  return MxPolygonCellExtract::getLongestEdgeLength(*meshGeometry,this);
}

//-----------------------------------------------------------------------------
inline double 
MbPolygonCell::getArea(const MiGeometryI* meshGeometry) const
{
  return MxPolygonCellExtract::getArea(*meshGeometry,this);
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolygonCell::getNumEdges() const
{
  return m_nodeIds.size();
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolygonCell::getNumNodes() const
{
  return m_nodeIds.size();
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolygonCell::getNodeIndex(size_t nod) const
{
  return m_nodeIds[nod];
}

//-----------------------------------------------------------------------------
inline std::ostream& 
MbPolygonCell::toStream(std::ostream& s) const
{
  s << "MbPolygonCell (";
  size_t numNodes = m_nodeIds.size();
  for (size_t i=0; i<numNodes-1; ++i)
    s << m_nodeIds[i] << ",";
  s << m_nodeIds[numNodes-1];
  s << ")";
  return s;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif


