/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PB_MESH3D_
#define  _PB_MESH3D_

#include <MeshViz/3Ddata/PbMesh.h>

class PoMeshSkin;
class PoMeshCrossSection;
class PoMeshCrossContour;
class PoMeshSkeleton;
class PoMesh3D;
class PoMesh3DVec;
class PiCellOctree;
class PoCellFilter;
class PiMeshSkinCache;
class PiMeshSkin;

/**
 * @DTEXT  Defines an abstract volume mesh.
 * 
 * @ingroup MeshProperty
 * 
 * @DESCRIPTION
 *   A volume mesh is made of polyhedral cells, that define a 3D volume.
 *   The topology of this mesh is either regular (see derived class
 *   PbGrid3D) or irregular (see derived class PbIndexedMesh3D).
 * 
 */
class MESHVIZ_API PbMesh3D : public PbMesh {

 public:

  /**
   * Gets the volume of the mesh.
   */
  virtual float getVolume() const;

  /**
   * Returns always 0.
   */
  virtual float getArea() const
    { return 0.0;}

 SoEXTENDER public:

  PbMesh3D(SbBool is_data_duplicate=TRUE);
  PbMesh3D(const PbMesh3D &mesh);
  virtual ~PbMesh3D();

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:

  // Assignment operator.
  PbMesh3D &operator=(const PbMesh3D &mesh);

  virtual void meshSkin(PoMeshSkin *_PoMeshSkin) const;
  virtual void meshLevelSurfShapeIndices(PoMesh3D *_PoMesh3D, int surfOrientation=1, 
                                         const float *per_cell_value=NULL) const;
  virtual void meshCrossSection(PoMeshCrossSection *_PoMeshCrossSection) const;
  virtual void meshCrossContour(PoMeshCrossContour *_PoMeshCrossContour) const;
  virtual void meshSkeleton(PoMeshSkeleton *skeleton, const float *nod_values, 
                            float *x_cont, float *y_cont,float *z_cont) const; 
  virtual void mesh3DVec(PoMesh3DVec *_PoMesh3DVec) const;

  virtual SbBool isCrossSectionOptimal() const;

  void print(FILE *fp) const;
  void printInfo() const {print(stdout);};

  /** 
   * Get an approximation of the number of faces on the skin.
   * It returns the exact number for grid mesh, otherwise
   * something generally greater than the real number.
   */
  virtual int evaluateSkinFacesNum() const;

  PiMeshSkin* getSkinTopology(const PoCellFilter*, int valuesIdFilter, uint32_t &wasUpToDate) const;

 protected:

  const PbCell *findContainingCellProtected(const SbVec3f &point, 
                                            float tolerance, 
                                            SbVec3f &pcoord, 
                                            PbArrayOfInt &test_cell) const;

  mutable SbBool         m_skinIsUpdated;
  mutable PiCellOctree   *m_cellOctree;
  mutable SbBool         m_cellOctreeIsUpdated;

 private:

  void copy(const PbMesh3D &mesh);
  void destroy();
  mutable PiMeshSkinCache* m_skinTopologyCache;
};

/*---------------------------------------------------------------------------*/

#endif /* _PB_MESH3D_ */

