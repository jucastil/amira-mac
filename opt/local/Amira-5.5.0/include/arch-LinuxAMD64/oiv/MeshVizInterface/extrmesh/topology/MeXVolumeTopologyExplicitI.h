/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXVolumeTopologyExplicitI_H
#define _MeXVolumeTopologyExplicitI_H

#include <MeshVizInterface/mesh/topology/MiVolumeTopologyExplicitI.h>
#include <MeshVizInterface/extrmesh/topology/MeXTopologyI.h>
#include <MeshVizInterface/extrmesh/cell/MeXVolumeCell.h>


//-----------------------------------------------------------------------------
/**
* @DTEXT List of extracted volume cells interface.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an extracted unstructured volume mesh topology. 
* 
*/
class MeXVolumeTopologyExplicitI : public MiVolumeTopologyExplicitI, virtual public MeXTopologyI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MeXVolumeCell* getCell(size_t id) const = 0;

};


#endif
