/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_TETRAHEDRONMESH3D_
#define  _PO_TETRAHEDRONMESH3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFTetrahedronMesh3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbTetrahedronMesh3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoTetrahedronMesh3D : public PoMeshProperty {

  SO_NODE_HEADER(PoTetrahedronMesh3D) ;
  

 public:

  /**
   * Constructor.
   */
  PoTetrahedronMesh3D() ;

  /**
   * Field containing a mesh of type PbTetrahedronMesh3D.
   */
  PoSFTetrahedronMesh3D mesh;

  /**
   * Gets the instance of the class PbTetrahedronMesh3D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbTetrahedronMesh3D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                   int num_cells, const int *cell_index);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoTetrahedronMesh3D() ;

} ; 


/*----------------------------------------------------------------------------*/
inline void 
PoTetrahedronMesh3D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                                 int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index);
}

#endif /* _PO_TETRAHEDRONMESH3D_  */

