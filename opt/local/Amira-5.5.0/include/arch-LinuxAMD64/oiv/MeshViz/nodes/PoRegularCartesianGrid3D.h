/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_REGULARCARTESIANGRID3D_
#define  _PO_REGULARCARTESIANGRID3D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFRegularCartesianGrid3D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbRegularCartesianGrid3D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoRegularCartesianGrid3D : public PoMeshProperty {

  SO_NODE_HEADER(PoRegularCartesianGrid3D) ;
  

 public:



  /**
   * Constructor.
   */
  PoRegularCartesianGrid3D() ;

  /**
   * Field containing a mesh of type PbRegularCartesianGrid3D.
   */
  PoSFRegularCartesianGrid3D mesh;

  /**
   * Gets the instance of the class PbRegularCartesianGrid3D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbRegularCartesianGrid3D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, int num_z,  
                   float x_min, float y_min, float z_min,  
                   float x_max, float y_max, float z_max);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoRegularCartesianGrid3D() ;

 private:

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoRegularCartesianGrid3D::setGeometry(int num_x, int num_y, int num_z,  
                                      float x_min, float y_min, float z_min,  
                                      float x_max, float y_max, float z_max)
{
  mesh.setGeometry(num_x, num_y, num_z,  
                   x_min, y_min, z_min,  
                   x_max, y_max, z_max);
}

#endif /* _PO_REGULARCARTESIANGRID3D_  */

