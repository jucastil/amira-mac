/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef LDM_RESOURCE_PARAMETER_H
#define LDM_RESOURCE_PARAMETER_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/fields/SoFieldContainer.h>
#include <Inventor/fields/SoSubFieldContainer.h>

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFVec3i32.h>

#include <Inventor/SbBox.h>

#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/cassert>

class SoDataSet;
class SoLDMMediator;
class SoLDMResourceManager;
class SoLDMTileVisitor;

/**
* @LDMEXT Describes resource parameters constraints for a specific LDM data set.
*
* @ingroup LDMMisc
*
* @DESCRIPTION
*   This class contains fields and functions for setting resource parameters for
*   one specific SoDataset.
*
*   Global LDM parameters can be set using static methods in class SoLDMGlobalResourceParameters.
*   See the SoLDMGlobalResourceParameters class description for an overview of LDM memory management.
*
* @SEE_ALSO
*    SoDataSet,
*    SoVolumeData,
*    SoLDMGlobalResourceParameters
*
*/
class LDM_API SoLDMResourceParameters : public SoFieldContainer
{
  SO_FIELDCONTAINER_HEADER(SoLDMResourceParameters);

public:
  /**
  * This structure returns information to the application when using fixed resolution mode.
  */
  struct FixedResolutionReport{
    /**
     * Available report code.
     */
    enum ReportCode
    {
      /**
      * Loading in progress.
      * In this case, the progress is indicated by the two variables #numTilesToLoad
      * and #numTilesLoaded.
      * The current resources of the machine allow LDM to load
      * the data at the specified resolution. In this case, the only possible way
      * to receive an ABORT report code from the system is either if the user changes
      * the resources (i.e., decreases the main memory space), or add some new geometry
      * to the scene.
      */
      PROGRESS,
      /**
      * If LDM cannot grant a fixed resolution request, the \oivnetdoc delegate \else callback \endoivnetdoc
      * function is called with an ABORT report code. In this case, LDM will automatically
      * disable the fixed resolution mode.
      * The FixedResolutionCB \oivnetdoc delegate \else callback \endoivnetdoc will be called with an ABORT report code in
      * the following cases:
      * - The request to load the data at the specified resolution level (resolution
      * argument in the #enableFixedResolutionMode function) in main memory
      * for the current geometry (either SoVolumeRender, SoVolumeSkin, SoOrthoSlice, SoObliqueSlice,
      * volume geometries, or other LDM based render nodes) is not possible because the main memory space (set by the
      * setMaxMainMemory function) is not large enough. In this case, the \oivnetdoc delegate \else callback \endoivnetdoc
      * is called with an ABORT code immediately after the first sceneGraph traversal,
      * once the fixed resolution mode has been enabled.
      * - There was a geometry change (i.e., a geometry node was added to the scene graph) and
      * there is not enough room in memory for the geometry nodes to be displayed at the current
      * resolution level.
      * In this case, the memory space needed in addition for LDM to be able to grant
      * the request, is specified by the #numTilesToAdd variable. If there is enough main memory
      * resources on the user machine, an automatic memory adjustment can then be realized
      * by calling setMaxTilesInMainMem( getMaxTilesInMainMem() + numTilesToAdd ) right before
      * #enableFixedResolutionMode is called again. Those two calls can be done within the \oivnetdoc delegate \else callback \endoivnetdoc
      * function so LDM does not disable the fixed resolution mode after an ABORT report code
      * has been sent.
      */
      ABORT
    };
    /**
    * Report code.
    */
    ReportCode what;
    /**
    * How many more tiles need to be allowed in main memory. The value of this variable
    * is relevant only if the \oivnetdoc delegate \else callback \endoivnetdoc is called with an ABORT report code.
    * An automatic memory adjustment is possible by calling
    * setMaxTilesInMainMem( getMaxTilesInMainMem() + numTilesToAdd ) and then reenabling the
    * fixed resolution mode within the \oivnetdoc delegate \else callback \endoivnetdoc function.
    */
    int numTilesToAdd;
    /**
    * How many tiles need to be loaded. The value of this variable
    * is relevant only if the \oivnetdoc delegate \else callback \endoivnetdoc is called with a PROGRESS report code.
    */
    int numTilesToLoad;
    /**
    * Number of tiles LDM has already loaded. The value of this variable
    * is relevant only if the \oivnetdoc delegate \else callback \endoivnetdoc is called with a PROGRESS report code.
    */
    int numTilesLoaded;
  };

  /**
  *
  * When using the fixed resolution mode, this \oivnetdoc delegate \else callback \endoivnetdoc is used by the application
  * to get a report back from LDM as far as progress achieved and requests made.
  */
  typedef void FixedResolutionCB(FixedResolutionReport&, void*);

  /**
   * Tile Load Policy.
   */
  enum LoadPolicy {
    /** Load tiles only when when there is no user interaction, i.e., application idles.
     * (Default)
     */
    NO_USER_INTERACTION,
    /** Always load tiles. */
    ALWAYS,
    /** No tile loading. Allows suspension of the loading process. */
    NEVER
  };

  /**
   * Constructor.
   */
  SoLDMResourceParameters();

  /**
   * Destructor.
   */
  virtual ~SoLDMResourceParameters();

  /**
  * Maximum allowed main memory in MB that LDM is allowed
  * to use for this data set.
  * You can set the allowed main memory for all the data sets by calling
  * SoLDMGlobalResourceParameters::setMaxMainMemory().
  *
  * Default is SoLDMGlobalResourceParameters::getMaxMainMemory/num_dataset.
  *
  * The minimum value is 2 (MB). The maximum value is
  * SoLDMGlobalResourceParameters::getMaxMainMemory - 2*num_datasets (i.e., reserving 2 MB for
  * each of the other data sets).
  *
  * If you change this value, the amount of the change is
  * distributed across the other data sets, if any.  For example,
  * if you have three data sets, increasing the max main memory for
  * one data set by 64 MB will decrease the max main memory for each of
  * the other two data sets by 32 MB.
  *
  * By default, if you create a new data set it will get
  * SoLDMGlobalResourceParameters::getMaxMainMemory / num_datasets MB of memory
  * (and that amount of memory will be subtracted from the other data sets).
  *
  * You can protect a data set from having its memory (and other parameters) changed
  * automatically by calling the fixParams() method. In no case can the total of all
  * requested memory exceed SoLDMGlobalResourceParameters::getMaxMainMemory.
  *
  * Changing this number will automatically adjust the maximum number of tiles in the
  * #maxTilesInMainMem field.
  */
  SoSFInt32 maxMainMemory;

  /**
  * 
  * Maximum number of tiles in main memory for this data set. @BR
  * Changing this number will automatically adjust the maximum amount of memory
  * set by #maxMainMemory (memory required for each tile depends on tile size
  * and voxel size).
  * Default is (maxMainMemory/numDatasets)/(tileSize in MB).
  */
  SoSFInt32 maxTilesInMainMem;

  /**
  * Tile loading policy. 
  * Use enum #LoadPolicy. Default is NO_USER_INTERACTION.  
  * NO_USER_INTERACTION means the asynchronous loading
  * threads will only load tiles when the user is not interacting with the scene (i.e. the
  * application is idle).
  *
  * The loading occurs as long as there is something to load if ALWAYS is passed.
  * No loading occurs if NEVER is passed, however at least the resolution 0 is loaded.
  */
  SoSFEnum loadPolicy;

  /**
  * Maximum allowed texture (GPU) memory in MB for this data set. @BR
  * Changing this number will automatically adjust the field #maxTilesInTexMem
  * (number of tiles allowed in texture memory).
  * You can set the allowed texture memory for all the data sets by calling SoLDMGlobalResourceParameters::setMaxTexMemory().
  * Default is SoLDMGlobalResourceParameters::getMaxTexMemory()/numDatasets.
  */
  SoSFInt32 maxTexMemory;

  /**
  * Maximum number of 3D tiles in texture memory for this data set.
  * Each tile needed for volume rendering (SoVolumeRender) and volume geometry must be 
  * stored in GPU memory as a 3D texture.
  * Changing this number will automatically adjust the field #maxTexMemory (maximum
  * amount of texture memory). Default is maxTexMemory/(tileSize in MB).
  */
  SoSFInt32 maxTilesInTexMem;

  /**
  * Maximum number of 3D tiles to be loaded into texture memory per frame for this data set. @BR
  * You can set this number for all data sets by calling SoLDMGlobalResourceParameters::setTex3LoadRate().
  * Default is SoLDMGlobalResourceParameters::getTex3LoadRate().
  *
  * Each tile needed for volume rendering (SoVolumeRender) and volume geometry must be 
  * transfered to GPU memory as a 3D texture.
  * So, for example, transfering 1000 tiles at the default loadRate (10) requires 100 frames.
  * (How many seconds this takes depends on the frames per second possible, which in turn
  * depends on many factors including the complexity of the scene graph.)  Increasing the
  * loadRate value reduces the number of frames required to reach maximum resolution.  But
  * the render traversal has to wait for the data transfer to finish, so each frame may take
  * longer to render, increasing the total time to reach maximum resolution.  
  */
  SoSFInt32 tex3LoadRate;

  /**
  * Maximum number of 2D tiles allowed in texture (GPU) memory for this data set.
  * Each tile needed to render a slice (SoOrthoSlice, SoVolumeSkin, etc) must be stored
  * in GPU memory as a 2D texture.  This method limits the amount of GPU memory that can
  * be used by (for example) SoOrthoSlice and SoVolumeSkin nodes.  This can be useful when
  * combining slices and volume rendering because the 3D textures used by volume rendering
  * require much more GPU memory.
  * Default is SoLDMGlobalResourceParameters::getMaxTex2D().
  */
  SoSFInt32 max2DTextures;

  /**
  * Maximum number of 2D tiles to be loaded in texture memory per frame. @BR
  * This affects rendering nodes that use 2D textures, for example SoOrthoSlice and SoVolumeSkin.
  * Default is SoLDMGlobalResourceParameters::getTex2LoadRate().
  *
  * Each tile needed to render a slice (SoOrthoSlice, SoVolumeSkin, etc) must be loaded
  * into GPU memory as a 2D texture.  Increasing the loadRate value reduces the number of
  * frames required to reach maximum resolution.  But the render traversal has to wait for 
  * the data transfer to finish, so each frame may take longer to render, increasing 
  * the total time to reach maximum resolution.  
  */
  SoSFInt32 tex2LoadRate;

  /**
  * Minimum loading threshold for LDM module.
  * Specifies to LDM to never unload tiles below this resolution threshold.
  * Threshold is the power of 2 of the desired subsample level.
  * For instance, passing 2 means never unload tiles of resolution 1/4.
  * Default is -1, meaning the minimum subsample level.
  *
  * If used with an ROI enabled, only tiles below the min resolution threshold
  * and within the ROI subvolume will never be unloaded. All tiles outside the ROI
  * subvolume will be unloaded. The ROI box allows you to specify where it is the
  * most important to increase the resolution within the subvolume. By default,
  * (subvolume ROI flag enabled) this would be within the box. If for example using
  * the exclusion box mode, then lower resolution tiles will be within the box and higher
  * resolution ones outside the box and within the subvolume.
  *
  * The minimum subsample level can be queried using SoLDMNodeFrontManager::getMinResolution.
  * NOTE: SoLDMNodeFrontManager is declared SoEXTENDER and is intended for advanced users.
  * For details see its header file.
  */
  SoSFInt32 minResolutionThreshold;

  /**
  * Maximum loading threshold for the LDM module. @BR
  * LDM will never load tiles below this resolution threshold.
  * Threshold is the power of 2 of the desired subsample level.
  * For instance, passing 1 means never load tiles of full resolution.
  * Default is 0, full resolution, i.e., load everything.
  */
  SoSFInt32 maxResolutionThreshold;

  /**
  * Sets the tile size for non-LDM data. @BR
  * When using the LDM module with unconverted data, i.e., any file format other than LDM,
  * LDM will convert it to an LDM data set on the fly. In this case,
  * it is possible to specify the tile size with this field. (The tile size
  * is already defined in LDM files, which is why this method does not apply to them.)
  * Default is (64, 64, 64).
  */
  SoSFVec3i32 tileDimension;

  /**
   * Size of subtiles used by some accelerated algorithms.
   * Default is (16, 16, 16).
   */
  SoSFVec3i32 subTileDimension;

  /**
   * Lock parameter values.
   * Default is FALSE.
   * By default, the resource parameters are automatically recalculated if the parameters
   * for another data set change or a new data set is created (to respect the global amount of resources).
   * If this field is TRUE, the resources for this data set are not allowed to change.
   */
  SoSFBool fixedParams;

  /**
  * Tile loading notification rate.
  * Default is 50 tiles.
  * When @B rate@b tiles have been loaded in main memory, a redraw will be scheduled.
  * Which means, for the default rate, that if each voxel is one byte and the
  * tile size is 64x64x64, a redraw will be scheduled whenever 13 MB of data has been loaded.
  */
  SoSFInt32 loadNotificationRate;

  /**
  * Sets the tile overlap value (number of voxels) for non-LDM data.
  * Default is 1.
  * Applies to non-LDM files only, because LDM have this value in the header.
  * The value can be 0 (no overlap) or >= 1 (overlap). If 0, you may see a line
  * at the tile borders because no interpolation is done between the tiles.
  * If 1 or higher, interpolation is done across tile boundaries.
  */
  SoSFInt32 overlapping;

  /**
  * Tile half-life (seconds).
  * Default is 2 seconds.
  * When calling SoDataSet::getLdmDataAccess::getData(), once a tile is unlocked by
  * the application (call to SoDataSet::getLdmDataAccess::releaseData), its weight will decrease
  * until the tile is weighted again by LDM. This function allows you to set how long
  * it takes for the tile's weight to be divided by 2 (initial weight is 1). 
  * The tile weight will be set to 0 when the weight becomes less than 0.05.
  */
  SoSFFloat tileHalfLife;

  /**
  * Fixed resolution mode.
  * Default is FALSE.  This mode allows you to request that LDM render using 
  * tiles at the specified resolution level (see #resolution field).  If the
  * requested resolution requires more memory than currently allowed (see 
  * #maxMainMemory, #maxTexMemory and SoLDMGlobalResourceParameters) the
  * highest resolution that fits in memory will be used. Note that
  * tiles at lower resolution levels are always loaded into memory, but tiles
  * at higher resolution levels (if any) will not be loaded.
  */
  SoSFBool fixedResolution;

  /**
   * Resolution level for fixed resolution mode. 
   * Default is 1, i.e., 1 out of 2 voxels resolution.
   * The requested resolution is specified as the power of 2 of the desired subsample level.
   * Resolution level 0 is full resolution data.
   * If requested resolution requires more memory than allowed (see #maxMainMemory,
   * #maxTexMemory, SoLDMGlobalResourceParameters) the highest resolution that fits
   * is used.
   */
  SoSFInt32 resolution;

  /**
   * Maximum number of triangles allowed to be rendered by LDM render nodes. @BR
   * Default value is 0 meaning no limits.
   * This is an approximate value because some nodes using this parameter draw
   * indivisible chunks of triangles.  Particularly useful to limit the number of
   * triangles generated for an SoHeightFieldGeometry.  A global limit for all
   * nodes can be set using SoLDMGlobalResourceParameters.
   */
  SoSFInt32 maxNumTriangles;


  /** @deprecated No longer used. Use the field #maxMainMemory.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMaxMainMemory( int maxMainMemory );

  /** @deprecated No longer used. Use the field #maxMainMemory.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMaxMainMemory();

  /** @deprecated No longer used. Use the field #maxTilesInMainMem.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMaxTilesInMainMem( int numTiles );
  /** @deprecated No longer used. Use the field #maxTilesInMainMem.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int  getMaxTilesInMainMem();

  /** @deprecated No longer used. Use the field #loadPolicy.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setLoadPolicy( LoadPolicy policy );

  /** @deprecated No longer used. Use the field #loadPolicy.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED LoadPolicy getLoadPolicy();

  /**
  *
  * Sets the amount of time (in seconds) during which LDM continues not loading once a user
  * stops interaction.
  * In other words, LDM will start loading again timeOut seconds after the
  * user stops interaction.
  * Considered only in NO_USER_INTERACTION mode.
  * Default is 0.3 seconds.
  */
  void setMovingTimeOut(float timeout);

  /**
  *
  * Returns the amount of time during which LDM continues not loading data once a user
  * stops interaction.
  * Considered only in NO_USER_INTERACTION mode.  See #setMovingTimeOut().
  */
  float getMovingTimeOut();

  /** @deprecated No longer used. Use the field #loadNotificationRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setLoadNotificationRate(int rate);

  /** @deprecated No longer used. Use the field #loadNotificationRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getLoadNotificationRate();

  /** @deprecated No longer used. Use the field #maxTexMemory.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMaxTexMemory( int maxTexMemory );

  /** @deprecated No longer used. Use the field #maxTexMemory.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMaxTexMemory();

  /** @deprecated No longer used. Use the field #maxTilesInTexMem.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMaxTilesInTexMem( int numTiles );

  /** @deprecated No longer used. Use the field #maxTilesInTexMem.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMaxTilesInTexMem();

  /** @deprecated No longer used. Use the field #tex3LoadRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setTex3LoadRate( int loadRate );

  /** @deprecated No longer used. Use the field #tex3LoadRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getTex3LoadRate();

  /** @deprecated No longer used. Use the field #max2DTextures.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMax2DTextures( int numTextures );

  /** @deprecated No longer used. Use the field #max2DTextures.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMax2DTextures();

  /** @deprecated No longer used. Use the field #tex2LoadRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setTex2LoadRate( int loadRate );

  /** @deprecated No longer used. Use the field #tex2LoadRate.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getTex2LoadRate();

  /** @deprecated No longer used. Use the field #minResolutionThreshold.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMinResolutionThreshold( int threshold );

  /** @deprecated No longer used. Use the field #minResolutionThreshold.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMinResolutionThreshold();

  /** @deprecated No longer used. Use the field #maxResolutionThreshold.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setMaxResolutionThreshold( int threshold );

  /** @deprecated No longer used. Use the field #maxResolutionThreshold.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getMaxResolutionThreshold();

  /** @deprecated No longer used. Use the field #tileDimension.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED void setTileSize( int tileDim );

  /** @deprecated No longer used. Use the field #tileDimension.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getTileSize();

  /** @deprecated No longer used. Use the field #fixedParams.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void fixParams( SbBool flag);

  /** @deprecated No longer used. Use the field #fixedParams.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED SbBool isParamsFixed();

  /** @deprecated No longer used. Use the field #overlapping.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void setOverlapping( int border );

  /** @deprecated No longer used. Use the field #overlapping.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED int  getOverlapping();

  /**
  * Gets the size of a voxel in bytes.
  */
  int getDataSize();

  /** @deprecated No longer used. Use the field #tileHalfLife.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void setTileHalfLife(float timeInSec);

  /** @deprecated No longer used. Use the field #tileHalfLife.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED float getTileHalfLife();

  /** @deprecated No longer used. Use the fields #fixedResolution and #resolution.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void disableFixedResolutionMode();

  /** @deprecated No longer used. Use the fields #fixedResolution and #resolution.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED SbBool isFixedResolutionMode();

  /**
  * Use this method only if you need a callback.
  * Otherwise use the fields #fixedResolution and #resolution.
  */
  void enableFixedResolutionMode(int resolution, FixedResolutionCB* func);

  /** @deprecated No longer used. Use the field #resolution.
   * @DEPRECATED_SINCE_OIV 7.0
  */
  SoDEPRECATED int getFixedResolution();

  /**
  * Sets the importance of one type of geometry relative to others.
  *
  * The geometry type should be one of the VolumeViz or ReservoirViz geometry classes. For example,
  * SoOrthoSlice::getClassTypeId().
  *
  * The priority passed must be between 0 and 1, 0 being lowest priority and 1 the highest.
  * LDM will refine tiles first where geometries are the most important.
  * For example, if an SoVolumeRender node has a higher priority than slices, then the tiles required for
  * this SoVolumeRender node will be refined first.
  *
  * Default is 0.5 for a volume, 0.9 for other geometry.
  */
  void setGeometryPriority(SoType geometryType, float priority);

  /**
  * Returns the priority of the specified geometry type.
  * The function will return FALSE if the geometry is of unknown type.  See #setGeometryPriority().
  */
  SbBool getGeometryPriority(SoType geometryType, float& priority);

SoINTERNAL public:
  typedef struct GeomPriority
  {
    float   m_weight;
    SoType  m_geomId;
  } GeomPriority;

  /**
   * Sets the data set at which this node is bound.
   */
  void setDataSet(SoDataSet *ds);

  /**
   * Copies some LDM parameters which are not in fields.
   */
  void copyParameters(SoLDMMediator *mediator);

  /**
  * Prints all parameters into f.
  */
  void fprintfResourceManager(FILE *f);

  /*
  * This function allows you to synchronously unload the data if it needs to be refetched.
  */
  void invalidateData();

  /*
  * This function is used when collecting the geometry.
  * If fixed resolution mode is enabled, each collected geometry will count how many tiles
  * are needed to render them.
  * After geometry collection, volumeData will report to the application the total count.
  */
  void setNumTiles(int numTiles);

  /**
   * Return how many tiles are needed to render at a given level of resolution
   */
  int getNumTiles();

  /**
   * Converts geometry coordinates to voxel coordinates for a geometry box.
   * (useful to figure out num tiles needed for fixed res mode)
   */
  SbBox3i32 XYZToVoxel(const SbBox3f &dataBox);


  /**
   * Fixed resolution methods
   */
  bool isReportDisabled();
  void setReportDisabled(bool flag);
  FixedResolutionCB* getFixedResCB();
  int getNumTilesLoaded();
  bool toReport();
  void setToReport(bool flag);
  void increaseNumTilesLoaded();
  void decreaseNumTilesLoaded();
  void resetNumTilesLoaded();
  void resetFixedResVar();

  void sendToLdm(SoDataSet* ds);

  void enableParamsNotify(SbBool state);

  virtual void notify(SoNotList*);

  inline void setResourceManager(SoLDMResourceManager* resourceManager);

  /**
   * If true, load the maximum possible resolution.
   * This used to simulate the brute force render mode of volumeviz
   * but with LDM.
   */
  inline void forceFixedResolution(bool flag);

  /**
   * Return true if maximum possible resolution
   * must be loaded synchronously.
   */
  inline bool isFixedResolutionForced() const;

private:
  bool m_forceFixedResolution;

  /**
   * Forbid recopy constructors
   */
  SoLDMResourceParameters& operator=(const SoLDMResourceParameters& ldmrp);
  SoLDMResourceParameters(const SoLDMResourceParameters& );

  //Methods used in ldmParameterChangedCB
  void updateMaxNumTriangles(int numTriangles);
  void updateTileHalfLife(float timeInSec);
  void updateOverlapping( int border );
  void updateLoadNotificationRate(int rate);
  void updateFixParams( SbBool fixed );
  void updateTileSize( const SbVec3i32 &tileDim );
  void updateMaxResolutionThreshold( int threshold );
  void updateMinResolutionThreshold( int threshold );
  void updateTex2LoadRate( int loadRate );
  void updateMax2DTextures( int numTextures );
  void updateTex3LoadRate( int loadRate );
  void updateMaxTilesInTexMem( int numTiles );
  void updateMaxTexMemory( int maxTexMemory );
  void updateMaxTilesInMainMem( int numTiles );
  void updateMaxMainMemory( int mem );
  void updateEnableFixedResolutionMode(int resolution, FixedResolutionCB* func);
  void updateDisableFixedResolutionMode();

  SoDataSet* m_ds;
  SoLDMResourceManager* m_resourceMgr;

  FixedResolutionCB* m_fixedResCB;
  int  m_numTilesLoaded;
  int  m_numTilesNeeded;
  bool m_toReport;
  bool m_reportDisable;
  bool m_isFixedRes;
  bool m_bLdmParamDebug;

  /** used to avoid calling m_resourceMgr->getMinResolutionThreshold */
  int m_previousMinThreshold;

  //to save current system state before using fixed res mode
  LoadPolicy         m_policyUsed;
  int                m_resolution;
  bool               m_viewCulling;
  bool               m_viewRefinement;
  SoLDMTileVisitor*  m_fixedResVisitor;
  SoLDMTileVisitor*  m_beforeFixedResVisitor;
  bool m_beforeFixedResVisitorFlag;

  std::vector<GeomPriority> m_geomPriority;
  int getGeometryIndex(SoType geometryType);

  static bool s_artForceFixed;
};

/***************************************************************************/
inline bool
SoLDMResourceParameters::isReportDisabled()
{
  return m_reportDisable;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::setReportDisabled(bool flag)
{
  m_reportDisable = flag;
}

/***************************************************************************/
inline SoLDMResourceParameters::FixedResolutionCB*
SoLDMResourceParameters::getFixedResCB()
{
  return m_fixedResCB;
}

/***************************************************************************/
inline int
SoLDMResourceParameters::getNumTilesLoaded()
{
  return m_numTilesLoaded;
}

/***************************************************************************/
inline bool
SoLDMResourceParameters::toReport()
{
  return m_toReport;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::setToReport(bool flag)
{
  m_toReport = flag;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::increaseNumTilesLoaded()
{
  m_numTilesLoaded++;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::decreaseNumTilesLoaded()
{
  m_numTilesLoaded--;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::resetNumTilesLoaded()
{
  m_numTilesLoaded = 0;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::setResourceManager(SoLDMResourceManager* resourceManager)
{
  m_resourceMgr = resourceManager;
}

/***************************************************************************/
inline SoLDMResourceParameters&
SoLDMResourceParameters::operator=(const SoLDMResourceParameters& )
{
  assert(0);
  return *this;
}

/***************************************************************************/
inline void
SoLDMResourceParameters::forceFixedResolution(bool flag)
{
  m_forceFixedResolution = flag;
}

/***************************************************************************/
inline bool
SoLDMResourceParameters::isFixedResolutionForced() const
{
  return m_forceFixedResolution || s_artForceFixed;
}

/***************************************************************************/
extern LDM_API std::ostream& operator << (std::ostream& os, const SoLDMResourceParameters& p);

//Oiv6 compatibility
#define LDMResourceParameter SoLDMResourceParameters

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
