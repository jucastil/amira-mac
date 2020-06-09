/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_PARALCARTESIANGRID3D_
#define  _PO_SF_PARALCARTESIANGRID3D_

#include <MeshViz/3Ddata/PbParalCartesianGrid3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbParalCartesianGrid3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbParalCartesianGrid3D.
 * 
 */
class MESHVIZ_API PoSFParalCartesianGrid3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFParalCartesianGrid3D, PbParalCartesianGrid3D, const PbParalCartesianGrid3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbParalCartesianGrid3D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, int num_z,  
                   const float *xn, const float *yn, const float *zn);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_PARALCARTESIANGRID3D_  */

