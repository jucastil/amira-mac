/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_PARALCARTESIANGRID3D_
#define  _PO_PARALCARTESIANGRID3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFParalCartesianGrid3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbParalCartesianGrid3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoParalCartesianGrid3D : public PoMeshProperty {

  SO_NODE_HEADER(PoParalCartesianGrid3D) ;
  

 public:



  /**
   * Constructor.
   */
  PoParalCartesianGrid3D() ;

  /**
   * Field containing a mesh of type PbParalCartesianGrid3D.
   */
  PoSFParalCartesianGrid3D mesh;

  /**
   * Gets the instance of the class PbParalCartesianGrid3D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbParalCartesianGrid3D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, int num_z,  
                   const float *xn, const float *yn, const float *zn);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoParalCartesianGrid3D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoParalCartesianGrid3D::setGeometry(int num_x, int num_y, int num_z,  
                                    const float *xn, const float *yn, const float *zn)
{
  mesh.setGeometry(num_x,num_y,num_z, xn,yn,zn);
}

#endif /* _PO_PARALCARTESIANGRID3D_  */

