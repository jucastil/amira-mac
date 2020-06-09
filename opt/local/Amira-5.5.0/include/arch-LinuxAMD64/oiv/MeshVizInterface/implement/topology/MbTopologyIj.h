/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTOPOLOGYIJ_H
#define _MBTOPOLOGYIJ_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiTopologyIj.h>
#include <MeshVizInterface/implement/topology/MbTopology.h>
#include <MeshVizInterface/implement/MbIjToI.h>

#include <Inventor/STL/cassert>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    An implementation for a IJ implicit mesh topology. 
* 
*/
class MbTopologyIj : public MiTopologyIj, public MbTopology, private MbIjToI
{
public:
  /** Constructor */
  MbTopologyIj(size_t numCellI, size_t numCellJ)
    : MbIjToI(numCellI), m_numJ(numCellJ), m_hasDeadCells(false)
  {
#ifndef MBMESH_DONT_USE_STL
    m_deadCells.resize(numCellI*numCellJ);
#else
    m_deadCells = new bool[numCellI*numCellJ];
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
  * Returns true if the mesh contains some dead cells.
  */
  virtual bool hasDeadCells() const { return m_hasDeadCells;}

  /** 
  * Returns true if the cell of index (i,j) should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param (i,j) the index of the cell to check
  */ 
  virtual bool isDead(size_t i, size_t j) const;

  /**
  * Set the dead flag of cell (i,j).
  */
  void setDeadFlag(size_t i, size_t j, bool isDead=true);

protected:
  size_t m_numJ;
  bool m_hasDeadCells;

};

//-----------------------------------------------------------------------------
inline bool
MbTopologyIj::isDead(size_t i, size_t j) const
{
#ifndef MBMESH_DONT_USE_ASSERT
  assert(i<m_numI && j<m_numJ);
#endif
  return m_deadCells[getI(i,j)];
}


//-----------------------------------------------------------------------------
inline void
MbTopologyIj::setDeadFlag(size_t i, size_t j, bool isDead)
{
  if (i<m_numI && j<m_numJ) 
  {
    m_deadCells[getI(i,j)] = isDead;
    m_hasDeadCells |= isDead;
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
