/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MbQuadrangleCellsSet_H
#define _MbQuadrangleCellsSet_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiSurfaceTopologyExplicitI.h>
#include <MeshVizInterface/implement/topology/MbTopologyI.h>
#include <MeshVizInterface/implement/cell/MbQuadrangleCell.h>

#include <Inventor/STL/algorithm>


/**
* @DTEXT Build a quadrangle cell set.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbQuadrangleCellsSet : virtual public MiSurfaceTopologyExplicitI, public MbTopologyI
{
public:

  /** 
  * Construct an empty set of quadrangle.
  */
  MbQuadrangleCellsSet();

  /**
  * Returns the i-th cell of this set.
  */
  virtual const MbQuadrangleCell* getCell(size_t cellId) const;

  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const;

  /**
  * Returns the first node index in this quadrangle list.
  */
  virtual size_t getBeginNodeId() const
  {
    return m_beginNodeId;
  }

  /**
  * Returns the end node index in this quadrangle list.
  */
  virtual size_t getEndNodeId() const
  {
    return m_endNodeId;
  }

  /** 
  * Defines a new list of quadrangle according to their indices.
  * Thus distance(endId-beginId) should be a multiple of 4.
  */
  template <typename _NodeIdIter>
  void assign(_NodeIdIter beginId, _NodeIdIter endId);

protected:
  std::vector<MbQuadrangleCell> m_cells;
  size_t m_beginNodeId;
  size_t m_endNodeId;

};


//-----------------------------------------------------------------------------
inline
MbQuadrangleCellsSet::MbQuadrangleCellsSet()
: m_beginNodeId(0), m_endNodeId(0)
{
}

//-----------------------------------------------------------------------------
inline const MbQuadrangleCell* 
MbQuadrangleCellsSet::getCell(size_t cellId) const
{
  if (hasDeadCells() && isDead(cellId)) throw "Error accessing dead cells";
  return &(m_cells[cellId]);
}

//-----------------------------------------------------------------------------
inline size_t 
MbQuadrangleCellsSet::getNumCells() const
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
template <typename _NodeIdIter>
inline void 
MbQuadrangleCellsSet::assign(_NodeIdIter beginId, _NodeIdIter endId)
{
  size_t numIds = std::distance(beginId,endId);
  size_t numCells = (numIds - numIds%4)/4;
  m_beginNodeId = std::numeric_limits<size_t>::max();

  m_cells.clear();
  m_cells.reserve(numCells);
  _NodeIdIter it = beginId;
  size_t node[4];
  for (size_t i=0; i<numCells; ++i)
  {
    for (size_t n=0; n<4; n++)
    {
      node[n] = *it++; 
      if(node[n]+1 > m_endNodeId) m_endNodeId = node[n]+1;
      if(node[n]   < m_beginNodeId) m_beginNodeId = node[n];
    }
    m_cells.push_back(MbQuadrangleCell(node[0],node[1],node[2],node[3]));
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

