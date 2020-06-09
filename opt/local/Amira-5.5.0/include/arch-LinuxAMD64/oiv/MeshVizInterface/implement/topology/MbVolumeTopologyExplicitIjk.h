/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBVOLUMETOPOLOGYEXPLICITIJK_H
#define _MBVOLUMETOPOLOGYEXPLICITIJK_H

#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitIjk.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>
#include <MeshVizInterface/implement/topology/MbTopologyIjk.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for a structured explicit volume mesh topology. 
* 
*/
class MbVolumeTopologyExplicitIjk : public MiVolumeTopologyExplicitIjk, public MbTopologyIjk
{
public:
  ~MbVolumeTopologyExplicitIjk();

  /**
  * Returns a cell of this topology. The cell 
  * is identified by three id i,j,k.
  */
  const MiVolumeCell* getCell(size_t i, size_t j, size_t k) const ;

  /**
  * Returns the max node id +1 used by this topology. This topology used only 
  * node index in the interval [beginNodeId,EndNodeId[. Thus the maximum node
  * index used by the topology is getEndNodeId() -1 and the number of 
  * nodes used by this topology is getEndNodeId()-getBeginNodeId().
  */
  size_t getEndNodeId() const;

    /**
  * Returns the number of cells on the first logical axis.
  */
  size_t getNumCellsI() const { return m_numI; }

  /**
  * Returns the number of cells on the second logical axis.
  */
  size_t getNumCellsJ() const { return m_numJ; }

  /**
  * Returns the number of cells on the third logical axis.
  */
  size_t getNumCellsK() const { return m_numK; }

  /** 
  * Returns true if the cell of index (i,j,k) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j,k) the index of the cell to check
  */ 
  bool isDead(size_t i, size_t j, size_t k) const 
  {
    return MbTopologyIjk::isDead(i,j,k);
  }

  /**
  * Set the nodes indices of cell (i,j,k)
  */
  virtual void setCellNodeInds(size_t i, size_t j, size_t k, 
                       const size_t* beginId, const size_t* endId) = 0;

  /**
  * Returns the number of cells
  */
  size_t getNumCells() const;

protected:
  // abstract class
  MbVolumeTopologyExplicitIjk(size_t numCellI, size_t numCellJ, size_t numCellK);
  MbVolumeTopologyExplicitIjk(const MbVolumeTopologyExplicitIjk& topology);
  /**
  * Defines a specialized output on stream 
  */
  virtual std::ostream& toStream(std::ostream& s) const;

  std::vector<MiVolumeCell*> m_cells;
  size_t m_numNodes;

};

//-----------------------------------------------------------------------------
inline
MbVolumeTopologyExplicitIjk::MbVolumeTopologyExplicitIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
: MbTopologyIjk(numCellI,numCellJ,numCellK), m_numNodes(0)
{
  m_cells.resize(numCellK*m_numIxJ,NULL);
}

//-----------------------------------------------------------------------------
inline
MbVolumeTopologyExplicitIjk::MbVolumeTopologyExplicitIjk(const MbVolumeTopologyExplicitIjk& topology)
: MbTopologyIjk(topology), m_numNodes(topology.m_numNodes)
{
}

//-----------------------------------------------------------------------------
inline
MbVolumeTopologyExplicitIjk::~MbVolumeTopologyExplicitIjk()
{
  for(size_t i=0; i<m_cells.size();i++)
    if(m_cells[i]) delete m_cells[i];
}

//-----------------------------------------------------------------------------
inline size_t
MbVolumeTopologyExplicitIjk::getNumCells() const 
{
  return m_cells.size();
}

//-----------------------------------------------------------------------------
inline const MiVolumeCell* 
MbVolumeTopologyExplicitIjk::getCell(size_t i, size_t j, size_t k) const
{
  if (hasDeadCells() && isDead(i,j,k)) throw "Error accessing dead cells";
  return m_cells[getI(i,j,k)];
}

//-----------------------------------------------------------------------------
inline size_t
MbVolumeTopologyExplicitIjk::getEndNodeId() const
{
  return m_numNodes;
}

//-----------------------------------------------------------------------------
inline std::ostream&
MbVolumeTopologyExplicitIjk::toStream(std::ostream& s) const
{
  s << "#Volume topology explicitIjk " << std::endl;
  s << "# num cells" << std::endl;
  s << getNumCells() << std::endl;

  for(size_t i=0; i<m_numI; i++)
    for(size_t j=0; j<m_numJ; j++)
      for(size_t k=0; k<m_numK; k++)
      {
        s << "# cell #("<<i<<","<<j<<","<<k<<")";
        if (hasDeadCells() && isDead(i,j,k))
             s <<"(dead)";
        s << std::endl << *m_cells[getI(i,j,k)] << std::endl;
      }
  return s;
}

#endif
