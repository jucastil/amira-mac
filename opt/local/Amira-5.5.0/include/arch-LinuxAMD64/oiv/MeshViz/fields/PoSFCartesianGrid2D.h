/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_SF_CARTESIANGRID2D_
#define  _PO_SF_CARTESIANGRID2D_

#include <MeshViz/3Ddata/PbCartesianGrid2D.h>
#include <MeshViz/fields/PoSFMesh.h>

/**
 * @DTEXT  Inventor field containing a mesh of type PbCartesianGrid2D.
 * 
 * @ingroup MeshFields
 * 
 * @DESCRIPTION
 *  This field contains an instance of the class PbCartesianGrid2D.
 * 
 */
class MESHVIZ_API PoSFCartesianGrid2D : public PoSFMesh {
  
  SO_SFIELD_HEADER(PoSFCartesianGrid2D,PbCartesianGrid2D,const PbCartesianGrid2D&) ;


 public:

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbCartesianGrid2D::setGeometry().
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

#endif /* _PO_SF_CARTESIANGRID2D_  */

