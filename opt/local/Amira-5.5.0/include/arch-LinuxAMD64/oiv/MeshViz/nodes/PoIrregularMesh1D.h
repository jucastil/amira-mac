/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_IRREGULARMESH1D_
#define  _PO_IRREGULARMESH1D_

#include <MeshViz/nodes/PoMeshProperty.h>
#include <MeshViz/fields/PoSFIrregularMesh1D.h>

class PbMesh;

/**
 * @DTEXT  Inventor node defining a mesh of type PbIrregularMesh1D.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoIrregularMesh1D : public PoMeshProperty {

  SO_NODE_HEADER(PoIrregularMesh1D) ;
  

 public:

  /**
   * Constructor.
   */
  PoIrregularMesh1D() ;

  /**
   * Field containing a mesh of type PbIrregularMesh1D.
   */
  PoSFIrregularMesh1D mesh;

  /**
   * Gets the instance of the class PbIrregularMesh1D contained by the field mesh.
   */
  const PbMesh* getMesh() const { return (const PbMesh*)&mesh.getValue();};

  /**
   * Convenience method to change the geometry of the mesh. See also
   * PbIrregularMesh1D::setGeometry().
   */
  void setGeometry(int size, const float *x);

  /*----------------------------------------------------------------------------*/
 SoEXTENDER public:
  virtual void  doAction(SoAction *action) ;

 SoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;
  
 protected:
  const PoSFMesh* getSFieldMesh() const { return &mesh; }
  virtual ~PoIrregularMesh1D() ;

} ; 
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
inline void 
PoIrregularMesh1D::setGeometry(int size, const float *x)
{
  mesh.setGeometry(size, x);
}

#endif /* _PO_IRREGULARMESH1D_ */

