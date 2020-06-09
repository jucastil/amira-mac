/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESH3D_
#define  _PO_MESH3D_

#include <Inventor/fields/SoSFShort.h>
#include <Inventor/nodes/SoIndexedLineSet.h>

#include <MeshViz/3Ddata/PoMesh.h>
#include <MeshViz/3Ddata/PbCell.h> // to define SbBoolVector

class SoMFVec3f;

class PiMeshSkin;
class PbMesh3D;
class PbParalCartesianGrid3D;
class PbRegularCartesianGrid3D;
class PbIndexedMesh3D;
class PbTetrahedronMesh3D;
class PbHexahedronMesh3D;
class PbGrid3D;
class SoNormal;

/**
 * @DTEXT  Base class for all volume mesh representations.
 * 
 * @ingroup MeshRepresentation
 * 
 * @DESCRIPTION
 * 
 */
class MESHVIZ_API PoMesh3D : public PoMesh {

  SO_KIT_HEADER(PoMesh3D) ;


 public:



  /**
   * Defines the current volume mesh. See PoMesh for explanation about the current mesh.
   */
  void setMesh(PbMesh3D *mesh);

  /**
   * Gets the current volume mesh.
   */
  const PbMesh3D * getMesh() const;

  /*----------------------------------------------------------------------------*/
 PoINTERNAL public:
  static void initClass() ;
	static void exitClass() ;

  void indexedMeshLevelSurfShapeIndices(PbIndexedMesh3D *mesh, int surfOrientation=1, 
                                        const float *per_cell_value=NULL);
  void tetrahedronMeshLevelSurfShapeIndices(PbTetrahedronMesh3D *mesh, int surfOrientation=1, 
                                            const float *per_cell_value=NULL) ;
  void hexahedronMeshLevelSurfShapeIndices(PbHexahedronMesh3D *mesh, int surfOrientation=1, 
                                           const float *percell_value=NULL) ;
  virtual void addOptQuadrangle(int num_quad, int *quad_nodes, int cell_index);

  virtual const float *getIsosurfDataSet() { return NULL; }
  virtual float getIsosurfValue() const { return 0; }
  virtual int getSurfOrientation() { return 1; }

  int addSurfPoint (int nod_ind1, int nod_ind2, int32_t &point_index);
  void computeCrossPointCoord(int index, const float *x, const float *y, const float *z, const float *v, 
                              int n0, int n1, float d0, float d1);

  /**
   * Gets the number of bytes allocated by this instance
   */
  virtual size_t getMemorySize();
  size_t getHashTableMemorySize();

  /**
   * Gets the number of cells touched by the level surface or cross section.
   */
  int getNumIsoCells() {
    return m_numIsoCells;
  }
  
  void newIsoCell() {
    m_numIsoCells++;
  }
  void clearIsoCells() {
    m_numIsoCells = 0;
  }

 protected:
  PoMesh3D() ;
  // Constructor

  virtual ~PoMesh3D() ;  
  // Destructor

  virtual void basicObjectChange(PbBase *basicObj);
  virtual void preRebuild();

  void crossPlaneAndQuadrangle(const float *x, const float *y, const float *z, const float *v, 
                               const int32_t *quad_nodes, const int32_t *quad_ind, float xn,float yn,float zn, 
                               float dist_plane_orig, SbBool &intersect,int32_t *point_ind);
  void getParalCartGrid3DCrossContour(PbParalCartesianGrid3D *mesh, const float *nod_values, 
                                      float xn, float yn, float zn, float dist_to_origin, 
                                      SoIndexedLineSet *indexed_line_set, SoCoordinate3 *coordinate);
  void getRegularGrid3DCrossContour(PbRegularCartesianGrid3D *mesh, const float *nod_values, 
                                    float xn, float yn, float zn, float dist_to_origin, 
                                    SoIndexedLineSet *indexed_line_set, SoCoordinate3 *coordinate);

  virtual void initOptQuadrangleList();
  virtual void addLevelSurfOptQuadrangle();


  void makeCrossContour(float dist_to_origin, float xn, float yn, float zn, 
                        const float *x, const float *y, const float *z, const float *nod_values,
                        SoGroup *local_group);
  void initSurfPointList();


  void updateSurfaceShapeBindings(SbBool strip_set_used=FALSE);

  void meshLevelSurf(const PbMesh3D *mesh);

  void updateLevelSurfTopology(const float *values, float &isovalue);
  void updateLevelSurfCoord(const float *values, float isovalue);
  void updateLevelSurfColors(const float *values, float isovalue);
  void updateLevelSurfTextures();
  void updateLevelSurfContouring();
  void updateLevelSurfPointValues(std::vector< float > &point_values);
  
  virtual int getIsosurfDataSetId() const { return -1; }
  virtual int getIsosurfDataSetIndex() const { return -1; }
  virtual SbVec3f getOverallNormal() const { return SbVec3f(0,0,0); } 

  const PbMesh3D *m_mesh3D; // mesh used by all derived Po classes

  mutable PiMeshSkin *m_skin; // reference to the skin contained in the cache of skin

  SbBool m_useStripSet;

  mutable int m_numIsoCells; // number of cells touched by the isosurface
  /*----------------------------------------------------------------------------*/

 private:
   SbBoolVector *m_nodeSign; // m_nodeSign[i] is true if the value at i-th node is > isovalue

  PbMesh3D *m_mesh3DSet;  // mesh set by the setMesh method
  void checkOrientation(SoMFVec3f *coords, SoMFInt32 *coordIndex, SbVec3f *normal);

  typedef struct {
    int      index;
    int      alloc_indirect;
    int      num_indirect;
    int      *indirect_index;
  } Tdirect;
  
  typedef struct {
    int n1,n2;  // node id of this edge
    float r;    // ratio used for interpolation of value or color
  } Tedge_interpol;
  
  Tedge_interpol *TTabEdgeInterpol;
  int           TAllocEdgeInterpol;
  int           TNumEdgeInterpol;
  
  int     TAllocTabDirect;
  Tdirect *TabDirect;

} ;

/*----------------------------------------------------------------------------*/

#endif /* _PO_MESH3D_ */

