/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : JM Godinaud (May 2006)
**=======================================================================*/

#ifndef _SOMESHSHAPE_H
#define _SOMESHSHAPE_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/SoLDMTileID.h>
#include <LDM/SoLDMNodeFrontManager.h>
#include <LDM/nodes/SoLdmShape.h>

#include <Inventor/nodes/SoShape.h>
#include <Inventor/SbBox.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBox3f.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/sys/SoGLType.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>
#include <Inventor/STL/string>

class SoDataSet;
class SoMeshGeometry;
class SoMeshProperty;
class SoGLRenderAction;
class SoTransferFunction;
class SoLDMMeshTile;
class SoGLVolCacheList;
class SoPrimitiveVertex;
class SoRayPickAction;
class SoPickedPoint;
class SoFieldSensor;
class SoGLVBOCache;
class SoSubSectionId;
class SoShaderProgram;
class SoMeshShader;
class SoToiTileLogicalSliceCache;

#define NUM_DATA_PER_CELL 24 // size of the cell geometry (24 float)
#define NUM_COORD_PER_VERTEX 3 // size of the vtx geometry (3 float)

/**
 * [OIV-WRAPPER NAME{LDMLevelReachedCB}]
 */
typedef void SoLDMLevelReachedCB(int level, int levelMax, void *userdata);


/**
 * @RVEXT Cell filter functor interface.
 *
 * @ingroup ReservoirVizNodes
 *
 * @DESCRIPTION
 *
 * This class can be derived to implement a cell filter at render time.
 * Cell filter functors can be used to do dynamic filtering of cells by data set values for instance.
 *
 * The operator()() should return true for accepted cells and false otherwise.
 *
 * The getTimeStamp() method must return a different value whenever the filter function changes in order
 * to trigger a rebuild of the shape and the touch method of the shape must be called to invalidate the
 * Open Inventor cache.
 *
 * @SEE_ALSO
 * SoMeshShape
 */
class SoCellFilterFctor {
public:
  /**
  * The operator() should return true for accepted cells and false otherwise.
  * @param (i,j,k) indices of the cell to be checked.
  */
  virtual bool operator() (size_t i, size_t j, size_t k) const = 0;

  /**
  * Returns a time stamp on this cell filter. When the content of the filter
  * changes, the time stamp must also change. The time stamp allows the shape
  * to be aware about any change to this filter.  It is sufficient to simply
  * increment an internal size_t value and return it.
  */
  virtual size_t getTimeStamp() const = 0;

  /** Destructor */
  virtual ~SoCellFilterFctor() {};
};

/**
 * Internal class used to compare tiles in a storage map.
 * [OIV-WRAPPER-NO-WRAP]
 */
class compLDMTileID
{
public:
  bool operator() (const SoLDMTileID& lhs, const SoLDMTileID& rhs) const
  {
    if(lhs.getID()<rhs.getID() /* && lhs.getTimeStep() < rhs.getTimeStep()*/)
      return true;
    else
      return false;
  }

};

/**
 * @RVEXT Abstract base class for all mesh representations in ReservoirViz.
 *
 * @ingroup ReservoirVizNodes
 *
 * @DESCRIPTION
 *   This class groups common fields used by all mesh representations in ReservoirViz.
 *
 * @SEE_ALSO
 *    SoMeshLogicalSlice,
 *    SoMeshPlaneSlice,
 *    SoMeshSkin
 *
 *
 */
class RESERVOIRVIZ_API SoMeshShape : public SoLdmShape
{
  SO_NODE_ABSTRACT_HEADER( SoMeshShape );

public:

  SoMeshShape();

  enum Interpolation {
    /**
      * Uses only one color per cell of the mesh. Default.
      */
    NEAREST,
    /**
     * Applies a linear interpolation at each pixel used
     * to draw a cell, resulting in a smooth coloring of the mesh.
     */
    LINEAR
  };

  /**
  * Specifies the interpolation type. Default is NEAREST.
  */
  SoSFEnum interpolation;

  /**
  * Hides or shows edges of cells. The edge color is specified by the #outlineColor field.
  * Default is FALSE.
  */
  SoSFBool outline;

  /**
  * Color of the cell edges. Only used if #outline field is TRUE. Default is 0,0,0.
  */
  SoSFColor outlineColor;

  /**
  * Maximum LDM resolution level used to draw the shape. This is an offset from the
  * best possible resolution.
  * No offset (i.e., maxResolution = 0) means the best possible resolution.
  * An offset of 1, (i.e., maxResolution = 1) means the second best possible
  * resolution, etc.
  * The field can be modified, for instance, while moving a slice on a very large
  * mesh. It should be reset to 0 when the slice is no longer being moved.
  *
  * Default value is 0.
  */
  SoSFUInt32 maxResolution;

  /**
   * Returns the current LDM resolution level if in slice
   * equal resolution mode. Otherwise, returns the minimum LDM resolution
   * level.
   */
  virtual int getCurrentResolution();

  /**
   * Returns the next time step resolution (minimum displayable resolution if not in
   * equal resolution).
   */
  virtual int getNextTimeStepResolution();

  /**
  * Called each time the next time step reaches a new level in slice equal res mode.
  */
  void setNextTimeStepPrefetchedCB(SoLDMLevelReachedCB *func, void *userData);

  /**
  * Called each time a new level is reached in slice equal res mode.
  */
  void setLevelReachedCB(SoLDMLevelReachedCB *func, void *userData);

  /**
  * Set Cell Filter functor. @BR
  * The Cell Filter functor will be called for each cell and should return true for accepted cells
  * and false otherwise.
  * Cell Filter functors can be used to do dynamic filtering of cells by data set values for instance.
  * The application must derive a new class from SoCellFilterFctor and implement operator().
  * @M_SINCE 8.0
  */
  virtual void setCellFilterFctor(const SoCellFilterFctor& cellFilterFctor);

  /**
  * Returns the current Cell Filter functor. Returns NULL if not set.
  * @M_SINCE 8.0
  */
  const SoCellFilterFctor* getCellFilterFctor() const;

SoEXTENDER public:
  void GLRender(SoGLRenderAction *action);
  virtual void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /** gets the distance of this shape to the tile divided by the tile "size"
   * [OIV-WRAPPER VISIBILITY{PublicProtected}]
   */
  virtual float getRelativeDistanceToTile(SbBox3i32& tileBox, SbBox3f &tileGeomPos)=0;

  SoMeshProperty *getPropertyData(int index) const {
    return (SoMeshProperty *)m_propData[index];
  }
  int getNumPropertyData() const {
    return (int)m_propData.size();
  }

  //Call m_levelReachedCB each time the next time step reach
  //a new resolution level
  void notifyNextStepLevelChange(int nextStepLevel, int currentLevel, int minRes);

  static SbBox3i32 intersection(SbBox3i32 &b1, SbBox3i32 &b2);
  static SbBox3i32 getSubTileBox(SoMeshGeometry *meshData, SbVec3i32 &tile_size, SbBox3i32& tp, SbBox3i32& section_box, float ratios[6]);

  virtual bool isDead(size_t i, size_t j, size_t k);
  virtual bool hasDeadCellsOrCellFilter();

protected:
  virtual void ldmAction(SoLdmValuationAction* action);
  virtual ~SoMeshShape();

  virtual SoShaderProgram* getShaderProgram(SoState* state);
  virtual void pushDefaultShaderProgram(SoGLRenderAction* glRenderAction);
  virtual void popDefaultShaderProgram(SoState* state);
  virtual SbString getDefaultShaderName()=0;

  //Set an usefull culling mode when a shapehints is in the state
  void setupGLCulling(SoState *state);

  //Do GL or primitive rendering
  virtual void doRendering(SoAction *action, SbBool genPrimitive = FALSE);
  void generatePrimitives(SoAction *action);

  void drawGenPrimitive(float num_cell_on_j, float num_cell_on_k,
                        int startOffset, SbVec3i32 tileIJKPos,
                        int axisJ, int axisK,
		                    int j_offset, int k_offset, int level,
		                    SoAction *action);

  void drawVBOGL(float du, float dv,
	      	       int num_cell_on_j, int num_cell_on_k);

  virtual int getNextLoadedStepLevel() = 0;

  void drawElement(int i, int j, int num_cell_on_i);

  void computeZAxisAndZSection(const SbBox3i32 &sectionBox,int Zside, int& Zaxis,int & Zsection, unsigned char& faces_to_draw,int &sliceNumber);
  void checkCacheValidity(SoState *state, SoLDMNodeFrontManager* nfm, SoLDMTextureManager* tm, const SbBox3i32 &sectionBox,int Zaxis,int Zsection,SoSubSectionId* sectionId, SbBool& cacheIsNotValid, SbBool& geomCacheIsNotValid);
  void updateListOfTileToLoad(SoSubSectionId* sectionId,SoState *state, SoLDMTextureManager* tm, bool geomCacheValid);
  void getTileDimensions();

  //Rendering with VBO
  SoGLVBOCache *m_vbo;
  static bool init;

  //Debug variable, if false don't load geometry when changing slice
  SbBool m_recreateVBO;

  //Avoid to recreate incides and uv for each tiles
  std::vector<SoGLVBOCache *> m_cachedIndices;
  std::vector<SoGLVBOCache *> m_cachedUV;

  SoGLVBOCache *getVBOIdx(int num_cell_on_i, int num_cell_on_j);
  SoGLVBOCache *getVBOUV(int num_cell_on_i, int num_cell_on_j);
  void generateVBOUV(float du, float dv,
                     int num_cell_on_i, int num_cell_on_j);
  GLenum m_glDrawMode;

  bool isCulled(SoLDMTileID tile, SoState* state);

  enum Plane {
    X = 0, Y, Z
  };

  void getCurrentMeshAndPropertyData(SoState *state);

  virtual void GLRenderLDM(SoGLRenderAction *action);

  void drawSubTile(SoState *state, SoLDMTileID tile, SoLDMMeshTile* mt, SbBox3i32& volume_box, unsigned char faces_to_draw,
                   SbBool genPrimitive = FALSE, SbBool line_style=FALSE);
  void drawUnshrinkedSubTile(SoState *state, SoLDMTileID& tile, SoLDMMeshTile* tex_tile, int Zaxis, int Zsection, int Zside, int sliceNumber,
                   SbVec3i32& tileIJKPos,SbBox3i32& sectionBox,SbBool genPrimitive = FALSE, SbBool line_style=FALSE);
  void getProperties(SoLDMTileID& dataTile);

  void drawSubTileFace(SoState *state, SoLDMMeshTile* tex_tile, float iMin, float jMin, float kMin,
    int sliceNumber,
    int num_cell_on_i, int num_cell_on_j,
    float ck,
    float ci0, float ciN, float cj0, float cjN,
    int face_node[4], int face_node2[4],
    int i_goffset, int j_goffset, int k_goffset, // geometric offset
    int i_doffset, int j_doffset, int k_doffset, // data offset
    Plane facePlane, const SbVec3i32 &tileIJKPos, int level,
    SbBool genPrimitive, SbBool lineStyle, SoAction *action,int resolution);


  void sendFaceCoord(float iMin, float jMin, float kMin,
                     int num_cell_on_j, int num_cell_on_k,
                     int j_offset, int k_offset, Plane facePlane,
                     const SbVec3i32 &tileIJKPos, int level,
                     SbBool genPrimitive, SoAction *action);

  SbVec2f getTexCoordTranslation(float iMin, float jMin, float kMin, Plane facePlane);

  void drawTileCells(int num_cells);

  void getFaceCoordOfTileOfVertex(float iMin, float jMin, float kMin,
                         int32_t num_i, int num_j,
                         float ck,
                         float ci0, float ciN, float cj0, float cjN,
                         int i_offset, int j_offset, int k_offset,
                         std::vector<SbVec3f> &face_coord) const;

  // get a pointer to the cell coordinates array
  const float* getCellCoord(int i, int j, int k) const {
    return m_tileGeometry + NUM_DATA_PER_CELL*(k*(m_tileSizeI*m_tileSizeJ) + j*m_tileSizeI +i);
  }

  // get a pointer to the node coordinates array
  const float* getNodeCoord(int i, int j, int k) const {
    return m_tileGeometry + NUM_COORD_PER_VERTEX*(k*((m_tileSizeI+1)*(m_tileSizeJ+1)) + j*(m_tileSizeI+1) +i);
  }

  // get a pointer to the cell property array
  const float* getCellProperty(int numProp, int i, int j, int k) const {
    return m_tileProperties[numProp] + (k*(m_tileSizeI*m_tileSizeJ) + j*m_tileSizeJ +i);
  }

  virtual SoDetail *createTriangleDetail(SoRayPickAction *action,
                                         const SoPrimitiveVertex *v1,
                                         const SoPrimitiveVertex *v2,
                                         const SoPrimitiveVertex *v3,
                                         SoPickedPoint *pp);

  void bindTexture2D(SoState *state, SoLDMMeshTile* tex_tile, int axis, int slice_number);
  void bindTexture3D(SoState *state, SoLDMMeshTile* tex_tile);

  void renderSection(SoAction *action, SbBool genPrimitive, int Zaxis, int Zsection, int Zwidth, int Zside,
                     SoSubSectionId* sectionId);

  void renderSubSection(SoAction *action, SbBool genPrimitive, SbBox3i32 &rsbox,
                        int Zside, SoSubSectionId* sectionId);


  virtual bool isCacheValid(SoState* state);
  virtual void invalidateCache();
  virtual void addElementsToCache(SoState* state, SoCache* cache) const;


  // temp variable containing the last sub section drawn
  mutable SoSubSectionId*           m_sectionId;

  mutable SoMeshGeometry*               m_meshData;
  mutable std::vector<SoDataSet *>  m_propData;
  mutable std::vector<SbVec3f>      m_faceCoord;
  mutable std::vector<SbVec3f>      m_faceCoordSaved;
  mutable std::vector<float>        m_faceProperty;
  mutable float*                    m_tileGeometry;
  mutable std::vector<float*>       m_tileProperties;
  mutable int                       m_tileSizeI;
  mutable int                       m_tileSizeJ;
  mutable int                       m_tileSizeK;


  static  int sm_faceImin[4]; // node ids of the cell face on i = imin
  static  int sm_faceImax[4]; // node ids of the cell face on i = imax
  static  int sm_faceJmin[4]; // node ids of the cell face on j = jmin
  static  int sm_faceJmax[4]; // node ids of the cell face on j = jmax
  static  int sm_faceKmin[4]; // node ids of the cell face on k = kmin
  static  int sm_faceKmax[4]; // node ids of the cell face on k = kmax

  SoFieldSensor *m_interpolationSensor;
  static void invalidateCacheCB(void * instance, SoSensor *);

  SbBox3f m_cachedBBox;
  //Used to distribute the master bbox to all oiru
  SoSFBox3f m_oiruBBox;

  int m_currentResolution;
  short m_curTimeStep;
  short m_curTimeStepInc;
  int m_previousNextStepLevel;
  bool hasTimeStepChanged(SoState *state);

  SoLDMLevelReachedCB *m_levelReachedCB;
  void *m_levelReachedUserData;

  SoLDMLevelReachedCB *m_nextStepLevelReachedCB;
  void *m_nextStepLevelReachedUserData;

  SoMeshShader* m_defaultShader;

  bool m_hasDeadCells;

  // List of caches for cells with faults
  std::map<SoLDMTileID,SoToiTileLogicalSliceCache*,compLDMTileID> m_toiTiles;

  SoCache* m_cache;

  const SoCellFilterFctor* m_cellFilterFctor;
};


inline void
SoMeshShape::doRendering(SoAction *, SbBool)
{}


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SOMESHSHAPE_H
