/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_POLARGRID2D_
#define  _PO_SF_POLARGRID2D_

#include <MeshViz/3Ddata/PbPolarGrid2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbPolarGrid2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbPolarGrid2D.
 * 
 */
class MESHVIZ_API PoSFPolarGrid2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFPolarGrid2D,PbPolarGrid2D,const PbPolarGrid2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbPolarGrid2D::setGeometry().
   */
  void setGeometry(int num_r, int num_t, 
                   const float *r, const float *t, const float *z=NULL);

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_POLARGRID2D_  */

