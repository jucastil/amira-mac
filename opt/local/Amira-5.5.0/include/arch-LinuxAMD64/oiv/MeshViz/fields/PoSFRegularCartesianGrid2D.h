/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_REGULARCARTESIANGRID2D_
#define  _PO_SF_REGULARCARTESIANGRID2D_

#include <MeshViz/3Ddata/PbRegularCartesianGrid2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbRegularCartesianGrid2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbRegularCartesianGrid2D.
 * 
 */
class MESHVIZ_API PoSFRegularCartesianGrid2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFRegularCartesianGrid2D, PbRegularCartesianGrid2D, const PbRegularCartesianGrid2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbRegularCartesianGrid2D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, 
                   float x_min, float y_min, 
                   float x_max, float y_max, 
                   const float *z=NULL);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_REGULARCARTESIANGRID2D_  */

