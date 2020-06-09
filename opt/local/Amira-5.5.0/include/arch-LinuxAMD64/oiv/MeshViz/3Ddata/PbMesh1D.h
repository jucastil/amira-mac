/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_MESH1D_
#define  _PB_MESH1D_

#include <MeshViz/3Ddata/PbMesh.h>

class PoChart ;
class SoMaterial ;
class SoState ;

/**
 * @DTEXT  Defines an abstract mono-dimensional mesh.
 * 
 * @ingroup GraphProperty
 * 
 * @DESCRIPTION
 *   A mono-dimentional mesh is made of points cells.
 * 
 */
class MESHVIZ_API PbMesh1D : public PbMesh {


 public:

  /**
   * Returns always 0.
   */
  virtual float getVolume() const { return 0.0;}

  /**
   * Returns always 0.
   */
  virtual float getArea() const { return 0.0 ;}

  /**
   * Returns always NULL.
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord, const PbCell *adjacent_cell) const;

  /**
   * Returns always NULL.
   */
  virtual const PbCell* findContainingCell(const SbVec3f &point, float tolerance, SbVec3f &pcoord) const;

  /**
   * Returns always NULL.
   */
  virtual const PbCell *getCell(int cell_index) const;

  virtual void getAdjacentCellsIndByNode(int cell_index, PbArrayOfInt &adjacent_cells) const;

  virtual void getAdjacentCellsIndByFacet(int cell_index, PbArrayOfInt &adjacent_cells) const;

  virtual void getNodeOwnerCellsInd(int nod_index, PbArrayOfInt &owner_cells) const;

  /**
   * Returns always an empty list of index.  
   */
  virtual void getNodesOwnerCellsInd(const PbArrayOfInt &nod_indices, PbArrayOfInt &owner_cells) const;

  /**
   * Assignment operator.
   */
  PbMesh1D& operator=(const PbMesh1D &mesh) ;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  virtual void print(FILE *fp) const;
  
  // Retrieves the geometry of the mesh1D
  // A color is retrieved for each vertex of the geometry.
  // The indices of the source points (if the curve is smoothed for
  // instance) can be retreived.
  virtual void getXYGeometry(const PoChart *chartRep,
                             const SoState *state,
                             int &size,
                             float* &x,
                             float* &y,
                             SoMaterial* &matPerVertex,
                             SbBool isIndexSourceNeeded,
                             int*   &indexSource) const;

  // Retrieves the filtered (according to the current mesh 1D filter)
  // geometry of the mesh1D.
  // A color is retrieved for each vertex of the geometry.
  // For filters which need an interpolation (PoPeriodFilter/PoCoordinateListFilter)
  virtual void getFilteredXYGeometry(const PoChart *chartRep,
                                     const SoState *state,
                                     int &size,
                                     float* &x,
                                     float* &y,
                                     SoMaterial* &matPerVertex) const ;
  
  virtual void getFilteredXYGeometry(const PoChart *chartRep,
                                     const SoState *state,
                                     int &size,
                                     float* &x,
                                     float* &y,
                                     SoMaterial* &matPerVertex,
                                     float *&vset1) const ;
  
  virtual void getFilteredXYGeometry(const PoChart *chartRep,
                                     const SoState *state,
                                     int &size,
                                     float* &x,
                                     float* &y,
                                     SoMaterial* &matPerVertex,
                                     float *&vset1,
                                     float *&vset2) const ;
  
  // Retrieves the geometry of the mesh1D adding points corresponding
  // to the intersection between the geometry and a vertical or horizontal
  // threshold.
  // A color is retrieved for each vertex of the geometry.
  // The indices of the source points (if the curve is smoothed for
  // instance) can be retreived.
  void getGeometryInterThreshold(const PoChart *chartRep,
                                 const SoState *state,
                                 SbBool isVertOrient, float threshold,
                                 int &sizeTmp, float* &xTmp, float* &yTmp, 
                                 SoMaterial* &matTmp, SbBool isIndexSourceNeeded, 
                                 int* &indexSource, int &numInters, int* &indexInters) const ;

  virtual float getXCoord(int nodeIndex) const=0 ;

 protected:
  PbMesh1D() ;
  // Constructor.

  PbMesh1D(const PbMesh1D &_mesh) ;
  // Contructor per copy.

  virtual void updateCellBoundingBox() const;
  virtual const PbCell* findContainingCellProtected(const SbVec3f &point, float tolerance, 
                                                    SbVec3f &pcoord, PbArrayOfInt &test_cell) const;

  int   m_size ;

 private:
  void copy(const PbMesh1D &other_mesh) ;

  static void setMaterialInterVertex(const float *x, const float *y, int startIndex,
                                     int num, SoMaterial *matPerVertex) ;
  
  static void setMaterialAtVertex(const SoMaterial *matSrc, const float *colValSet, 
                                  int srcIndex, int index, SoMaterial *matPerVertex) ;
  
  static void interpolateMaterial(SoMaterial *srcMat, int startIndexSrc, int endIndexSrc,
                                  float value, SoMaterial *dstMat, int indexDst) ;

  static SbBool isBBoxCurveThresholdInter(const SbBox2f &bboxCurve, SbBool isVertOrient,
                                          float threshold) ;
} ;

inline const PbCell* 
PbMesh1D::findContainingCell(const SbVec3f &, float , SbVec3f &, const PbCell *) const
{ return NULL ; }

inline const PbCell*
PbMesh1D::findContainingCell(const SbVec3f &, float , SbVec3f &) const
{ return NULL ; }

inline const PbCell *
PbMesh1D::getCell(int) const
{ return NULL ; }

inline const PbCell* 
PbMesh1D::findContainingCellProtected(const SbVec3f &, float, SbVec3f &, PbArrayOfInt &) const
{ return NULL ; }


/*---------------------------------------------------------------------------*/

#endif /* _PB_MESH1D_ */

