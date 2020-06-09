/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_CARTESIANGRID3D_
#define  _PO_SF_CARTESIANGRID3D_

#include <MeshViz/3Ddata/PbCartesianGrid3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbCartesianGrid3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbCartesianGrid3D.
 * 
 */
class MESHVIZ_API PoSFCartesianGrid3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFCartesianGrid3D, PbCartesianGrid3D, const PbCartesianGrid3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbCartesianGrid3D::setGeometry().
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

#endif /* _PO_SF_CARTESIANGRID3D_  */

