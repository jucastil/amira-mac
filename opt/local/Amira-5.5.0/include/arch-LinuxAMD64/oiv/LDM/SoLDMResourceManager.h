/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : J.HUMMEL (Dec 2002)
** Modified by : T.DUFOUR (MMM yyyy)
**=======================================================================*/
#ifndef  _SO_LDM_RESOURCE_MANAGER_
#define  _SO_LDM_RESOURCE_MANAGER_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/SoLDMLargeDataManagement.h>
#include <Inventor/SbVec.h>
#include <Inventor/STL/vector>
#define MIN_RES_THRESHOLD 10000 //high number meaning not set

class SoDataSet;

// callback function prototypes
typedef void SoLDMTexFrontCB (void *userData);

/**
 * @LDMEXT Resource Manager
 *
 * @ingroup LDMKernel
 *
 * @DESCRIPTION
 *
 * The SoLDMResourceManager maintains information about the resources available on the machine
 * and constrains the data flow to these resource limits. The major constraints are
 * texture memory, main memory, and main memory-to-texture memory bandwidth.
 * Each of them can entirely be specified by the application, at any time.
 *
 * It queries
 * the SoLDMTileManager for main memory constraints and also queries the SoLDMNodeFrontManager for
 * texture memory and bandwidth constraints.
 * The SoLDMTileVisitor queries the Resource Manager to know the tiles of which resolution
 * that must always be kept in main memory and tiles of which resolution the application never
 * wants to load.
 *
 * @SEE_ALSO
 * SoLDMLargeDataManagement,
 * SoLDMNodeFrontManager,
 * SoLDMTileManager.
 *
 */

SoEXTENDER_Documented class LDM_API SoLDMResourceManager : public SoLDMLargeDataManagement
{
public:
  /**
   * Constructor.
   */
  SoLDMResourceManager(SoDataSet* ds);

  /**
   * Destructor.
   */
  virtual ~SoLDMResourceManager();

private:
  static std::vector<SoLDMResourceManager*> m_resourceManagers; // list of all ResourceManager's

  /////////////////////////////////////////////////////////////////////////////
  // tile dimension, data size, texel size and data set dimension info
private:
  SbVec3i32 m_tileDimension;    // tile dimension, default is 64.
  int m_border;           // tile overlapping (0 or 1), default is 0.
  int m_dataSize;         // data size in bytes (1,2 or 4), default is 1.
  int m_texelSize;        // texel size in bits, default is 8.
                          // =8  for 8 bits indexed 3D textures
                          // =32 for RGBA 3D textures
                          // =24 for 8 bits indexed 2D textures
                          // =96 for RGBA 2D textures
  SbVec3i32 m_volDim;     // dataset dimension
  SbBool m_isParamsFixed; // force parameters to be fixed, if TRUE parameters won't changed automatically

SoEXTENDER public:
  /**
   * When using getData functions from #SoDataSet::SoLDMDataAccess, once a tile is unlocked by
   * the application (call to #SoDataSet::SoLDMDataAccess::releaseData), its weight will decrease
   * until the tile is weighted again by LDM. This function allows you to set how long
   * it takes for the tile for its weight to be divided by 2 (initial weight is 1). Default is 2 seconds.
   * The tile weight will be set to 0 when the weight becomes less than 0.05.
   */
  void setTileHalfLife(float timeInSec);
  /**
   * Returns tile half life.
   */
  float getTileHalfLife();
SoINTERNAL public:
  float m_decreaseWeightFactor;
  float m_tileHalfLife;
  float getDecreaseWeightFactor(){return m_decreaseWeightFactor;};

  /**
   * Sets maximum global amount of triangles allowed to be displayed.
   * The sum of each number of triangles allowed per data set (see SoLDMResourceParameters maxNumTriangles field)
   * must be less or equal than #getMaxVVizGlobalNumTriangles
   */
  static void setMaxVVizNumTriangles(int numTriangles);

  /**
   * Returns the maximum global amount of displayable triangles.
   */
  static int getMaxVVizNumTriangles();

  /**
   * Sets the data set associated with this manager.
   */
  inline void setDataSet(SoDataSet* ds);

  /** Number of allowed triangles */
  void setMaxNumTriangles(int numTriangles);

SoEXTENDER public:
  /**
   * Sets dimension of the tile stored in disk.
   */
  void setTileSize( SbVec3i32 tileDim );

  /**
   * Returns the tile dimension.
   */
  SbVec3i32  getTileSize() const;

  /**
   * @deprecated No longer used. Use getTileSize()
   */
  SoDEPRECATED int getTileDimension();

  /**
  * @deprecated No longer used. Use setTileSize( SbVec3i32 tileDim );
  */
  SoDEPRECATED void setTileSize( int dim );

  /**
   * Sets the tile overlapping flag.
   * The value can be 0 (no overlap) or >=1 (overlap). If 0, you may see a line
   * at the tile borders because no interpolation is done between the tiles.
   * If 1, interpolation is done at the borders.
   */
  void setOverlapping( int border );
  /**
   * Returns the tile overlapping flag.
   */
  int  getOverlapping();
  /**
   * Sets the size of the data in number of bytes.
   */
  void setDataSize( int dataSize );
  /**
   * Returns the data size in number of bytes.
   */
  int  getDataSize();
  /**
   * Sets the size of a texture element in bits(for instance, 32 if RGBA).
   */
  void setTexelSize( int texelSize );
  /**
   * Returns the size of a texture element in bits.
   */
  int  getTexelSize();
  /**
   * Sets the dimension of the data set.
   */
  void setVolumeDim( const SbVec3i32& dim );
  /**
   * Returns the dimension of the data set.
   */
  SbVec3i32 getVolumeDim();
  /**
   * By default, the parameters of a resource manager are automatically recalculated if the parameter
   * for another data set changes (to respect the global amount of resources).
   * If the fixed parameters flag is set to TRUE, the resources for this data set are not allowed to change.
   */
  void fixParams( SbBool flag);
  /**
   * Returns the fixed parameters flag.
   */
  SbBool isParamsFixed();

  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use setVolumeDim( const SbVec3i32& dim )
   */
  SoDEPRECATED void setVolumeDim( const SbVec3s& dim )
  {
    SbVec3i32 dimI32( dim[0], dim[1], dim[2] );
    setVolumeDim( dimI32 );
  }

  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // disk to main memory controls
SoEXTENDER public:
  enum LoadPolicy {
    NO_USER_INTERACTION,   // Only load when no user interaction
    ALWAYS,                // Always load
    NEVER                  // Never. No loading happens anymore. Allows suspending loading process.
  };

  static void        setMonitoringAmount(int);
  static int         getMonitoringAmount();

SoINTERNAL public:
  int         getNumTileToTime();

private:
  LoadPolicy m_loadPolicy; // load policy
  float      m_movingTimeOut; //keep not loading for timeOut sec after the user
                                //stoped interacting.

  static int m_loadNotificationRate;
  static int m_memToLoad;

  //number of IO:
  static unsigned int m_numIO;
  static SbBool       m_isMultiIO;

SoEXTENDER public:
  /**
   *
   * Sets whether LDM should use multiple loading threads or not.
   * Default is TRUE.
   */
  static void   setMultiIO(SbBool on);
  /**
   *
   * Returns TRUE if LDM uses multiple loading threads.
   */
  static SbBool getMultiIO();

  /**
   * Sets how many loading threads to use if multiIO mode is on.
   * Default is 4.
   */
  static void         setNumIO(unsigned int numIO);

  /**
   *
   * Returns current number of loading threads.
   */
  static unsigned int getNumIO();

  /**
   * Sets loading behavior. Passing NO_USER_INTERACTION means the asynchronous loading
   * thread will only load when the user does not interact with the scene (i.e., the
   * application idles).
   *
   * The loading occurs as long as there is something to load if ALWAYS is passed.
   * No loading occurs if NEVER is passed.
   * Default is NO_USER_INTERACTION.
   */
  void setLoadPolicy( LoadPolicy loadPolicy );
  /**
   * Returns the current #LoadPolicy value.
   */
  LoadPolicy getLoadPolicy();

  /*
   * Sets the time (in seconds) for which VViz does not load once a user
   * stoped interaction
   * Consulted only in NO_USER_INTERACTION mode
   * Default is 0.3 seconds.
   */
  void setMovingTimeOut(float);
  /*
   * gets the time for which VViz should not load once a user
   * stoped interaction
   */
  float getMovingTimeOut();

  /**
   * When @B rate@b tiles have been loaded in main memory, a redraw will be scheduled.
   * The default is 50 tiles, which means, for example, if tileSize is 64x64x64,
   * the system will be notified that new data has arrived every 13MB.
   */
  static void setLoadNotificationRate( int rate );
  /**
   * Returns notification rate.
   */
  static int getLoadNotificationRate();

  /////////////////////////////////////////////////////////////////////////////
  // main memory controls
private:
  static int m_maxVVizMainMemory; // amount in Kb of main memory allowed for all the LDM datasets, default is 256 MB.
  static int m_sumMaxMainMemory;  // sum in Kb of all the amounts of main memory per dataset.
  int m_maxMainMemory;            // amount in Kb of main memory allowed for the corresponding dataset.

  int m_numTilesInMainMem;        // num tiles allowed in main memory = m_maxMainMemory / tileSize

SoEXTENDER public:
  /**
   *
   * This function allows you to synchronously unload the data if it needs to be refetched.
   */
  void invalidateData();

  /**
   * Sets maximum global amount of main memory in MB. All data sets will share this amount of memory.
   * The sum of each main memory space allowed per data set (#setMaxMainMemory)
   * must be less or equal than #getMaxVVizMainMemory.
   */
  static void setMaxVVizMainMemory( int maxMainMemory ); // set/get the allowed main memory in MB

  /**
   * Returns the maximum global amount of main memory in MB.
   */
  static int  getMaxVVizMainMemory();                    // for all the LDM datasets.

  /** @deprecated No longer used. Use SoDataSet's field maxMainMemory
  */
  void setMaxMainMemory( int maxMainMemory );            // set/get the allowed main memory in MB

  /** @deprecated No longer used. Use SoDataSet's field maxMainMemory
  */
  int  getMaxMainMemory();                               // for the corresponding dataset.

  /** @deprecated No longer used. Use SoDataSet's field maxTilesInMainMem
  */
  void setMaxTilesInMainMem( int numTiles );             // set/get the allowed number of tiles in main memory,

  /** @deprecated No longer used. Use SoDataSet's field maxTilesInMainMem
  */
  int  getMaxTilesInMainMem();                           // equivalent to the previous method but more accurate.


private:
  static void updateMainMemParams( int mem, SoLDMResourceManager* exclude );
  static void updateNumTilesInMainMem();

  static void updateTex3LoadRateParams( int rate, SoLDMResourceManager* exclude );

  static void updateTex2LoadRateParams( int rate, SoLDMResourceManager* exclude );

  /** update number of 2D Textures for each ressources */
  static void updateMax2DTextures( int numTextures, SoLDMResourceManager* exclude );

  /** update number of 2D Textures for each ressources */
  static void updateSumMax2DTextures();

  /** update number of triangles for each ressources */
  static void updateNumTrianglesParams(int triangles, SoLDMResourceManager* exclude);

  /**
   * @TOBEREVIEWED
   * Returns the list of resource managers to update.
   * A SoLDMResourceManager can be updated in case it's SoVolumeData has been rendered once.
   */
  static const std::vector<SoLDMResourceManager*>& getRSToUpdate();

  /////////////////////////////////////////////////////////////////////////////
  // texture memory controls (for SoVolumeRender, SoVolumeGeometry)
private:
  static int m_maxVVizTexMemory; // amount in Kb of texture memory allowed for all the LDM datasets, default is 48 MB.
  static int m_sumMaxTexMemory;  // sum in Kb of all the amounts of texture memory per dataset.

  int m_maxTexMemory;            // amount in Kb of texture memory allowed for the corresponding dataset.

  int m_numTilesInTexMem;        // num tiles allowed in texture memory = m_maxTexMemory / tileTexSize

SoEXTENDER public:
  /**
   * Sets the allowed global texture memory in MB (for all data sets). Default is 48 MB.
   * The sum of each texture memory space allowed per data set (#setMaxTexMemory)
   * must be less or equal than #getMaxVVizTexMemory.
   */
  static void setMaxVVizTexMemory( int maxTexMemory );
  /**
   * Returns the allowed global texture memory in MB (for all data sets).
   */
  static int  getMaxVVizTexMemory();

  /** @deprecated No longer used. Use SoDataSet's field maxTexMemory
   */
  void setMaxTexMemory( int maxTexMemory );

  /** @deprecated No longer used. Use SoDataSet's field maxTexMemory
   */
  int  getMaxTexMemory();

  /** @deprecated No longer used. Use SoDataSet's field maxTilesInTexMem
   */
  void setMaxTilesInTexMem( int numTiles );

  /** @deprecated No longer used. Use SoDataSet's field maxTilesInTexMem
   */
 int  getMaxTilesInTexMem();

private:
  static void updateTexMemParams( int mem, SoLDMResourceManager* exclude );
  static void updateNumTilesInTexMem();


  /////////////////////////////////////////////////////////////////////////////
  // texture 3 memory load rate controls (for SoVolumeRender, SoVolumeGeometry)
private:
  static int m_tex3VVizLoadRate;  // num tiles allowed to load in tex mem per frame for all the LDM datasets, default is 1.
  int m_tex3LoadRate;             // num tiles allowed to load in tex mem per frame for the corresponding dataset.

SoEXTENDER public:
  /**
   * Sets the total number of tiles allowed to be loaded in texture memory per frame
   * (for all data sets). Default is 1.
   */
  static void setTex3VVizLoadRate( int loadRate );
  /**
   * Returns total number of tiles allowed to be loaded in texture memory per frame
   * (for all data sets).
   */
  static int  getTex3VVizLoadRate();

  /** @deprecated No longer used. Use SoDataSet's field tex3LoadRate
   */
  void setTex3LoadRate( int loadRate );

  /** @deprecated No longer used. Use SoDataSet's field tex3LoadRate
   */
  int  getTex3LoadRate();

  /////////////////////////////////////////////////////////////////////////////
  // texture 2 memory controls (for SoOxxSlice, SoVolumeSkin)
private:
  static int s_sumMaxVViz2DTextures;
  static int s_maxVViz2DTextures; // num 2D tiles allowed in texture memory for all LDM datasets, default is 256.
  int m_num2DTextures;            // num 2D tiles allowed in texture memory for the corresponding primitives.

SoEXTENDER public:
  /**
   * Sets maximum global numbers of 2D Textures allowed to be displayed.
   * The sum of each number of 2D textures allowed per data set (see SoLDMResourceParameters max2DTextures  field)
   * must be less or equal than #getMaxVVizGlobal2DTextures
   */
  static void setMaxVViz2DTextures(int numTextures);

  /**
   * Returns the maximum global numbers of 2D Textures displayable.
   */
  static int getMaxVViz2DTextures();

  /** @deprecated No longer used. Use SoDataSet's field max2DTextures
   */
  void setMax2DTextures( int numTextures );

  /** @deprecated No longer used. Use SoDataSet's field max2DTextures
   */
  int getMax2DTextures();


  /////////////////////////////////////////////////////////////////////////////
  // texture 2 memory load rate controls (for SoOxxSlice, SoVolumeSkin)
private:
  static int m_tex2VVizLoadRate;  // num tiles allowed to load in tex mem per frame for all the LDM datasets, default is 64.
  int m_tex2LoadRate;             // num tiles allowed to load in tex mem per frame for the corresponding dataset.

SoEXTENDER public:
  /**
   * Sets the total number of tiles allowed to be loaded in texture memory per frame
   * (for all data sets). Default is 1.
   */
  static void setTex2VVizLoadRate( int loadRate );
  /**
   * Returns total number of tiles allowed to be loaded in texture memory per frame
   * (for all data sets).
   */
  static int  getTex2VVizLoadRate();

  /** @deprecated No longer used. Use SoDataSet's field tex2LoadRate
   */
  void setTex2LoadRate( int loadRate );

  /** @deprecated No longer used. Use SoDataSet's field tex2LoadRate
   */
  int  getTex2LoadRate();


  /////////////////////////////////////////////////////////////////////////////
  // resolution threshold controls
private:
  int m_minResThreshold;       // minimum resolution required (0:1/1, 1:1/2, 2:1/4, ...), default is 100.
  int m_maxResThreshold;       // maximum resolution allowed (0:1/1, 1:1/2, 2:1/4, ...), default is 0.

SoEXTENDER public:
  /** @deprecated No longer used. Use SoDataSet's field minResolutionThreshold
   */
  void setMinResolutionThreshold( int threshold = MIN_RES_THRESHOLD );   // don't unload above this threshold.

  /** @deprecated No longer used. Use SoDataSet's field minResolutionThreshold
   */
  int  getMinResolutionThreshold();

  /** @deprecated No longer used. Use SoDataSet's field maxResolutionThreshold
   */
  void setMaxResolutionThreshold( int threshold );   // don't load below this threshold.

  /** @deprecated No longer used. Use SoDataSet's field maxResolutionThreshold
   */
  int  getMaxResolutionThreshold();

SoINTERNAL public:
  /*
  Those set of functions returns the sum of resources of all data sets registered
  */
  int  getSumOfMaxTilesInTexMem();
  int  getSumOfTex3LoadRate();
  int  getSumOfMax2DTextures();
  int  getSumOfTex2LoadRate();
  void getSumOfMemAndTileSize(uint64_t &mem, int& tileSize);
  void getSumOfNumTilInMem( uint64_t &maxTileInMem );
  unsigned int getSumOfMaxNumTriangles();
  int getMaxNumTriangles();
  void updateParamFirstRender();
  static void computeInternalCounters();

  void setIdealTextFrontCb( SoLDMTexFrontCB *func, void* userData = NULL);
  void idealTexFrontReached();
  SoLDMTexFrontCB* m_callbackFunc;
  void* m_userData;
  SoDataSet* getDataSet() { return m_ds; };
  bool checkMaxTile() { return m_checkMaxTile; };

 private:
  float getDataTileSizeInKB();
  float getTexTileSizeInKB();

  SoDataSet* m_ds;

  /** Number of allowed triangles in the whole app */
  static int s_maxVVizNumTriangles;

  /** sum of all existing dataset */
  static int s_sumMaxVVizNumTriangles;

  /** Number of allowed triangles */
  int m_maxNumTriangles;

  /** 
    Check if maxTileInMem must be taken in account
    for loading management 
  */
  bool m_checkMaxTile;

  // List of resourceManager to take in account for 
  // resource sharing
  static std::vector<SoLDMResourceManager*> s_rsToUpdate;

  // Store the number of mask associated to each data set
  static  std::map<SoLDMMediator*, int> m_maskPerMediator;

  // store the number of volume data that are not volumeMask.
  static size_t m_nbVolumeData;
};

/*****************************************************************************/
void
SoLDMResourceManager::setDataSet(SoDataSet* ds)
{
  m_ds = ds;
}


#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_LDM_RESOURCE_MANAGER_
