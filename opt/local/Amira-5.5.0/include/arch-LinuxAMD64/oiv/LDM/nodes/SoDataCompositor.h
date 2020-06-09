/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Dec 2005)
**=======================================================================*/


#ifndef  _SO_DATA_COMPOSITOR__
#define  _SO_DATA_COMPOSITOR__

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbDataType.h>
#include <Inventor/SbVec.h>
#include <LDM/SoLDM.h>

class SoBufferObject;
class SoCpuBufferObject;

/**
 * @LDMEXT Data set compositor node
 *
 * @ingroup LDMNodes
 *
 * @DESCRIPTION
 *
 * The SoDataCompositor node allows you to combine multiple data sets
 * in memory instead of having to store the combined data sets on disk.
 * For example, it can be used to visualize the result of the difference between two data sets.
 * Notice: The SoDataCompositor cannot be used for unary operation (the number of data set
 * used with a data compositor must be stricly greater than one).
 * Unary operation can be performed using the SoLDMDataTransformCB (see SoDataSet node).
 *
 * NOTE: This node is only useful in LDM mode.
 *
 * A number of rules apply to the use of SoDataCompositor:
 * - The SoDataCompositor node and SoDataSet nodes must be children of an
 *   SoMultiDataSeparator node (an ordinary SoSeparator will not work correctly).
 * - The SoDataCompositor node must be inserted before the SoDataSet nodes in the scene graph.
 * - No rendering primitives (e.g., SoOrthoSlice, SoVolumeRender) are allowed between the
 * SoDataSet nodes that are used for the composition.
 * - A SoDataSet node
 * used for data compositing should not be referenced twice in the scene graph.
 * Another data set node pointing to the same file should rather be instantiated).
 * - All nodes needed to realize the compositing must be under the same SoSeparator node.
 * - No other nodes must be under this SoSeparator node.
 * - It is not possible to mix SoDataSet nodes used for compositing with SoDataSet nodes used
 * for normal rendering under the same SoSeparator.
 *
 * For example, to realize the difference of two data sets, only the SoDataCompositor node,
 * the SoDataSet nodes, and the rendering primitive node must be inserted under the 
 * SoMultiDataSeparator node created to handle the composition.
 *
 * Each SoDataSet following the compositor must have the same exact dimensions. However,
 * the data set nodes can have different voxel data types (bytes per voxel).
 * The final voxel data type is specified by
 * the data compositor node through the #dataType field.
 *
 * If the #rgbaMode field is set to TRUE, then #dataType and #numSigBits are ignored, 
 * and the output data is generated as UNSIGNED_INT32 with 32 significant bits.
 *
 * The SoDataCompositor node offers different default composition operators (see #preDefCompositor) but it is
 * possible to create a customized operator by subclassing the node and redefining one of the #compose
 * methods.
 * To use the custom operator, the #preDefCompositor field must be set to NONE.
 *
 * LIMITATION: This node is available for VolumeViz but not yet available for ReservoirViz.
 *
 * @FILE_FORMAT_DEFAULT
 * DataCompositor{
 *    @TABLE_FILE_FORMAT
 *    @TR dataType           @TD UNSIGNED_BYTE
 *    @TR numSigBits         @TD 0
 *    @TR rgbaMode           @TD FALSE
 *    @TR preDefCompositor   @TD MINUS
 *    @TR convert            @TD TRUE
 *    @TABLE_END
 * }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction,
 * SoWriteAction,
 * SoGetBoundingBoxAction,
 * SoPickAction @BR
 * Sets data compositor parameters in the traversal state.
 *
 * @SEE_ALSO
 * SoDataSet, SoLDMDataTransform, SoVolumeTransform
 *
 *
 */

class LDM_API SoDataCompositor : public SoNode {
  SO_NODE_HEADER( SoDataCompositor );

 public:

  /** 
   * Constructor
   * [OIVJAVA-WRAPPER-CUSTOM-CODE]
   */
  SoDataCompositor();

  /**
   * Supported data types
   */
  enum DataType {
    /** unsigned byte */
    UNSIGNED_BYTE  = SbDataType::UNSIGNED_BYTE,
    /** unsigned short */
    UNSIGNED_SHORT = SbDataType::UNSIGNED_SHORT,
    /** unsigned int (32bits) */
    UNSIGNED_INT32 = SbDataType::UNSIGNED_INT32,
    /** signed byte */
    SIGNED_BYTE  = SbDataType::SIGNED_BYTE,
    /** signed short */
    SIGNED_SHORT = SbDataType::SIGNED_SHORT,
    /** signed int (32bits) */
    SIGNED_INT32 = SbDataType::SIGNED_INT32,
    /** float */
    FLOAT = SbDataType::FLOAT
  };

  /**
   * Data type of the final composed buffer.
   * Use enum #DataType. Default is UNSIGNED_BYTE.
   * NOTE: If #rgbaMode is TRUE, this field is ignored and the output buffer is UNSIGNED_INT32.
   */
  SoSFEnum dataType;

  /** 
   * Number of significant bits of the final composed datum. @BR
   * Default is 0 meaning all bits are significant.
   * If this field is set to 24 on an UNSIGNED_INT32 data type, only the lowest 24 bits
   * will be taken into account when creating textures.
   * @NOTES: If #rgbaMode is TRUE, this field is ignored and all 32 bits are significant.
   */
  SoSFShort numSigBits;

  /**
   * Final composed buffer contains RGBA values (default is FALSE). @BR
   * If set to TRUE then the #dataType and #numSigBits fields are ignored and the
   * output data is UNSIGNED_INT32 with 32 significant bits.
   */
  SoSFBool rgbaMode;

  /**
   * Predefined compositor.
   */
  enum PreDefCompositor {
    /** none */
    NONE  ,
    /** minus */
    MINUS,
    /** add */
    ADD,
    /** multiply */
    MULTIPLY
  };

  /**
   * Predefined composition method.
   * Use enum #PreDefCompositor. Default is MINUS.
   * If preDefCompositor is set to NONE, then LDM will call one of the virtual compose
   * methods. Otherwise it will use the specified composition operator.
   * 
   */
  SoSFEnum preDefCompositor;

  /**
   * If the convert field is TRUE, LDM will call the compose method after automatically
   * converting data to the final data type if necessary. Otherwise the compose method
   * is called without conversion and
   * the application is responsible for handling the conversion.
   * Default is TRUE.
   */
  SoSFBool convert;

  /**
   * The compose method can be overridden in a subclass to specify a custom composition.
   * Inputs are:
   * - numDataSet is the number of data sets to compose.
   * - tileDimension specifies the dimension of the tile (same for each data set).
   * - vdid is an array of integers giving the id of each data set (set by the dataSetId field
   *   of the SoDataSet node).
   * - inputBuffer is an array of buffers containing the tile of each data set. For example,
   * inputBuffer[0] is the data corresponding to the data set with id vdid[0] .
   * Each tile has already been converted to the final data type (dataType field) if necessary.
   * - outputBuffer is the buffer to fill with the composed data (allocated by LDM, filled
   * in by the compose method).
   * The outputBuffer is of type dataType (number of bytes returned by getDataSize).
   *
   * NOTE: For compatibility purposes, if this method is not redefined then the version with 
   * void* parameters instead of SoBufferObject* will be used.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY{numDataSet},ARRAY{numDataSet},IN]
   */
  virtual void compose(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoBufferObject* outputBuffer);
  
  /** 
   * @deprecated No longer used. Use the SoBufferObject version.
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED virtual void compose(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, void** inputBuffer,
               void* outputBuffer);

  /**
   * Same as the compose method described above with one additional parameter:
   * dataTypes is an array of SoDataSet::dataType giving the data type of each input
   * buffer (e.g., inputBuffer[0] is of data type dataTypes[0]).
   *
   * This compose method is called if the #convert field is set to FALSE.
   * In this case LDM does not automatically convert data to the final data type,
   * and the application is responsible for doing the conversion if necessary.
   *
   * NOTE: For compatibility purposes, if this method is not redefined then the version with 
   * void* parameters instead of SoBufferObject* will be used.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY{numDataSet},ARRAY{numDataSet},ARRAY{numDataSet},IN]
   */
  virtual void compose(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer, SoDataCompositor::DataType* dataTypes,
               SoBufferObject* outputBuffer);

  /**
   * @deprecated No longer used. Use SoBufferObject version.
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED virtual void compose(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, void** inputBuffer, SoDataCompositor::DataType* dataTypes,
               void* outputBuffer);

  /**
  * Returns TRUE if the given data type is a signed integer data type. @BR
  * Note: If #rgbaMode is TRUE, then the data is considered to be UNSIGNED_INT32 (not signed).
  */
  static SbBool isDataSigned( DataType dataType );

  /**
   * Returns number of bytes for output datum.
   */
  int getDataSize() const;

  /**
   * Returns the output number of significant bits.
   */
  int getNumSigBits() const;

  /**
   * Returns the output data type.
   */
  DataType getDataType()const;

 SoEXTENDER public:

  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void write(SoWriteAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void pick(SoPickAction *action) ;


 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  void preDefCompose(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoBufferObject* outputBuffer);

 protected:
  // Destructor
  virtual ~SoDataCompositor();

 private:
  
  // TODO Damien: Fix this class

  // CPU optimized version
  void minus(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoCpuBufferObject* outputBuffer);
  void add(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoCpuBufferObject* outputBuffer);
  void multiply(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoCpuBufferObject* outputBuffer);

  // CUDA optimized version
  void minus(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoBufferObject* outputBuffer);
  void add(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoBufferObject* outputBuffer);
  void multiply(int numDataSet, const SbVec3i32& tileDimension,
               int* vdid, SoBufferObject** inputBuffer,
               SoBufferObject* outputBuffer);
};
//--------------------------------------------------------------------------------

#endif // _SO_DATA_COMPOSITOR__
