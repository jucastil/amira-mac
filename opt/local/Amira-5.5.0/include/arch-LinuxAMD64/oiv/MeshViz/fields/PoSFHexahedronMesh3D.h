/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_HEXAHEDRONMESH3D_
#define  _PO_SF_HEXAHEDRONMESH3D_

#include <MeshViz/3Ddata/PbHexahedronMesh3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbHexahedronMesh3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbHexahedronMesh3D.
 * 
 */
class MESHVIZ_API PoSFHexahedronMesh3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFHexahedronMesh3D, PbHexahedronMesh3D, const PbHexahedronMesh3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbHexahedronMesh3D::setGeometry().
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

#endif /* _PO_SF_HEXAHEDRONMESH3D_  */

