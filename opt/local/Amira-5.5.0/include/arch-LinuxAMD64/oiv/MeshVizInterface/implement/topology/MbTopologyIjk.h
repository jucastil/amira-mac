/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTOPOLOGYIJK_H
#define _MBTOPOLOGYIJK_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiTopologyIjk.h>
#include <MeshVizInterface/implement/topology/MbTopology.h>
#include <MeshVizInterface/implement/MbIjkToI.h>

#ifndef MBMESH_DONT_USE_ASSERT
#include <Inventor/STL/cassert>
#endif

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    An implementation for a IJK implicit mesh topology. 
* 
*/
class MbTopologyIjk : virtual public MiTopologyIjk, public MbTopology, protected MbIjkToI
{
public:
  /** Constructor */
  MbTopologyIjk(size_t numCellI, size_t numCellJ, size_t numCellK)
    : MbIjkToI(numCellI,numCellJ), m_numJ(numCellJ), m_numK(numCellK),
      m_hasDeadCells(false)
  {
#ifndef MBMESH_DONT_USE_STL
    m_deadCells.resize(m_numIxJ*numCellK);
#else
    m_deadCells = new bool[m_numIxJ*numCellK];
#endif
  }

  /**
  * Returns the number of cells on the first logical axis.
  */
  virtual size_t getNumCellsI() const { return m_numI; }

  /**
  * Returns the number of cells on the second logical axis.
  */
  virtual size_t getNumCellsJ() const { return m_numJ; }

  /**
  * Returns the number of cells on the third logical axis.
  */
  virtual size_t getNumCellsK() const { return m_numK; }

  /**
  * Returns true if the mesh contains some dead cells.
  */
  virtual bool hasDeadCells() const { return m_hasDeadCells;}

  /** 
  * Returns true if the cell of index (i,j,k) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j,k) the index of the cell to check
  */ 
  virtual bool isDead(size_t i, size_t j, size_t k) const;

  /**
  * Set the dead flag of cell (i,j).
  */
  void setDeadFlag(size_t i, size_t j, size_t k, bool isDead=true);

protected:
  size_t m_numJ;
  size_t m_numK;
  bool m_hasDeadCells;

};

//-----------------------------------------------------------------------------
inline bool
MbTopologyIjk::isDead(size_t i, size_t j, size_t k) const
{
#ifndef MBMESH_DONT_USE_ASSERT
  assert(i<m_numI && j<m_numJ && k<m_numK);
#endif
  return m_deadCells[getI(i,j,k)];
}


//-----------------------------------------------------------------------------
inline void
MbTopologyIjk::setDeadFlag(size_t i, size_t j, size_t k, bool isDead)
{
  if (i<m_numI && j<m_numJ && k<m_numK) 
  {
    m_deadCells[getI(i,j,k)] = isDead;
    m_hasDeadCells |= isDead;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
