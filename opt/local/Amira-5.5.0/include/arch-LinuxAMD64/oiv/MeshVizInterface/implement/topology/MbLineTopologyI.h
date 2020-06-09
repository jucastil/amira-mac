/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Fev 2011)
**=======================================================================*/
#ifndef _MbLineTopologyI_H
#define _MbLineTopologyI_H

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include <MeshVizInterface/implement/topology/MbTopologyI.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of line cells.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    Implementation for a I implicit mesh topology. 
* 
*/
class MbLineTopologyI : public MbTopologyI
{
public:
  MbLineTopologyI(size_t numCells) : m_numCells(numCells) {}

  /**
  * Returns the number of cells in the set.
  */
  virtual size_t getNumCells() const
  {
    return m_numCells;
  }

private:
  size_t m_numCells;

};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif
