/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_INDEXEDMESH2D_
#define  _PO_INDEXEDMESH2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFIndexedMesh2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbIndexedMesh2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoIndexedMesh2D : public PoMeshProperty {

  SO_NODE_HEADER(PoIndexedMesh2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoIndexedMesh2D() ;

  /**
   * Field containing a mesh of type PbIndexedMesh2D.
   */
  PoSFIndexedMesh2D mesh;

  /**
   * Gets the instance of the class PbIndexedMesh2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. Defines a 2D geometry. 
   * See also PbIndexedMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  
                   int num_cells, const int *cell_index, const int *cell_type);

  /**
   * Convenience method to change the geometry of the mesh. Defines a 3D geometry.
   * See also PbIndexedMesh2D::setGeometry().
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
  virtual ~PoIndexedMesh2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoIndexedMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,  
                             int num_cells, const int *cell_index, const int *cell_type)
{
  mesh.setGeometry(num_nodes, xn,yn, num_cells, cell_index,cell_type);
}

/*----------------------------------------------------------------------------*/
inline void 
PoIndexedMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                             int num_cells, const int *cell_index, const int *cell_type)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index,cell_type);
}

#endif /* _PO_INDEXEDMESH2D_  */

