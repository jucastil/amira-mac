/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _LDM_READER_
#define _LDM_READER_

#include <LDM/nodes/SoDataSet.h>
#include <Inventor/STL/vector>
#include <Inventor/threads/SbThread.h>
#include <LDM/readers/SoVolumeReader.h>
#include <LDM/xml/SbXmlTag.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#pragma warning(disable:4996)
#endif

class TiXmlElement;
class SbThreadMutex;
class SiBitFile;
class SoDataCompressor;
class SoDataCompressInfo;

/**
 * @LDMEXT Base class for LDM data set readers
 *
 * @ingroup LDMReaders
 *
 * @DESCRIPTION
 *
 * This is the base class for specific LDM readers.
 *
 *  This class retrieves the LDM header file tags that are general to
 *  all LDM files.
 *  Custom tags for classes derived from SoLDMReader can be retrieved by overriding
 *  the #handleHeader method.
 *  General tags common for all LDM Readers are:
 * \code
 *  <?xml version="1.0" encoding="utf-8" ?>
 *  <VolumeInformation>
 *    <OriginalFile>3dhead.vol</OriginalFile>
 *    <Size> //or dimension//
 *      <U>256</U>
 *      <V>256</V>
 *      <W>109</W>
 *    </Size>
 *    <TileSize>
 *      <U>64</U>
 *      <V>64</V>
 *      <W>64</W>
 *    </TileSize>
 *    <DataType>
 *       <Type>n</Type><Num>m</Num>
 *       ...
 *    <DataType>
 *    <Border>1</Border>
 *    <DataFilename>3DHEAD.dat</DataFilename>//separate datafile//
 *    <WordFormat>1</WordFormat>//data stored in little/big endian//
 *    <CompletionFilename>3dhead.fcp</CompletionFilename>//if the conversion was interrupted, refer to this file
 *
 *    <RectilinearMapping>
 *     <mapping axis="U">
 *      <map>-180</map>
 *      <map>-160</map>
 *      ... one entry per voxel on U axis
 *     </mapping>
 *      ... repeat for V, W axis
 *    </RectilinearMapping>
 * \endcode
 * Note that the minimum tags that MUST be in the LDM header are \<Size\> or \<Dimension\> and \<TileSize\>.
 * Otherwise the reader will throw a "tag missing" exception.
 */

// abstract class for LDM reader
class LDM_API SoLDMReader : public SoVolumeReader
{
  SO_FIELDCONTAINER_HEADER(SoLDMReader);

public:
  using SoVolumeReader::getDataChar;
  using SoVolumeReader::getSubSlice;
  using SoVolumeReader::readTile;

  /**
   * LDM Reader error code
   */
  enum SoLDMError{
    /** no error */
    LDM_NO_ERROR,
    /** file not found */
    LDM_FILE_NOT_FOUND,
    /** XML START Tag not found */
    LDM_XML_ROOT_START_TAG_NOT_FOUND,
    /** XML END Tag not found */
    LDM_XML_ROOT_END_TAG_NOT_FOUND,
    /** Alternate file not found */
    LDM_ALTERNATE_FILE_NOT_FOUND,
    /** XML parsing error */
    LDM_XML_PARSING_ERROR,
    /** Size tag missing */
    LDM_SIZE_TAG_MISSING,
    /** Completion file not found */
    LDM_COMPLETION_FILE_NOT_FOUND,
    /** No error */
    LDM_RD_NO_ERROR,
    /** file not found */
    LDM_RD_FILE_NOT_FOUND_ERROR,
    /** Unsupported data file type */
    LDM_RD_UNSUPPORTED_DATA_TYPE_ERROR,
    /** Unknown error */
    LDM_RD_UNKNOWN_ERROR
  } ;

  /** Constructor. */
  SoLDMReader();

  /**
   *
   * Returns the bounding box of the total data in world coordinates.
   */
  virtual SbBox3f getSize();
  /**
   *
   * Returns the dimension of the data.
   */
  virtual SbVec3i32 getDimension();
  /**
   *
   * Returns the size of a data tile
   */
  virtual SbBool getTileSize(SbVec3i32& tile);

  /** @deprecated No longer used. Use getTileSize( SbVec3i32& ).
   * @DEPRECATED_SINCE_OIV 6.0
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  SoDEPRECATED virtual SbBool getTileSize(SbVec3s& size);

  /**
   * Returns the bounding box of the data associated with
   * the specified file ID. The file ID corresponds to the
   * tile ID in an LDM data file. If returns FALSE, not supported.
   */
  //not used in vviz. used on resviz because the geom is not implicit anymore.
  virtual SbBool getBbox(int fileId, SbBox3f& box);

  /**
   * Returns the center of the data associated with the
   * specified file ID. If returns FALSE, not supported.
   */
  //not used in vviz. used on resviz because the geom is not implicit anymore.
  virtual SbBool getCenter(int fileId, SbVec3f& center);

  /**
   * Gets the characteristics (file header) of the data volume.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar( SbBox3f &size, SoDataSet::DataType &type,  SbVec3i32 &dim );

  /**
   *  Note: SoLDMReader does not implement this method.
   */
  void getSubSlice( const SbBox2i32& subSlice, int sliceNumber, void * data );

  /**
   *
   * Given an index, reads a tile if the data is organized in tiles (for LDM).
   * In the default LDM architecture, the LDM data is based on an octree
   * topology (see SoLDMFileReader). The index passed is 0 for the tile
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
   * @param index specifies a fileID, the id of an existing tile (fileID=tileID in a cubical volume).
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition specifies the position of the data in the associated volume data of the tile
   * corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   * used but it is passed as a convenience for customized reader (can be used for mapping to a
   * different index scheme).
   */
  virtual SbBool readTile(int index, unsigned char*&buffer, const SbBox3i32& tilePosition);

  /**
   * Given an index, reads a tile if the data is organized in tiles (for LDM).
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
   * Returns a pointer to an allocated buffer containing the data.
   */
  virtual SoBufferObject* readTile(int index, const SbBox3i32& tilePosition);

   /**
   * Read directly from the LDM data source, a trace inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the data in the associated volume data of the tile
   *    corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   *    used but it is passed as a convenience for customized reader (can be used for mapping to a
   *    different index scheme).
   * @param tracePosition represents the (i,j) coordinates of the trace.
   */
  virtual SbBool readXTraceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const SbVec2i32& tracePosition);

   /**
   * Read directly from the LDM data source, an orthoslice on the X axis inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the data in the associated volume data of the tile
   *    corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   *    used but it is passed as a convenience for customized reader (can be used for mapping to a
   *    different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readXSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

  /**
   * Read directly from the LDM data source, an orthoslice on the Y axis inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the data in the associated volume data of the tile
   *    corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   *    used but it is passed as a convenience for customized reader (can be used for mapping to a
   *    different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readYSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

  /**
   * Read directly from the LDM data source, an orthoslice on the Z axis inside a tile.
   * @param index The fileId of the tile.
   * @param buffer The buffer in which the data is returned.
   * @param tilePosition Specifies the position of the data in the associated volume data of the tile
   *    corresponding to the given index. In the default SoVRLdmFileReader, the tilePosition isn't actually
   *    used but it is passed as a convenience for customized reader (can be used for mapping to a
   *    different index scheme).
   * @param slicePosition The slice position in the tile.
   */
  virtual SbBool readZSliceInTile(int index, unsigned char*& buffer, const SbBox3i32& tilePosition, const uint32_t& slicePosition );

  /**
   * Returns the minimum and maximum data values (obsolete).
   * [OIVJAVA-WRAPPER NAME{getIntMinMax}]
   */
  virtual SbBool getMinMax(int & min, int & max);

  /**
   * Returns the minimum and maximum data values.
   */
   virtual SbBool getMinMax(int64_t & min, int64_t & max);

  /**
   * Returns the minimum and maximum data values (for float values).
   * [OIVJAVA-WRAPPER NAME{getDoubleMinMax}]
   */
  virtual SbBool getMinMax(double & min, double & max);

  /**
   *
   * Returns the distribution of data values, i.e., the number of voxels per data value.
   * @B numVox(0)@b  is the number of voxels with value 0, @B numVox(1)@b  is the number of voxels
   * with value 1, and so on.
   */
  virtual SbBool getHistogram(std::vector<int64_t>& numVox);

  /**
   * Returns whether the bytes of the data are stored in big or little endian order.
   * The order is little endian if the function returns true.
   */
  virtual bool isLittleEndian();

  /**
   *
   * Returns original file name from which the data has been converted
   * to LDM format if stored in file.
   */
  virtual SbString getOriginalFilename() const;

  /**
   *
   * Returns the border flag. If 0, tiles do not overlap. If not 0, they do.
   */
  virtual int getBorderFlag();

  /**
   *
   * Gets the first occurrence of the XML element whose tag name is specified by @B tagName@b.
   * Then the associated value or subtags can be fetched using the SbXmlElement methods.
   * Custom XML tags can be added to the LDM header file by using
   * the method SoLDMConverter::setXmlCallback().
   */
  virtual SbXmlTag getXmlTag( const char * tagName );

  /**
   *
   * Returns the reader type.
   */
  virtual ReaderType getReaderType (){return LDM;};

  /**
   * Handle tags of LDM reader inheriting from this base class
   */
  virtual int handleHeader(TiXmlElement *) {return LDM_NO_ERROR;} ;

  /**
   * Should return TRUE if the reader is thread safe. @BR
   * This function is called by VolumeViz when using the multiIO mode (LDM only).
   * LDM multi-threaded data loading can only be used if this method returns TRUE.
   */
  virtual SbBool isThreadSafe() const;

 SoINTERNAL public:

  /**
   * This function must be implemented when deriving from the general LDM reader.
   * Describes each datum as a vector of m*n dataTypes (see SoDataSet).
   */
  virtual std::vector<SoDataSet::DatumElement> getDatumDescription();

  /**
   * Return number of bytes per Datum.
   */
  int  getNumBytesPerDatum();

  virtual bool isLDMReader() { return true; }

  virtual bool isVolumeMaskReader() { return false; }

  /**
   * This method is only of interest to people writing a custom LDM file reader.
   * Returns the data used to render a hole (a tile which does not exist in the file).
   * This may occur when the original file was not fully converted.
   * By default, a tile of all zeros is returned.
   */
  virtual unsigned char* getHoleData();

  SiBitFile* getFileCompletion();

  SoLDMError getLastErr() { return m_lastError; };

  //Return the default size of a tile (64x64x64)
  static const SbVec3i32 &getDefaultTileDim() { return DEFAULT_TILE_DIM; }

  /**
   * Returns true if the each cell of a tile contains 8 vertices.
   * Returns false if the each cell of a tile contains 1 vertices.
   */
  SbBool getCell8to1() {
    return m_cell8to1;
  }

  /**
   * Returns the minimum and maximum data values for the given tile. @BR
   * v[0] is min, v[1] is max
   */
  inline const SbVec2d& getMinMax(int fileId) const;

  /**
   * Returns true if per tile min-max information is available.
   */
  inline bool hasPerTileMinMax() const;

  /**
   * Returns the undefined value. Default is Nan @BR
   * The undefined value is used by some render nodes, for example
   * SoHeightFieldRender, which ignore vertices having this value.
   */
  inline double getUndefinedValue() const;

  /**
   * Returns the pointer to specific header handled by specific reader
   */
  virtual void* getSpecificHeader() { return NULL; }

  /**
   * Virtual method, only used by ResViz for now
   */
  virtual uint64_t getTileSizeFromFid(int fileId);

  /**
   * Virtual internal method, used to close all handle on opened
   * files. Mainly used for save Editing feature
   */
  virtual void closeAllHandles();

  /**
  * Virtual internal method, used to re open all handle closed
  * when edition is saved
  */
  virtual void restoreAllHandles();

  /**
  * Virtual internal method to know if the data set handled by 
  * the reader is a bitset DataSet
  */
  virtual bool isDataSetBitSet();
 
  /**
  * Virtual internal method to specify to the reader if dataset
  * has tile dimensions forced to Pow2 or not. 
  */
  virtual void setTileDimPow2Forced( bool flag );

  /**
   * @copydoc SoVolumeReader::isDataConverted
   */
  virtual SbBool isDataConverted() const
    { return TRUE; }

  virtual void reloadTileMinMax();

protected:
  /** Destructor. */
  virtual ~SoLDMReader();

  SoLDMError m_lastError;
  int m_makeFakeData;
  int m_levelMax;

  bool readXmlHeader(int& errorCode);

  static const SbVec3i32 DEFAULT_TILE_DIM;
  SbVec3i32 m_tileSize;
  int m_border;
  double m_defaultValue;

  SbBool m_cell8to1;
  int m_compression;
  SbBox3f   m_size;
  SbVec3i32 m_dim;

  unsigned char* m_hole;
  SbBool m_HeaderRead;

  //Compression
  bool m_useCrc32;
  SoType m_compressType;
  size_t m_compressLevel;
  size_t m_numTileInfos;
  SoDataCompressInfo* m_compressInfos;

  // Some preference info
  SbBool m_ldmUseCompressedBitSet;
  SbBool m_ldmUseInMemCompression; 

  SbString m_alternateFileName;
  SbString m_completionFileName;
  SbString m_originalFile;

  bool hasCompletionFile() const { return m_hasCompletionFile; }

  unsigned int *m_compressionIndexArray;

  struct Descriptor {
    FILE*         file;
    SiBitFile*    completion;
    SbThreadId_t  threadID;
    SoDataCompressor *compressor;
  };
  std::vector<Descriptor*> m_descriptors;
  Descriptor* getDescriptor( SbThreadId_t id, bool forceBuffering = false );

  SbThreadMutex* m_ldmFileMutex;

  SbBool getFakeData(int index, unsigned char*&buffer, const SbBox3i32& tilePosition);
  SbBool getFakeDataGeom(int index, unsigned char*&buffer, const SbBox3i32& tilePosition);
  double getFakeValue( const SbBox3i32& tilePosition);

  /* These three function have been added to handle specific header
   * managed by specific reader
   */

  // Read the specific header from file
  virtual void readSpecificHeader(FILE*) {};   // No name for parameter to avoid compilation warning
                                               // parameter is the name of the file currently read

  // Flag to determine if the specific header has already
  // been read
  virtual bool isSpecificHeaderRead() { return true; }

  // get the specific offset from the specific header. This offset
  // represent the amount of data added by specific reader at the beginning
  // of the LDM file
  virtual int getSpecificOffset(bool aligned = true) { return !aligned; }

  void* m_xmlDoc;
  void* m_xmlRoot;// a son can parse header from m_xmlRoot

  bool m_littleEndian;
  bool m_headerDirty;

  void oldUncompress(FILE* dataFile, int64_t compressedSize, size_t tileSize, char* buffer);
  void oldGetOffsetAndSize(int index, int64_t& compressedSize, int64_t& offset);

  void uncompressTile(Descriptor* desc, int64_t compressedSize, size_t tileSize, char* buffer);
  void getOffsetAndSize(Descriptor* compressor, int index, int64_t& compressedSize, int64_t& offset);
  void checkCrc32(char* buffer, int tileIndex, size_t tileSize);

private:
  enum DebugBorderMode
  {
    NORMAL_BORDERS = 0,
    MARK_BORDERS = 1,
    ONLY_BORDERS = 2
  };


  void internalInit();

  /**Fill buffer with perlin noise data */
  template<typename T> void getFakeDataNoise(void* buffer, const SbBox3i32& tilePosition);

  /** Highlight borders with special value*/
  void visibleBorder(unsigned char* buffer);

  /** Read only borders */
  void readBorderOnly(unsigned char* buffer);

  /** Load min max tiles infos */
  void readTileMinMax(TiXmlElement *s);

  /** Extract undefined value from xml */
  void extractUndefValue(TiXmlElement* element);

  /** Number of file id in file */
  size_t m_numFileIds;

  /** MinMax of each fileid */
  std::vector<SbVec2d> m_tileMinMax;

  /** Undefined value */
  double m_undefValue;

  /** Undef value defined or not */
  bool m_hasUndefValue;

  /** Variables used for fake data noise */
  bool m_fakeDataNoise;
  unsigned int m_fakeDataNumOctaves;
  float m_fakeDataPersistence;

  /** Debug borders: 1 mark borders with a special value, 2 show only border, 0 off */
  static DebugBorderMode s_debugBorders;

  SbBool m_hasCompletionFile;
  SbBool m_hasAlternateFile;

  // Specific flag to handle bitset dataset
  bool m_bIsBitSetDataSet;

  /** If true, tile dim is rounded to a pow 2 dim*/
  bool m_forcePow2TileDim;

  // Used to restore internal path after filename has been changed
  // mainly used be edition 
  void resetInternalPath();
};

/*******************************************************************************/
inline const SbVec2d&
SoLDMReader::getMinMax(int fileId) const
{
  return m_tileMinMax[fileId];
}

/*******************************************************************************/
inline bool
SoLDMReader::hasPerTileMinMax() const
{
  return !m_tileMinMax.empty();
}

/*******************************************************************************/
inline double
SoLDMReader::getUndefinedValue() const
{
  return m_undefValue;
}

inline SbBool
SoLDMReader::getBbox(int , SbBox3f& )
{
  return FALSE;
}

inline SbBool
SoLDMReader::getCenter(int , SbVec3f& )
{
  return FALSE;
}

inline void
SoLDMReader::getSubSlice( const SbBox2i32& , int , void *)
{
}

inline SbBool
SoLDMReader::getMinMax(int & , int & )
{
  return FALSE;
}

inline SbBool
SoLDMReader::getMinMax(int64_t & , int64_t & )
{
  return FALSE;
}

inline
SbBool SoLDMReader::getMinMax(double & , double & )
{
  return FALSE;
}

inline SbBool
SoLDMReader::getHistogram(std::vector<int64_t>& )
{
  return FALSE;
}

inline uint64_t
SoLDMReader::getTileSizeFromFid(int)
{
  return 0;
}

inline bool
SoLDMReader::isDataSetBitSet()
{
  return m_bIsBitSetDataSet;
}

inline void
SoLDMReader::setTileDimPow2Forced( bool flag )
{
  m_forcePow2TileDim = flag;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
