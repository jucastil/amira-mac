/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_PARALCARTESIANGRID2D_
#define  _PO_SF_PARALCARTESIANGRID2D_

#include <MeshViz/3Ddata/PbParalCartesianGrid2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbParalCartesianGrid2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbParalCartesianGrid2D.
 * 
 */
class MESHVIZ_API PoSFParalCartesianGrid2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFParalCartesianGrid2D, PbParalCartesianGrid2D, const PbParalCartesianGrid2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbParalCartesianGrid2D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, 
                   const float *xn, const float *yn, const float *zn=NULL);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_PARALCARTESIANGRID2D_  */

