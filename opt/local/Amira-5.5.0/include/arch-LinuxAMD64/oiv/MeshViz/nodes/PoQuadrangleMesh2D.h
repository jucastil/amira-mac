/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_QUADRANGLEMESH2D_
#define  _PO_QUADRANGLEMESH2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFQuadrangleMesh2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbQuadrangleMesh2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoQuadrangleMesh2D : public PoMeshProperty {

  SO_NODE_HEADER(PoQuadrangleMesh2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoQuadrangleMesh2D() ;

  /**
   * Field containing a mesh of type PbQuadrangleMesh2D.
   */
  PoSFQuadrangleMesh2D mesh;

  /**
   * Gets the instance of the class PbQuadrangleMesh2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. Defines a 2D geometry. 
   * See also PbQuadrangleMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  
                   int num_cells, const int *cell_index);

  /**
   * Convenience method to change the geometry of the mesh. Defines a 3D geometry.
   * See also PbQuadrangleMesh2D::setGeometry().
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
  virtual ~PoQuadrangleMesh2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoQuadrangleMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,
                                int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn, num_cells, cell_index);
}

/*----------------------------------------------------------------------------*/
inline void 
PoQuadrangleMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                                int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index);
}

#endif /* _PO_QUADRANGLEMESH2D_  */

