/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXSurfaceTopologyExplicitI_H
#define _MeXSurfaceTopologyExplicitI_H

#include <MeshVizInterface/mesh/topology/MiSurfaceTopologyExplicitI.h>
#include <MeshVizInterface/extrmesh/topology/MeXTopologyI.h>
#include <MeshVizInterface/extrmesh/cell/MeXSurfaceCell.h>


//-----------------------------------------------------------------------------
/**
* @DTEXT List of extracted surface cells interface.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an extracted unstructured surface mesh topology. 
* 
*/
class MESHIVIZ_API MeXSurfaceTopologyExplicitI : public MiSurfaceTopologyExplicitI, virtual public MeXTopologyI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MeXSurfaceCell* getCell(size_t id) const = 0;

};


#endif
