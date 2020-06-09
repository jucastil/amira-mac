/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_IRREGULAR_MESH1D_
#define  _PB_IRREGULAR_MESH1D_

#include <MeshViz/3Ddata/PbMesh1D.h>

/**
 * @DTEXT  Defines a irregular mono-dimensional mesh.
 * 
 * @ingroup mesh
 * 
 * @DESCRIPTION
 *   
 * 
 */
class MESHVIZ_API PbIrregularMesh1D : public PbMesh1D {


 public:

  /**
   * Constructor.
   */
  PbIrregularMesh1D() ;

  /**
   * Copy constructor.
   */
  PbIrregularMesh1D(const PbIrregularMesh1D &mesh);

  /**
   * Constructor with geometry.
   */
  PbIrregularMesh1D(int size, const float *x) ;

  /**
   * Destructor.
   */
  ~PbIrregularMesh1D() ;

  /**
   * Assignment operator.
   */
  PbIrregularMesh1D& operator=(const  PbIrregularMesh1D &mesh) ;

  /**
   * Equality comparison operator.
   */
  MESHVIZ_API friend int operator ==(const PbIrregularMesh1D &m1, const PbIrregularMesh1D &m2);

  /**
   * Inequality comparison operator.
   */
  MESHVIZ_API friend int operator !=(const PbIrregularMesh1D &m1, const PbIrregularMesh1D &m2)
  { return !(m1 == m2); }

  /**
   * Defines a new geometry.
   */
  void setGeometry(int size, const float *x) ;

  /**
   * Gets the mesh geometry. x must be used like a vector (i.e. x[n]).
   * [OIV-WRAPPER-ARG NO_WRAP,ARRAY{size}]
   */
  void getGeometry(int &size, const float* &x) const ;

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
  void destroy() ;
  void copy(const PbIrregularMesh1D &other_mesh) ;

  float   *m_x ;
} ;
/*---------------------------------------------------------------------------*/

#endif /* _PB_IRREGULAR_MESH1D_ */

