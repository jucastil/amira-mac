/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Martial Bonaventure (Apr 2011)
**=======================================================================*/
#ifndef _MeWVolumeTopologyExplicitI_h
#define _MeWVolumeTopologyExplicitI_h


#include <MeshVizInterface/extrmesh/topology/MeXVolumeTopologyExplicitI.h>

/**
* @DTEXT Abstract interface to write unstructured volume mesh topology.
* 
* @ingroup MeshIViz_ExtractedMesh_Topology
* 
* @DESCRIPTION
*    This interface is used by the existing tessellator instances (see MiTessellator)
*    to write the topology of the tessellated volume meshes.
*    It is designed to allow the application to implement its own tessellator class.
*
*/
class MeWVolumeTopologyExplicitI : public MeXVolumeTopologyExplicitI
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
  * Add a new tessellated tetrahedron cell in the topology. For instance,
  * if the tessellator builds the tessellated mesh using tetrahedrons,
  * this method must be called by giving the 4 node ids for each tetrahedron
  * of the tessellation.
  * The following image shows the expected nodes numbering. 
  * @IMAGE LinearTetrahedron4.png "Nodes and faces numbering"
  * @param[in] nodeIds List of nodes id in the tessellated tetrahedron cell.
  */
  virtual void addTetrahedron(const size_t nodeIds[4]) = 0;

    /**
  * Add a new tessellated pyramid cell in the topology. For instance
  * if the tessellator builds the tessellated mesh using pyramids,
  * this method must be called by giving the 5 node ids for each pyramid
  * of the tessellation. The first 4 node ids must represent the base.
  * The following image shows the expected nodes numbering. 
  * @IMAGE LinearPyramid5.png "Nodes and faces numbering"
  * @param[in] nodeIds List of nodes id in the tessellated pyramid cell.
  */
  virtual void addPyramid(const size_t nodeIds[5]) = 0;

  /**
  * Add a new tessellated wedge cell in the topology. For instance
  * if the tessellator builds the tessellated mesh using wedges,
  * this method must be called by giving the 6 node ids for each wedge
  * of the tessellation.
  * The following image shows the expected nodes numbering. 
  * @IMAGE LinearWedge6.png "Nodes and faces numbering"
  * @param[in] nodeIds List of nodes id in the tessellated wedge cell.
  */
  virtual void addWedge(const size_t nodeIds[6]) = 0;

    /**
  * Add a new tessellated volume cell in the topology. For instance
  * if the tessellator builds the tessellated mesh using hexahedron,
  * this method must be called by giving the 8 node ids for each hexahedron
  * of the tessellation.
  * The following image shows the expected nodes numbering. 
  * @IMAGE LinearHexahedron8.png "Nodes and faces numbering"
  * @param[in] nodeIds List of nodes id in the tessellated hexahedron cell.
  */
  virtual void addHexahedron(const size_t nodeIds[8]) = 0;

};


#endif

