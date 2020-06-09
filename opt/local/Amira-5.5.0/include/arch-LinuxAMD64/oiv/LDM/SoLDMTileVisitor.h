/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_TILE_VISITOR_
#define  _SO_LDM_TILE_VISITOR_

#include <LDM/SoLDMLargeDataManagement.h>

#include <LDM/SoLDMTileID.h>
#include <Inventor/STL/vector>
#include <Inventor/SbBox.h>
#include <Inventor/SbViewVolume.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoSeparator;
class SoState;
class SoLDMGeomElement;
/**
 *
 * @LDMEXT Tile Visitor
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * This class is only needed for advanced users who intend to extend or replace
 * internal LDM algorithms.
 *
 * The SoLDMTileVisitor allows the user to define a strategy to evaluate what part of
 * the data set is the most important based on viewpoint and geometries. It is responsible
 * for assessing the importance of tiles. This information is used by the node front manager
 * (SoLDMNodeFrontManager)
 * as a predictor to optimally fill the texture memory. When the node front manager evaluates
 * texture node front, it asks the SoLDMTileVisitor for the weight of each tile by calling the
 * #getTileWeight function. The SoLDMTileVisitor queries the SoLDMTileManager to find out
 * if the tile is present in main memory. If not, a null weight is returned to ensure the
 * data of all requested textures are in main memory. The SoLDMTileVisitor also queries
 * the SoLDMGeometry node to access geometric information related to the zone of the tile
 * to be weighted.
 *
 * @SEE_ALSO
 * SoLDMNodeFrontManager,
 * SoLDMTileManager,
 * SoLDMGeometry,
 * SoLDMResourceManager
 *
 *
 */

SoEXTENDER_Documented class LDM_API SoLDMTileVisitor : public SoLDMLargeDataManagement {
 public:

  /**
   * Constructor.
   */
   SoLDMTileVisitor();

  /**
   * Destructor.
   */
  ~SoLDMTileVisitor();

  /**
   * Information structure for the tile to evaluate.
   * This structure is returned to the SoLDMNodeFrontManager
   * so it knows whether the tile is
   * visible, in an ROI, or in a subvolume.
   */
  struct NodeStatus
  {
    /**
     * Is the tile visible.
     */
    bool m_visible;
    /**
     * Is the tile inside the ROI (if any).
     */
    bool m_inROI;
    /**
     * Is the tile inside the subvolume (if any).
     */
    bool m_inSubVolume;
  };
  /**
   * Method in charge of evaluating the weight of the tile @B tileID@b
   * according to the SoLDMGeometry node.
   * The returned value is the weight assigned to the tile.
   * This default method may be overridden.
   */
  virtual float getTileWeight( SoLDMTileID tileID, NodeStatus& status);

  /** TODO: doc with graph (default behavior graph) */

  /**
   * Is the tile culled. Takes effect only if SoVolumeRendering::m_viewCulling is TRUE.
   * Returns distance to screen center in screen coordinates if the tile is culled.
   */
  bool isCulled(const SbBox3f& tileBox, float& distToScreenCenter, int cullbits = 7);

  /**
   * Assigns a weight based on distance to the center of the screen.
   * May be overridden by the application.
   * distToScreen is the signed distance from the tile considered to the
   * center of the screen in normalized screen coordinate.
   * This functions is called only if the tile is culled.
   * The returned weight must be between 0 and 1.
   * Default returns 0 always.
   */
  virtual float getCullWeight(float distToScreen);

  /**
   * Assigns a weight based on voxel size in pixel.
   * May be overridden by the application.
   * voxelsize parameter is the size of the biggest voxel dimension for a given tile in pixel.
   * The returned weight must be between 0 and 1.
   * Called only if screen resolution culling is enabled (see SoVolumeRendering, true by default).
   */
  virtual float getScreenResCullWeight(float voxelsize);

  /**
   * Assigns a weight based on distance to a surface geometry.
   * May be overridden by the application.
   * distToGeom is the signed distance from the surface to the considered
   * tile in data coordinates.
   * < 0 means the tile is behind or outside the geometry.
   * > 0 means the tile is in front of or inside the geometry.
   * = 0 means the tile intersects the geometry.
   * (the normal of a geometry plane is oriented towards increasing data (from voxel 0 to 1))
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns geometryPriority if the distance is null, else 0.
   */
  virtual float getSurfaceGeomWeight(float distToGeom, float geometryPriority);

  /**
   * Assigns a weight based on distance to a data set geometry.
   * May be overridden by the application.
   * distToGeom is the signed distance from the data set to the considered
   * tile in data coordinates.
   * < 0 means the tile is outside the data set.
   * > 0 means the tile is inside the data set.
   * = 0 means the tile intersects the data set.
   * (the normal of a geometry plane is oriented towards increasing data (from voxel 0 to 1))
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns geometryPriority if the distance is null, else 0.
   */
  virtual float getVolumeGeomWeight(float distToGeom, float geometryPriority);

  /**
   * Assigns a weight based on distance to ROI.
   * May be overridden by the application.
   * distToROI is the signed distance from the geometry ROI to a tile in data coordinates.
   * < 0 means the tile is outside the ROI.
   * > 0 means the tile is inside the ROI.
   * = 0 means the tile intersects the ROI.
   * The geometryPriority argument is the weight of the geometry considered.
   * The returned weight must be between 0 and 1.
   * Default returns 1 if the distance is >= 0, else 0.
   */
  virtual float getROIWeight(int distToROI, float geometryPriority);

  /**
   * This function combines the current tile weight with its parent.
   * The returned weight must be less than parentWeight.
   * Default multiplies weights.
   */
  virtual float combineParentWeight(float parentWeight, float weight);

  //TODO: virtual getVPWeight.

  /**
   * Reset notification (the data has changed).
   */
  virtual void reset();

  /**
   * Returns the model view projection matrix to assign a weight
   * based on the viewpoint.
   * [OIV-WRAPPER-RETURN-TYPE VALUE]
   */
  const SbMatrix* getMVPMatrixPtr()
  {
    const MatrixVec& matVec = m_ModelViewProjMatMap.begin()->second;
    return &matVec[0];
  }

  /**
   * Notify of a change of evaluator (change visitor type).
   */
  void valuationChangeNotify();

  //------------------------------------------------------------------------------
 SoINTERNAL public:

  static void initClass();

  bool isTransparent(SoLDMGeomElement*, SoLDMTileID);

  std::vector<SoLDMTileID> m_tileIDs;
  std::vector<SoLDMTileID>& getLastValuated(){return m_tileIDs;};

  /*
   * Called by the NodeFrontManager
   * There is different cases where the returned weight could be null:
   * - there is geometry in the tile but the tile is not yet loaded.
   *   In this case, the tile is scheduled to be loaded.
   * - there is no geometry in the tile.
   * - the tile is outside the view frustum or ROI.
   * The returned boolean tells the node front weather or not the tile has been scheduled
   * to be loaded
   */
  SbBool getTileWeight( SoLDMTileID tileID,
                        float parentWeight,
                        float& weight,
                        int subsampleLevel,
                        NodeStatus& status,
                        SbBool scheduleLoad=TRUE);

  SbVec3f getGeomCenter(const SoLDMTileID& tileID);
  SbBox3f getGeomPos(const SoLDMTileID& tileID);

  //set MVP and cullbits ptr
  void setMVPMatrixPtr(SoState* state, const SbMatrix* MVP, const SbMatrix* Model);

  //set screen size in pixel
  void setScreenPixelSizeAndView(SoState* state);

  //These three bits keep track of which view-volume planes we need
  //to test against. This function resets all bits at 1.
  void resetCullBits();

  /**
   * Setup all needed constant for traversal
   */
  void init();

  /**
   * Remove matrix belonging to unusued context
   */
  void clearContextCache(SoState* state);

protected:
  typedef std::vector<SbMatrix> MatrixVec;
  typedef std::map<int, MatrixVec> CtxMatrixVecMap;
  typedef std::map<int, SbMatrix> CtxMatrixMap;
  typedef std::map<int, SbViewVolume> CtxViewVolMap;

  SbBox3f m_prevVolExtent;
  SbVec3i32 m_prevVolDim;
  float     m_xFactor,m_yFactor,m_zFactor;
  float     getScreenDistance(SbVec3f& A);
  SbVec3f   getProjectedPoint(const SbMatrix& mvp, const SbVec3f& point) const;
  CtxMatrixVecMap  m_ModelViewProjMatMap;
  SbMatrix  m_ModelMat;
  int       m_distanceMax;

  float     getViewPointWeight(const SbBox3f&);

  int       m_screenWidthPixel;
  int       m_screenHeightPixel;
  CtxViewVolMap m_viewVolumeMap;
private :
  /** Remove all unusued context from specified map */
  template<typename MapCont> void removeUnusuedContext(MapCont& m);

  /** Clear mvp matrix list for the given context */
  void clearMatrixList(int ctx);

  /** Compute voxel size for each matrices */
  float getVoxelPixelSize(const MatrixVec& matVec,
                          const SbViewVolume& viewVol,
                          const SbBox3f& geomBox,
                          unsigned int numVoxels, float lmax);

  /** Compute culling state for each matrices */
  bool isCulled(const MatrixVec& matVec, const SbBox3f& tileBox,
                float& distToScreenCenter);
  /**
   * Return weight according to viewpoint
   */
  float getViewPointWeight(const SbBox3f& box, const SbViewVolume& viewVol);

  /**
   * Used during octree traversal.
   * Same thing as getTileWeight but avoid to call getTile/GeomPos
   * for each nodes
   */
  float getTileWeightInternal( SoLDMTileID tileID,
                               SoLDMTileVisitor::NodeStatus& status);

  /** Init some factors used during traversal */
  void initFactor();

  /** Compute viewpoint weight with Oiv8 method */
  float getViewPointWeightOiv8(const SbBox3f& box, const SbViewVolume& viewVol);

  /** Compute viewpoint weight with Oiv6 method */
  float getViewPointWeightOiv6(const SbBox3f& box, const SbViewVolume& viewVol);

  //allows to Keep track of what planes we need to test culling against.(1 bit per axe)
  int       m_cullBits;
  SbVec3i32 m_eye;

  /**
   * Return pixel size of the given worldspace bbox
   */
  float getVoxelPixelSize(const SbBox3f& geomBox);

  /**
   * Return pixel size of the given screen space bbox
   */
  float getVoxelPixelSize(const SbBox3f& screenBbox, unsigned int numVoxels);

  bool m_handleTransparentTiles;
  int m_numStepsToPrefetch;

  /**
   * List of all geometries in the scenegraph
   */
  SbPList m_geomList;
  size_t m_numGeoms;

  /**
   * Minimum geometry weight of a tile intersecting
   * the geometry. Each entry map to an entry of m_geomList
   */
  std::vector<float> m_minIntersecintWeights;

  /**
   * Bounding box in data and world space of the
   * tile being weighted
   */
  SbBox3i32 m_curTileBboxIjk;
  SbBox3f m_curTileBboxXyz;
  SbBox3f m_rootBboxXyz;
  SbBox3f m_rootBboxXyzModelSpace;

  /**
   * Result of m_viewVolume.getMatrix()
   */
  CtxMatrixMap m_affineProjMatMap;

  /**
   * Fill m_affineProjMatMap
   */
  void getViewVolMatrix(const CtxViewVolMap::value_type v);

  /** Force Oiv6 weighting method */
  static SbBool s_useOiv6Weight;
  static int s_numStepsToPrefetch;

  static const float s_epsilon;
};
//--------------------------------------------------------------------------------

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_LDM_TILE_VISITOR_
