/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _PO_SF_INDEXEDMESH2D_
#define  _PO_SF_INDEXEDMESH2D_

#include <MeshViz/3Ddata/PbIndexedMesh2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbIndexedMesh2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbIndexedMesh2D.
 * 
 */
class MESHVIZ_API PoSFIndexedMesh2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFIndexedMesh2D, PbIndexedMesh2D, const PbIndexedMesh2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. It defines a 2D geometry. See also
   * PbIndexedMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  
                   int num_cells, const int *cell_index, const int *cell_type);

  /**
   * Convenience method to change the geometry of the mesh. It defines a 3D geometry. See also
   * PbIndexedMesh2D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                   int num_cells, const int *cell_index, const int *cell_type);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_INDEXEDMESH2D_  */

