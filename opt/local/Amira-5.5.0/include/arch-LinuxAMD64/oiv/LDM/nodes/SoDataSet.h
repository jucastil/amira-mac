/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Jerome Hummel (Mar 2006)
** Modified by : Benjamin Grange (MMM yyyy)
** Modified by : Jean-Michel Godinaud. (MMM yyyy)
**=======================================================================*/


#ifndef _SO_DATA_SET_
#define _SO_DATA_SET_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//includes
#include <Inventor/SbBox.h>
#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBox3f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFieldContainer.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbDataType.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFUShort.h>
#include <Inventor/misc/SoMemoryObject.h>
#include <Inventor/misc/SoRef.h>
#include <Inventor/nodes/SoNode.h>
#include <LDM/SoLDM.h>
#include <LDM/SoLDMMediator.h>
#include <LDM/SoLDMTileID.h>
#include <LDM/SoLDMTileManager.h>
#include <LDM/fields/SoSFLDMResourceParameters.h>
#include <LDM/fields/SoSFLDMDataTransform.h>
#include <LDM/nodes/SoLDMResourceParameters.h>

// TODO: Should be removed : For compatibility only
#include <Inventor/devices/SoCpuBufferObject.h>

class SoGLRenderAction;
class SoCallbackAction;
class SoWriteAction;
class SoState;
class SoLDMGeomElement;
class SoLDMGeometry;
class SoLDMFrontTile;
class SoLDMReader;
class SoTransferFunction;
class SoMultiDataSeparator;
class SoVolumeHistogram;
class SoVolumeReader;
class SoPerfCounterManager;
class SoPerfCounter;
class SoBufferObject;
class SoGLTexture;

class SoDataExtract;
class SoConversion;
class SoAlgorithms;
class SoLDMAlgorithms;
class SoLdmValuationAction;
class SoDataRange;

/**
*
* @LDMEXT Data set node.
*
* @ingroup LDMNodes
*
* @DESCRIPTION
*   This class specifies the data set and its properties, and also provides utilities for
*   extracting a subset of the data set and for resampling the data set. The data can be
*   read from directly from a file or can be accessed via a user-defined volume reader.
*
* The data set can be specified by:
*
*   - Setting the #fileName field @BR
*      This implies that the data set is stored on disk, in one of the file
*      formats for which LDM has a built-in reader. LDM
*      will automatically select a reader based on the file extension,
*      for example ".am" for the AmiraMesh file format.
*
*  - Calling the setReader() method @BR
*     This is the most general method because an application can
*     specify one of the standard LDM readers or implement
*     a customized subclass of SoVolumeReader.
*     LDM will get the data set properties (dimensions, size, data type, etc) and
*     access the data through the specified reader object. This allows the
*     application to completely control how, and from where, the data is loaded.
*
*   This class is the parent class of the VolumeViz and ReservoirViz data nodes
*   SoVolumeData and SoMeshGeometry. These nodes provide the data for VolumeViz nodes
*   (SoVolumeRender, SoOrthoSlice, SoObliqueSlice, etc.) and ReservoirViz nodes
*   (SoMeshSkin, SoMeshLogicalSlice etc.).
*
* @SEE_ALSO
*    SoDataSetId,
*    SoDataCompositor,
*    SoVolumeData,
*    SoMeshGeometry,
*    SoMeshProperty
*
*
*/
class LDM_API SoDataSet : public SoNode
{
  SO_NODE_ABSTRACT_HEADER( SoDataSet );

public:

  /**
  * When using multiple SoDataSet nodes, the #dataSetId field uniquely
  * identifies each data set used in the compositing.
  * It also specifies the OpenGL texture unit in which the textures for
  * this data set will be stored when doing render compositing.
  * It is 1 by default (texture unit 0 is reserved for the color lookup table by default).
  * The number of available texture units depends on your hardware. You can query
  * this number using #getMaxNumDataSets.
  *
  * Note: The SoDataSetId node can also be used to define dataSetId.
  * If an SoDataSetId node is traversed before the SoDataSet node,
  * the id from the SoDataSetId node is used and this field is ignored.
  *
  * @FIELD_SINCE_OIV 6.0
  */
  SoSFUShort   dataSetId;

  /**
   * Indicates the file location containing the data set . Depending on the file
   * type, the corresponding SoVolumeReader (if it exists) is used.
   *
   *    @TABLE_1B
   *       @TR @B File Extension @b @TD @B Loader Class @b  @TD @B Description @b
   *       @TR .am                  @TD SoVRAmFileReader    @TD Amira Mesh file format
   *       @TR .dc3, .dic, .dicom   @TD SoVRDicomFileReader @TD Dicom file format
   *       @TR .fld                 @TD SoVRAvsFileReader   @TD AVS field file format
   *       @TR .lda or .ldm         @TD SoVRLdmFileReader   @TD Large Data Management file format
   *       @TR .sgy or .segy        @TD SoVRSegyFileReader  @TD SEG Y revision 1 file format
   *       @TR .vol                 @TD SoVRVolFileReader   @TD Vol file format
   *       @TR .vox                 @TD SoVRVoxFileReader   @TD Vox file format
   *       @TR .lst	                @TD SoVRRasterStackReader @TD Lst file format
   *    @TABLE_END
   *
  * The filename extension is not case sensitive.
  *
  * Note: SoDataSet and its derived classes (SoVolumeData, etc) do @I not @i search
  * the SoInput directory list to find files specified in this field.  To check file
  * existence and other properties the SbFileHelper class may be useful.
  */

  SoSFFilePathString  fileName;

  /**
  * Controls use of the OpenGL texture compression extension (if available). FALSE
  * means don't use it. Default is TRUE. A significant advantage of compressed
  * textures is that they conserve texture memory space. At the moment, the
  * extension works on RGBA textures only, not on paletted textures. The compression
  * factor is about 5.
  */
  SoSFBool   useCompressedTexture;

  /**
  *
  * Specifies the color index texture storage size in bits. Default is 8. This means that at most
  * the first 8 significant bits will be used for the rendering.
  * The valid values are 0, 4, 8, and 12.
  * When set to 0, LDM chooses the best precision, i.e., the first valid precision
  * greater than or equal to the number of significant bits.
  *
  * @FIELD_SINCE_OIV 6.0
  */
  SoSFUShort texturePrecision;

  /**
   * The real size (extent) of the volume in modeling coordinates. @BR
   * Note this can be used to define a volume with non-uniform voxel
   * spacing.  For example, if the volume dimensions (voxels) are 64x64x64,
   * but the voxel spacing in Z is twice the X and Y spacing, then you
   * might specify the volume size as -1 to 1 for X and Y but -2 to 2 for Z.
   */
  SoSFBox3f extent;

  /**
   * If set to an appropriate SoLDMDataTransform object,
   * the object's transformFunction method is called after each tile is loaded,
   * but before it is stored in main memory.
   * This allows you to modify the original data (for example, scaling or
   * filtering) before it is displayed.
   *
   * Note: Before Open Inventor 8.0, the data transformFunction was set
   * using the setLDMDataTransformFunction method. That method is now deprecated.
   *
   * @FIELD_SINCE_OIV 8.0
   */
  SoSFLDMDataTransform dataTransform;

  /**
  * Indicates if resource allocation is done only on first render traversal
  * or as soon as the node is created
  */
  SoSFBool   allocateResourceOnRender;

  /**
   * Indicates if this data set is time dependant.
   */
  SbBool isTimeDependent() ;

  /**
   * Returns the number of time steps.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  int getNumTimeSteps() ;

  /**
   * Returns the data set dimension.
   */
  const SbVec3i32&    getDimension();

  /**
   * Returns the tile dimension.
   */
  SbVec3i32    getTileDimension();

  /**
   * Returns the tile border (overlap) in voxels.
   */
  int getOverlapping();

  /**
   * Returns the number of bytes per voxel in VolumeViz or per cell in ReservoirViz.
   */
  unsigned int getDatumSize();

  /**
   * Copies the specified tile into the provided buffer. @BR
   * Applies the data transformation (set in dataTransform field)
   * if @B transform@b is true.
   * Returns the size, in byte, copied in the buffer. If size == 0
   * nothing have been written due to memory allocation error
   */
  virtual size_t readTile( SoBufferObject*& bufferObject, SoLDMTileID tileID, bool transform );

  /**
   * Copies the specified tile into the provided buffer. @BR
   * Applies the data transformation (set in dataTransform field)
   * if @B transform@b is true.
   */
  virtual void readTile(SoLDMTileID tileID, SoBufferObject* buffer, bool transform);

  /**
   * @deprecated No longer used. Use void readTile(tileID, SoBufferObject*, bool ) instead.
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED virtual void readTile(SoLDMTileID tileID, unsigned char* buffer, bool transform);

  /**
   * Contains an SoLDMResourceParameters object which allows you to set LDM
   * resource parameters.
   */
  SoSFLDMResourceParameters ldmResourceParameters;

  /**
   * @deprecated Use public field #ldmResourceParameters instead.
   * @BR
   * Returns a reference to the LDMResourceParameter. The returned
   * value can't be copied. You should use it directly or put it in a
   * reference variable:
   * \code
   * SoLDMResourceParameters& tmp = dataset->getLdmResourceParameter()
   * \endcode
   * You should now use the pointer returned by ldmResourceParameters.getValue()
   * directly:
   * \code
   * SoLDMResourceParameters* tmp = dataset->ldmResourceParameters.getValue()
   * \endcode
   *
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED SoLDMResourceParameters& getLdmResourceParameter();

  /**
   * Returns a reference to the SoLDMDataAccess object. @BR
   * This object can be used to query data from the volume.
   */
  SoLDMDataAccess       & getLdmDataAccess();

  /**
   * Returns a reference to the SoLDMDataEditor object. @BR
   * This object can be used to edit the data in the data set.
   * Note that convenience methods, e.g. startEditing, are
   * provided and should normally be used instead of explicitly
   * querying this object.
   */
  SoLDMDataEditor       & getLdmDataEditor();

  /**
  * Initiate an editing transaction. @BR
  * Returns a unique transaction id.
  * This value is required for finishing the edit transaction and useful for undoing.
  */
  virtual void startEditing( int & ) {};

  /**
  * Terminate an editing transaction. @BR
  * SHould only be called after calling startEditing. On error does nothing.
  */
  virtual void finishEditing(int ) {};

  /**
  * Fill a tile with given data. @BR
  * The buffer size (in bytes) must match the tile size (in bytes) exactly.
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeTile( const SoLDMTileID& , SoBufferObject* ) { return 0; };

  /**
  * Fill a subVolume with given data. @BR
  * The buffer size (in bytes) must match the subvolume size (in bytes) exactly.
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeSubVolume( const SbBox3i32& , SoBufferObject* ) { return 0; };

  /**
  * Fill a tile with a value. @BR
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeTile( const SoLDMTileID& , const double&  ) { return 0; };

  /**
  * Fill a subvolume with a value. @BR
  * Returns 0 if successful, else an result code defined by SoLDMDataEditor::ErrorValue.
  */
  virtual int writeSubVolume( const SbBox3i32& , const double&  ) { return 0; };

  /**
  * Undo all modifications associated with specified transaction id. @BR
  * All modified tiles are restored to their original value in the data source.
  * May only be called when no threads are editing, i.e. after all threads that
  * called startEditing have called finishEditing.  On error does nothing.
  * Note that undo does not manage overlapping transactions, meaning that
  * if a tile has been edited in two different transactions,
  * the undo operation will restore the tile from its original state,
  * not from its previous edited state.
  */
  virtual void undoEditing(int ) {};

  /**
  * Save modifications to a file. @BR
  * All modified tiles are written back to the data file using SoLDMWriter.
  * May only be called when no threads are editing, i.e. after all threads that
  * called startEditing have called finishEditing.  On error does nothing.
  */
  virtual bool saveEditing(bool recomputeLowerResolution = TRUE, const std::vector<char*> conversionParameters = std::vector<char*>() );

  /**
   * Returns a pointer to the LDM tile manager.
   */
  SoLDMTileManager *getTileManager() { return getLdmManagerAccess().getTileManager(); }

  /**
   * Returns a pointer to the LDM texture manager.
   */
  SoLDMTextureManager *getTextureManager() { return getLdmManagerAccess().getTextureManager(); }

  /**
   * Returns the current LDM tile visitor.
   */
  SoLDMTileVisitor *getTileVisitor() { return getLdmManagerAccess().getTileVisitor(); }

  /**
   * Sets a custom LDM tile visitor.
   */
  void setTileVisitor(SoLDMTileVisitor* tileVisitor) { return getLdmManagerAccess().setTileVisitor(tileVisitor); }

  /**
   * Returns a pointer to the LDM geometry object.
   */
  SoLDMGeometry *getVVizGeometry() { return getLdmManagerAccess().getVVizGeometry(); }

  /**
   * Returns a pointer to the LDM node front manager.
   */
  SoLDMNodeFrontManager *getNodeFrontManager() { return getLdmManagerAccess().getNodeFrontManager(); }

  /**
   * Returns a pointer to the current data set reader object. @BR The actual type will be
   * a subclass of SoVolumeReader, either one of the predefined subclasses or an
   * application-defined subclass. Returns NULL if no reader is currently being used
   * (for example if setVolumeData() was called).
   */
  SoLDMReader*   getLDMReader();

  /**
   * Sets the LDM volume reader object to use. @BR This method allows the data to
   * be read directly from the disk using the specified subclass of
   * SoVolumeReader.
   */
  void           setLDMReader(SoLDMReader*);

  /**
  * Returns the current data set reader object. @BR The actual type will be
  * a subclass of SoVolumeReader, either one of the predefined subclasses or an
  * application-defined subclass. Returns NULL if no reader is currently being used
  * (for example if setVolumeData() was called).
  */
  SoVolumeReader* getReader();

  /**
  * Returns the current data set reader object. @BR The actual type will be
  * a subclass of SoVolumeReader, either one of the predefined subclasses or an
  * application-defined subclass. Returns NULL if no reader is currently being used
  * (for example if setVolumeData() was called).
  * [OIV-WRAPPER-NOT-WRAP]
  */
  inline SoVolumeReader* getReader() const;

  /**
   * Supported data type
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
  * Returns the number of bytes per voxel of the specified data type.
  */
  static int dataSize( DataType dataType );

  /**
  * Returns TRUE if the given data type is a signed integer data type.
  */
  static SbBool isDataSigned( DataType dataType );

  /**
  * Returns TRUE if the given data type is a float data type.
  */
  static SbBool isDataFloat( DataType dataType );

  /**
  * Returns the number of significant bits.
  */
  int numSigBits() const;

  /**
  * Returns @B min @b and @B max @b values of the data set data. Returns FALSE if
  * the requested data is not available (for example, if no data set exists).
  *
  * NOTE: This method might force LDM to load the @I entire @i data set if
  * the volume reader does not respond to the getMinMax query. Normally for an
  * LDM format data set, the min and max values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, LDM will load the entire data set to
  * compute the min and max values. For a large data set this may take a long time.
  */
  virtual SbBool getMinMax( int64_t &min, int64_t &max);

  /**
  * Returns @B min @b and @B max @b values of the data set. Returns FALSE if
  * the requested data is not available (for example, if no data set exists).
  *
  * NOTE: This method might force LDM to load the @I entire @i data set if
  * the volume reader does not respond to the getMinMax query. Normally for an
  * LDM format data set, the min and max values are stored in the LDM header.
  * For a non-LDM data set, if a filename and/or reader have been specified and
  * the data set has not yet been loaded, LDM will load the entire data set to
  * compute the min and max values. For a large data set this may take a long time.
  * [OIVJAVA-WRAPPER NAME{getDoubleMinMax}]
  */
  virtual SbBool getMinMax( double &min, double &max);

  /**
   * Returns the data type.
   */
  DataType getDataType();

  /**
   * Returns the number of bytes per voxel in VolumeViz, per cell in ReservoirViz
   */
  int getDataSize();

/**
 * @deprecated. Use #dataTransform field which handle an SoLDMDataTransform fieldContainer.
 * Type declaration for the data transform function. See #setLDMDataTransformFunction.
 * This function allows a tile of data to be transformed after it is loaded, but before
 * it is stored in main memory.  It is not currently possible to access other tiles of
 * data (for example using the data access API) from this function.  Note that the
 * function will be called from LDM data loader threads, so multiple threads may be
 * executing in this function at the same time (on different tiles).
 * Inputs are:
 *  - The associated data set object the function is calling for.
 *    This allows retrieving information such as data type (ds->getDataType()).
 *  - The dimensions of the tile to transform.
 *    This defines the size of the buffer and is the same for every tile in a dataset.
 *    However tiles on the "outside" of the dataset may be partial tiles and contain
 *    less than the full number of actual data values.
 *  - A buffer containing the tile data to transform.
 *    The data should be modified "in place" in this buffer.
 *  - The position and extent of the tile in data space (voxel coordinates).
 *    For lower resolution tiles (level > 0) the extent of the tile will be larger
 *    than the dimensions of the tile (number of values in the tile).
 *  - The tile resolution level.  Level 0 is full resolution data.
 *  - Optional user data specified with setLDMDataTransformFunction.
 *
 * @DEPRECATED_SINCE_OIV 8.0
 * [OIV-WRAPPER NAME{LDMDataTransformCB}]
 * [OIV-WRAPPER-ARG IN,IN,ARRAY{ds != nullptr? ds->getDataSize()*bufferDimension[0]*bufferDimension[1]*bufferDimension[2]: 0},IN,IN,IN]
 */
  /*SoDEPRECATED*/ typedef void SoLDMDataTransformFunction(SoDataSet* ds,
                                          const SbVec3i32& bufferDimension, //tile dim
                                          void* bufferToTransform,
                                          const SbBox3i32& dataBox,      //position of tile in data space
                                          int resolutionLevel,	  //resolution level of the tile
                                          void* userData);


  /**
   * @deprecated. Use the #dataTransform field. @BR
   * If set, the user-defined function is called after each tile is loaded,
   * but before it is stored in main memory.
   * This allows you to modify the original data (for example, scaling or
   * filtering) before it is displayed.
   *
   * @DEPRECATED_SINCE_OIV 8.0
   * [OIV-WRAPPER EVENT_NAME{LDMDataTransformCallback}]
   */
  SoDEPRECATED void setLDMDataTransformFunction(SoLDMDataTransformFunction* func, void* userData = NULL);

  /**
   * This method allows the data to
   * be read directly from the disk using the specified subclass of
   * SoVolumeReader.
   * If the @B takeOwnership @b parameter is FALSE (default), LDM
   * will not delete the specified instance. Otherwise, LDM will automatically
   * delete the specified instance, for example, when the #SoDataSet node is deleted.
   * [OIV-WRAPPER-ARG IN&STRONG_REF,IN]
   *
   * Note: When using a custom reader, any reader method that changes the volume
   * properties (dimension, size, data type, etc) should notify the SoVolumeData
   * node by calling the reader's touch() method.  If this notification is not done,
   * SoDataSet fields, for example #extent, won't be updated correctly.
   */
  void setReader( SoVolumeReader &reader, SbBool takeOwnership = FALSE );

   /**
   * Returns the maximum number of data sets that can be render composited on the
   * current hardware (essentially the number of texture units - 1).
   */
  static int getMaxNumDataSets() ;

  /**
   * Enable or disable LDM mode
   */
  virtual void setLDM(SbBool);

SoEXTENDER_Documented public:
  /**
  * Returns a reference to an LDMManagerAccess.
  */
  SoLDMMediator::LDMManagerAccess &getLdmManagerAccess() { return m_mediator->ldmManagerAccess; }

  /**
  * reset previously set custom reader setup by setReader call.
  */
  void resetReader();

SoEXTENDER public:

  void callback( SoCallbackAction *action );
  void GLRender( SoGLRenderAction *action );
  void getBoundingBox(SoGetBoundingBoxAction *action);
  void pick(SoPickAction *action) ;
  void write(SoWriteAction *action);
  void search(SoSearchAction *action);

  /**
  * Create fake data in buffer
  */
  virtual void useFakeData(SoLDMTileID tileID, SoBufferObject* buffer);

  /**
  * Adds a reference to an instance.
  * This is defined to be const so users can call it on any instance, even const ones.
  */
  virtual void ref() const;

  /**
  * Removes a reference from an instance.
  * This method removes a reference from the object. If the reference
  * count goes to zero the object is automatically deleted.
  * This is defined to be const so users can call it on any instance, even const ones.
  */
  virtual void unref() const;

SoINTERNAL public:

  // This map is used to maintain signature of each tile in cache
  // It's used to be able to find a uncompressed version of a given tile in the cache
  // when already uncompressed tile are reloaded.
  typedef std::map<SoLDMTileID, uint64_t> tileSigInCacheMap;

  static void initClass();
  static void exitClass();

  // return the number of SoDataSet instance created
  // this is usefull to optimize SoLdmValuationAction
  static int getNumInstance()
  { return s_numInstance; }

  /** Initialize Thread local storage structure. */
  SB_THREAD_TLS_HEADER();

  typedef std::vector<SoGLTexture*> TextureList;

  /** Return the current dataset/id pair according to the state */
  SoLDM::DataSetIdPair getDataSetIdPair(SoState* state) const;

  SoMultiDataSeparator *getMultiDataSeparator() { return m_MultiDataSeparator; }
  void setMultiDataSeparator(SoMultiDataSeparator *mds);

  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

  /**
   * Copy all parameters of SoLDMResourceParameters to the SoLDMResourceManager
   */
  void sendParametersToLDM(SoLdmValuationAction* action);

  /**
   * Returns true if LDM is used. Returns always true in ReservoirViz.
   */
  SbBool       isLDM();


  /** a SoDataSet must return the LDMelt defining the weights of the representations
   * that are going to use it.
   * [OIV-WRAPPER VISIBILITY{PublicProtected}]
   */
  virtual SoLDMGeomElement* getAppropriateElement(SoLDMGeometry* v) = 0;

  //When true data set won't be used for rendering
  void ignoredByMultiDataSeparator(bool state);
  bool isIgnoredByMultiDataSeparator() { return m_ignoredByMultiDataSeparator; }

  int getIndTexPrec() const;
  virtual void doAction( SoAction *action );
  virtual bool loadInMemory(SoState* s = NULL);
  void setListChange(bool val){m_listChange = val;};
  bool getListChange(){return m_listChange;};

  //eye settings to pass to mediator
  SbVec3i32 getEyeDataCoord(SoState* state);

  /**
   * Compute the biggest axis of the bbox and the axis used to draw slices
   * @param volBbox the box to determine the axis
   * @param dataAligned true for data aligned slices
   * @return the biggest axis of the transformed bbox according to the renderding state
   */
  int getZaxis(SoState *state, const SbBox3f& volBbox, bool dataAligned) const;

  /**
   * Return vector going from eye to data set center
   */
  SbVec3f getVolCenterToEyeVector(SoState *state, const SbBox3f& volBbox) const;

  /** Return eyeAxis in object space */
  SbVec3f getObjectSpaceEyeAxis(SoState *state) const;

  //shall we accumulate the node in state?
  void     setAccumulate(bool val){m_toAccumulate = val;};
  bool     isAccumulated(){return m_toAccumulate;};
  bool     m_toAccumulate;
  SbBool   getCurrentMatrixDifference(SoState*, SbMatrix&);

  //multi-data
  void lookForSceneGraphChange(SoAction* action);

  // extract slice data
  virtual SoBufferObject* getDataOneSlice( const SbVec3i32& tileSize, SoBufferObject* tileData, int Zaxis, int slice);
  virtual void releaseDataOneSlice(SoBufferObject *sliceDataBuffer);

  //***** factory methods ****

  virtual SoLDMFrontTile* getAppropriateFrontTile(SoLDMTileID, SbVec3i32);
  virtual SoLDMTileManager::LDMSliceAccessor* getAppropriateSliceAccessor(const SoLDM::DataSetIdPair& p);
  virtual SoLDMReader* getAppropriateLDMReader( const SbString& pathname);

  /**
   * Return bbox of given tile id.
   * Return false if not available
   */
  virtual bool getBbox(SoLDMTileID tileId, SbBox3f& box);

  // logical center per id
  bool getCenter(SoLDMTileID tileID, SbVec3f& center)const;

  SoLDMMediator* getMediator(){return m_mediator;};
  void setMediator(SoLDMMediator* m);

  virtual bool createTex(int Zaxis, SoState *state, const SbVec3i32 &tileSize, SoBufferObject *tileDataBuffer, SoTransferFunction *transferFunction,
                         const TextureList& texList);

  virtual SbBool updateDataTex3DPage(SoState*, SbVec3i32 &, SoBufferObject *, SbBox3i32 &);

  // TODO FIXME : should cleanup this call.
  /** @param numElem is the number of datum to convert */
  void* getTexData(const void* tileBuffer, int numElem, SoTransferFunction* transferFunction,
                   int alphaUse, int texPrec, void *textureBuffer, SoState* state)
  {
    if (textureBuffer==NULL)
    {
      SoDebugError::post("SoDataSet::getTexData","no more supported with a tex parameter == NULL");
      return NULL;
    }
    else
    {
      SoCpuBufferObject tileBufferObject((void*)tileBuffer,numElem*getDatumSize());
      SoCpuBufferObject textureBufferObject((void*)textureBuffer,numElem*getDatumSize());
      SoBufferObject *resultBufferObject = getTexData(&tileBufferObject, transferFunction, alphaUse, texPrec, &textureBufferObject, state);
      if ( resultBufferObject != &textureBufferObject )
      {
        SoDebugError::post("SoDataSet::getTexData","unable to retrieve data");
        return NULL;
      }
      return textureBuffer;
    }
  }
  void* getTexData(const void* tileBuffer, int numElem, SoTransferFunction* transferFunction,
                   int alphaUse, int texPrec, void *textureBuffer, SoDataRange* datarange, SoState* state);

  // allocate ( if needed ) and initialize the texture buffer, according to the input buffer and the transfer function.
  // The texture buffer can be given with the tex_data argument. In this case no allocation is done and tex_data is returned.
  // Otherwise returns the initialized texture buffer.
  // Returned pointer do not needs to be deleted, but reference to this buffer will be valid only until the next getTexData call.
  SoBufferObject* getTexData(SoBufferObject* tileBufferObject, SoTransferFunction* transferFunction,
                   int alphaUse, int texPrec, SoBufferObject* textureBufferObject, SoState* state);

  SoBufferObject* getTexData(SoBufferObject* tileBufferObject, SoTransferFunction* transferFunction,
                             int alphaUse, int texPrec, SoBufferObject* textureBufferObject,
                             SoDataRange* dr, SoState* state);

  template <typename DataClassIn>
  static SoBufferObject *permuteData(const SbVec3i32 & tileSize, SoBufferObject *srcRgbaBuffer, int axis);

  virtual void computeLighting( const SbVec3i32 & tileSize, SoBufferObject *rgbaBuffer );
  int getRGBAInternalFormat() const;

  virtual void updateColorTable(SoState *, SoTransferFunction *,int32_t**,int32_t*);

  SoLDMResourceManager& getResourceManager() { return *m_resourceManager; }

  //Display loaded tiles
  virtual void drawTilesInMainMemory(SoState *state);

  //Copy dataset's fields if needed into the given mediator
  void copyLDMParameters(SoLDMMediator *mediator);

  /**
   * Return true if multidata is enabled
   */
  virtual bool isMultidataEnabled() const { return m_multidataEnabled; }

  // draw a colored Box
  enum BoxColor {
    GREY,
    RED,
    BLUE,
    GREEN,
    FULL_RES_GREY,
    FULL_RES_GREEN
  };

  enum FieldId {
    MAX_MAIN_MEMORY = 0,
    MAX_TILES_IN_MAIN_MEMORY,
    LOAD_POLICY,
    LOAD_NOTIFICATION_RATE,
    MAX_TEX_MEMORY,
    MAX_TILES_IN_TEX_MEMORY,
    TEX3_LOAD_RATE,
    MAX_2D_TEXTURES,
    TEX2_LOAD_RATE,
    MIN_RESOLUTION_THRESHOLD,
    MAX_RESOLUTION_THRESHOLD,
    TILE_SIZE,
    FIX_PARAMS,
    OVERLAPPING,
    TILE_HALF_LIFE,
    FIXED_RESOLUTION_MODE,
    LAST_ID
  };

  /**
   * Return the current id. (Useful to know the previous value
   * when the field dataSetId is changed)
   */
  unsigned short getId() const { return m_id; }

  /**
   * Return true if there is a read error
   */
  inline bool hasReadError();

  /**
  * A datum is a series of m*n data type. e.g. 3 int followed by 4 float followed by 6 short
  * n is num in the DatumElement struct, data type is type.
  */
  struct DatumElement{
    SoDataSet::DataType type;
    int                 num;
  };

  /**
   * convert the given data to byte according to ds datatype
   * from [data(Type|Range)Min,data(Type|Range)Max]->[0, 255]
   */
  unsigned char convertToByte(SoState* state, const float data);

  /**
  * Tell if given tile has been edited or not
  */
  virtual bool isEditedTile( const SoLDMTileID& ) {return FALSE;};

  /**
  * Change the edited state of a given tile.
  */
  virtual void setEditedTile( int , const SoLDMTileID& , bool ) {};

  /**
  * Change the edited state of a list of tiles.
  */
  virtual void setEditedTile( int , const SoLDM::TileIdVector& , bool ) {};

  /**
  * Tell if the current DataSet is currently under edition
  * ie: finishEditing has not yet been called
  */
  virtual bool isEditing() {return false;};

  /**
  * Tell if the current thread is editing the DataSet
  * ie: finishEditing has not yet been called by current thread
  */
  virtual bool isCurrentThreadEditing(SbThreadId_t ) {return false;};

  /**
  * Used to undo all unsaved edition before deletting the node
  */
  virtual void cleanUnsavedEdition() {};

  /**
  * UpdateParam is called when when dataset is inserted into a SG
  * Internal use only
  */
  void updateParams();

  /**
  * Mark dataset has initialized (texture params init)
  * Internal use only.
  */
  void setFirstRenderDone(bool flag) { m_firstRenderDone = flag;};
  bool isFirstRenderDone() { return m_firstRenderDone;};

  virtual bool isPalettedTexture(SoState*);

  // Get a unique signature for a given tile. If tile already loaded, return the
  // previously generated signature. Otherwise, generate a new one. Each dataset
  // manage its signature list.
  virtual uint64_t getTileSignature(const SoLDMTileID& tileId);

  // Uniq Id management
  uint64_t getUniqueId();

protected:
  /**
   * Set to LDM mode without sending notification
   */
  virtual void setLDMInternal(SbBool) {}

  SoDataSet();
  virtual ~SoDataSet();

  /**
   * Put the data set element on the state
   */
  virtual void setElement(SoState* state);

  /**
   * Return true if the extent specified by the reader must be use
   */
  inline bool isUsingUserExtent();

  /*
  Allows a class inheriting from SoDataSet to decide whether multiple data should be allowed or not.
  If it is the SoDataSet will assign one mediator for all dataset.
  Else one mediator is assigned for all dataset (one LDM core per dataset).
  In vviz this method checks whether a compositor or a shader is present in the state.
  If not then multidata is not allowed.
  */
  virtual bool enableMultidata(SoState* state);

  //Return a reader according to m_filename and m_data
  virtual SoVolumeReader* getAppropriateReader();

  /** If true, tile dim is rounded to a pow 2 dim*/
  bool m_forcePow2TileDim;

  //LDM reader
  SoRef<SoFieldContainer> m_reader;
  SbBool          m_internalReader;

  //did the list change?
  bool m_listChange;

  bool load(SoState*);
  virtual void unload();
  virtual void releaseMemory();

  bool assignLDMMediator(SoState* state);
  bool m_multidataEnabled;

  SbVec3i32     m_dimension;
  bool          m_ldmOn;
  bool          m_initialized;

  SbDataType       m_type;
  int              m_numBits;
  bool             m_isDataFloat;
  bool             m_isDataSigned;
  unsigned int     m_datumSize;

  bool m_deletedFlag;
  //True if data header has already been read
  bool m_dataCharRead;

  SbString      m_filename;
  virtual void updateFilename();

  //Notify mediator or multidataseparator about id change
  void dataIDChanged(int newId);
  unsigned short m_id;

  void ldmResourceParamChanged();

  /**
   *Release memory and set the new reader
   */
  virtual void readerChanged();

  /**
   * If user set its own extent, use it until a filename change
   * happens
   */
  void extentChanged();

  void initReader();
  void setType(SbDataType);

  //
  void getFilePathName( SbString& pathName, SbString& fileExtension);

  virtual SoLDMMediator *createMediator();
  SoLDMMediator* m_mediator;

  SoMultiDataSeparator *m_MultiDataSeparator;
  bool m_ignoredByMultiDataSeparator;

  SoLDMResourceManager* m_resourceManager;

  virtual int isSharedPalettedTexture() { return FALSE; }

  //Return the precision of the texture in bits
  //<=0 if in RGBA texture mode
  virtual int getTexPrec(SoState*);
  void getTransferFunction(SoTransferFunction *transferFunction, int alphaUse,
                           int &shift, int &offset, int &nrgba, unsigned int * &rgba);

  SbVec3i32 getPow2(SbVec3i32) const;

  //OpenGL display of tiles given in tileIDs. The line width increase with the level of the tile.
  void drawTiles(SoState *state, const SoLDM::TileIdVector& tileIDs,
                 const SbVec4f &tileColor, const SbVec4f &maxLevelColor,
                 size_t maxLineWidth);
  template<class DataType>
  void buildSlice(SoCpuBufferObject& slice, const SbVec3i32& min, const SbVec3i32& max, const SbVec3i32& tileSize);

  //Build a tile out of the original full resolution data.
  //The data is taken out from disk by the reader (vol, am,..)
  //and subsampled until the desired level.
  virtual void buildTile(SoLDMTileID tileID, SoBufferObject* buffer);

  //Set data characteristic size, extent...
  virtual void readChar();

  //Set if an undefinedValue was defined
  virtual void setUseUserUndefinedValue(bool useUserUndefinedValue);

  bool m_useUserExtent;

  SoVolumeHistogram *m_histogram;

  // Cache element to monitor DataCompositor modification
  SoCache* m_dataCompositorCache;

  /**
   * thread specific variables
   */
  struct MTstruct {
    SoBufferObject *tmpTexture;
    SoBufferObject *tmpColormap;
    SoBufferObject *tmpTexturePermute;
  };

  std::map<int, std::vector<SoLDMTileID> > m_editedTilesLists;
  std::vector<int> m_transationIdsList;
  std::vector<SbThreadId_t> m_editingThread;
  int m_nbThreadEditing;
  int m_editionTransactionId;
  bool m_isEditing;


SoINTERNAL protected:
  SoSFFieldContainer customReader;
  SoSFBool           customReaderOwnerShip;

  virtual void ldmAction(SoLdmValuationAction* action);

  /**
   * Returns TRUE if the data represents RGBA color values.
   */
  virtual SbBool isRGBAData();

private:
  /** Update m_id if needed */
  void updateDataSetId(SoState* state);

  /** Enable the thin volume optim if possible */
  void enableThinVolume();

  // Take in account modification of DataCompositorElement
  void updateCompositorCache(SoState *state);

  /**
   * Return false if dim is <= 0
   */
  bool isValidDimension(const SbVec3i32& dim) const;

  /**
   * Send error message to user
   */
  void displayReadError(int err);

  /**
   * Return a positive border size inferior to tileDim
   * Display an error message if clamping is done.
   */
  int clampBorder(int border, const SbVec3i32& tileDim) const;

  /**
  * Return a positive tile size.
  * Display an error message if clamping is done.
  */
  SbVec3i32 clampTileDimension(const SbVec3i32& tileDim) const;

  /**
   * Dataset bigger than this, won't be processed
   */
  static const unsigned int MAX_DATASET_DIMENSION;

  /**
   * Tile size bigger than this will be ignored
   */
  static const int MAX_TILE_DIMENSION;

  bool isIdUsed(int id, std::vector<SoDataSet*>);

#ifndef HIDDEN_FROM_DOC
  friend class SoLDMMediator;
  friend class SoLDMMediator::LDMManagerAccess;
  friend class SoCpuBufferFromVolumeReader;
#endif

  bool m_filenameChange;

  /**
   * True if a read error happened
   */
  bool m_hasReadError;

  bool m_accumulate;

  SoPerfCounterManager* m_perf;

  // Perf counter used for data copy timing
  SoPerfCounter* m_nbTexGen;
  SoPerfCounter* m_byteGetTexData;
  SoPerfCounter* m_timeCreateTex;
  SoPerfCounter* m_timeGetTexData;

  static SoAlgorithms* s_algorithms;
  static SoLDMAlgorithms* s_LDMAlgorithms;

  bool m_firstRenderDone;
  friend class SoLdmValuationAction;
  bool m_ldmUseInMemCompression;

  static int s_numInstance;

  // Static id generator.
  static uint64_t s_lasUniqId;

  // Some stuff to manage cache. Static mutex to be sure all dataset won't access
  // at the same time to Id generator
  static SbThreadMutex s_sigCacheMutex;

  // Map to manage internal association between tileId and uniqId
  tileSigInCacheMap m_tileSigInCache;
};

/*****************************************************************************/
SoVolumeReader*
SoDataSet::getReader() const
{
  return (SoVolumeReader*)m_reader.ptr();
}

/*****************************************************************************/
inline SoVolumeReader*
SoDataSet::getReader()
{
  return (SoVolumeReader*)m_reader.ptr();
}

/*****************************************************************************/
inline bool
SoDataSet::hasReadError()
{
  return m_hasReadError;
}

inline SoLDMReader*
SoDataSet::getAppropriateLDMReader(const SbString&)
{
  return NULL;
}

inline void
SoDataSet::computeLighting( const SbVec3i32 &, SoBufferObject *)
{
}

inline void
SoDataSet::useFakeData(SoLDMTileID , SoBufferObject* )
{
}

inline bool
SoDataSet::saveEditing( bool, const std::vector<char*> )
{
  return false;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif  // _SO_DATA_SET_
