/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTOPOLOGYI_H
#define _MBTOPOLOGYI_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/mesh/topology/MiTopologyI.h>
#include <MeshVizInterface/implement/topology/MbTopology.h>
#include <Inventor/STL/cassert>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    An abstract implementation for a I implicit mesh topology. 
* 
*/
class MbTopologyI : virtual public MiTopologyI, public MbTopology
{
public:

  /** 
  * Assign a list of boolean flags defining if a cell is dead or not.
  * The number of flags given must equal the number of cells.
  * Thus distance(endId-beginId) should equals the number of cells.
  */
  template <typename _BoolIter>
  void assignDeadFlags(_BoolIter beginId, _BoolIter endId);

 /** 
  * Returns true if the cell of index i should be ignored.
  * This value is ignored if the hasDeadCell() method returns false.
  * The default implementation returns always false.
  * @param i the index of the cell to check
  */ 
  virtual bool isDead(size_t i) const;

protected:
  /*
  * abstract class
  */
  MbTopologyI() {}

};

//-----------------------------------------------------------------------------
inline bool 
MbTopologyI::isDead(size_t cellId) const 
{ 
  assert ( cellId < getNumCells() ); // check cellId < #cells
  return m_deadCells[cellId]; 
}

//-----------------------------------------------------------------------------
template <typename _BoolIter>
inline void 
MbTopologyI::assignDeadFlags(_BoolIter beginId, _BoolIter endId)
{
#ifndef MBMESH_DONT_USE_STL
  m_deadCells.assign(beginId,endId);
#else
  delete m_deadCells;
  m_deadCells = new bool[this->getNumCells()];
  size_t i = 0;
  for (_BoolIter it = beginId; it != endId; ++it,++i)
    m_deadCells[i] = *it;
#endif
  m_timeStamp = MxTimeStamp::getTimeStamp();
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
