/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_REGULAR_MESH1D_
#define  _PB_REGULAR_MESH1D_

#include <MeshViz/3Ddata/PbMesh1D.h>

/**
 * @DTEXT  Defines a regular mono-dimensional mesh.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *    Class to define a regular mono-dimentional mesh. This mesh is said regular
 *    because the gap between 2 consecutive nodes is constant.
 * 
 *    The values on the mesh nodes are defined by the 
 *    PbMesh::addValuesSet(set_index,val) method, where val argument is an 
 *    array of num_x floats.
 * 
 */
class MESHVIZ_API PbRegularMesh1D : public PbMesh1D {


 public:

  /**
   * Constructor.
   */
  PbRegularMesh1D() ;

  /**
   * Copy constructor.
   */
  PbRegularMesh1D(const PbRegularMesh1D &mesh);

  /**
   * Constructor with geometry.
   */
  PbRegularMesh1D(int numX, float xmin, float xmax) ;

  /**
   * Destructor.
   */
  ~PbRegularMesh1D() ;

  /**
   * Assignment operator.
   */
  PbRegularMesh1D& operator=(const  PbRegularMesh1D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbRegularMesh1D &m1, const PbRegularMesh1D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbRegularMesh1D &m1, const PbRegularMesh1D &m2)
  { return !(m1 == m2); }

  /**
   * Defines a new geometry.
   */
  void setGeometry(int numX, float xmin, float xmax) ;

  /**
   * Gets the mesh geometry.
   */
  void getGeometry(int &numX, float &xmin, float &xmax) const ;

  /**
   * Gets the coordinates of a node.
   */
  virtual SbVec3f getNodeCoord(int nod_index) const ;

  /*---------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual void print(FILE *fp) const;

 protected:
  virtual inline float getXCoord(int nodeIndex) const ;

  virtual void updateBoundingBox() const;

 private:
  void copy(const PbRegularMesh1D &other_mesh) ;

  float m_xMin, m_xMax, m_dx ;
} ;
/*---------------------------------------------------------------------------*/

#endif /* _PB_REGULAR_MESH1D_ */

