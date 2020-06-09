/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_TRIANGLEMESH2D_
#define  _PO_SF_TRIANGLEMESH2D_

#include <MeshViz/3Ddata/PbTriangleMesh2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbTriangleMesh2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbTriangleMesh2D.
 * 
 */
class MESHVIZ_API PoSFTriangleMesh2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFTriangleMesh2D, PbTriangleMesh2D, const PbTriangleMesh2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. It defines a 2D geometry. See also
   * PbTriangleMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  
                   int num_cells, const int *cell_index);

  /**
   * Convenience method to change the geometry of the mesh. It defines a 3D geometry. See also
   * PbTriangleMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                   int num_cells, const int *cell_index);

  /**
   * Convenience method to set a new 2D geometry from a points field.
   * The triangulation is realized by the DELAUNAY method.
   */
  void setGeometry(int numPoints, const float *xPointsField, const float *yPointsField) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_TRIANGLEMESH2D_  */

