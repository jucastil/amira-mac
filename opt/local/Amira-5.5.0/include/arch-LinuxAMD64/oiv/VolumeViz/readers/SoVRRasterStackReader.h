/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. Ognier (Jul 2005)
**=======================================================================*/
#ifndef  _SO_VR_RASTER_STACK_READER_
#define  _SO_VR_RASTER_STACK_READER_

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <LDM/readers/SoVolumeReader.h>
#include <Inventor/helpers/SbFileHelper.h>
#include <Inventor/image/SoRasterImageFile.h>
#include <Inventor/image/SoRasterReaderSet.h>
#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/image/SbRasterImage.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/string>
#include <VolumeViz/nodes/SoVolumeData.h>

/**
 *
 * @VREXT Raster stack reader.
 *
 * @ingroup VolumeVizReaders
 *
 * @DESCRIPTION
 *
 *  Reader for raster stack.
 *
 *  A raster stack is a list of raster images (that is, containing pixels, not vector graphics)
 *  of the same size so as to create a voxel volume.
 *  This reader uses a descriptive file (.lst) including a header and a list of all the raster image filenames.
 *  The file is structured as follows:
 * <PRE>
 *  Parameters {
 *    Raw 0
 *    Dims 2048 2048 100
 *    Size 10.000000 10.000000 10.000000 1250.000000 1250.000000 500.000000
 *    Channel 2
 *  }
 *
 *  C:/tmp/tiff/img00000.tiff
 *  C:/tmp/tiff/img00001.tiff
 *  C:/tmp/tiff/img00002.tiff
 *  C:/tmp/tiff/img00003.tiff
 *  C:/tmp/tiff/img00004.tiff
 *  ....</PRE>
 *  OR
 *  <PRE>
 *  Parameters {
 *    Raw 1
 *    Endianess 1
 *    HeaderLength 256
 *    PrimType 0
 *    Binary 0
 *    Dims 1024 1024 300
 *    Size 50.000000 50.000000 50.000000 1050.000000 1050.000000 250.000000
 *    Channel 1
 *  }
 *
 *  img00000.raw
 *  img00001.raw
 *  img00002.raw
 *  img00003.raw
 *  img00004.raw
 *  ....
 * </PRE>
 *  @B Header Description@b
 *
 *   - Raw: 0 (formatted data file), 1 (raw data file).@BR
 *   - Endianess: 0 (little endian), 1 (big endian) (for raw data only).@BR
 *   - HeaderLength: length of header in characters/bytes (for raw data only).@BR
 *   - PrimType: See SoDataSet::DataType (for raw data only).@BR
 *   - Binary: 0 (ASCII), 1 (binary) (for raw data only).@BR
 *   - Dims: height, width, depth in pixels of the stack.@BR
 *   - Size: Xmin Ymin Zmin Xmax Ymax Zmax, bounding box of the data set.@BR
 *   - Channel: See SoVRRasterStackReader::ChannelSelection.@BR
 *
 * Images in the list can be of different formats (uses all files formats supported by Open Inventor).
 * If images are of different sizes, RD_UNSUPPORTED_DATA_TYPE_ERROR is returned by #getDataChar.
 * The file path can be relative or absolute.
 *
 *
 */

 class VOLUMEVIZ_API SoVRRasterStackReader : public SoVolumeReader  
 {
  SO_FIELDCONTAINER_HEADER(SoVRRasterStackReader);

 public:

   /** Channel selection */
   enum ChannelSelection {
    /**
    *  Maximum of all channels.
    */
    MAX_CHANNEL = 0,   // Maximum of all channels
    /**
    *  Luminance.
    */
    LUMINANCE = 1,     // Luminance
    /**
    *  Red channel.
    */
    RED_CHANNEL = 2,   // Red channel
    /**
    *  Green channel.
    */
    GREEN_CHANNEL = 3, // Green channel
    /**
    *  Blue channel.
    */
    BLUE_CHANNEL = 4,  // Blue channel
    /**
    *  Alpha channel.
    */
    ALPHA_CHANNEL = 5, // Alpha channel
    /**
    *  All channels combined.
    */
    ALL_CHANNELS = 11  // All channels combined
   };

  /** Constructor. */
  SoVRRasterStackReader();

  /**
  * Specifies the path of the file. Returns 0 for success. Any other return
  * value indicates failure.
  */
  virtual int setFilename(const SbString& filename);

  /**
   * Gets the characteristics (file header) of the data volume. See SoVolumeData.
   * @B size@b is the size of the actual volume. @B type@b is the type of the data.
   * @B dim@b is the dimension of the data.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  virtual ReadError getDataChar(SbBox3f& size, SoDataSet::DataType& type, SbVec3i32& dim);

  #ifdef OIV_NET_DOC
 /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory referenced by @B data@b.
   * Slices will not always be read sequentially.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
 #else
  /**
   * New method required by VolumeViz 3.0 when using large volume support.
   * Must copy a rectangular part of an XY slice to the memory pointed to by @B data@b.
   * Slices will not always be read sequentially.
   */
#endif
  virtual void getSubSlice(const SbBox2i32& subSlice, int sliceNumber, void* data);

  /**
   * Defines the bounding box size in physical units of the data set.
   */
  void setSize(SbBox3f& size) {m_size = size;};

  /**
   * Selects channels to be used for data rendering.
   */
  void setChannelSelection(ChannelSelection cs) {m_channelSelection = cs;};

  /**
   * Returns the reader type.
   */
  virtual ReaderType getReaderType ()  {return RASTERSTACK;};

  /**
   * Returns TRUE if the data set contains RGBA color values.
   */
  virtual SbBool isRGBA() const;

protected:

  int extractFileList(const SbString& headFile);
  SbBool extractParameters(const char* lineStr);

  SoDataSet::DataType findOutDestType(const SbRasterImage::Components nc, const unsigned int numComponent);

  void RGBA2HLS(SbVec3f& hls, float* rgba);

  float   convertFloat(float   value);
  short   convertShort(short   value);
  int32_t convertInt32(int32_t value);
  unsigned short convertUShort(unsigned short value);
  uint32_t convertUInt32(uint32_t value);
  SbBool needEndianConversion();

  int getChannelId(const char* channel);

  template <typename T>
  void getSubSliceInternal(const SbBox2i32 &subSlice, int sliceNumber, void* data);

  template <typename TSRC, typename T>
  void convertSubSliceInternal(TSRC* srcData, const SbVec2s srcSize, const unsigned int srcNumComponent, std::vector<T>& dstVector);


  template <typename T>
  SbBool readImage(int numImage, SbRasterImage& rasterImage, std::vector<T>& dataVector, SbBool infoOnly);

  template <typename T>
  void getSingleChannelData(std::vector<T> srcVector, SbVec2i32& size2s,
    unsigned int xMin, unsigned int xMax,
    unsigned int yMin, unsigned int yMax,
    void* data);

  template <typename T>
  T endianConverter(const T value);

  SbString  m_listDirectory;
  SbBox3f   m_size;
  SbVec3i32 m_dim;
  SbBool    m_isRawData;
  unsigned int m_nc;
  SoDataSet::DataType m_srcType;
  SoDataSet::DataType m_destType;
  ChannelSelection m_channelSelection;
  std::vector< SbString > m_fileList;
  unsigned int m_rawHeaderSize;
  SbBool m_rawIsBigEndian;
  SbBool m_rawIsBinary;

private:
  bool m_isInitialized;
};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif /* _SO_VR_RASTER_STACK_READER_ */

