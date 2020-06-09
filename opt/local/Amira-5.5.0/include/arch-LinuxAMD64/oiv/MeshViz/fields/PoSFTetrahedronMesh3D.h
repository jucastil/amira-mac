/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_TETRAHEDRONMESH3D_
#define  _PO_SF_TETRAHEDRONMESH3D_

#include <MeshViz/3Ddata/PbTetrahedronMesh3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbTetrahedronMesh3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbTetrahedronMesh3D.
 * 
 */
class MESHVIZ_API PoSFTetrahedronMesh3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFTetrahedronMesh3D, PbTetrahedronMesh3D, const PbTetrahedronMesh3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbTetrahedronMesh3D::setGeometry().
   */
  void setGeometry(int num_nodes, const float *xn, const float *yn,  const float *zn,
                   int num_cells, const int *cell_index);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_TETRAHEDRONMESH3D_  */

