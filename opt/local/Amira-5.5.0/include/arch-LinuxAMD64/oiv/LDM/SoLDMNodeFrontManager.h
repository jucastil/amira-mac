/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (May 2003)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_NODE_FRONT_MGR__
#define  _SO_LDM_NODE_FRONT_MGR__

#include <LDM/SoLDMLargeDataManagement.h>
#include <LDM/SoLDMTileID.h>
#include <Inventor/STL/vector>
#include <Inventor/SbBox.h>
#include <Inventor/sensors/SoAlarmSensor.h>

class SoTimerSensor;
class SoLdmShape;
class SoShape;
class SbThreadMutex;

/**
 * @LDMEXT LDM Node Front Manager abstract base class.
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * This class is only needed for advanced users who intend to extend or replace
 * internal LDM algorithms.
 *
 * The SoLDMNodeFrontManager is in charge of maintaining a data structure representing
 * the multiresolution organization of the data stored on disk and the state of this
 * data in main memory for a specific frame (tiles loaded in main memory and their
 * importance and attributes for rendering).
 *
 * The set of tiles of higher weights in this data structure represent the best available
 * textures to fit in texture memory for the frame to render. This collection is the result of
 * the data structure evaluation.
 *
 * An evaluation of the structure is performed when LDM asks
 * (#getNextTexFront, #getNextSliceTexFront, #getOrderedDataFront) for an update of
 * the texture node front and if the SoLDMNodeFrontManager was previously notified
 * that something changed (#geomChangeNotify, #resourceChangeNotify, #movingChangeNotify)
 * e.g., some geometry has changed, some new tiles have been loaded, etc.
 *
 * The
 * SoLDMNodeFrontManager asks the SoLDMTileVisitor to compute the weight of each node.
 * Based on these weights, decisions are made to either refine (load tiles of higher resolution)
 * or collapse the multiresolution system (unload).
 * The SoLDMNodeFrontManager works under constraints given by the
 * SoLDMResourceManager (number of texture allowed in texture memory and texture load rate).
 *
 * If the user does not interact with the model, the quality of the rendering will increase
 * until it reaches an optimal state.
 * The asynchronous loading process continues loading until the weight of the next tile to load is
 * less than the weight of the next tile to unload meaning that the optimal collection of tiles
 * is present in main memory and in texture memory.
 *
 * @SEE_ALSO
 * SoLDMResourceManager, SoLDMTileManager
 *
 *
 */

SoEXTENDER_Documented class LDM_API SoLDMNodeFrontManager : public SoLDMLargeDataManagement
{

public:

  /**
   * Constructor.
   */
  SoLDMNodeFrontManager();

  /**
   * Destructor.
   */
  virtual ~SoLDMNodeFrontManager();

  //----------------------------------------------------------------------------------------
  // Topology-dependent methods :
  // All the following methods must be defined since they are dependent on the topology used.
  //----------------------------------------------------------------------------------------

  /**
   * Returns the total number of tile IDs used.@BR
   * @B m_numTileIDs@b must be initialized the first time getNextTexFront is called.
   * If the data set has x,y,z for dimension, then getNumTileIDs represents the number of
   * tiles in a cubic data set of dimension D, where
   *
   * D = nearest power of 2 greater than max(x,y,z)
   *
   * (This number varies depending on the topology used).
   * Used by the Texture Manager to initialize the array of texture information containing
   * texture ids,...
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  LDM_TILE_ID_TYPE getNumTileIDs();

  /**
   * Returns the total number of file IDs used ( < getNumTileIDs() ).@BR
   * @B m_numFileIDs@b must be initialized the first time getNextTexFront is called.
   *
   * If the data set has dimension x,y,z, then getNumTileIds represents the number of
   * tiles in a cubic data set of dimension D, where
   *
   * D = nearest greater power of 2 to max(x,y,z)
   *
   * (This number varies depending on the topology used).
   * A fileID represents the ID of a tile that is actually used and is 0
   * if the tile is outside of the
   * actual non cubic data set of dimension x,y,z.
   *
   * getNumFileIDs returns the number of non null fileIds and is used by the Tile Manager.
   * (It represents the maximum number of non-empty tiles that can be present in main memory.)
   */
  int getNumFileIDs();

  /**
   * Returns the file ID corresponding to the specified tile ID (ID of the tile in the file).
   * Returns 0 if the tile is outside of the real data set (i.e., no data is present in
   * the file for this tile).
   */
  virtual int getFileID( SoLDMTileID tileID ) = 0;

  /**
   * Returns the tile position in data coordinates of the specified tile ID.
   */
  virtual SbBox3i32 getTilePos( SoLDMTileID tileID ) = 0;

  /**
   * Returns how many different subsample levels of the data set the data stores.
   * The number returned is the power of 2 of the lowest resolution.
   */
  virtual int getMinResolution() = 0;
  /**
   * Given the position of a cell (i,j,k) and the resolution,
   * returns the tile ID of the corresponding tile.
   */
  virtual SoLDMTileID getTileID( const SbVec3i32& cellPos, int resolution = 0 ) = 0;

  /**
   * Given a @B tileID@b, returns the @B tileID@b  whose texture will be used for the
   * input @B tileID@b.
   * In other words, the @B tileID@b returned is in the texture front and may be the input
   * @B tileID@b
   * or its closest ancestor in the front.
   */
  virtual SoLDMTileID getTexTileID ( SoLDMTileID tileID ) = 0;


  /**
   * Same thing as #getTexTileID but for a 2d shape.
   */
  virtual SoLDMTileID getShape2dTexTileID ( SoLdmShape* shape, const SoLDMTileID& tileID );

  /**
   * Given a @B tileID@b, returns the @B tileID@b whose data will be used for the input
   * @B tileID@b.
   * In other words, the @B tileID@b returned is in the data front managed by the Tile Manager
   * and may be the input @B tileID@b or its closest ancestor in the front.
   */
   virtual SoLDMTileID getDataTileID ( SoLDMTileID tileID ) = 0;

  // -------------------------------------------------------------------------------------------
  // Data set tex front methods ------------------------------------------------------------------

   /**
   * Returns the list of tiles unloaded from texture memory and
   * the list of tiles loaded into texture memory by a previous getNextTexFront.
   * The texture front is not updated.
   */
  virtual void getTexFront(std::vector<SoLDMTileID>& toLoad, std::vector<SoLDMTileID>& toUnload) = 0;


  /**
   * Returns the list of tiles to unload from texture memory and
   * the list of tiles to load into texture memory.
   * If necessary, this method will update the texture front according to the
   * Resource Manager.
   * It is called by the Texture Manager.
   */
  virtual void getNextTexFront(std::vector<SoLDMTileID>& toLoad, std::vector<SoLDMTileID>& toUnload,
                               int maxRes = 0) = 0;

  /**
   * Same as #getNextTexFront but for 2d shapes.
   * @param hf The 2d shape rendering node
   * @param toLoad Contains texture tiles to load
   * @param toUnload Contains texture tiles to unload
   */
  virtual void getNextShape2dTexFront(SoLdmShape* hf,
                                      std::vector<SoLDMTileID>& toLoad,
                                      std::vector<SoLDMTileID>& toUnload);

  /**
   * Same as #getNextTexFront but for skin geometry.
   * Only tiles intersecting boxes will be loaded.
   * @param toLoad contains texture tiles to load
   * @param toUnload contains texture tiles to unload
   * @param boxes are the boxes which intersect the loaded tiles
   */
  virtual void getNextSkinTexFront(std::vector<SoLDMTileID>& toLoad,
                                   std::vector<SoLDMTileID>& toUnload,
                                   const std::vector<SbBox3i32>& boxes);
  /**
   * Returns the texture front tiles sorted according to distance from the
   * viewpoint in data coordinates. The number of tiles is returned also.
   * The tiles are returned in order, back to front.@BR
   * This method does not update the texture front. It is called after getTexFront() method
   * for rendering purposes only.
   */
  virtual void getOrderedTexFront(const SbVec3i32 &viewPoint, std::vector<SoLDMTileID>& orderedTexFront) = 0;

  /**
   * Same as #getOrderedTexFront but for skin geometry. Default implementation
   * just calls getOrderedTexFront
   */
  virtual void getOrderedSkinTexFront(const SbVec3i32 &viewPoint, std::vector<SoLDMTileID>& orderedTexFront);

  /**
   * Same as #getOrderedTexFront but for 2d shapes slice geometry. Default implementation
   * just calls getOrderedTexFront
   */
  virtual void getOrderedShape2dTexFront(SoLdmShape* shape,
                                         const SbVec3i32 &viewPoint, std::vector<SoLDMTileID>& orderedTexFront);

  /**
   * Returns the data front tiles sorted according to distance from the
   * viewpoint in data coordinates. The number of tiles is returned also.
   * The tiles are returned in order, back to front.@BR
   */
  virtual void getOrderedDataFront(const SbVec3i32 &viewPoint, std::vector<SoLDMTileID>& orderedDataFront) = 0;

  // -------------------------------------------------------------------------------------------
  // slices tex front methods ------------------------------------------------------------------

  /**
   * Returns the list of tiles intersecting the specified region.
   */
  virtual void getTiles(const SbBox3i32 &region, std::vector<SoLDMTileID> &tiles) = 0;

  /**
   * Given a resolution, returns the list of tiles intersecting the specified region.
   * Returns FALSE if the specified resolution is incorrect, i.e., if the resolution
   * specified is less than the lowest resolution of the data.
   */
  virtual bool getTiles(const SbBox3i32 &region, int resolution, std::vector<SoLDMTileID> &tiles) = 0;

  /**
   * This function must be called by a slice to notify the nodeFrontManager
   * that a new data structure
   * must be maintained for it. The returned value indicates whether the slice has already been
   * registered (TRUE) or not.
   */
  virtual bool registerSlice(int& id,SoShape*) = 0;
  /**
   * Notifies SoLDMNodeFrontManager that the slice of ID @B sliceID@b is no longer valid.
   */
  virtual void unRegisterSlice( int sliceID ) = 0;
  /**
   * Tells SoLDMNodeFrontManager what plane the slice is in.
   */
  virtual void setSlicePlane( int sliceID, const SbPlane &plane ) = 0;
  /**
   * Returns the next set of 2D tiles to load and unload for slice texturing of
   * slice @B sliceID@b.
   */
  virtual void getNextSliceTexFront( int sliceID, std::vector<SoLDMTileID>& toLoad, std::vector<SoLDMTileID>& toUnload ) = 0;

  // -------------------------------------------------------------------------------------------
  // notifications -----------------------------------------------------------------------------

  /**
   * Notifies SoLDMNodeFrontManager that it's necessary
   * to re-evaluate the data structure due to geometry or property changes.
   * The redraw flag specifies whether to redraw the data set or not.
   */
  virtual void geomChangeNotify(SbBool redraw=FALSE);

  /**
   * Notifies SoLDMNodeFrontManager that texture resources have
   * changed and the front needs to be recalculated.
   */
  virtual void resourceChangeNotify();

  /**
   * Notifies SoLDMNodeFrontManager if the user is interacting
   * with the scene or not.
   */
  void movingChangeNotify(SbBool movingValue);

  /**
   * Indicates if there is no texture to be loaded yet because nothing is in
   * main memory.
   */
  virtual bool isTextureFrontEmpty(){return true;}
  /**
   * Indicates if there is no texture to be loaded yet because nothing is in
   * main memory.
   */
  virtual bool isSliceTexFrontEmpty(int){return true;};

  /**
   * This function is called at the beginning of each traversal and can be
   * used to initialize whatever
   * variables are necessary for the SoLDMNodeFrontManager.
   */
  virtual void startTraversalNotify(){};

  /**
   * Utility function to get a tile's weight.
   */
  virtual float getWeight(SoLDMTileID tileID);

  /**
   * return the maximum tileID at a given depth. Used to prioritize tiles until a given level of
   * resolution
   */
  virtual LDM_TILE_ID_TYPE getMaxTileIDAtResolution( int level ) = 0;

  /**
   * return the depth of the given tileID.
   */
  virtual int getTileLevel(SoLDMTileID tileID) = 0;

  /**
   * return the depth of the tileID at the next time step.
   */
  virtual int getNextTimeStepTileLevel(SoLDMTileID tileID) = 0;

  /**
   * Indicates that the manager should be initialized.
   */
  virtual void shouldInit()
  {;}

  /**
   * Set the maximum display resolution of slice sliceID
   */
  virtual void setSliceMaxVisualResolution(int sliceID, int res) = 0;

  /**
  * Return the level of the next time step
  */
  virtual int getNextLoadedStepLevel(int id);

SoINTERNAL public:
  static void initClass();

  virtual void init(SbBool initTm = TRUE);

  //for debug only (used to draw octree outline).
  virtual int getNumFileIDsAtResolution(int resolution);
  void setUpdatingTopology(bool val){ m_updatingTopology = val; };
  bool isUpdatingTopology(){return m_updatingTopology; };
  /*
   * Simulates a node front manager update to know how many tiles would be needed
   * to render a geometry at a given resolution.
   * Basically returns the number of non null tiles (tiles intersecting the geometry).
   * Used for fixed resolution case to evaluate how many tiles are needed.
   */
  virtual void tryUpdateNode(int& count, LDM_TILE_ID_TYPE node,int octreeLevel, int resolution );

  virtual int getMaxLevel() const
  { return m_levelMax ; }

  /**
   * Return true if there is user interaction
   */
  SbBool isMoving() const { return m_moving; }

  /**
   * If true, getNextTexFront won't do
   * progressive loading
   */
  inline void setFixedResolution(bool flag);

  virtual bool getTiles(const SbBox3i32 &, int , std::vector<SoLDMTileID> &, std::vector<SoLDMTileID> &, std::vector<SoLDMTileID> &, bool ) {return true; };

  /** Return tile bbox without its borders */
  SbBox3i32 getTilePosWithoutBorders( const SoLDMTileID& tileID );

  /** Notify an user interaction stop at the specified time */
  void scheduleStoppedInteraction(const SbTime& time);

  // -------------------------------------------------------------------------------------------
 protected:
  /**
   * Ignore texture load rate if true.
   */
  bool m_fixedResolution;

  //Could be useful for any daughter class.
  static void redrawSensorCB(void *data, SoSensor *sensor);
  void scheduleRedraw();

  /** Ask for an octree evaluation if stopped moving */
  static void stoppedInteractionCB(void *data, SoSensor *sensor);

  /*
   * This sensor can be used to schedule a new rendering if the ideal texture node front
   * has not been reached yet. Useful to try and refine. Call m_scheduleRedrawSensor->schedule()
   * in the getNextTexFront method.
   */
  SoTimerSensor *m_scheduleRedrawSensor;
  bool           m_scheduleRedrawIndicator;
  SbThreadMutex* m_redrawSensorMutex;

  //notification boolean
  //m_geomChangeNotify is a critical section shared by the main loading thread
  //and the application thread.
  SbBool m_geomChangeNotify;
  SbThreadMutex* m_geomChangeNotifyMutex;
  SbBool m_moving; //is the user interacting or not ?

  //numTile/Files
  LDM_TILE_ID_TYPE m_numTileIDs;
  int m_numFileIDs;
  int m_levelMax;

  //are we only updating flags for the texture front (m_updatingTopology = false)
  //or really updating octree nodes values (m_updatingTopology = true)?
  bool m_updatingTopology;

  int m_maxSliceVisualRes;

  /** Called when the user stopped moving since more than getMovingTimeOut()*/
  SoAlarmSensor m_userInteractionAlarm;
private:
  // default is 30;
  static float s_ldmRedrawRate;
};

/*******************************************************************************/
void
SoLDMNodeFrontManager::setFixedResolution(bool flag)
{
  m_fixedResolution = flag;
}


inline float SoLDMNodeFrontManager::getWeight(SoLDMTileID)
{
  return 0.f;
}

inline int SoLDMNodeFrontManager::getNextLoadedStepLevel(int)
{
  return 0;
}

inline void SoLDMNodeFrontManager::init(SbBool)
{
}

inline int
SoLDMNodeFrontManager::getNumFileIDsAtResolution(int)
{
  return 0;
}

inline void
SoLDMNodeFrontManager::tryUpdateNode(int& , LDM_TILE_ID_TYPE ,int , int )
{
}

#endif // _SO_LDM_NODE_FRONT_MGR__
