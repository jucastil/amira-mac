/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (MMM yyyy)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_TILE_MANAGER_
#define  _SO_LDM_TILE_MANAGER_

class SbBox3i32;
class SoLDMTileID;
class SoTransferFunction;
class SoLDMDataAccess;
class SoLdmSubDivisionPolicy;
class SoState;
class SoBufferObject;
class SoLDMDataEditor;

#include <LDM/SoLDMLargeDataManagement.h>
#include <LDM/SoLDMNodeFrontManager.h>

#include <Inventor/STL/vector>
/**
* @LDMEXT LDM Tile Manager
*
* @ingroup LDMKernel
*
* @DESCRIPTION
*
* This class is only needed for advanced users who intend to extend or replace
* internal LDM algorithms.
*
* The SoLDMTileManager is responsible for managing the data in main memory, loading the most important
* tiles according to the user (see SoLDMTileVisitor), unloading the less important ones, and delivering
* them (#getTile) to create textures for rendering.
*
* The amount of memory, dedicated to storing the data in main memory, is up to the application and stored in
* the SoLDMResourceManager. The SoLDMTileManager works under constraint of the SoLDMResourceManager. The
* loading of new tiles is managed by the SoLDMTileVisitor. The visitor assigns a weight to a tile and asks
* the SoLDMTileManager for the existence of the tile in main memory by calling #checkResidencyAndUpdateWeight.
* Notice: The tile manager should keep track of weights passed through this function to remember priorities.
* Indeed, even though, weights between tile manager and node front manager are consistent
* (same weight in between 0 and 1), they are out of synchronisation: the visitor declares a tile's weight
* as null to the node front manager if the tile manager declares the tile as not loaded
* (#checkResidencyAndUpdateWeight returns false).
* So the tile manager must know the importance of the tile to know when to load it next, when the balance
* is reached, and not entirely rely on the #getWeight function of the SoLDMNodeFrontManager.
*
* The tile manager should register the SoDataSet node passed to the #registerVolumeData function to access
* different information needed to page data from disk:
* - Access to the reader (dataSet->getReader()) when a tile needs to be loaded
* - Access to information about fixed resolution mode if supporting this feature, in this case tiles of
*   non null weight must be loaded synchronously.(access to m_fixedResCB to be called, isFixedResolutionMode function).
* - Access to the SoDataCompositor (volData->getDataCompositor()) if in composition mode when handling
*   several SoDataSet.
* - Access to the dataSetId when handling several SoDataSet to know what piece of data to return
*   when #getTile is called.
* - Access to the resources of a given data set when handling several SoDataSet (note there is
*   one resource manager associated to each data set).
*
* As described above, multiple SoDataSet can be inserted in a scene graph and combined together to do render
* or data compositing (see SoDataSet). In this case, only one SoLDMTileManager handles them all and the
* #registerVolumeData function is called for each data set.
* In the case of a render compositing, each time a tile needs to be stored in memory, the tile manager
* needs to load the piece of data corresponding to the tile for each data set registered so that when a tile
* is declared in memory, the associated data resides for each data set (at any time, the amount of data loaded
* for each data set must be synchronized).
* In the case of a data compositing (volData->getDataCompositor() is not NULL) then when a tile is loaded,
* it must be loaded for each data set, each piece of data must be combined together by the data compositor and
* the final composed data must be stored and managed by the tile manager.
*
* @SEE_ALSO
* SoLDMTileVisitor,
* SoLDMResourceManager,
* SoLDMNodeFrontManager,
* SoDataSet,
* SoVolumeRendering,
* LDMDefaultSliceAccessor
*
*
*/

SoEXTENDER_Documented class LDM_API SoLDMTileManager : public SoLDMLargeDataManagement {

public:
 /**
  * Constructor.
  */
  SoLDMTileManager(){};

 /**
  * Destructor.
  */
  virtual ~SoLDMTileManager(){};

SoEXTENDER public:
  /**
   * Function of initialization. This function is called only once after the SoLDMNodeFrontManager
   * initialization (so the tile manager can query the number of data tiles to manage by calling
   * getNodeFrontManager()->getNumFileIDs()).
   * The input parameter indicates which tiles should be in memory after initialization.
   * All tileIds between 0 and up to tilesToLoad must be in memory.
   */
  virtual void init(SoLDMTileID tilesToLoad) = 0;

  virtual void startNumDataNotify(int id = -1, int entry = -1) = 0;//not sure we will use this one
  virtual void endNumDataNotify (bool isAdded, bool sync, bool shouldInit=false) = 0;//

 /**
  * Get Tile dimension. For the default topology (octree) this function should
  * always return the same size.
  */
  virtual SbVec3i32 getTileDimension(SoLDMTileID tileID) const = 0;

 /**
  * Functions to keep memory state stable when querying state.
  * Indicates a memory transaction is starting.
  * Memory state should not change until #endTransaction is called.
  * A transaction is defined as follow:
  * startTransaction() indicates the following set of functions will/might be called to analyze how
  * texture front should evolve and what set of tiles to use to render a particular geometry.
  * Note that the data front managed by the tile manager should evolve based on the weights passed by
  * #isTileResidentAndUpdateWeight.
  * For a given transaction, functions will be called in the following order:
  * #startTransction()
  * {
  *   #prioritizeTile(for topology evaluation). Only called once for all geometry.
  *   #getMinMax(for topology evaluation). Only called once for all geometry and if
  *   ignoring the fully transparent tiles.
  *   #setAllowLoading if NO_USER_INTERACTION mode is On. Only called once for all geometry.
  *   #resetWeights (for topology evaluation). Only called once for all geometry.
  *   #isTileResidentAndUpdateWeight (for octree evaluation). Only called once for all geometry.
  *   #isInMemory. Always called per geometry to calculate the texture front.
  *   Allows a tile manager user to know what tiles should be locked during a given transaction
  *   until #getTiles is called.
  *   #getTile or #getTileExt. Called per geometry if there is a texture front change or if more texture can be loaded.
  * }
  * #endTransaction()
  */
  virtual void startTransaction() = 0;

 /**
  * Notify a transaction has ended.
  */
  virtual void endTransaction()   = 0;

 /**
  * Returns whether the input tile resides in memory and update its weight.
  * Called when the tile visitor evaluates the topology.
  * The input weight is an indication of how LDM prioritize data for the current
  * scene state. Tiles of higher weight should arrive in memory first.
  * Note that the root tile must always resides in memory.
  */
  virtual bool checkResidencyAndUpdateWeight(SoLDMTileID tileID, float weight) = 0;

 /**
  * Indicates whether a tile is in main memory.
  * Called when the node front manager evaluates the texture front.
  */
  virtual bool isInMemory(SoLDMTileID tileID) const = 0;

 /** 
  * Indicates whether the data attached to a tile is in main memory.
  * Called when the node front manager evaluates the texture front.
  *
  * This allows to manage data that implements SoBufferAsyncInterface.
  */
  virtual bool isDataInMemory(const SoLDMTileID& tileID) const = 0;

 /** 
  * Launch an asynchronous request for the data attached to the specified tile.
  *
  * This allows to manage data that implements SoBufferAsyncInterface.
  */
  virtual bool requestRefetch(const SoLDMTileID& tileID, const double weight) const = 0;


 /**
  * Gets the data buffer associated with a tile for a given data set. LDM expects the data to be stored
  * as a stack of slices along the Z Inventor axis.
  * Called after texture front evaluation. Only called on tiles that the tile manager declared as
  * resident in memory. The input tileID has been called previously by the #isInMemory function
  * and the answer was true.
  */
  virtual const SoBufferObject* getTile(SoLDMTileID tileID, unsigned short dataSetId) = 0;

 /**
  * This function must return the data associated with the given tileID and dataSetId
  * but it must be stored as a stack of slices along the X Inventor axis.
  * Only called if the useExtendedData flag from SoDataSet is TRUE. Allows equalizing performance
  * of axis aligned slices roaming through a data set.
  */
  virtual const SoBufferObject* getTileExt(SoLDMTileID tileID, unsigned short dataSetId) = 0;

  /**
   * Allows accessing a 2D buffer for slice and volumeSkin rendering. @BR
   * When needing to render an SoOrthoSlice or SoVolumeSkin, LDM accesses the 2D buffer needed
   * by calling the functions of the tile manager inner slice accessor object.
   */
  class LDM_API LDMSliceAccessor {

  public:
    /**
     * Default Destructor.
     */
    virtual ~LDMSliceAccessor() {}

    /**
     * Access the 2D buffer of the given slice along the sliceAxis axis at sliceNumber position
     * within the tile. @BR See #releaseOrthoSliceBuffer.
     */
    virtual SoBufferObject* getOrthoSliceBuffer(const SoLDMTileID& tile, int sliceAxis, int slice, SoState * state=NULL, bool useExtendedData=false) = 0;

    /**
     * Release the buffer returned by #getOrthoSliceBuffer.
     */
    virtual void releaseOrthoSliceBuffer(SoBufferObject*) = 0;

    /**
     * Specifies the kind of slice the accessor is managing.
     */
    virtual void setLargeSliceSupport (SbBool flag) =0;
  };

  /**
   * Return an instance of slice accessor handling the data corresponding to the given data set/id pair.
   * Called when rendering an SoOrthoSlice.
   * When subclassing from the tile manager there is no immediate need to redefine the functions of the
   * slice accessor. LDM already handles the extraction of the buffer from the 3D tile.
   * One can simply use the LDMDefaultSliceAccessor.
   */
  virtual LDMSliceAccessor* getLdmSliceAccessor(const SoLDM::DataSetIdPair& p) = 0;

 /**
  * Gets the minimum and maximum values in a tile of data. @BR
  * The returned value indicates whether it has been calculated yet or in other words, if the tile
  * was ever loaded.
  * Only called if ignoring fully transparent tiles (see SoVolumeRendering).
  */
  virtual bool getMinMax(SoLDMTileID tile, double& min, double& max) const = 0;

 /**
  * This function must ensure that all the data associated with the input set of tiles is loaded in
  * main memory when returning. The data associated to a given tileID must be locked in memory
  * until #releaseTileData is called.
  * Called when using the data access functions (getData) from the SoLDMDataAccess.
  * @deprecated No longer used. getTileData( const std::vector<SoLDMTileID>& tileIDs, int& errorIndicator, unsigned short volumeDataId);
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED virtual void getTileData( const std::vector<SoLDMTileID>& tileIDs, int& errorIndicator, unsigned short volumeDataId)
  {
    getTileData( tileIDs, errorIndicator, volumeDataId, NULL);
  }

  /**
  * This function must ensure that all the data associated with the input set of tiles is loaded in
  * main memory when returning. The data associated to a given tileID must be locked in memory
  * until #releaseTileData is called.
  * Called when using the data access functions (getData) from the SoLDMDataAccess.
  */
  virtual void getTileData( const std::vector<SoLDMTileID>& tileIDs, int& errorIndicator, unsigned short volumeDataId,SoLDMDataAccess* pDataAccess ) = 0;

 /**
  * Initiates an asynchronous request and returns immediately.
  * It must use dataAccess->getRequestedTile() to get the requested tile list.
  * Returns true if the request is in fact synchronous (all tiles were already loaded).
  * [OIVJAVA-WRAPPER PACK{AsyncRequestInfo}]
  */
  virtual bool requestTileData(int requestId, int& memError, SoLDMDataAccess& dataAccess);

 /**
  * Releases previously requested data associated with a given tileID from memory.
  * If supported, dataSetId allows you to specify which data set should be released.
  * -1 means all data sets in the MultiDataVolumeGroup.
  */
  virtual void releaseTileData(SoLDMTileID tileID, unsigned short dataSetId = -1) = 0;

 /**
  * Notification of a memory resource change.
  * If the application changes the main memory resource using the SoLDMResourceManager,
  * resourceChangeNotify is called to notify the SoLDMTileManager that more tiles can be
  * loaded or some must be unloaded.
  */
  virtual void resourceChangeNotify() = 0;

 /**
  * This function is called when using the NO_USER_INTERACTION mode.
  * This mode should essentially allow loading only when the user does not interact with the scene.
  */
  virtual void setAllowLoading(bool allowLoad) = 0;

 /**
  * Reset weights to init the topology before evaluating it. This function is called
  * before a topology evaluation starting with #checkResidencyAndUpdateWeight(0, weight).
  */
  virtual void resetWeights() = 0;

 /**
  * Allows to let the user know what tiles are prioritary and should not be reset
  * in the resetWeight functions.
  * All tileIds between 0 and up to maxTileId are prioritary.
  * This function is called right before the resetWeight function.
  */
  virtual void prioritizeTiles(SoLDMTileID maxTileId) = 0;

 /**
  * Update a region of data in memory. All the tiles intersecting the regions must
  * be refetched.
  * Called if the application uses the SoDataSet::updateRegion function.
  */
  virtual void updateRegions(const SbBox3i32* region, int numRegions) = 0;

 /**
  * This function is only used if in multiple data mode.
  * There was a scene graph change in multiple data mode and only one tile manager must remain
  * for all data sets involved. LDM will keep the one that has loaded the more data.
  */
  virtual int getMemoryUsed() const = 0;

 /**
  * Flush tiles of a given resolution from memory pool.
  * Called only if the fixedResolution LDM mode is ON or if the maximum resolution threshold changes
  * (See LDMResourceParameter).
  */
  virtual void flushTilesOfRes(int resolution) = 0;

 /**
  * Debug purpose only. Used for visual feedback to highlight tiles in main memory.
  * Only called if the SoVolumeRendering::DRAW_TOPOLOGY flag is true.
  */
  virtual void getTileIDInMemory(std::vector<LDM_TILE_ID_TYPE>& tilesInMemory) const;

 /**
  * Indicates that the manager should be initialized.
  */
  virtual void shouldInit() {};

  /**
   * Set the LOCKED state to FALSE for all tiles loaded in memory
   */
  virtual void unLockTiles()=0;

  /**
  * Set the LOCKED state to true for all tile loaded in memory
  */
  virtual void lockTiles() =0;

  /**
  * Set the LOCKED state to true for the given SoLDMTileID
  */
  virtual void lockTile( const SoLDMTileID& tileId ) =0;

  /**
  * Set the LOCKED state to false for the given SoLDMTileID
  */
  virtual void unLockTile( const SoLDMTileID& tileId, bool forceUnload = false ) =0;

  /**
  * Mark tile given as parameter as edited (flag to true) or not edited (flag to false)
  * This will prevent the tile from been unlocked during rendering
  */
  virtual void setTileEdited( const SoLDMTileID& tileId, bool flag ) =0;

 /**
  * Return true if the tile is edited, false otherwise
  */
  virtual bool isTileEdited( const SoLDMTileID& ) = 0;

SoINTERNAL public:
  typedef std::vector<SbBox3i32> BoxesList;

  /**
   * Set the subtile manager used for subtiles
   */
  virtual void setSubTileManager(const SoType& type);

  /**
   * Subdivise the given tile according to the subtile manager type and the policy.
   */
  virtual void getSubDivisedTiles(BoxesList* &tilesBoxes, SoLdmSubDivisionPolicy* policy, SoLDMTileID tile);

  virtual bool isLoadOver() { return false; };

  virtual void replaceTileBuffer(const SoLDMTileID &, const unsigned short &, SoBufferObject* ) {};

  virtual void updateTile(const SbBox3i32& , const SoLDMTileID& );

  // Used to determine if the SoVolumeData needs to save some edition
  virtual bool getSaveState();
  virtual void setSaveState(bool flag );

  // Internal use. Useful to determine when all loaders are idle
  virtual void waitForAllLoadersIdle() {};
  virtual void setTileHasChanged ( const SoLDMTileID& , const unsigned short &) {};

  /** Recompute the subtile octree */
  virtual void recomputeSubtiles(const SoLDMTileID&, unsigned short) {}

protected:

 /**
  * This function can be used by the tile manager to notify other components of a data change.
  * Auditors can watch for this notification to update their state accordingly.
  * e.g. the node front manager can request a new render when data has arrived
  * by calling getNodeFrontManager()->geomChangeNotify(TRUE).
  */
  virtual void notifyDataChange(const SbBox3i32* region, int numRegions);

 /**
  * This function can be used by the tile manager to notify other components that
  * new data has arrived in main memory.
  * Auditors can watch for this notification to update their state accordingly.
  */
  virtual void notifyDataAvailable(){getNodeFrontManager()->geomChangeNotify(TRUE);};
  virtual SoBufferObject* getTilePointer( SoLDMTileID , unsigned short ) { return NULL;};

  friend class SoLDMDataEditor;

  bool m_bSaveState;

};

inline bool
SoLDMTileManager::requestTileData(int , int& , SoLDMDataAccess& )
{
  SoError::post("Doing an synchronous request with a base SoLDMTileManager class."
    " You must create your own TileManager implementing requestTileData method.");
  return false;
}

inline void
SoLDMTileManager::getTileIDInMemory(std::vector<LDM_TILE_ID_TYPE>& ) const
{
}

inline void
SoLDMTileManager::getSubDivisedTiles(BoxesList* &, SoLdmSubDivisionPolicy* , SoLDMTileID )
{
}

inline void
SoLDMTileManager::setSubTileManager(const SoType&)
{
}

inline void
SoLDMTileManager::notifyDataChange(const SbBox3i32* , int )
{
}

inline void
SoLDMTileManager::updateTile(const SbBox3i32& , const SoLDMTileID& )
{
}

inline bool
SoLDMTileManager::getSaveState()
{
  return FALSE;
}

inline void
SoLDMTileManager::setSaveState(bool flag)
{
  m_bSaveState = flag;
}

#endif // _SO_LDM_TILE_MANAGER_
