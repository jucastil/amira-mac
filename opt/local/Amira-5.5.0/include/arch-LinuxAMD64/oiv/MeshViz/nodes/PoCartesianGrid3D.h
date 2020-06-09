/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CARTESIANGRID3D_
#define  _PO_CARTESIANGRID3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFCartesianGrid3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbCartesianGrid3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoCartesianGrid3D : public PoMeshProperty {

  SO_NODE_HEADER(PoCartesianGrid3D) ;
  

 public:



  /**
   * Constructor.
   */
  PoCartesianGrid3D() ;

  /**
   * Field containing a mesh of type PbCartesianGrid3D.
   */
  PoSFCartesianGrid3D mesh;

  /**
   * Field containing a mesh of type PbCartesianGrid3D.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbCartesianGrid3D::setGeometry().
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
  virtual ~PoCartesianGrid3D() ;

} ; 
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
inline void 
PoCartesianGrid3D::setGeometry(int num_x, int num_y, int num_z,  
                               const float *xn, const float *yn, const float *zn)
{
  mesh.setGeometry(num_x,num_y,num_z, xn,yn,zn);
}

#endif /* _PO_CARTESIANGRID3D_  */

