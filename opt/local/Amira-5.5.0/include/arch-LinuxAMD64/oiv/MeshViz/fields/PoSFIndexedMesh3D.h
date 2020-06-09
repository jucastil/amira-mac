/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _PO_SF_INDEXEDMESH3D_
#define  _PO_SF_INDEXEDMESH3D_

#include <MeshViz/3Ddata/PbIndexedMesh3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbIndexedMesh3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbIndexedMesh3D.
 * 
 */
class MESHVIZ_API PoSFIndexedMesh3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFIndexedMesh3D, PbIndexedMesh3D, const PbIndexedMesh3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbIndexedMesh3D::setGeometry().
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

#endif /* _PO_SF_INDEXEDMESH3D_  */

