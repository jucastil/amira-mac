/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_POLARGRID2D_
#define  _PO_POLARGRID2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFPolarGrid2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbPolarGrid2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoPolarGrid2D : public PoMeshProperty {

  SO_NODE_HEADER(PoPolarGrid2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoPolarGrid2D() ;

  /**
   * Field containing a mesh of type PbPolarGrid2D.
   */
  PoSFPolarGrid2D mesh;

  /**
   * Gets the instance of the class PbPolarGrid2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbPolarGrid2D::setGeometry().
   */
  void setGeometry(int num_r, int num_t, 
                   const float *r, const float *t, const float *z=NULL);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoPolarGrid2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoPolarGrid2D::setGeometry(int num_r, int num_t, 
                           const float *r, const float *t, const float *z)
{
  mesh.setGeometry(num_r,num_t, r,t,z);
}

#endif /* _PO_POLARGRID2D_  */

