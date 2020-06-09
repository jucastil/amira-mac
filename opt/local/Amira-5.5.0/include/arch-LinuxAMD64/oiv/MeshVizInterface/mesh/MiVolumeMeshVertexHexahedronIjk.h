/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MiVolumeMeshVertexHexahedronIjk_H
#define _MiVolumeMeshVertexHexahedronIjk_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif

#include <MeshVizInterface/mesh/MiMeshIjk.h>
#include <MeshVizInterface/mesh/geometry/MiGeometryHexahedronIjk.h>

/**
* @DTEXT  Hexahedron mesh IJK abstract interface.
* 
* @ingroup MeshIViz_Mesh
* 
* @DESCRIPTION
*    This interface defines a structured mesh as a 3D grid of hexahedrons. Each hexahedron is defined 
*    by 8 explicit coordinates. This mesh type does not use indexed vertices, so the topology of the mesh
*    is just the I, J and K dimensions of the 3D grid (see MiTopologyIjk).
*
*    The geometry of this mesh explicitly defines the 8 vertices for each hexahedron (i,j,k) where i,j,k 
*    are indices of the hexahedron in the grid. As each hexahedron is defined by its own 8 vertices, 
*    this type of mesh is useful to define "faults" as in a petroleum reservoir model. For instance if the  
*    top vertices of the hexahedron (i,j,k) are not equal to the bottom vertices of the 
*    hexahedron (i,j,k+1), a fault exists between these 2 cells.
*  
*    This type of mesh is similar to an MiVolumeMeshCurvilinear except that the geometry explicitly defines 
*    every vertex of every cell. If all hexahedrons in a MiVolumeMeshVertexHexahedronIjk mesh share 
*    their vertices with their adjacent cells, then a MiVolumeMeshCurvilinear is more appropriate 
*    and is more efficient.
* 
*    This type of mesh is also similar to MiVolumeMeshHexahedronIjk, but each hexahedron is defined
*    by 8 coordinates instead of 8 indices.
*
*    As no vertex indices are defined, this type of mesh can handle only PER_CELL data sets 
*    (see MiDataSet::getBinding()).
*  
*  @see MiGeometryHexahedronIjk to define the geometry of this mesh.
*  @see MiTopologyIjk to define the topology of this mesh. @BR
*  @see MiVolumeMeshHexahedronIjk for IJK meshes where hexahedrons are defined by indices.
*  @see MiVolumeMeshCurvilinear for IJK meshes where adjacent cells share the same points.
*  
* 
*/
class MiVolumeMeshVertexHexahedronIjk : virtual public MiMeshIjk
{
public:
  /**
  * Returns the structured geometry of this mesh. 
  */
  virtual const MiGeometryHexahedronIjk& getGeometry() const = 0;

  /**
  * @copydoc MiVolumeMeshUnstructured::getNewClone() const
  */
  virtual const MiVolumeMeshVertexHexahedronIjk* getNewClone() const
  {
    throw MiAbstractMethodError("MiVolumeMeshVertexHexahedronIjk::getNewClone()");
  }

protected://PROTECTED_TO_DOCUMENT
  /**
  * @copydoc MiMesh::toStream(std::ostream& s) const
  */
  virtual std::ostream& toStream(std::ostream& s) const
  {
    MbVec3d v[8];
    s << "#MiVolumeMeshVertexHexahedronIjk" << std::endl;
    s << getTopology() << std::endl;
    s << "#mesh geometry" << std::endl;
    for(size_t i=0; i<getTopology().getNumCellsI(); ++i)
      for(size_t j=0; j<getTopology().getNumCellsJ(); ++j)
        for(size_t k=0; k<getTopology().getNumCellsK(); ++k)
        {
            getGeometry().getCellCoords(i,j,k,v[0],v[1],v[2],v[3],v[4],v[5],v[6],v[7]);
            s << i << "," << j << "," << k << ": (" << v[0];
            for ( size_t n = 1; n < 8; ++n)
              s << "; " << v[n] << std::endl;
            s << ")" << std::endl;
        }
    return s;
  }

};

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif
