/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MILINETOPOLOGYEXPLICITI_H
#define _MILINETOPOLOGYEXPLICITI_H

#include <MeshVizInterface/mesh/topology/MiTopologyExplicitI.h>
#include <MeshVizInterface/mesh/cell/MiLineCell.h>


//-----------------------------------------------------------------------------
/**
* @DTEXT List of line cells interface.
* 
* @ingroup MeshIViz_Mesh_Topology
* 
* @DESCRIPTION
*    A generic abstract interface for unstructured line mesh topology. 
* 
*/
class MiLineTopologyExplicitI : public MiTopologyExplicitI
{
public:

  /**
  * Returns a cell of this topology. The cell 
  * is identified by one id.
  */
  virtual const MiLineCell* getCell(size_t id) const = 0;

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */ 
  virtual std::ostream& toStream(std::ostream& s) const
  {
    s << "#Line topology explicitI " << std::endl;
    return MiTopologyExplicitI::toStream(s);
  }

};


#endif
