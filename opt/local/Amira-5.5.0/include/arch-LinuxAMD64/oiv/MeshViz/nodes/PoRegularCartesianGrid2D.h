/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_REGULARCARTESIANGRID2D_
#define  _PO_REGULARCARTESIANGRID2D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFRegularCartesianGrid2D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbRegularCartesianGrid2D.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoRegularCartesianGrid2D : public PoMeshProperty {

  SO_NODE_HEADER(PoRegularCartesianGrid2D) ;
  

 public:



  /**
   * Constructor.
   */
  PoRegularCartesianGrid2D() ;

  /**
   * Field containing a mesh of type PbRegularCartesianGrid2D.
   */
  PoSFRegularCartesianGrid2D mesh;

  /**
   * Gets the instance of the class PbRegularCartesianGrid2D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. 
   * See also PbRegularCartesianGrid2D::setGeometry().
   */
  void setGeometry(int num_x, int num_y, 
                   float x_min, float y_min, 
                   float x_max, float y_max, 
                   const float *zn=NULL);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoRegularCartesianGrid2D() ;

 private:

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoRegularCartesianGrid2D::setGeometry(int num_x, int num_y, 
                                      float x_min, float y_min, 
                                      float x_max, float y_max, 
                                      const float *zn)
{
  mesh.setGeometry(num_x, num_y,  
                   x_min, y_min, 
                   x_max, y_max, 
                   zn);
}

#endif /* _PO_REGULARCARTESIANGRID2D_  */

