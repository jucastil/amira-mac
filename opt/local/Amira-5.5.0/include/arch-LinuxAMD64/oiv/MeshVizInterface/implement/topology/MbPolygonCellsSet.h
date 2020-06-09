/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBPOLYGONCELLSSET_H
#define _MBPOLYGONCELLSSET_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiSurfaceTopologyExplicitI.h>
#include <MeshVizInterface/implement/topology/MbTopologyI.h>
#include <MeshVizInterface/implement/cell/MbPolygonCell.h>

#include <Inventor/STL/algorithm>


/**
* @DTEXT Build a set of polygons.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbPolygonCellsSet : virtual public MiSurfaceTopologyExplicitI, public MbTopologyI
{
public:

  /** 
  * Construct an empty set of polygons.
  */
  MbPolygonCellsSet();

  /**
  * Returns the i-th cell of this set.
  */
  virtual const MbPolygonCell* getCell(size_t cellId) const;

  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const;

  /**
  * Returns the first node index in this polygonal geometry.
  */
  virtual size_t getBeginNodeId() const
  {
    return m_beginNodeId;
  }

  /**
  * Returns the number of nodes in this tetra list.
  */
  virtual size_t getEndNodeId() const
  {
    return m_maxNodeId;
  }

  /** 
  * Defines a new list of polygons according to their indices
  * and number of nodes.
  * Thus distance(endNum-beginNum) is the number of polygons.
  */
  template <typename _NodeIdIter, typename _numNodeIter>
  void assign(_NodeIdIter beginId, _NodeIdIter endId,_numNodeIter beginNum, _numNodeIter endNum);

protected:
  std::vector<MbPolygonCell> m_cells;
  size_t m_beginNodeId;
  size_t m_maxNodeId;

};


//-----------------------------------------------------------------------------
inline
MbPolygonCellsSet::MbPolygonCellsSet()
: m_beginNodeId(0), m_maxNodeId(0)
{
}

//-----------------------------------------------------------------------------
inline const MbPolygonCell* 
MbPolygonCellsSet::getCell(size_t cellId) const
{
  if (hasDeadCells() && isDead(cellId)) throw "Error accessing dead cells";
  return &(m_cells[cellId]);
}

//-----------------------------------------------------------------------------
inline size_t 
MbPolygonCellsSet::getNumCells() const
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
template <typename _NodeIdIter, typename _numNodeIter>
inline void 
MbPolygonCellsSet::assign(_NodeIdIter beginId, _NodeIdIter endId,
                          _numNodeIter beginNum, _numNodeIter endNum)
{
  size_t numCells = std::distance(beginNum,endNum);
  m_beginNodeId = std::numeric_limits<size_t>::max();
  m_cells.reserve(numCells);
  _NodeIdIter itBeginPolyg = beginId;
  _NodeIdIter itEndPolyg;
  _numNodeIter it = beginNum;
  for(size_t i=0; i<numCells; i++)
  {
    itEndPolyg = (itBeginPolyg + *it);
    m_cells.push_back(MbPolygonCell(itBeginPolyg,itEndPolyg));
    for(size_t j=0; j<*it; j++)
    {
      if(*itBeginPolyg+1>m_maxNodeId) m_maxNodeId = *itBeginPolyg+1;
      if(*itBeginPolyg < m_beginNodeId) m_beginNodeId = *itBeginPolyg;
      itBeginPolyg++;
    }
    it++;
    //itBeginPolyg = itEndPolyg;
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

