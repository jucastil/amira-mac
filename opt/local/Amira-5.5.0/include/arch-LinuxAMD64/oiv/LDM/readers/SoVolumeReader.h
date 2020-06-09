/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_VOLUME_READER_
#define  _SO_VOLUME_READER_

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/nodes/SoNode.h>
#include <Inventor/SoPreferences.h>
#include <LDM/nodes/SoDataSet.h>

#include <Inventor/STL/vector>
class SbThreadMutex;
/**
 * @LDMEXT Abstract base class for volume data set readers.
 *
 * @ingroup LDMReaders
 *
 * @DESCRIPTION
 *   This virtual class provides the interface through which VolumeViz
 *   accesses volume data that is not already in memory.  Predefined
 *   reader classes are provided for many common formats like DICOM and SEGY.
 *   See the list of supported file formats and class names below.
 *
 *   Application developers may implement custom reader classes. Custom
 *   reader classes allow VolumeViz to access data stored in other file
 *   formats. This is particularly useful for converting data to LDM format.
 *   A custom reader class could also allow VolumeViz to access data through
 *   a proprietary data manager or data stored in application memory.
 *
 *   The application must implement a class derived from SoVolumeReader, and must
 *   overload the methods getDataChar() and getSubSlice(). In addition, the optional
 *   methods getNumSignificantBits() and getSubVolume() can be overloaded. These methods
 *   are called once when loading data from the disk or each time SoVolumeData::subSetting()
 *   and SoVolumeData::reSampling() methods are called. In these cases,
 *   SoVolumeData::reSampling() allows you to load a (smaller) approximation of a
 *   very large data set.
 *
 *   In addition to the usual requirements for an application-defined reader,
 *   e.g., implementing the getDataChar() method, an application-defined
 *   reader for LDM data is required to:
 *
 *   - redefine #isDataConverted method to return TRUE @BR
 *     This must return TRUE when the reader is passed to
 *     SoVolumeData to ensure that LDM manager classes are
 *     correctly initialized.
 *
 *   - Implement the readTile() method. @BR
 *       - When implementing the readTile() method, be aware that 
 *         how the SoCpuBuffer object is created affects how its memory will be managed.  
 *         In general you should create the object using the constructor with no parameters, 
 *         then allocate memory inside the object using the setSize() method.  In this case the 
 *         buffer object owns the memory and the memory will be freed when LDM no longer needs this tile.
 *         This implies for example that to avoid data copying when reading tile data from a file, 
 *         you should create and allocate the buffer object, map the buffer object, then read the data into 
 *         the buffer object. If you create the buffer object “wrapping” an existing block of memory, 
 *         that memory will not be freed when LDM releases the buffer object.
 *         The application owns that memory and is responsible for freeing it.
 *
 *       - Also note that readTile can return one of the specialized sub-classes of SoCpuBufferObject
 *         that use less system memory:
 *           - SoCpuBufferUniform: This buffer contains a "uniform" tile in which all the voxels
 *             have the same value.  It is stored efficiently as a single value until needed.
 *           - SoCpuBufferCompressed: This buffer contains a compressed tile.  It is stored
 *             efficiently in its compressed form until needed.
 *           - SoCpuBufferBasicProperty: This buffer contains a standard tile, but can also store
 *             the tile's min and max data values for use in various optimizations.
 *           - SoCpuBufferBitset: This contains a bitset tile in which each voxel is a boolean
 *             value. It is stored efficiently in a packed form until needed.
 *
 *   - Implement the getTileSize() method
 *
 *   - Implement the getBorderFlag() method  @BR
 *     Return non-zero value (the number of overlap voxels) if tiles will be returned with voxel
 *     overlap so VolumeViz can do edge blending between tiles.
 *
 * An application-defined LDM reader may optionally:
 *
 *   - Implement the getMinMax() method  @BR
 *     Return TRUE and the requested values if the min and max data values for the
 *     volume are known to the reader, e.g., are in the file header.
 *     The reader should implement this method if possible, because applications typically
 *     query these values to setup their SoDataRange node.  If not implemented then
 *     VolumeViz must load every tile to compute the volume min and max.
 *
 *   - Implement the getHistogram() method @BR
 *     Return TRUE and the requested values if the min and max
 *     data values are known to the reader, e.g., are in the file header.
 *
 *   Starting with Open Inventor 7.0, general rectilinear grids are supported.
 *   This feature allows non-uniform voxel spacing along each axis of
 *   the volume.
 *   The AmiraMesh reader (.am file), the in-memory reader, and the LDM reader
 *   support rectilinear coordinates.  Call the method setRectilinearCoordinates
 *   to specify rectilinear coordinates (if they are not already stored in
 *   the data file and set by the reader).
 *
 *   Starting with Open Inventor 7.0, SoVolumeReader is derived from SoFieldContainer.
 *   This allows client classes like SoVolumeData to be automatically notified
 *   when the reader's state changes, and update their own state appropriately.
 *   Any reader method that changes the volume properties (dimension, size, data type,
 *   etc) should trigger notification by calling the reader's touch() method.  If this
 *   notification is not done, client node fields, for example SoDataSet::extent, won't be updated
 *   correctly.  For example, a reader with a method setData(SbVec3i32 size, void* data)
 *   that loads a new data set should call touch() at its end.  This reader could also
 *   be implemented using an SoSFArray3D field instead of the setData method.  Modifying
 *   this field will automatically trigger notification.
 *
 *   Note that methods getNextSlice(), skipSlice(), and end() are deprecated.
 *
 *	 Applications should subclass from SoVolumeReader when creating any type of custom volume reader, 
 *   including an LDM (tiled) volume reader. The classes SoLDMReader and SoVRLdmFileReader are internal 
 *   classes which are specific to the VSG defined LDM file format.
 *
 *
 *   This class cannot be instantiated directly.
 *
 * @H3 Supported file formats: @h3
 *
 *   @TABLE_1B
 *   @TR @B File extension @b  @TD @B Reader class @b     @TD @B Description @b
 *   @TR .am                   @TD SoVRAmFileReader       @TD Avizo Mesh file format
 *   @TR .dc3, .dic, .dicom    @TD SoVRDicomFileReader    @TD DICOM file format
 *   @TR .fld                  @TD SoVRAvsFileReader      @TD AVS field file format
 *   @TR .lda or .ldm          @TD SoVRLdmFileReader      @TD LDM file format
 *   @TR .sgy or .segy         @TD SoVRSegyFileReader     @TD SEG Y rev 1 file format
 *   @TR .vol                  @TD SoVRVolFileReader      @TD Vol file format
 *   @TR .vox                  @TD SoVRVoxFileReader      @TD Vox file format
 *   @TR .lst                  @TD SoVRRasterStackReader  @TD Lst file format
 *   @TABLE_END
 *
 * @SEE_ALSO
 *    SoDataSet,
 *    SoVolumeData,
 *    SoConverter
 *
 *
 */

class LDM_API SoVolumeReader : public SoFieldContainer
{
  SO_FIELDCONTAINER_ABSTRACT_HEADER(SoVolumeReader);

 public:

  /**
   * Read error.
   */
   enum ReadError {
    /**
     * No error.
     */
    RD_NO_ERROR,
    /**
     * The data file is not found.
     */
    RD_FILE_NOT_FOUND_ERROR,
    /**
     * Invalid data.
     */
    RD_INVALID_DATA_ERROR,
    /**
     * Unsupported data type (but the data is valid).
     */
    RD_UNSUPPORTED_DATA_TYPE_ERROR,

    /**
     * Unknown error.
     */
    RD_UNKNOWN_ERROR
   } ;

  /**
   * Which axis to handle
   * @see getRectilinearCoordinates
   */
  enum Axis {
    X,
    Y,
    Z
  };

  /**
   * Constructor.
   */
   SoVolumeReader();

  /**
   * Gets the characteristics (file header) of the data volume. See
   * SoDataSet::setVolumeData().@BR
   * You can use the convenience method setFilename() to specify the file location,
   * in which case you will not have to open the file yourself. Then you can use
   * the convenience method getBuffer() to read the header in order to get the requested
   * information.
   *
   * NOTE: We strongly recommend that readers implement this version of #getDataChar,
   * introduced in VolumeViz 5.1, because it uses SbVec3i32 for the volume dimension.
   * [OIVJAVA-WRAPPER PACK{DataInfo}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{readError}]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type, SbVec3i32 &dim )=0;

  /**
   * Sets the output data type. Returns FALSE if the reader does not support this feature.
   * If the reader does support this feature and @B doChange @b is set to TRUE, data is
   * converted before being returned (by getSubSlice() for instance).
   * If @B doChange @b is set to FALSE, data is not converted and is returned as is.
   */
  virtual SbBool setOutputDataType( SbBool doChange, SoDataSet::DataType outputType );

  /**
   * Requests that the input be converted from the specified range to the range depending on
   * the output data type.
   * This allows, for instance, if the output data type is unsigned byte, conversion of float data
   * from range [min,max] to range [0,255].
   * If doChange is FALSE no range conversion is applied.
   * Always returns TRUE.
   */
  virtual SbBool setInputDataRange( SbBool doChange, double min, double max );

  /**
   * This method is optional. It returns the number of significant bits of the volume data.
   *
   * If it is not implemented, the default return value is 0, meaning the number of bits
   * depends on the data type. See the last parameter of SoVolumeData::setVolumeData().
   * This method is called immediately after getDataChar().
   */
  virtual int getNumSignificantBits() { return 0; };

  /**
   * This method is optional. It returns the number of time step if any.
   *
   * If it is not implemented, the default return value is 1.
   * This method is called immediately after getDataChar().
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  virtual int getNumTimeSteps() { return m_numTimeSteps; };

  /**
   * This method defines which time step to read.
   * The first time step is 0, the last one is getNumTimeSteps()-1.
   * Default time step is 0.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  void setCurrentTimeStep( int curTimeStep ) { m_curTimeStep = curTimeStep; };

  /**
   * Returns the current time step.
   *
   * @NOTES
   *    Only supported by ReservoirViz module extension.
   */
  int getCurrentTimeStep() const { return m_curTimeStep ;}

  /**
   * Method required by VolumeViz 3.0.
   * Must copy the rectangular part defined by @B subSlice @b of the XY slice @B sliceNumber @b
   * to the memory referenced by @B data@b.
   * Slices will not always be read sequentially.
   *
   * @param subSlice 2D region of the slice to return.
   * @param sliceNumber Slice number on the volume Z axis (first slice is 0).
   * @param data Copy the data into this buffer.
   *
   * You can use the convenience method getBuffer() to read data from file. Note:
   * setFilename() must have been called previously.
   */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data )=0;

  /** 
   * Same as getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data )
   * but using an SoBufferObject as the target of the data.
   * If not reimplemented then the version with "unsigned char*" parameter is called
   */
  virtual void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, SoBufferObject * bufferObject);

  #ifdef OIV_NET_DOC
 /**
   * This method is optional. If it is not implemented, the method GetSubSlice() is used
   * instead. In this case, GetSubSlice() must be implemented.
   *
   * If this method is implemented, it must copy the brick defined by @B subVolume @b to
   * the memory referenced by @B data@b, and must return true.
   * This method is useful only if the system provides a very fast way to get a brick.
   * Otherwise GetSubSlice() is more efficient.
   *
   * NOTE: This method is not called in LDM mode.
   */
 #else
  /**
   * This method is optional. If it is not implemented, the method getSubSlice() is used
   * instead. In this case, getSubSlice() must be implemented.
   *
   * If this method is implemented, it must copy the brick defined by @B subVolume @b to
   * the memory pointed to by @B data@b, and must return TRUE.
   * This method is useful only if the system provides a very fast way to get a brick.
   * Otherwise getSubSlice() is more efficient. 
   *
   * NOTE: This method is not called in LDM mode.
   */
#endif
  virtual SbBool getSubVolume( const SbBox3i32& subVolume, void * data );

  /**
   * Memory management policies
   **/
  enum CopyPolicy
  {
    /** VolumeViz will manage memory. */
    COPY,
    /** The reader manages memory. */
    NO_COPY,
    /** The reader allocates the memory and VolumeViz deallocates it. */
    NO_COPY_AND_DELETE
  };

  /**
   * This method, if implemented, will be used by VolumeViz to know
   * what the reader wants to do and what it is able to do.
   * VolumeViz will specify the real subvolume of the brick (the size may not be a
   * power of 2 if the brick is on the border) and the subSampling level
   * it wants to use.
   * The reader, based on those inputs, will respond by telling VolumeViz
   * exactly at what subSampling level it will return the data (by setting
   * the @B actualSubSampleLevel@b parameter) and who will be in charge
   * of managing the memory (by setting the @B policy@b parameter).
   * The method should return FALSE if getSubVolume is not used. 
   * NOTE: This method is not called in LDM mode.
   * [OIVJAVA-WRAPPER PACK{SubVolumeInfo}]  
   */
   virtual SbBool getSubVolumeInfo(
    const SbBox3i32& subVolume,                 // in: bounds of subvolume (brick)
    const SbVec3i32& requestedSubsampleLevel,   // in: subsample level VolViz needs
    SbVec3i32& actualSubsampleLevel,            // out : subsample level reader returns.
    SoVolumeReader::CopyPolicy& policy          // out : copyPolicy
    );

  /**
   * This method is optional.
   * If implemented, VolumeViz will use the data returned by the reader.
   * Given the subVolume that VolumeViz needs,
   * the reader should either copy the data using the pointer VolumeViz gives
   * (if its copyPolicy is COPY) or just set the data pointer to where the data
   * is present in memory (if its copyPolicy is NO_COPY).
   *
   * If the reader is unable to return data at the requested subsample level,
   * VolumeViz will automatically subsample the data that the reader provides.
   * (This was the only supported behavior in Version 3.0.)
   *
   * If the reader returns data that's at the requested (or lower) resolution,
   * VolumeViz will use that data without additional processing. This allows you
   * to avoid the overhead of subsampling and is also a way to force VolumeViz
   * to use lower resolution data.
   *
   * Generally, if you implement getSubVolume, you must also implement
   * #getSubVolumeInfo. If not, then you must return full resolution data and
   * copy it using the pointer that VolumeViz gives.
   *
   * NOTE: This method is not called in LDM mode.
   */
  virtual SbBool getSubVolume(
    const SbBox3i32& subVolume,               // in: bounds of subvolume (brick)
    const SbVec3i32& actualSubsampleLevel,    // in: reader subsample
    void *& data
  );

  /**
   * Utility function provided by SoVolumeReader for subclass readers to call.
   *
   * Returns the size of the brick the reader must use, based on @B subsamplingLevel@b
   * and @B realSize@b of the brick.
   * If the subsampling level is greater than 0 on an axis, the corresponding size
   * is computed as follows:<BR>
   * 1. @B realSize@b is divided by 2**@B subsamplingLevel@b,<BR>
   * 2. @B brickSize@b is the next greater power of 2.
   *
   * For example, if @B subsamplingLevel@b[0]=1 and @B realSize@b[0]=21, then the returned @B readerSize@b[0]=16.
   *
   * If @B subsamplingLevel@b is 0, the corresponding size is the @B realSize@b.
   */
   SbVec3i32 getNumVoxels( const SbVec3i32& realSize, const SbVec3i32& subsamplingLevel );

   /**
    * Utility function provided by SoVolumeReader for subclass readers to call.
    *
    * If the reader uses the NO_COPY policy, this method returns the size
    * to allocate for the brick.
    * For each axis of the brick, this size is:
    *
    * (first power of 2 greater than @B realSize@b) / ( 2**@B subsamplingLevel@b)
    */
   SbVec3i32 getSizeToAllocate( const SbVec3i32& realSize, const SbVec3i32& subsamplingLevel );

  /**
  * Specifies the path of the file. Returns 0 for success. Any other return
  * value indicates failure.
  */
  virtual int setFilename( const SbString& filename );

 /**
  * Returns the path of the file.
  */
  SbString getFilename() const;

  //------------ for LDM -----------------//
  /**
   * Returns TRUE if the data is already organized in tiles for the LDM module. @BR
   * In other words, all drivers that directly support the getTile() method should
   * return TRUE from isDataConverted.
   * If TRUE is returned, VolumeViz will use the readTile method and will NOT call
   * getSubVolume() or getSubSlice().
   */
  virtual SbBool isDataConverted() const
    { return m_dataConverted; }

  /**
   * Returns tile dimensions in voxels when using data stored in tiles. @BR
   * Return FALSE if data is not stored in tiles.
   */
  virtual SbBool getTileSize(SbVec3i32& size);

  #ifdef OIV_NET_DOC
/**
   *
   * Given an index, reads a tile if the data is organized in tiles (for LDM).
   * In the default LDM architecture, the LDM data is based on an octree
   * topology (see SoVRLdmFileReader). The index passed is 0 for the tile
   * of lowest resolution representing the entire volume (octree root node).
   * The index increments linearly going down through the octree.
   *
   * Indexing works as follows:
   *
   * Tile 1 is the lower back left corner of the cube.
   * The index increments on X, then Y, and finally Z.
   * So the back tiles are:@BR
   *
   * 3  4@BR
   * 1  2
   *
   * And the front tiles are:@BR
   *
   * 7  8@BR
   * 5  6
   *
   * The tiles of full resolution are the leaf tiles.
   *
   * @param index Specifies a fileID, the id of an existing tile (fileID=tileID only in a cubical volume).
   * @param buffer The tile data should be copied into this buffer (allocated by VolumeViz).
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   */
 #else
  /**
   * Given an index, returns the corresponding tile data (if the data is organized in tiles for LDM). @BR
   * In the default LDM architecture, the LDM data is based on an octree
   * topology (see SoVRLdmFileReader). The index passed is 0 for the tile
   * of lowest resolution representing the entire volume (octree root node).
   * The index increments linearly going down through the octree.
   *
   * Indexing works as follows:
   *
   * Tile 1 is the lower back left corner of the cube.
   * The index increments on X, then Y, and finally Z.
   * So the back tiles are:@BR
   *
   * 3  4@BR
   * 1  2
   *
   * And the front tiles are:@BR
   *
   * 7  8@BR
   * 5  6
   *
   * The tiles of full resolution are the leaf tiles.
   *
   * @param index Specifies a fileID, the id of an existing tile (fileID=tileID only in a cubical volume).
   * @param buffer The tile data should be copied into this buffer (allocated by VolumeViz).
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   *
   * @deprecated No longer used. Use SoBufferObject* readTile(int index, const SbBox3i32& tilePosition).
   * @DEPRECATED_SINCE_OIV 8.5
   *
   */
#endif
  SoDEPRECATED virtual SbBool readTile(int index, unsigned char*&buffer, const SbBox3i32& tilePosition);
  
  /** 
   * Same as readTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition)
   * but using an SoBufferObject (allocated by LDM) as the target of the data.
   * If not reimplemented then the version with "unsigned char*" parameter is called
   *
   * @deprecated No longer used. Use SoBufferObject* readTile(int index, const SbBox3i32& tilePosition).
   * @DEPRECATED_SINCE_OIV 8.5
   *
   */
  SoDEPRECATED virtual SbBool readTile(int index, SoBufferObject *buffer, const SbBox3i32& tilePosition);

  /**
   * Given an index, reads a tile if the data is organized in tiles (for LDM). @BR
   * In the default LDM architecture, the LDM data is based on an octree
   * topology (see SoLDMFileReader). The index passed is 0 for the tile
   * of lowest resolution representing the entire volume (octree root node).
   * The index increments linearly going down through the octree.
   *
   * @param index specifies a fileID, the id of an existing tile (fileID=tileID in a cubical volume).
   * @param tilePosition specifies the position of the data in the associated volume data of the tile
   * corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   * used but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   *
   * Returns the pointer to a buffer (allocated by the reader) containing data.
   */
  virtual SoBufferObject* readTile(int index, const SbBox3i32& tilePosition);

   /** 
   * Read directly from the data source, a trace inside a tile. @BR
   * @param index the fileId of an existing tile.
   * @param buffer the buffer in which the data is returned.
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   * @param tracePosition represents the (i,j) coordinates of the trace.
   */
  virtual SbBool readXTraceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const SbVec2i32& tracePosition);

   /** 
   * Read directly from the data source, an orthoslice on the Y axis (Zaxis == 1) inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readYSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

   /** 
   * Read directly from the data source, an orthoslice on the Z axis (Zaxis == 2) inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readZSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

   /** 
   * Read directly from the data source, an orthoslice on the X axis (Zaxis == 0) inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the tile in the associated volume, in voxel coordinates. @BR
   * In the default SoVRLdmFileReader, the tilePosition isn't actually used by the reader
   * but it is passed as a convenience for customized readers (can be used for mapping to a
   * different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readXSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

  /**
   * Should return TRUE if the reader is thread safe. @BR
   * This function is called by VolumeViz when using the multiIO mode (LDM only).
   * LDM multi-threaded data loading can only be used if this method returns TRUE.
   */
  virtual SbBool isThreadSafe() const;

  /**
   * Returns the number of data tiles that have been subsampled (non full resolution).
   */
  inline int getNumSubsampledTiles()
  {return m_numSubsampledTiles;};

  /**
   * Returns original file name from which the data has been
   * converted to LDM format if stored in file.
   */
  virtual SbString getOriginalFilename() const
  { return SbString(""); }

  /**
   * Returns border (overlap) value if stored in file.
   */
  virtual int getBorderFlag()
  {return -1;}

  /**
   * Returns min max if stored in file (obsolete)
   * [OIVJAVA-WRAPPER NAME{getIntMinMax}]
   */
  virtual SbBool getMinMax(int& min, int& max);

  /**
   * Returns min max if stored in file for integer data type
   */
  virtual SbBool getMinMax(int64_t & min, int64_t & max);

  /**
   * Returns min max if stored in file for float data type
   * [OIVJAVA-WRAPPER NAME{getDoubleMinMax}]
   */
  virtual SbBool getMinMax(double & min, double & max);

  /**
   * Returns histogram if stored in file.
   */
  virtual SbBool getHistogram(std::vector<int64_t>& numVox);

  /**
   * Sets whether or not the reader should automatically try to detect if the coordinate system
   * used is direct or not.
   * The function will return FALSE if the feature is not supported
   * by the current reader.
   * Default is false.
   */
  virtual SbBool setDirectCoordSysAutoDetection(SbBool autoValue);
  /**
   * Return automatic detection value.
   */
  virtual SbBool getDirectCoordSysAutoDetection();

  /**
   * Specify if the coordinate system used is direct or not.
   * The function will return FALSE if the feature is not supported
   * by the current reader.
   * Default is true.
   */
  virtual SbBool setDirectCoorSys(SbBool directCoord);

  /**
   * Return whether the coordinate system used is direct or not.
   */
  virtual SbBool getDirectCoordSys();


  /**
   * Available reader type.
   */
  enum ReaderType {
    /** Unknown */
    NO_READER,
    /** Amira .am */
    AM,
    /** AVS */
    AVS,
    /** Dicom */
    DICOM,
    /** Generic */
    GENERIC,
    /** Open Inventor LDM */
    LDM,
    /** In memory */
    MEMORY,
    /** Raster Stack */
    RASTERSTACK,
    /** Segy */
    SEGY,
    /** Vol */
    VOL,
    /** Vox */
    VOX
  };

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType (){return NO_READER;};

  /**
   * Coordinate type used by this data set.
   */
  enum CoordinateType {
  /**
   * Uniform grid spacing along each axis.
   */
    COORDINATES_UNIFORM = 0,
  /**
   * Grid spacing defined by x, y, z values.
   */
    COORDINATES_RECTILINEAR
  };

  /**
   * Returns coordinate type used by the data set.
   */
  CoordinateType getCoordinateType();

  /**
   * Returns the coordinates for the specified axis.
   */
  const float * getRectilinearCoordinates(Axis axis) const;

  /**
   * Sets rectilinear coordinates for the data set.
   */
  void setRectilinearCoordinates(const float *x, const float *y, const float *z);

  /**
   * Returns TRUE if the data set contains RGBA color values.
   */
  virtual SbBool isRGBA() const 
  { return m_isRGBA; }

  /**
   * Specifies if data must be considered as RGBA.
   */
  inline void setRGBA(const SbBool flag)
  { m_isRGBA = flag; }

  ////////////////////////////////////////////////////////////////////////////////////////////////
  // deprecated methods
  //

  /** @deprecated No longer used. Use getSubSlice() instead.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED virtual void getNextSlice( int sliceNumber, void *data );

  /** @deprecated No longer used.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED virtual void skipSlice( int numSlices );

  /** @deprecated No longer used.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED virtual void end( ) {};

  /** @deprecated No longer used. Use getTileSize( SbVec3i32& ).
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIVJAVA-WRAPPER NAME{getShortTileSize}]
   */
  SoDEPRECATED virtual SbBool getTileSize(SbVec3s& size)
  {
    SbVec3i32 sizeI32;
    SbBool rc = getTileSize( sizeI32 );
    size.setValue( (short)sizeI32[0], (short)sizeI32[1], (short)sizeI32[2] );
    return rc;
  };

  /** @deprecated No longer used. Use getDataChar( SbBox3f& , SoDataSet::DataType &, SbVec3i32& ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual void getDataChar( SbBox3f &size, SoDataSet::DataType &type, SbVec3s &dim )
  {
    SbVec3i32 dimI32;
    getDataChar( size, type, dimI32 );
    dim.setValue( (short)dimI32[0], (short)dimI32[1], (short)dimI32[2] );
  };

  /** @deprecated No longer used. Use getNumVoxels( const SbVec3i32&, const SbVec3i32& ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED SbVec3s getNumVoxels( const SbVec3s& realSize, const SbVec3s& subsamplingLevel )
  {
    SbVec3i32 realSizeI32( realSize[0], realSize[1], realSize[2] );
    SbVec3i32 subsamplingLevelI32( subsamplingLevel[0], subsamplingLevel[1], subsamplingLevel[2] );
    SbVec3i32 numVoxels = getNumVoxels( realSizeI32, subsamplingLevelI32 );
    return SbVec3s( (short)numVoxels[0], (short)numVoxels[1], (short)numVoxels[2] );
  };

  /** @deprecated No longer used. Use getSizeToAllocate( const SbVec3i32&, const SbVec3i32& ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED SbVec3s getSizeToAllocate( const SbVec3s& realSize, const SbVec3s& subsamplingLevel )
  {
    SbVec3i32 realSizeI32( realSize[0], realSize[1], realSize[2] );
    SbVec3i32 subsamplingLevelI32( subsamplingLevel[0], subsamplingLevel[1], subsamplingLevel[2] );
    SbVec3i32 size = getSizeToAllocate( realSizeI32, subsamplingLevelI32 );
    return SbVec3s( (short)size[0], (short)size[1], (short)size[2] );
  };

  /** @deprecated No longer used. Use getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual void getSubSlice( const SbBox2s& subSlice, int sliceNumber, void * data )
  {
    SbBox2i32 subSliceI32( subSlice.getMin()[0], subSlice.getMin()[1], subSlice.getMax()[0], subSlice.getMax()[1] );
    getSubSlice( subSliceI32, sliceNumber, data );
  };

  /** @deprecated No longer used. Use getSubVolume( const SbBox3i32& subVolume, void * data ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual SbBool getSubVolume( const SbBox3s& subVolume, void * data )
  {
    SbBox3i32 subVolumeI32( subVolume.getMin()[0], subVolume.getMin()[1], subVolume.getMin()[2],
                            subVolume.getMax()[0], subVolume.getMax()[1], subVolume.getMax()[2] );
    return getSubVolume( subVolumeI32, data );
  };

  /** @deprecated No longer used. Use getSubVolume( const SbBox3i32&, const SbVec3i32&, void *& data ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual SbBool getSubVolume( const SbBox3s& subVolume, const SbVec3s& aSL, void *& data )
  {
    SbBox3i32 subVolumeI32( subVolume.getMin()[0], subVolume.getMin()[1], subVolume.getMin()[2],
                            subVolume.getMax()[0], subVolume.getMax()[1], subVolume.getMax()[2] );
    SbVec3i32 aSLI32( aSL[0], aSL[1], aSL[2] );
    return getSubVolume( subVolumeI32, aSLI32, data );
  };

  /** @deprecated No longer used. Use getSubVolumeInfo( const SbBox3i32&, const SbVec3i32&, SbVec3i32&, SoVolumeReader::CopyPolicy& ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual SbBool getSubVolumeInfo( const SbBox3s& subVolume, const SbVec3s& rSL, SbVec3s& aSL, SoVolumeReader::CopyPolicy& policy)
  {
    SbBox3i32 subVolumeI32( subVolume.getMin()[0], subVolume.getMin()[1], subVolume.getMin()[2],
                            subVolume.getMax()[0], subVolume.getMax()[1], subVolume.getMax()[2] );
    SbVec3i32 rSLI32( rSL[0], rSL[1], rSL[2] );
    SbVec3i32 aSLI32;
    SbBool rc = getSubVolumeInfo( subVolumeI32, rSLI32, aSLI32, policy );
    aSL.setValue( (short)aSLI32[0], (short)aSLI32[1], (short)aSLI32[2] );
    return rc;
  };

  /** @deprecated No longer used. Use readTile( int index, unsigned char*&buffer, const SbBox3i32& tilePosition ).
   * @DEPRECATED_SINCE_OIV 6.0
   */
  SoDEPRECATED virtual SbBool readTile( int index, unsigned char*&buffer, const SbBox3s& tilePosition );


  //
  // end deprecated methods
  ////////////////////////////////////////////////////////////////////////////////////////////////

SoINTERNAL public:
  //for volume having a series of data per datum
  //used by ReservoirViz. The converter asks the eclipse reader for the datum.
  //not used in vviz which uses getDataChar(...type...). (must keep for compatibility reasons).
  virtual ReadError getDataChar( SbBox3f &size, std::vector<SoDataSet::DatumElement>& datum, SbVec3i32 &dim );

  void lockFileMutex();
  void unlockFileMutex();
  void setNumSubsampledTiles(int num){m_numSubsampledTiles = num;};
  /**
   * Converts from type @B typeIn @b to type @B typeOut @b.
   * By default, if typeOut is of smaller size than typeIn, only the most significant bytes are
   * copied into the dest buffer (data is right shifted).
   * If typeOut is of bigger size than typeIn, then the data is shifted to the left
   * because VolumeViz truncates the least significant bytes if the data range is larger than the color range.
   * (Tt maps an unsigned short on an 8-bit color map by looking at the 8 most significant bits.)
   * If shiftData is FALSE, nothing is shifted (the data isn't changed).
   */
  void convert( SoDataSet::DataType typeIn , SoBufferObject* bufferIn,
                SoDataSet::DataType typeOut, SoBufferObject* bufferOut, int size, SbBool shiftData = true);

  /** @deprecated No longer used since version 8.0.
   * Use convert( SoDataSet::DataType, SoBufferObject* ,SoDataSet::DataType, SoBufferObject*, int , SbBool) instead.
   */
  SoDEPRECATED void convert( SoDataSet::DataType typeIn , void* bufferIn,
                SoDataSet::DataType typeOut, void* bufferOut, int size, SbBool shiftData = true);

  void convertDataRange( bool doRange, double min, double max );

  virtual int getNumBytesPerDatum();

  virtual bool isLDMReader() { return false; }
  virtual bool isVolumeMaskReader() { return false; }

  virtual bool hasDeadCell() { return false; }

  virtual bool isDead(int i,int j,int k);

  virtual uint8_t* getCellGridState() { return NULL; }

  virtual int getNbCell() { return 0; }

  virtual uint64_t getTileSizeFromFid(int fileId);// Virtual method, only used
                                                  // by resviz for now

  virtual void closeAllHandles() {}; // used internally to close all opened file before saving
                                     // ( needed for edition )

  virtual void restoreAllHandles() {}; // used internally to re open all closed file before saving
                                       // ( needed for edition )

 protected: //PROTECTED_TO_DOCUMENT
  /**
   * Destructor.
   */
  virtual ~SoVolumeReader();

  /** @deprecated No longer used. Redefine method isDataConverted() .
   * @DEPRECATED_SINCE_OIV 8.5
   */
  SbBool m_dataConverted;

  /**
   * Returns a pointer to a buffer of @B size @b bytes corresponding to a part of the file
   * at @B offset @b bytes from the beginning of the file.
   * Then you can directly read the memory pointed to by the returned pointer. This method
   * uses the memory paging system mechanism and thus is quite efficient.
   */
  void *getBuffer(int64_t offset, unsigned int size);

  // Convenient methods

  /**
   * Utility method that returns an integer from @B sizeBytes @b bytes starting at address @B ptr@b.
   * Also takes into account the machine architecture (little/big endian).
   */
  int bytesToInt( unsigned char *ptr, int sizeBytes );

  /**
   * Utility method to convert an integer into the correct architecture (little/big endian).
   */
  void swapBytes( int *intPtr, int sizeBytes );

  /**
   * Utility method to swap bytes of each element of an array of @B numElements @b elements.
   * The size of each element is @B numBytesPerElement@b.
   */
  void swapBytesN( void *buffer, int numElements, int numBytesPerElement );

  /**
   * Utility method to check if value is a valid IEEE 754 floating point number
   */
  SbBool isValidFloat( const float val );

  /**
   * Returns the size of the file when file I/O is handled by this class.
   */
  int64_t fileSize();

  //------------------------------------------------------------------------------
#ifndef HIDDEN_FROM_DOC
  SbString m_filename;

#endif // HIDDEN_FROM_DOC

protected:

  //if true, try to detect automatically whether the coord sys is diret or not.
  //default is true
  SbBool m_directCoordSysAutoDetect;
  //has the data been stored using a direct coordinate system?
  //default is true
  SbBool m_directCoordSys;

  std::vector<SoDataSet::DatumElement> m_datum;
  int m_bytesPerVoxel;
  int m_numTimeSteps;
  int m_curTimeStep;

  double m_rangeMin, m_rangeMax;
  bool   m_doRange;

  //True if header has already been read
  SbBool m_headerRead;

  CoordinateType m_coordinateType;
  std::vector<float> m_rectilinearCoordinates[3];

private:
  SbBool       m_isRGBA;
  int          m_numSubsampledTiles;
  SbBool       m_useFMM;
  void        *m_filehandle;
  int          m_filedesc;
  int64_t      m_filesize;
  void        *m_fmmdata;
  int64_t      m_fmmoffset;
  unsigned int m_fmmsize;

  void releasefmm();
  void bestmap(int64_t);

  SbThreadMutex* m_fileMutex;
};

inline SbBool
SoVolumeReader::getSubVolume( const SbBox3i32& , void *)
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getSubVolumeInfo(const SbBox3i32& ,const SbVec3i32& ,SbVec3i32& ,SoVolumeReader::CopyPolicy& )
{
   return FALSE;
}

inline SbBool
SoVolumeReader::getSubVolume(const SbBox3i32& ,const SbVec3i32& ,void *& )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::readTile(int , unsigned char*&, const SbBox3i32& )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::readXTraceInTile(int , unsigned char*& , const SbBox3i32& , const SbVec2i32& )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::readXSliceInTile(int , unsigned char*& , const SbBox3i32& , const uint32_t& )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::readYSliceInTile(int , unsigned char*& , const SbBox3i32& , const uint32_t& )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getMinMax(int& , int& )
{
  return FALSE;
}


inline SbBool
SoVolumeReader::getMinMax(int64_t &, int64_t &)
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getMinMax(double & , double & )
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getHistogram(std::vector<int64_t>&)
{
  return FALSE;
}

inline SbBool
SoVolumeReader::setDirectCoordSysAutoDetection(SbBool)
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getDirectCoordSysAutoDetection()
{
  return m_directCoordSysAutoDetect;
}

inline SbBool
SoVolumeReader::setDirectCoorSys(SbBool)
{
  return FALSE;
}

inline SbBool
SoVolumeReader::getDirectCoordSys()
{
  return m_directCoordSys;
}

inline void
SoVolumeReader::getNextSlice( int , void *)
{
}

inline void
SoVolumeReader::skipSlice( int )
{
}

inline bool
SoVolumeReader::isDead(int, int, int)
{
  return false;
}

inline uint64_t
SoVolumeReader::getTileSizeFromFid(int)
{
  return 0;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // _SO_VOLUME_READER_
