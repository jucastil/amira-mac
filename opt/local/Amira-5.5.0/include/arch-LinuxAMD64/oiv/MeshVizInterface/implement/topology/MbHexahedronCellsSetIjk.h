/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBHEXAHEDRONCELLSSETIJK_H
#define _MBHEXAHEDRONCELLSSETIJK_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/implement/topology/MbVolumeTopologyExplicitIjk.h>
#include <MeshVizInterface/implement/cell/MbHexahedronCell.h>

#include <Inventor/STL/algorithm>
#include <Inventor/STL/cassert>

/**
* @DTEXT Build an hexahedron cell set.
* 
* @ingroup MeshIViz_Implement_Topology
*/
class MbHexahedronCellsSetIjk : public MbVolumeTopologyExplicitIjk
{
public:

  //@{
  /** 
  * Construct an empty set of hexahedrons.
  */
  MbHexahedronCellsSetIjk(size_t numCellI, size_t numCellJ, size_t numCellK);
  MbHexahedronCellsSetIjk(const MbHexahedronCellsSetIjk& topology);
  //@}

  /** 
  * Defines a hexahedron according to its indices.
  * Thus distance(endId-beginId) should be 8.
  */
  void setCellNodeInds(size_t i, size_t j, size_t k, 
                       const size_t* beginId, const size_t* endId);

};


//-----------------------------------------------------------------------------
inline
MbHexahedronCellsSetIjk::MbHexahedronCellsSetIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
: MbVolumeTopologyExplicitIjk(numCellI,numCellJ,numCellK)
{
}

//-----------------------------------------------------------------------------
inline
MbHexahedronCellsSetIjk::MbHexahedronCellsSetIjk(const MbHexahedronCellsSetIjk& topology):
  MbVolumeTopologyExplicitIjk(topology)
{
  m_cells.resize(topology.getNumCells(),NULL);
  size_t node[8];
  for(size_t i=0; i<topology.getNumCells();++i)
  {
    if(topology.m_cells[i]!=NULL){
      for(size_t n=0;n<8;++n)
        node[n] = topology.m_cells[i]->getNodeIndex(n);
      m_cells[i] = new MbHexahedronCell(node[0],node[1],node[2],node[3],node[4],node[5],node[6],node[7]);
    }
  }
}

//-----------------------------------------------------------------------------
inline void
MbHexahedronCellsSetIjk::setCellNodeInds(size_t i, size_t j, size_t k, const size_t *beginId, const size_t* endId)
{
  assert(std::distance(beginId,endId)==8 && m_cells[getI(i,j,k)]==NULL);
  std::vector<size_t> nodeIds;
  nodeIds.reserve(8);

  size_t nodeId;
  for (const size_t* it = beginId; it != endId; ++it)
  {
      nodeId = *it; 
      if (nodeId+1 > m_numNodes) 
        m_numNodes = nodeId+1;
      nodeIds.push_back(nodeId);
  }
  m_cells[getI(i,j,k)] = new MbHexahedronCell(nodeIds[0],nodeIds[1],nodeIds[2],nodeIds[3],nodeIds[4],nodeIds[5],nodeIds[6],nodeIds[7]);
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

