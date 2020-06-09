/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMETOPOLOGYEXPLICITIJK_H
#define _MIVOLUMETOPOLOGYEXPLICITIJK_H

#include <MeshVizInterface/mesh/topology/MiTopologyIjk.h>

class MiVolumeCell;

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for a structured explicit volume mesh topology. 
* 
*/
class MESHIVIZ_API MiVolumeTopologyExplicitIjk : public MiTopologyIjk
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by three id i,j,k.
  */
  virtual const MiVolumeCell* getCell(size_t i, size_t j, size_t k) const = 0;

  /**
  * @copydoc MiVolumeTopologyExplicitI::getEndNodeId()
  */
  virtual size_t getEndNodeId() const = 0;

  /**
  * @copydoc MiVolumeTopologyExplicitI::getBeginNodeId()
  */
  virtual size_t getBeginNodeId() const { return 0; }

 /** 
  * Returns the name of the node.
  * The default implementation returns the node identifier as a string.
  * @param i the index of the node 
  */ 
  virtual std::string getNodeName(size_t i) const { 
    std::ostringstream strstream;
    strstream << i ;
    return strstream.str();
  }

};


#endif
