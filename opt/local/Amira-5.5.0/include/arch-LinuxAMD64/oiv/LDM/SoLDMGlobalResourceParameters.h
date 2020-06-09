/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_LDM_GLOBAL_RESOURCE_PARAM_
#define  _SO_LDM_GLOBAL_RESOURCE_PARAM_

class SoLDMTileManager;

#include <LDM/SoLDM.h>
#include <Inventor/nodes/SoSubNode.h>


/**
 *
 * Loading callback for LDM mode. Called with TRUE means the process starts loading.
 * FALSE means the process is done loading.
 * [OIV-WRAPPER NAME{LDMLoadCB}]
 */
typedef void SoLDMLoadCB( SbBool startLoading, void *userData );

/**
 *
 * Monitoring callback for LDM mode. Reports how much time is needed to load a given
 * amount of data. The amount of data is specified when setting the CB.
 * [OIV-WRAPPER NAME{LDMMonitoringCB}]
 */
typedef void SoLDMMonitoringCB(SoLDMTileManager *tm, double elapsedTime, double memLoaded, void *userData);

/**
 * @LDMEXT Global resource parameters for LDM.
 *
 * @ingroup LDMMisc
 *
 * @DESCRIPTION
 *   This class contains functions for controlling global resource parameters for the
 *   LDM module.
 *
 *   For extensions that use the LDM module, particularly VolumeViz, these parameters can have
 *   a significant effect on resource usage (primarily memory) and rendering performance.
 *
 *   @B Memory management @b
 *
 *   This class allows the application to specify how much system (CPU) and GPU memory VolumeViz can
 *   use to load data and textures.  By default the various memory limits are set to a
 *   percentage of the total available system and GPU memory (see the specific methods for details).
 *   Applications can use the SoCpuDevice and SoGLDevice classes to query the total and
 *   available memory on the CPU and GPU.
 *
 *   - Main memory @BR
 *     VolumeViz uses this amount of system memory to cache data tiles loaded by the volume reader.
 *     The main memory limit is set in megabytes using the #setMaxMainMemory() method.
 *     If the data set is small enough to fit in system memory, then generally the memory limit 
 *     should be set high enough to allow this.  If the data set is larger than system memory, 
 *     then the memory limit should be set as high as possible with impacting the application's
 *     other needs for memory.
 *     If the tile size is (for example) 64 and each voxel is a float value, then each tile
 *     requires approximately 1 MB of system memory.  However since Open Inventor 8.5, the
 *     system memory requirement is reduced for compressed tiles (stored compressed) and uniform
 *     tiles (stored as a single value). @BR @BR
 *     When there are multiple LDM data sets, by default each data set receives
 *     getMaxMainMemory() divided by the number of datasets.  Each time a new data set is created
 *     the per-dataset value is recomputed and some memory is taken away from existing data sets.
 *     The default allocation of memory to multiple data sets is not optimal if the data sets have
 *     significantly different sizes.  For example the memory required for a height field is
 *     normally much less than for a volume.  In this case the application can explicitly
 *     allocate memory to each data set using the maxMainMemory field of the SoLDMResourceParameters
 *     object associated with the data set (see the SoDataSet::ldmResourceParameters field).
 *
 *   - Texture memory @BR
 *     VolumeViz uses this amount of GPU memory to cache texture tiles on the GPU.
 *     The texture memory limit is set in megabytes using the #setMaxTexMemory() method.
 *     This value can also be set separately for each data set using SoLDMResourceParameters.
 *
 *   - LDM Tile cache @BR
 *     In some cases LDM needs to create tiles on-the-fly at runtime.  To reduce memory 
 *     usage and avoid duplicating application data, these created tiles are considered
 *     temporary and are stored in a tile cache.  This cache is separate from, and in 
 *     addition to, the LDM main memory.
 *     For example when compressed tiles are loaded from an LDM format file, they are 
 *     stored in LDM main memory still compressed.  When the tile data is needed, for 
 *     example to create textures, a temporary uncompressed tile is created and stored 
 *     in the tile cache.  Similarly if the volume data is “in memory” (a contiguous 
 *     block of application memory), when the tile data is needed, a temporary tile is 
 *     created and stored in the tile cache.  The tile cache is also used to expand
 *     uniform tiles, which are stored in the LDM file and in memory as a single value.
 *     The tile cache size can be set using the SoCpuBufferObjectCache method resize().
 *     The LDM tile cache can be accessed using the SoBufferObject static method
 *     getBufferObjectCache, which returns an instance of SoCpuBufferObjectCache.
 *     The tile cache size can only be set globally, not for each data set.
 *     The LDM tile cache was added in Open Inventor version 8.5.
 *
 * @SEE_ALSO
 *    SoDataSet,
 *    SoVolumeData,
 *    SoLDMResourceParameters
 *
 */
class LDM_API SoLDMGlobalResourceParameters
{

public:
  ////////////////////////////////////////////////////////////////////////////////
  // Memory Control Parameters section

  /**
   * Sets the maximum number of triangles allowed to be rendered for all VolumeViz render nodes. @BR
   * The sum of the max triangles values per data set (see SoLDMResourceParameters::maxNumTriangles field)
   * must be less or equal to this value.
   * This is an approximate value because some nodes using this parameter draw
   * indivisible chunks of triangles.  Particularly useful for limiting the number of triangles
   * generated by SoHeightFieldRender.
   * The default value is zero, which means there is no limit.
   */
  static void setMaxNumTriangles(int maxNumTriangles);

  /**
   * Get the maximum number of triangles allowed to be rendered for all VolumeViz render nodes.
   * See #setMaxNumTriangles.
   */
  static int getMaxNumTriangles();

  /**
   * Sets the maximum main (CPU) memory, in MB, to use for all VolumeViz data sets. @BR
   * You can also set the maximum main memory for each data set separately using the maxMainMemory
   * field of the data set's SoLDMResourceParameters object (see SoDataSet::ldmResourceParameters).
   * The sum of all per data set values must be less than or equal to the value set here.
   *
   * Default (since Open Inventor 8.1) is 50% of total CPU memory up to 70% of free memory.
   * See SoCpuDevice to query available CPU memory.
   */
  static void setMaxMainMemory( int maxMainMemory );

  /**
   * Returns the maximum main memory in MB for all the VolumeViz data sets.
   * See #setMaxMainMemory.
   */
  static int  getMaxMainMemory();

  /**
   * Sets the maximum texture (GPU) memory, in MB, for all VolumeViz data sets. @BR
   * You can also set the maximum texture memory for each data set separately using the
   * maxTexMemory field of the data set's SoLDMResourceParameters object
   * (see SoDataSet::ldmResourceParameters).  The sum of all per data set values must
   * be less than or equal to the value set here.
   * Default (since Open Inventor 8.1) is 75% of total GPU memory.
   * See SoGLDevice to query available GPU memory.
   */
  static void setMaxTexMemory( int maxTexMemory );

  /**
   * Returns the maximum texture memory in MB for all the VolumeViz data sets.
   * See #setMaxTexMemory.
   */
  static int  getMaxTexMemory();

  /**
   * Sets the maximum number of 2D textures allowed to be loaded for all VolumeViz data sets. @BR
   * The sum of each number of 2D textures allowed per data set (see SoLDMResourceParameters::max2DTextures field)
   * must be less than or equal to this value.  The total amount of GPU memory allowed is set
   * using the #setMaxTexMemory method.  This method limits the amount of GPU memory that can
   * be used by (for example) SoOrthoSlice and SoVolumeSkin nodes.  This can be useful when combining
   * slices and volume rendering because the 3D textures used by volume rendering require much more GPU
   * memory. Default (since Open Inventor 8.1) is 5% of total GPU memory
   */
  static void setMax2DTextures(int numTextures);

  /**
   * Get the maximum number of 2D textures allowed to be loaded.
   * See #setMax2DTextures.
   */
  static int getMax2DTextures();

  /**
   * Sets the maximum number of 3D textures allowed to be downloaded into texture (GPU) memory,
   * per frame (render traversal), for all VolumeViz data sets. @BR
   * You can set this parameter separately for each data set using field
   * SoLDMResourceParameter::tex3LoadRate.
   * Default is 10 3D textures (effectively 3 tiles) per render traversal.
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
  static void setTex3LoadRate( int loadRate );

  /**
   * Returns the maximum number of tiles (3D textures) allowed to be downloaded into texture (GPU)
   * memory per frame for all the VolumeViz data sets. 
   * See #setTex3LoadRate().
   */
  static int  getTex3LoadRate();

  /**
   * Sets the maximum number of 2D textures allowed to be downloaded into texture (GPU) memory per
   * frame (render traversal) for all the VolumeViz data sets. @BR
   * You can set this parameter separately for each data set using field
   * SoLDMResourceParameter::tex2LoadRate.
   * Default is 640 2D textures per frame.
   *
   * Each tile needed to render a slice (SoOrthoSlice, SoVolumeSkin, etc) must be loaded
   * into GPU memory as a 2D texture.  Increasing the loadRate value reduces the number of
   * frames required to reach maximum resolution.  But the render traversal has to wait for 
   * the data transfer to finish, so each frame may take longer to render, increasing 
   * the total time to reach maximum resolution.  
   */
  static void setTex2LoadRate( int loadRate );

  /**
   * Returns the maximum number of 2D textures allowed to be loaded into texture memory
   * per frame for all the VolumeViz data sets. 
   * See #setTex2LoadRate().
   */
  static int  getTex2LoadRate();

  /**
   * Sets how many loading threads to use if MultiIO mode is on. 
   * (MultiIO mode is on when LDM mode is on.) Default is 4.
   * These threads load tiles asynchronously in the background.
   *
   * The environment variable IVVR_NUM_LOADERS (see SoPreferences) allows you to specify
   * the initial number of loading threads. The environment variable IVVR_MAX_NUM_LOADERS
   * allows you to specify the maximum number of loading threads allowed (default is 20).
   */
  static void         setNumIO(unsigned int numIO);

  /**
   * Returns the current number of loading threads.
   * See #setNumIO().
   */
  static unsigned int getNumIO();

  ////////////////////////////////////////////////////////////////////////////////
  // VisualFeedback Parameters section

  /**
   * Visual feedback modes.
   * Used with #setVisualFeedbackParam() method.
   */
  enum VisualFeedbackParam {
  /**
   * Draw the tiles of SoVolumeRender or SoVolumeSkin primitives. They are drawn by default.
   */
    DRAW_TILES,
  /**
   * Use texturing for SoOrthoSlice, SoObliqueSlice, and SoVolumeGeometry primitives. They are used by default.
   */
    DRAW_SLICES_TEX,
  /**
   * Show tiles loaded in main memory.
   * This implies showing the multiresolution topology.
   * The tile outlines of tiles of full resolution are drawn with
   * a brighter yellow.
   * The topology is not drawn by default.
   * @IMAGE drawtopology.jpg
   */
    DRAW_TOPOLOGY,
  /**
   * Draw tile outlines for all primitives. The tile outline of tiles of full resolution
   * are drawn with a brighter gray for the volume, and a brighter green for the slices.
   * Outlines are not drawn by default.
   * @IMAGE drawtileoutline.jpg
   */
    DRAW_TILE_OUTLINE,
  /**
   * Show tiles visited by the Tile Visitor. They are not shown by default.
   *
   * For the default LDM implementation,
   * displays an octree representation showing traversal of the octree. Red dots are tiles
   * that have been valuated. Blue indicates the minimum and maximum resolution thresholds.
   * Yellow shows the octree itself.
   * @IMAGE showtilesvaluated.jpg
   */
    SHOW_TILES_VALUATED,
  /**
   * Show tiles loaded (in red) and unloaded (in blue) in texture memory. They are not
   * shown by default.
   */
    SHOW_LOAD_UNLOAD_TILES,
  /**
   * Use fake data instead of the real data during loading into main memory. The fake data
   * is programmatically generated and is designed to illustrate features of Large Data Management.
   * Fake data is not used by default.
   * @IMAGE fakedata.jpg
   */
    USE_FAKE_DATA
  };

  /**
   * Sets the specified visual feedback parameter to true or false..
   */
  static void setVisualFeedbackParam( VisualFeedbackParam param, SbBool state );

  /**
   * Returns the state of the specified visual feedback parameter.
   */
  static SbBool getVisualFeedbackParam( VisualFeedbackParam param );

  /**
   * LDM tile cache management (see class description for more information).
   * Used with #setTileCacheType() method.
   */
  enum TileCacheType {
    /**
    * LDM tile cache is not used. @BR
    * LDM works with all tiles uncompressed in memory. Each reader 
    * builds the tiles directly in LDM memory. 
    */
    NONE,
    /*
    * LDM tile cache is used for full resolution tiles only (Default). @BR
    * LDM reader won't uncompress full resolution tiles in memory, 
    * but will only store needed information so, when accessed, 
    * tiles can be generated, and cached, to be usable.
    */
    FULLRES_ONLY,
    /**
    * LDM tile cache is used for all tiles.  
    */
    ALL
  };

  /**
   * Specifies when the LDM tile cache should be used. @BR
   * Default is FULLRES_ONLY. See the class description for more information.
   * Added in Open Inventor 8.5.
   */
  static void setTileCacheType( TileCacheType cacheType );

  /**
  * Returns the LDM tile cache setting.
  * See #setTileCacheType().
  */
  static TileCacheType getTileCacheType();


  ////////////////////////////////////////////////////////////////////////////////
  // Viewing Parameters section

  /**
   * Sets the view culling flag. 
   * Default is TRUE.  When TRUE, only tiles that are inside the view frustum
   * (i.e. visible) will be loaded and conversely tiles that are outside the
   * view frustum may be discarded.
   */
  static void setViewCulling( SbBool state, SbBool forceRedraw = TRUE );

  /**
   * Returns the view culling flag.
   * See #setViewCulling().
   */
  static SbBool getViewCulling();

  /**
   * Sets the screen resolution culling flag.
   * Default is FALSE. When TRUE, only tiles for which the projection of a voxel is
   * greater than or equal to 1 pixel on screen will be loaded. This avoids unnecessary
   * loading of high resolution data for large volumes.
   * However if you "zoom out" from a volume, it does not force lower resolution tiles
   * to be used (high resolution tiles already in memory will still be used). If necessary
   * use the SoLDMResourceParameters::fixedResolution field to force use of lower
   * resolution tiles.
   */
  static void setScreenResolutionCulling( SbBool flag );

  /**
   * Returns the screen resolution culling state.
   * See #setScreenResolutionCulling().
   */
  static SbBool getScreenResolutionCulling();

  /**
   * Sets the IgnoreFullyTransparentTiles flag. 
   * Default is FALSE.  When TRUE, tiles for which all voxels between
   * their min and max values are fully transparent (alpha = 0) will not be refined.
   * In other words a low resolution version will always be used.  This can reduce
   * memory requirements for volumes with significant "empty space".
   */
  static void setIgnoreFullyTransparentTiles( SbBool state );

  /**
   * Returns the IgnoreFullyTransparentTiles flag.
   * See #setIgnoreFullyTransparentTiles().
   */
  static SbBool getIgnoreFullyTransparentTiles();

  /**
   * Sets the viewpoint refinement flag. 
   * Default is TRUE.  When TRUE, tile refinement depends on the viewpoint.
   * In other words, tiles closer to the camera have higher priority and higher
   * resolution data will be loaded for closer tiles first.  This can be useful
   * for large volumes that cannot be completely loaded in memory.
   */
  static void setViewpointRefinement( SbBool state );

  /**
   * Returns the viewpoint refinement flag.
   * See #setViewpointRefinement().
   */
  static SbBool getViewpointRefinement();

  /**
   * Sets the slice equal resolution flag. 
   * Default is FALSE. When TRUE, slice primitives, e.g. SoOrthoSlice and SoObliqueSlice,
   * are always rendered using a set of tiles at the same resolution level.  This avoids
   * potentially distracting visual effects caused by mixing tiles of different resolution
   * on the same slice.  But it means that the slice will be rendered at a lower resolution
   * if it is not possible to load every tile needed for the higher resolution.  When FALSE
   * and viewpoint refinement is enabled, higher resolution tiles will be loaded for
   * portions of the slice closer to the camera even if it is not possible to load every
   * high resolution tile.
   *
   * An alternative strategy is to enable the SoSlice::largeSliceSupport field.  When
   * large slice support is enabled, if all the required full resolution tiles have already
   * been loaded, then the slice data is taken from LDM cache memory as usual. But if some 
   * required tiles are not currently in memory, the full resolution slice data will be loaded
   * directly from the volume reader without loading the complete tiles. This reduces disk I/O
   * and reduces the amount of system memory required to display the slice at full resolution, 
   * so larger (or more) slices can be displayed. 
   */
  static void setSliceEqualResolution( SbBool state, SbBool forceRedraw = TRUE );

  /**
   * Returns the slice equal resolution flag.
   * See #setSliceEqualResolution().
   */
  static SbBool getSliceEqualResolution();

  /**
   * Sets the low resolution when moving flag.
   * Default is FALSE.  When TRUE, lower resolution tiles are automatically used
   * while the camera is moving (e.g. when user is panning and rotating.
   */
  static void setMoveLowResolution( SbBool state );

  /**
   * Returns the move low resolution flag.
   * See #setMoveLowResolution().
   */
  static SbBool getMoveLowResolution();

  /**
   * Sets the load notification rate (number of tiles).
   * When @B rate@b new tiles have been loaded in main memory, a redraw will be scheduled.
   * This is useful because tiles are loaded asynchronously using multiple threads.
   * The default is 50 tiles.  Which means, for example, if each voxel is one byte and the
   * tileSize is 64x64x64, a redraw will be scheduled whenever 13 MB of data has been loaded.
   */
  static void setLoadNotificationRate(int);

  /**
   * Returns the load notification rate.
   * See #setLoadNotificationRate().
   */
  static int getLoadNotificationRate();

  /**
   * Sets a \oivnetdoc delegate \else callback \endoivnetdoc to be called with the tile loading state. 
   * The \oivnetdoc delegate \else callback function \endoivnetdoc is called with true when the process
   * starts loading tiles. And with false when loading is complete, in other words when LDM has the
   * best possible set of tiles in memory for the current render nodes, viewpoint, etc.
   *
   * NOTE: This feature is available with VolumeVizLDM only.
   * [OIV-WRAPPER EVENT_NAME{LoadCallback}]
   */
  static void setLoadCB( SoLDMLoadCB *func, void *userData = NULL );

  /**
   * Sets a monitoring \oivnetdoc delegate \else callback \endoivnetdoc. 
   * This provides a snapshot of the tile loading performance.
   * The \oivnetdoc delegate \else callback \endoivnetdoc will be called each time memAmount MB 
   * of data have been loaded, with the amount of data and the amount of time elapsed to load that data.
   *
   * NOTE: This feature is available with VolumeVizLDM only.
   */
  static void setMonitoringCB( SoLDMMonitoringCB *func, int memAmount, void *userData = NULL );

  /**
   * Returns the default maximum number of 2D textures.
   */
  static inline int64_t getDefaultMaxTex2D() { return s_defaultMaxTex2D; }

  /**
   * Returns the default maximum GPU memory in MB.
   */
  static inline int64_t getDefaultMaxTexMem() { return s_defaultMaxTexMem; }

  /**
   * Returns the default maximum system (CPU) memory in MB.
   */
  static inline int64_t getDefaultMaxMainMem() { return s_defaultMaxMainMem; }

SoINTERNAL public:
  enum Cmd{
    SET_VISUAL_FEEDBACK_PARAM = 0,
    SET_MAX_MAIN_MEMORY,
    SET_MAX_TEX_MEMORY,
    SET_MAX_2D_TEXTURES,
    SET_MAX_NUM_TRIANGLES,
    SET_TEX3_LOAD_RATE,
    SET_TEX2_LOAD_RATE,
    SET_NUMIO,
    SET_WRITE_ALTERNATE_REP,
    SET_READ_ALTERNATE_REP,
    SET_DELAYED_RENDERING,
    SET_VIEW_CULLING,
    SET_SCREEN_RESOLUTION_CULLING,
    SET_VIEWPOINT_REFINEMENT,
    SET_IGNORE_FULLY_TRANSPARENT_TILES,
    SET_SLICE_EQUAL_RES,
    SET_MOVE_LOW_RES,
    SET_LOAD_NOTIFICATION_RATE
  };

  static void initClass();
  /** Return true if drawing tiles in CPU or GPU memory */
  static bool isDrawingOutlines();

protected:

// ------------------------------------------------------------
  // VisualFeedback Parameters
  static SbBool m_drawTiles;
  static SbBool m_drawSlicesTex;
  static SbBool m_drawTopology;
  static SbBool m_drawTileOutline;
  static SbBool m_showTilesLoaded;
  static SbBool m_showLoadUnloadTiles;
  static SbBool m_useFakeData;
  // ------------------------------------------------------------
  // Viewing Parameters
  static SbBool m_ignoreFullyTransparentTiles;
  static SbBool m_viewCulling;
  static SbBool m_screenResolutionCulling;
  static SbBool m_viewpointRefinement;
  static SbBool m_sliceEqualResolution;
  static SbBool m_moveLowResolution;

  static int64_t s_defaultMaxTexMem;
  static int64_t s_defaultMaxTex2D;
  static int64_t s_defaultMaxMainMem;

  static TileCacheType m_TileCacheType;

};
#endif // _SO_LDM_GLOBAL_RESOURCE_PARAM_
