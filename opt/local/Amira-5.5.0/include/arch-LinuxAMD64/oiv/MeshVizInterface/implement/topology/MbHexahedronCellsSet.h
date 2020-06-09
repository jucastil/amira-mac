/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBHEXAHEDRONCELLSSET_H
#define _MBHEXAHEDRONCELLSSET_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>
#include <MeshVizInterface/implement/topology/MbTopologyI.h>
#include <MeshVizInterface/implement/cell/MbHexahedronCell.h>

#include <Inventor/STL/algorithm>

/**
* @DTEXT Build a set of hexahedron.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbHexahedronCellsSet : virtual public MiVolumeTopologyExplicitI, public MbTopologyI
{
public:

  /** 
  * Construct an empty set of hexahedrons.
  */
  MbHexahedronCellsSet();

  /** 
  * Defines a new list of hexahedrons according to their indices.
  * Thus distance(endId-beginId) should be a multiple of 8.
  */
  template <typename _NodeIdIter>
  void assign(_NodeIdIter beginId, _NodeIdIter endId);

  /**
  * Returns the i-th cell of this set.
  */
  virtual const MbHexahedronCell* getCell(size_t cellId) const;

  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const;

  /**
  * Returns the first node id in this hexa geometry.
  */
  virtual size_t getBeginNodeId() const
  {
    return m_beginNodeId;
  }

  /**
  * Returns the end node id in this tetra geometry.
  */
  virtual size_t getEndNodeId() const
  {
    return m_endNodeId;
  }

protected:
  std::vector<MbHexahedronCell> m_cells;
  size_t m_beginNodeId;
  size_t m_endNodeId;
};


//-----------------------------------------------------------------------------
inline
MbHexahedronCellsSet::MbHexahedronCellsSet()
: m_beginNodeId(0), m_endNodeId(0)
{
}


//-----------------------------------------------------------------------------
inline const MbHexahedronCell* 
MbHexahedronCellsSet::getCell(size_t cellId) const
{
  if (hasDeadCells() && isDead(cellId)) throw "Error accessing dead cells";
  return &(m_cells[cellId]);
}

//-----------------------------------------------------------------------------
inline size_t
MbHexahedronCellsSet::getNumCells() const 
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
template <typename _NodeIdIter>
inline void 
MbHexahedronCellsSet::assign(_NodeIdIter beginId, _NodeIdIter endId)
{
  size_t numIds = std::distance(beginId,endId);
  size_t numCells = (numIds - numIds%8)/8;
  m_beginNodeId = std::numeric_limits<size_t>::max();

  m_cells.clear();
  m_cells.reserve(numCells);
  _NodeIdIter it = beginId;
  size_t i, node[8];
  for (i=0; i<numCells; ++i)
  {
    for(size_t n=0; n<8; n++){
      node[n] = *it++; 
      if(node[n]+1 > m_endNodeId) m_endNodeId = node[n]+1;
      if(node[n]   < m_beginNodeId) m_beginNodeId = node[n];
    }
    m_cells.push_back(MbHexahedronCell(node[0],node[1],node[2],node[3],node[4],node[5],node[6],node[7]));
  }
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

