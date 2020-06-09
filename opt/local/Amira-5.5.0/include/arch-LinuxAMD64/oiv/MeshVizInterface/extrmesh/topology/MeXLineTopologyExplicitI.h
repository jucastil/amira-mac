/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeXLineTopologyExplicitI_H
#define _MeXLineTopologyExplicitI_H

#include <MeshVizInterface/mesh/topology/MiLineTopologyExplicitI.h>
#include <MeshVizInterface/extrmesh/topology/MeXTopologyI.h>
#include <MeshVizInterface/extrmesh/cell/MeXLineCell.h>


//-----------------------------------------------------------------------------
/**
* @DTEXT List of extracted line cells interface.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for extracted unstructured line mesh topology. 
* 
*/
class MeXLineTopologyExplicitI : public MiLineTopologyExplicitI, virtual public MeXTopologyI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MeXLineCell* getCell(size_t id) const = 0;

};


#endif
