/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PARALCARTESIANGRID2D_
#define  _PO_PARALCARTESIANGRID2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFParalCartesianGrid2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbParalCartesianGrid2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoParalCartesianGrid2D : public PoMeshProperty {

  SO_NODE_HEADER(PoParalCartesianGrid2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoParalCartesianGrid2D() ;

  /**
   * Field containing a mesh of type PbParalCartesianGrid2D.
   */
  PoSFParalCartesianGrid2D mesh;

  /**
   * Gets the instance of the class PbParalCartesianGrid2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbParalCartesianGrid2D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, 
                   const float *xn, const float *yn, const float *zn=NULL);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoParalCartesianGrid2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoParalCartesianGrid2D::setGeometry(int num_x, int num_y, 
                                    const float *xn, const float *yn, const float *zn)
{
  mesh.setGeometry(num_x,num_y, xn,yn,zn);
}

#endif /* _PO_PARALCARTESIANGRID2D_  */

