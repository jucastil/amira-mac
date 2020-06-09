/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Sep 2008)
**=======================================================================*/


#ifndef  _SO_VOLUME_TRANSFORM_
#define  _SO_VOLUME_TRANSFORM_

#include <VolumeViz/nodes/SoVolumeRendering.h>
#include <LDM/SoLDMTileID.h>


#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFInt32.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/list>
#include <Inventor/STL/map>

class SoVolumeData;
class SoGLRenderAction;
class SoCallbackAction;
class SoWriteAction;
class SoState;
class SoPerfCounter;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @VREXT Transform data before texture creation.
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * The SoVolumeTransform node allows an application to apply a defined computation
 * on LDM data tiles just before they are sent to the GPU.  There are several other 
 * ways to apply a computation to LDM tiles, that are applied at different stages 
 * of the pipeline.  The SoLDMDataTransform class for example (see the dataTransform 
 * field of SoDataSet) applies a computation to each LDM tile requested from the 
 * volume reader before the tile is stored in system memory. This can be used to 
 * create multiple data sets from a single input (e.g. on disk) data set, but has the
 * drawback that each resulting data set must be stored in system memory. 
 * SoVolumeTransform can be used to create multiple data sets from a single data set
 * in system memory and does not require storing the created data sets in system memory
 * (only on the GPU).
 *
 * A cache mechanism, local to each instance of SoVolumeTransform, allows storing the
 * computed tiles for later reuse. The size of this cache (number of tiles to cache)
 * can be specified using the #cacheSize field. We recommend setting the cacheSize to
 * the number of tiles needed to display the biggest expected slice.  As an example,
 * for a dataset of size 128x512x1024 with a tile size equal to 128, the biggest slice
 * size is 512x1024. So 4x8 = 32 LDM tiles are needed for rendering and therefore a
 * cacheSize of 32 (tiles) is needed to avoid computing the same tile multiple times.
 * The apply method can retrieve the transformed data for other tiles from the cache
 * and can explicitly add the transformed data for other tiles to the cache.
 *
 * SoVolumeTransform works on tiles (not slices or volumes). If a compute function
 * needs data from other tiles, the application may use the SoLDMDataAccess API to get
 * that data. (This is another difference from SoLDMDataTransform, which does not allow
 * using the LDM data access API.)
 *
 * Multiple SoVolumeTransform nodes may be applied to the same SoDataSet. The transforms
 * are applied in the order of their appearance in the scene graph.  SoVolumeTransform
 * nodes may also be applied only to a specific SoDataSet using the #volumeTransformId field.
 * If this field is zero (the default), the transform is applied to all subsequent data set
 * nodes. Else the transform is only applied to data sets whose dataSetId field contains
 * the same value as the volumeTransformId.
 *
 * SoVolumeTransform is based on the Open Inventor computing framework and uses the
 * SoBufferObject classes to abstract and manage blocks of memory. The application can use
 * different devices to implement the computation, and manage input tiles and output tiles
 * stored on different devices.
 *
 * As mentioned previously, SoVolumeTransform can be used to create multiple data sets
 * on-the-fly from a single data set in system memory.  In this case the same data set node
 * will be instanced multiple times in the scene graph (although its data will only be
 * loaded in system memory once), but we still need to assign each data texture a unique id
 * so the shader program can access them uniquely.  This is done using SoDataSetId nodes to
 * specify a different data set id for each instance of the data set node. If an SoDataSetId
 * node is in the traversal state when a data set node is traversed, the dataSetId field is
 * ignored and the id from the SoDataSetId node is used.
 *
 * To implement a computation, the application must derive a new class from SoVolumeTransform
 * and (at least) implement the #apply() method, which performs the actual computation.  This
 * method is called with parameters that give access to information about the data set and the
 * specific tile being computed.  In a simple case you might only need to access the buffer object.
 *
 * It may also be useful to implement the isValid() and getTransformedMinMax() methods.  The
 * isValid() method will be called for each tile immediately before the apply() method.  If
 * this method returns FALSE, then the apply() method will not be called for that tile.  If
 * the application can compute or estimate the min and max values of the computed data set,
 * then it should implement the getTransformedMinMax() method so VolumeViz does not do
 * unnecessary work to compute these values.
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeTransform {
 *    @TABLE_FILE_FORMAT
 *       @TR volumeTransformId  @TD 0
 *       @TR cacheSize          @TD 1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction @BR
 * Sets volume transform parameters in the traversal state.
 *
 * @SEE_ALSO
 * SoDataSet, SoDataSetId, SoVolumeData
 */

class VOLUMEVIZ_API SoVolumeTransform : public SoNode
{
  SO_NODE_ABSTRACT_HEADER( SoVolumeTransform );

 public:
 /**
  * Allows the transform to be applied to all or one specific data set. @BR
  * A volume transform id of 0 means that this transform will be applied to
  * all subsequent data sets. A value greater than 0 means that this transform
  * will only be applied to data sets with a matching data set id.  For example,
  * if the transform id is 1, the transform will only be applied to data sets
  * whose data set id is also 1.  The default value is 0.
  */
  SoSFShort volumeTransformId;

  /**
   * Size of the computed tile cache for this transform. @BR
   * This is the number of computed tiles that will be cached and will not
   * need to be recomputed. Choose a value to balance between memory usage
   * and computing time. Default is 1.
   */
  SoSFInt32 cacheSize;

  /**
   * Constructor
   */
  SoVolumeTransform();

  /**
   * Apply in-place transformation to the specified dataset tile. @BR
   * The application must implement this method in the derived class.
   *
   * @param state Current traversal state.
   * @param p Dataset/id pair (p.first is an SoDataSet*, p.second is a dataSetId)
   *          Using the SoDataSet pointer you can obtain, for example, the actual data
   *          type of the data:
   *          \oivnetdoc
   *            \code
   *            SoDataSet DataSet = p.First;
   *            SoDataSet.DataTypes type = DataSet.GetDataType();
   *            \endcode
   *          \else
   *            \code
   *            SoDataSet *pDataSet = p.first;
   *            SoDataSet::dataType type = pDataSet->getDataType();
   *            \endcode
   *          \endoivnetdoc
   * @param bufferObject The buffer that contains the data
   * @param id Tile to be transformed
   *           Using this id and the SoDataSet pointer you can obtain, for example, 
   *           the actual position of the tile in the volume:
   *           \oivnetdoc
   *             \code
   *             SbBox3i32 tilePos = 
   *               DataSet.GetNodeFrontManager().GetTilePos( id );
   *             \endcode
   *           \else
   *             \code
   *             SbBox3i32 tilePos = 
   *               pDataSet->getNodeFrontManager()->getTilePos( id );
   *             \endcode
   *           \endoivnetdoc
   */
  virtual void apply(SoState *state, const SoLDM::DataSetIdPair& p, SoBufferObject *bufferObject , const SoLDMTileID &id) = 0;

  /**
   * Should return TRUE if the given parameters are valid for this compute function. @BR
   * If not the #apply function will not be called for this tile. The interpretation of
   * "valid" is up to the application.  For example, you could use this function to skip
   * computing for low resolution tiles.
   *
   * @param state Current traversal state.
   * @param p Dataset/id pair (p.first is an SoDataSet*, p.second is a dataSetId)
   * @param bufferObject The buffer that contains the data
   * @param id Tile to be transformed
   */
  virtual SbBool isValid(SoState *state, const SoLDM::DataSetIdPair& p, SoBufferObject *bufferObject , const SoLDMTileID &id);

  /**
   * Based on min max of the input data, this function should return the expected
   * data range of the result (transformed) data.
   */
  virtual inline void getTransformedMinMax(double &min, double &max);

  /** 
   * Returns the previously transformed data for a specific tile. @BR
   * This method is useful if the apply method depends on transformed
   * data for other tiles, for example adjacent tiles.  If the needed
   * tiles have already been transformed and saved in the cache, then
   * it is not necessary to recompute them. Returns NULL if the tile
   * was not found in the cache.  See also the #cacheSize field.
   */
  SoBufferObject* getFromCache(const SoLDMTileID &tileID);

  /** 
   * Add the transformed data for a specific tile to the cache. @BR
   * It is not necessary to call this method for the current tile, it will be
   * added to the cache automatically. This method is useful if the apply 
   * method computes transformed data for other tiles.  These tiles can be
   * saved in the cache to avoid recomputing them later.
   */
  void addInCache(const SoLDMTileID &tileID, SoBufferObject *bufferObject);

  //------------------------------------------------------------------------------

 SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);

  //------------------------------------------------------------------------------

 SoINTERNAL public:

  /**
   * Apply a list of volume transforms in the given order.
   */
  static SoBufferObject* applyListFunc(std::vector<SoVolumeTransform*> volumeTransformList, SoState *state, const SoLDM::DataSetIdPair& p, SoBufferObject *bufferObject , const SoLDMTileID &id);

  /** Register node type in database */
  static void initClass();

  /** UnRegister node type in database */
  static void exitClass();

  /** Initialize Thread local storage structure. */
  SB_THREAD_TLS_HEADER();

 protected:
  /**
   * Destructor
   */
  virtual ~SoVolumeTransform();

  /** Notification callback */
  virtual void notify(SoNotList * list);

  /**
   * thread specific variables
   */
  struct MTstruct {
    SoBufferObject *tmpBuffer;
  };

 private:
   /** Performance counters. */
   static SoPerfCounter *m_volumeTransformTimeCounter;
   static SoPerfCounter *m_volumeTransformDataCounter;

  /** Cache management */
  SbThreadMutex *m_cacheMutex;
  void resizeCache(const int newSize);

  typedef std::pair<SoLDMTileID,SoBufferObject*> TTransformedTileCacheEntry;
  typedef std::list<TTransformedTileCacheEntry> TTransformedTileCache;
  TTransformedTileCache transformedTileCache;
};

// Inline functions implementation
void SoVolumeTransform::getTransformedMinMax(double & , double &)
{
  // keep min and max unchanged by default.
}

#if defined(_WIN32)
#pragma warning( pop )
#pragma warning(disable:4251)
#endif

#endif // _SO_VOLUME_TRANSFORM_
