/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MITOPOLOGYEXPLICITI_H
#define _MITOPOLOGYEXPLICITI_H

#include <MeshVizInterface/mesh/topology/MiTopologyI.h>
#include <MeshVizInterface/mesh/cell/MiCell.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of generic cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an unstructured explicit mesh topology. 
* 
*/
class MESHIVIZ_API MiTopologyExplicitI : virtual public MiTopologyI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MiCell* getCell(size_t UNREF_PARAM(id)) const {return 0;} //= 0;

  /**
  * Returns the last node id + 1 used by this topology. This topology uses only 
  * node index in the interval [beginNodeId,EndNodeId[. Thus the maximum node
  * index used by the topology is getEndNodeId() - 1 and the number of 
  * nodes used by this topology is getEndNodeId() - getBeginNodeId().
  */
  virtual size_t getEndNodeId() const = 0;

  /**
  * Returns the first node id used by this topology. This topology uses only 
  * node index in the interval [beginNodeId,EndNodeId[. Thus the maximum node
  * index used by the topology is getEndNodeId() - 1 and the number of 
  * nodes used by this topology is getEndNodeId() - getBeginNodeId().
  * This default implementation returns 0.
  */
  virtual size_t getBeginNodeId() const { return 0; }

protected:

  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "# num cells" << std::endl;
    s << getNumCells() << std::endl;

    for(size_t i=0; i<getNumCells(); i++)
    {
      if (hasDeadCells() && isDead(i))
        s << "# cell #" << i << " (dead)" << std::endl;
      else
        s << "# cell #" << i << std::endl;

      s << *(getCell(i)) << std::endl;
    }
    return s;
  }

};


#endif
