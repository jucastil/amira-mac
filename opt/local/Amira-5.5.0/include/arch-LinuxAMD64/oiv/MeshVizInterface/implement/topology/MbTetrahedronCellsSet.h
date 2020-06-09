/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTETRAHEDRONCELLSSET_H
#define _MBTETRAHEDRONCELLSSET_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>
#include <MeshVizInterface/implement/topology/MbTopologyI.h>
#include <MeshVizInterface/implement/cell/MbTetrahedronCell.h>

#include <Inventor/STL/algorithm>


/**
* @DTEXT Build a set of Tetrahedron.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbTetrahedronCellsSet : virtual public MiVolumeTopologyExplicitI, public MbTopologyI
{
public:

  /** 
  * Construct an empty set of tetrahedrons.
  */
  MbTetrahedronCellsSet();

  /** 
  * Defines a new list of tetrahedrons according to their indices.
  * Thus distance(endId-beginId) should be a multiple of 4.
  */
  template <typename _NodeIdIter>
  void assign(_NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Returns the i-th cell of this set.
  */
  virtual const MbTetrahedronCell* getCell(size_t id) const;


  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const;

  /**
  * Returns the first node index in this tetra geometry.
  */
  virtual size_t getBeginNodeId() const
  {
    return m_beginNodeId;
  }

  /**
  * Returns the end node index in this tetra geometry.
  */
  virtual size_t getEndNodeId() const
  {
    return m_endNodeId;
  }

protected:
  std::vector<MbTetrahedronCell> m_cells;
  size_t m_endNodeId;
  size_t m_beginNodeId;
};


//-----------------------------------------------------------------------------
inline
MbTetrahedronCellsSet::MbTetrahedronCellsSet()
: m_endNodeId(0),m_beginNodeId(0)
{
}


//-----------------------------------------------------------------------------
inline const MbTetrahedronCell* 
MbTetrahedronCellsSet::getCell(size_t cellId) const
{
  if (hasDeadCells() && isDead(cellId)) throw "Error accessing dead cells";
  return &(m_cells[cellId]);
}

//-----------------------------------------------------------------------------
inline size_t
MbTetrahedronCellsSet::getNumCells() const 
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
template <typename _NodeIdIter>
inline void 
MbTetrahedronCellsSet::assign(_NodeIdIter beginId, _NodeIdIter endId)
{
  size_t numIds = std::distance(beginId,endId);
  size_t numCells = (numIds - numIds%4)/4;

  m_beginNodeId = std::numeric_limits<size_t>::max();
  m_cells.clear();
  m_cells.reserve(numCells);
  _NodeIdIter it = beginId;
  size_t i, node[4];
  for (i=0; i<numCells; ++i)
  {
    for (size_t j = 0; j < 4; ++j,++it)
    {
      node[j] = *it;
      if (*it+1 > m_endNodeId) m_endNodeId = *it+1;
      if (*it < m_beginNodeId) m_beginNodeId = *it;
    }
    m_cells.push_back(MbTetrahedronCell(node[0],node[1],node[2],node[3]));
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

