/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_REGULARMESH1D_
#define  _PO_REGULARMESH1D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFRegularMesh1D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbRegularMesh1D.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoRegularMesh1D : public PoMeshProperty {

  SO_NODE_HEADER(PoRegularMesh1D) ;
  

 public:



  /**
   * Constructor.
   */
  PoRegularMesh1D() ;

  /**
   * Field containing a mesh of type PbRegularMesh1D.
   */
  PoSFRegularMesh1D mesh;

  /**
   * Gets the instance of the class PbRegularMesh1D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbRegularMesh1D::setGeometry().
   */
  void setGeometry(int numX, float xmin, float xmax);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoRegularMesh1D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoRegularMesh1D::setGeometry(int numX, float xmin, float xmax)
{
  mesh.setGeometry(numX, xmin, xmax);
}

#endif /* _PO_REGULARMESH1D_  */

