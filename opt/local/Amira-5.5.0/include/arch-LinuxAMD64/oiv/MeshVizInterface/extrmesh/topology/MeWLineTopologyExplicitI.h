/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeWLineTopologyExplicitI_h
#define _MeWLineTopologyExplicitI_h


#include <MeshVizInterface/extrmesh/topology/MeXLineTopologyExplicitI.h>

/**
* @DTEXT Abstract interface to write unstructured line mesh topology.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    This interface is used by the existing tessellator instances (see MiTessellator)
*    to write the topology of the tessellated line meshes.
*    It is designed to allow the application to implement its own tessellator class.
*
*/
class MeWLineTopologyExplicitI : public MeXLineTopologyExplicitI
{
public:

  /**
  * Method called before the tessellation of the input mesh starts. @BR
  * It could be used for instance to allocate resources necessary to
  * store the tessellated topology or to clear the resources used by 
  * a previous tessellation.
  */
  virtual void startEditing() = 0;

  /**
  * Method called when the tessellation of the input mesh is finished.
  */
  virtual void finishEditing() = 0;

  /**
  * Add a new tessellated line cell in the topology. 
  *
  * @param[in] numNodes Number of nodes in the tessellated line cell.
  * @param[in] nodeIds List of node ids in the tessellated line cell.
  */
  virtual void addPolyline(size_t numNodes, const size_t* nodeIds) = 0;

};


#endif

