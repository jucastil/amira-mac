/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MBTOPOLOGY_H
#define _MBTOPOLOGY_H

#include <MeshVizInterface/mesh/topology/MiTopology.h>
#include <MeshVizInterface/MxTimeStamp.h>
#include <Inventor/STL/vector>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells.
* 
* @ingroup MeshIViz_Implement_Topology
* 
* @DESCRIPTION
*    A abstract omplementation for a mesh topology. 
* 
*/
class MbTopology : virtual public MiTopology
{
public:

#ifdef MBMESH_DONT_USE_STL
  virtual ~MbTopology()
  {
    delete [] m_deadCells;
  }
#endif

  /**
  * Returns a time stamp on this topology. When the content of the topology 
  * changes, the time stamp must also change. The time stamp allows MeshViz 
  * to be aware of any change to this topology.
  */
  virtual size_t getTimeStamp() const {return m_timeStamp;}

  /** 
  * Returns true if the topology contains dead cells.
  * When false, the cells traversal can be optimized by not testing the isDead() method of each individual cells.
  * The default implementation returns always false.
  */ 
  virtual bool hasDeadCells() const 
  { 
#ifndef MBMESH_DONT_USE_STL
    return !m_deadCells.empty();
#else
    return m_deadCells != NULL;
#endif
  }

  /**
  * @internal
  * Simulate a modification to this topology
  */
  void touch()
  {
    m_timeStamp = MxTimeStamp::getTimeStamp();
  }

protected:
  /*
  * abstract class
  */
  MbTopology() : m_timeStamp(MxTimeStamp::getTimeStamp()) 
#ifdef MBMESH_DONT_USE_STL
    ,m_deadCells(NULL)
#endif
  {}

#ifndef MBMESH_DONT_USE_STL
  std::vector<bool> m_deadCells;
#else
  bool* m_deadCells;
#endif
  size_t m_timeStamp;

};


#endif
