/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVOLUMETOPOLOGYEXPLICITI_H
#define _MIVOLUMETOPOLOGYEXPLICITI_H

#include <MeshVizInterface/mesh/topology/MiTopologyExplicitI.h>
#include <MeshVizInterface/mesh/cell/MiVolumeCell.h>

//-----------------------------------------------------------------------------
/**
* @DTEXT List of volume cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an unstructured explicit volume mesh topology. 
* 
*/
class MiVolumeTopologyExplicitI : public MiTopologyExplicitI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MiVolumeCell* getCell(size_t id) const = 0;

protected:

  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#Volume topology explicitI " << std::endl;
    return MiTopologyExplicitI::toStream(s);
  }
};


#endif
