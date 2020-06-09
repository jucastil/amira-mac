/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MITOPOLOGY_H
#define _MITOPOLOGY_H

#include <Inventor/STL/ostream>
#include <MeshVizInterface/MxMeshIViz.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for a mesh topology. 
* 
*/
class MESHIVIZ_API MiTopology 
{
public:
  virtual ~MiTopology() {}

  /**
  * Returns a time stamp on this topology. When the content of the topology 
  * changes, the time stamp must increase. The time stamp allows MeshViz 
  * to be aware of any change to this topology.
  */
  virtual size_t getTimeStamp() const = 0;

  /** 
  * Returns true if the topology contains dead cells.
  * When false, the cells traversal can be optimized by not testing the isDead() method of each individual cells.
  * The default implementation returns always false.
  */ 
  virtual bool hasDeadCells() const { return false ;}

  /**
  * @copydoc MiMesh::operator <<()
  */
  friend std::ostream& operator << (std::ostream& s, const MiTopology& topo)
  {
    return topo.toStream(s);
  }

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */ 
  virtual std::ostream& toStream(std::ostream& s) const { return s;}
};


#endif
