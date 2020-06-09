/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _PO_SF_IRREGULARMESH1D_
#define  _PO_SF_IRREGULARMESH1D_

#include <MeshViz/3Ddata/PbIrregularMesh1D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbIrregularMesh1D.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbIrregularMesh1D.
 * 
 */
class MESHVIZ_API PoSFIrregularMesh1D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFIrregularMesh1D, PbIrregularMesh1D, const PbIrregularMesh1D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbIrregularMesh1D::setGeometry().
   */
  void setGeometry(int size, const float *x) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;  
	static void exitClass() ;

 protected:
  virtual PbMesh* getMesh() const;
} ; 

/*----------------------------------------------------------------------------*/

#endif /* _PO_SF_IRREGULARMESH1D_ */

