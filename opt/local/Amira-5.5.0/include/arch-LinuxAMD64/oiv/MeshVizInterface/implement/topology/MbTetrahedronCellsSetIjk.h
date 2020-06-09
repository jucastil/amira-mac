/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTETRAHEDRONCELLSSETIJK_H
#define _MBTETRAHEDRONCELLSSETIJK_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/implement/topology/MbVolumeTopologyExplicitIjk.h>
#include <MeshVizInterface/implement/cell/MbTetrahedronCell.h>

#include <Inventor/STL/algorithm>


/**
* @DTEXT Build a set of tetrahedron.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbTetrahedronCellsSetIjk : public MbVolumeTopologyExplicitIjk
{
public:

  //@{
  /** 
  * Construct an empty set of hexahedrons.
  */
  MbTetrahedronCellsSetIjk(size_t numCellI, size_t numCellJ, size_t numCellK);
  MbTetrahedronCellsSetIjk(const MbTetrahedronCellsSetIjk& topology);
  //@}

  /** 
  * Defines a new tetrahedrons according to their indices.
  * Thus distance(endId-beginId) should be 4.
  */
  void setCellNodeInds(size_t i, size_t j, size_t k, 
                       const size_t* beginId, const size_t* endId);

};


//-----------------------------------------------------------------------------
inline
MbTetrahedronCellsSetIjk::MbTetrahedronCellsSetIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
: MbVolumeTopologyExplicitIjk(numCellI,numCellJ,numCellK)
{
}

//-----------------------------------------------------------------------------
inline
MbTetrahedronCellsSetIjk::MbTetrahedronCellsSetIjk(const MbTetrahedronCellsSetIjk& topology):
  MbVolumeTopologyExplicitIjk(topology)
{
  m_cells.reserve(topology.getNumCells());
  size_t node[4];
  for(size_t i=0; i<topology.getNumCells();++i)
  {
    for(size_t n=0;n<4;++n)
      node[n] = topology.m_cells[i]->getNodeIndex(n);
    m_cells.push_back(new MbTetrahedronCell(node[0],node[1],node[2],node[3]));
  }
}

//-----------------------------------------------------------------------------
inline void
MbTetrahedronCellsSetIjk::setCellNodeInds(size_t i, size_t j, size_t k, const size_t *beginId, const size_t *endId)
{
  size_t cellId = getI(i,j,k);
  assert(std::distance(beginId,endId)==4 && m_cells[cellId]==NULL);

  size_t node[4];
  size_t n=0;
  for (const size_t* it=beginId; it != endId; ++it,++n)
  {
      node[n] = *it; 
      if(node[n]+1 > m_numNodes) m_numNodes = node[n]+1;
  }
  m_cells[cellId] = new MbTetrahedronCell(node[0],node[1],node[2],node[3]);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

