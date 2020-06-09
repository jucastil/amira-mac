/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_DATA_COMPRESSOR_H
#define SO_DATA_COMPRESSOR_H

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

#include <Inventor/SoSubTypedClass.h>
#include <Inventor/sys/port.h>
#include <Inventor/SbString.h>
#include <Inventor/SbLinear.h>
#include <Inventor/STL/vector>

#include <LDM/nodes/SoDataSet.h>

/**
 *
 * @LDMEXT Data compression
 * @ingroup LDMCompressor
 * 
 * @DESCRIPTION
 *
 * This is an abstract class which is only needed for advanced users who intend to add a new
 * LDM data compression technique.
 *
 * By implementing each virtual method of this class, it is possible to create 
 * a new compression algorithm.
 * As with a custom node, the initClass of the custom compressor must be called before creating
 * and instantiating an instance of the custom class.
 * After you call initClass, the compression algorithm will be available in the '-c'
 * option of SoConverter.
 *
 * @SEE_ALSO
 * SoGzipDataCompressor, SoJpegDataCompressor
 * 
 * 
 */ 
class LDM_API SoDataCompressor {
  SO_TYPED_CLASS_ABSTRACT_HEADER();

public:

  /**
   * This structure contains the dimension and the type of the tile being processed.
   */
  struct TileInfo
  {
    /**
     * Dimensions of the tile.
     */
    SbVec3i32 dims;
    /**
     * Tile's data type (byte, int, etc.).
     */
    SoDataSet::DataType dataType;
  };

    /**
     * Constructor.
     */
  SoDataCompressor() : m_level(0){}
    /**
     * Destructor.
     */
  virtual ~SoDataCompressor() {}

  /**
   * Compresses the given buffer into the internal buffer.
   * @param src a pointer to the data to compress.
   * @param srcLen the size of the source buffer in bytes.
   * @param tileInfo contains information about the tile being processed.
   * @return The size in bytes of the compressed buffer.
   * [OIV-WRAPPER-ARG ARRAY,IN,IN]
   */
  virtual size_t compress(void *src, size_t srcLen, const TileInfo &tileInfo) = 0;

  /**
   * Uncompresses data from the internal buffer to the given buffer.
   * @param dest a pointer to the destination buffer.
   * @param destLen the size of the destination buffer in bytes.
   * @param tileInfo contains information about the tile being processed.   
   * @return The number of uncompressed bytes.
   * [OIV-WRAPPER-ARG ARRAY,IN,IN]
   */
  virtual size_t uncompress(void *dest, size_t destLen, const TileInfo &tileInfo) = 0;

  /**
   * Returns the name of the compression algorithm used by this class.
   * This is the name the user will pass to the "-c" option of the converter,
   * so it should be something simple and clear.
   * @return A SbString containing the name of the compression.
   */
  virtual SbString getCompressionFormatName() const = 0;

  /**
   * Returns true if the compression algorithm is lossless.
   * @warning It allows the converter to know if it must do CRC32 on original data
   * or decompressed data when the '-C' option is enabled. 
   * Computing CRC32 on lossy compression is more costly than on lossless
   * compression because data must be uncompressed before applying the CRC32 in order
   * to have the real data stored in the file.
   * Setting the environment variable LDM_COMPRESS_CHECK_CRC32 to 1 will force 
   * the LDM reader to check data integrity.
   * @return True if the compression is lossless.
   */
  virtual bool isLossless() = 0;

  /**
   * Sets the compression level.
   * @param level the level of the compression used. Valid compression levels are
   * specific to the compression algorithm.
   */
  virtual void setCompressionLevel(size_t level) { m_level = level; }

  /**
   * Allocates the internal buffer to hold the compressed data.
   * @param size is the size to allocate in bytes.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size}]
   */
  virtual void *allocateCompressedBuffer(size_t size)
  {
    m_size = size;
    m_compressedBuffer.resize(size);
    if ( size>0)
      return &m_compressedBuffer[0];
    else
      return NULL;
  }

  /**
   * Returns the compressed data. This pointer must not be deleted.
   * @return A pointer to the compressed data.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{UNKNOWN}]
   */
  virtual void *getCompressedBuffer() { return &m_compressedBuffer[0]; }

  /**
   * Utility function to get the CRC32 of a buffer.
   * @param buf a pointer to the data. 
   * @param len the size of the buffer.
   * @return The CRC32 of the data.
   * [OIV-WRAPPER-ARG ARRAY,IN]
   */
  static size_t crc32(const void *buf, size_t len);

  /**
   * Returns the compression level.
   * @return The level of compression. See #setCompressionLevel.
   */
  virtual size_t getCompressionLevel() { return m_level; };

  SoINTERNAL public:

  size_t getSize() { return m_size;};
  size_t m_size;

protected:
  SbString m_compressionName;

  std::vector<unsigned char> m_compressedBuffer;

  size_t m_level;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif
