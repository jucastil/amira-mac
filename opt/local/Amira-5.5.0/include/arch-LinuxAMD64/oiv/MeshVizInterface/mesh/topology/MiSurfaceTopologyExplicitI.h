/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MISURFACETOPOLOGYEXPLICITI_H
#define _MISURFACETOPOLOGYEXPLICITI_H

#include <MeshVizInterface/mesh/topology/MiTopologyExplicitI.h>
#include <MeshVizInterface/mesh/cell/MiSurfaceCell.h>


//-----------------------------------------------------------------------------
/**
* @DTEXT List of surface cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for an unstructured surface mesh topology. 
* 
*/
class MESHIVIZ_API MiSurfaceTopologyExplicitI : public MiTopologyExplicitI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MiSurfaceCell* getCell(size_t id) const = 0;

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */ 
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#Surface topology explicitI " << std::endl;
    return MiTopologyExplicitI::toStream(s);
  }
};


#endif
