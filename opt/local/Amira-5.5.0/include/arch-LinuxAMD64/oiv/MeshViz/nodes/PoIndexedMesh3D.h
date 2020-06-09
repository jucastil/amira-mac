/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_INDEXEDMESH3D_
#define  _PO_INDEXEDMESH3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFIndexedMesh3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbIndexedMesh3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoIndexedMesh3D : public PoMeshProperty {

  SO_NODE_HEADER(PoIndexedMesh3D) ;
  

 public:



  /**
   * Constructor.
   */
  PoIndexedMesh3D() ;

  /**
   * Field containing a mesh of type PbIndexedMesh3D.
   */
  PoSFIndexedMesh3D mesh;

  /**
   * Gets the instance of the class PbIndexedMesh3D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbIndexedMesh3D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                   int num_cells, const int *cell_index, const int *cell_type);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoIndexedMesh3D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoIndexedMesh3D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                             int num_cells, const int *cell_index, const int *cell_type)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index,cell_type);
}

#endif /* _PO_INDEXEDMESH3D_  */

