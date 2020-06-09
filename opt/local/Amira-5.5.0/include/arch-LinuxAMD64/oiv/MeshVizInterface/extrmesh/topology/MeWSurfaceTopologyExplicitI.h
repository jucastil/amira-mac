/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MeWSurfaceTopologyExplicitI_h
#define _MeWSurfaceTopologyExplicitI_h


#include <MeshVizInterface/extrmesh/topology/MeXSurfaceTopologyExplicitI.h>

/**
* @DTEXT Abstract interface to write unstructured surface mesh topology.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    This interface is used by the existing tessellator instances (see MiTessellator)
*    to write the topology of the tessellated surface meshes.
*    It is designed to allow the application to implement its own tessellator class.
*
*/
class MeWSurfaceTopologyExplicitI : public MeXSurfaceTopologyExplicitI
{
public:
  /**
  * @copydoc MeWLineTopologyExplicitI::startEditing()
  */
  virtual void startEditing() = 0;

  /**
  * @copydoc MeWLineTopologyExplicitI::finishEditing()
  */
  virtual void finishEditing() = 0;

  /**
  * Add a new tessellated surface cell in the topology. For instance
  * if the tessellator builds the tessellated mesh using always triangles,
  * this method is called by giving the 3 node ids for each triangle
  * of the tessellation.
  * @param[in] numNodes Number of nodes in the tessellated surface cell.
  * @param[in] nodeIds List of nodes id in the tessellated surface cell.
  */
  virtual void addPolygon(size_t numNodes, const size_t* nodeIds) = 0;

};


#endif

