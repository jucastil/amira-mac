/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_CARTESIANGRID2D_
#define  _PO_CARTESIANGRID2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFCartesianGrid2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbCartesianGrid2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoCartesianGrid2D : public PoMeshProperty {

  SO_NODE_HEADER(PoCartesianGrid2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoCartesianGrid2D() ;

  /**
   * Field containing a mesh of type PbCartesianGrid2D.
   */
  PoSFCartesianGrid2D mesh;

  /**
   * Gets the instance of the class PbCartesianGrid2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbCartesianGrid2D::setGeometry().
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
  virtual ~PoCartesianGrid2D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoCartesianGrid2D::setGeometry(int num_x, int num_y, 
                               const float *xn, const float *yn, const float *zn)
{
  mesh.setGeometry(num_x,num_y, xn,yn,zn);
}

#endif /* _PO_CARTESIANGRID2D_  */

