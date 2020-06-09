/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_REGULARCARTESIANGRID3D_
#define  _PO_SF_REGULARCARTESIANGRID3D_

#include <MeshViz/3Ddata/PbRegularCartesianGrid3D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbRegularCartesianGrid3D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbRegularCartesianGrid3D.
 * 
 */
class MESHVIZ_API PoSFRegularCartesianGrid3D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFRegularCartesianGrid3D, PbRegularCartesianGrid3D, const PbRegularCartesianGrid3D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbRegularCartesianGrid3D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, int num_z,  
                   float x_min, float y_min, float z_min,  
                   float x_max, float y_max, float z_max);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_REGULARCARTESIANGRID3D_  */

