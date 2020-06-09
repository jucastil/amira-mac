/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_TRIANGLEMESH2D_
#define  _PO_TRIANGLEMESH2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFTriangleMesh2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbTriangleMesh2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoTriangleMesh2D : public PoMeshProperty {

  SO_NODE_HEADER(PoTriangleMesh2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoTriangleMesh2D() ;

  /**
   * Field containing a mesh of type PbTriangleMesh2D.
   */
  PoSFTriangleMesh2D mesh;

  /**
   * Gets the instance of the class PbTriangleMesh2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to set a new 2D geometry from a points field.
   * The triangulation is realized by the DELAUNAY method.
   * See also PbTriangleMesh2D::setGeometry().
   */
  void setGeometry(int numPoints, const float *xPointsField, const float *yPointsField) ;

  /**
   * Convenience method to change the geometry of the mesh. Defines a 2D geometry. 
   * See also PbTriangleMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  
                   int num_cells, const int *cell_index);

  /**
   * Convenience method to change the geometry of the mesh. Defines a 3D geometry.
   * See also PbTriangleMesh2D::setGeometry().
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
  virtual ~PoTriangleMesh2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoTriangleMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,
                              int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn, num_cells, cell_index);
}

/*----------------------------------------------------------------------------*/
inline void 
PoTriangleMesh2D::setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                              int num_cells, const int *cell_index)
{
  mesh.setGeometry(num_nodes, xn,yn,zn, num_cells, cell_index);
}

/*----------------------------------------------------------------------------*/
inline void 
PoTriangleMesh2D::setGeometry(int numPoints, const float *xPointsField, const float *yPointsField)
{
  mesh.setGeometry(numPoints, xPointsField, yPointsField) ;
}

#endif /* _PO_TRIANGLEMESH2D_  */

