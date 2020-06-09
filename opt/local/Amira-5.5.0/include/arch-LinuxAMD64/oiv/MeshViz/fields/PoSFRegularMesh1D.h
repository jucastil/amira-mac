/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_REGULARMESH1D_
#define  _PO_SF_REGULARMESH1D_

#include <MeshViz/3Ddata/PbRegularMesh1D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbRegularMesh1D.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbRegularMesh1D.
 * 
 */
class MESHVIZ_API PoSFRegularMesh1D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFRegularMesh1D, PbRegularMesh1D, const PbRegularMesh1D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbRegularMesh1D::setGeometry().
   */
  void setGeometry(int numX, float xmin, float xmax) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_REGULARMESH1D_ */

