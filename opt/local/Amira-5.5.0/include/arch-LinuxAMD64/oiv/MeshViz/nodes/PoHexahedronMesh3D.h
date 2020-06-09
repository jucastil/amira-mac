/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_HEXAHEDRONMESH3D_
#define  _PO_HEXAHEDRONMESH3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFHexahedronMesh3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbHexahedronMesh3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoHexahedronMesh3D : public PoMeshProperty {

  SO_NODE_HEADER(PoHexahedronMesh3D) ;
  

 public:



  /**
   * Constructor.
   */
  PoHexahedronMesh3D() ;

  /**
   * Field containing a mesh of type PbHexahedronMesh3D.
   */
  PoSFHexahedronMesh3D mesh;

  /**
   * Gets the instance of the class PbHexahedronMesh3D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbHexahedronMesh3D::setGeometry().
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
  virtual ~PoHexahedronMesh3D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoHexahedronMesh3D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                                int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index);
}

#endif /* _PO_HEXAHEDRONMESH3D_  */

