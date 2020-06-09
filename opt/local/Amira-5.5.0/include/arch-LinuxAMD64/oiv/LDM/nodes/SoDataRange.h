/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DATA_RANGE__
#define  _SO_DATA_RANGE__

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFDouble.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFShort.h>

#include <LDM/nodes/SoDataSet.h>

class SoConversion;

/**
 * @LDMEXT Range of data values to be mapped to the color map.
 *
 * @ingroup LDMNodes
 *
 * @DESCRIPTION
 *
 * This node allows you to specify the range of data values in a data set
 * (SoDataSet or SoVolumeData) to be mapped to the color map (SoTransferFunction).
 *
 * By default VolumeViz maps the entire range of the voxel's data type
 * (e.g. 0..65535 for unsigned short) into the colormap.  This is often
 * correct for byte (8 bit) voxels, but seldom correct for 16 bit voxels
 * and never correct for floating point voxels. Use an SoDataRange node
 * to specify the actual (or desired) range of data values to be mapped.
 * - The voxel size in bytes can be queried using the SoDataSet method getDataSize().
 * - The min and max values for the data set can be queried using the SoDataSet
 *   method getMinMax(). @BR
 *   Note that this method might force VolumeViz to load the entire data set if the
 *   volume reader for that format does not implement the getMinMax query. Normally
 *   for an LDM format data set, the min and max values are stored in the LDM header.
 *   For a non-LDM data set, if a filename and/or reader have been specified and the
 *   data set has not yet been loaded, VolumeViz will load the entire data set to 
 *   compute the min and max values. For a large data set this may take a long time.
 *
 * When using multiple volumes, a single SoDataRange node can be used to specify the
 * data range for all volumes or each volume can have its own independent data
 * range. In the second case create one SoDataRange node for each volume and set the 
 * #dataRangeId equal to the SoDataSet::dataSetId of the corresponding volume.
 *
 * NOTE: Changing the data range may require VolumeViz to recreate the data
 * textures on the GPU.  This is necessary to maximize use of the available
 * bits of precision on the GPU.  This operation may be slow for a large data set.
 *
 * @FILE_FORMAT_DEFAULT
 * DataRange{
 *    @TABLE_FILE_FORMAT
 *    @TR dataRangeId           @TD 1
 *    @TR min                   @TD 0
 *    @TR max                   @TD 0
 *    @TR mapOnFullColorRange   @TD TRUE
 *    @TABLE_END
 * }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction,
 * SoPickAction,
 * SoWriteAction,
 * SoGetBoundingBoxAction @BR
 * Sets a data range in the current traversal state.
 *
 * @SEE_ALSO
 *    SoDataSet,
 *    SoTransferFunction
 *
 *
 */

class LDM_API SoDataRange : public SoNode {
  SO_NODE_HEADER( SoDataRange );

public:
  /**
   * Constructor.
   */
  SoDataRange();

 /**
  *
  * This field allows the use of multiple data range for the same geometry.
  * By default all data range nodes are initialized to a data range id of 1.
  * If you want to use multiple data ranges, different data range ids must be assigned.
  * The data range id is only used in a render compositing scheme (see SoDataSet).
  *
  * @FIELD_SINCE_OIV 6.1.2
  */
  SoSFShort dataRangeId;

  /**
   * Minimum data value of the data range.
   * If #min is equal to #max, this node is ignored.
   */
  SoSFDouble min;

  /**
   * Maximum data value of the data range.
   */
  SoSFDouble max;

  /**
   * Specifies how to map data values that are outside of the data range.
   * If mapOnFullColorRange is TRUE (default), then any data values less than or equal
   * to  the #min data value are mapped to the first color entry and any data values
   * greater than or equal to the #max data value are mapped to the last color entry.
   *
   * If mapOnFullColorRange is FALSE, then any data value less than
   * #min data value is mapped to the first color entry and the #min data value
   * is mapped to the second color entry; any data value greater than
   * the #max data value is mapped to the last color entry and the #max data value is mapped
   * to the next to the last color entry.
   */
  SoSFBool mapOnFullColorRange;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  /**
   * Function that compute datarange to index for generic bufferObject.
   * if both input and ouput are CudaBufferObject then it will call the 
   * CUDA optimized version, in all other case buffer will be map to cpu
   * and cpu version will be used
   * LIMITATION: only UNSIGNED_BYTE/UNSIGNED_SHORT dataTypeDst is supported 
   */
  static void mapDataRangeToIndex(
    const SoDataSet::DataType dataTypeSrc, SoBufferObject* sourceBufferObject,
    const SoDataSet::DataType dataTypeDst, SoBufferObject* targetBufferObject,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset
    );

  
  /**
   * Function that compute datarange to RGBA for generic bufferObject.
   * if both input and ouput are CudaBufferObject then it will call the 
   * CUDA optimized version, in all other case buffer will be map to cpu
   * and cpu version will be used.
   * LIMITATION: only UNSIGNED_INT32 (for RGBA) dataTypeDst is supported 
   */
  static void mapDataRangeToRgba(
    const SoDataSet::DataType dataTypeSrc, SoBufferObject* sourceBufferObject,
    const SoDataSet::DataType dataTypeDst, SoBufferObject* targetBufferObject,
    const double dataRangeMin, const double dataRangeMax, const bool dataRangeMap,
    const int shift, const int offset,
    SoBufferObject *rgba, const int numRgba
    );

  /**
   * Function that convert data to texture index for generic bufferObject.
   * if both input and ouput are CudaBufferObject then it will call the 
   * CUDA optimized version, in all other case buffer will be map to cpu
   * and cpu version will be used
   * LIMITATIONS: 
   * - only UNSIGNED_BYTE/UNSIGNED_SHORT dataTypeDst is supported 
   * - FLOAT dataTypeSrc is not supported
   */
  static void mapDataToIndex(
    const SoDataSet::DataType dataTypeSrc, SoBufferObject* sourceBufferObject,
    const SoDataSet::DataType dataTypeDst, SoBufferObject* targetBufferObject,
    const int numSigBits, const int shift, const int offset
    );

 
  /**
   * Function that convert data to rgba texture for generic bufferObject.
   * if both input and ouput are CudaBufferObject then it will call the 
   * CUDA optimized version, in all other case buffer will be map to cpu
   * and cpu version will be used
   * LIMITATIONS: 
   * - only UNSIGNED_INT32 (for RGBA) dataTypeDst is supported 
   * - FLOAT dataTypeSrc is not supported
   */
  static void mapDataToRgba(
    const SoDataSet::DataType dataTypeSrc, SoBufferObject* sourceBufferObject,
    const SoDataSet::DataType dataTypeDst, SoBufferObject* targetBufferObject,
    const int numSigBits, const int shift, const int offset,
    SoBufferObject *rgba, const int numRgba
    );

 
SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);

protected:
  // Destructor
  virtual ~SoDataRange();

private:

  static SoConversion* s_conversion;
};

#endif // _SO_DATA_RANGE__
