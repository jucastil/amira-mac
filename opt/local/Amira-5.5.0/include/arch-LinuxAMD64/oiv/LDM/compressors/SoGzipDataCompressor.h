/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_LDM_GZIP_COMPRESSOR_H
#define SO_LDM_GZIP_COMPRESSOR_H

#include <LDM/compressors/SoDataCompressor.h>

class SoZlib;

/**
* @LDMEXT Gzip data compression
* @ingroup LDMCompressor
*
* @DESCRIPTION
*
* This class implements a compression scheme based on zlib. It is a
* lossless compression and can be used on any data set type.
*
* The setCompressionLevel method (inherited from SoDataCompressor)
* accepts values between 0 and 9.
*
* @SEE_ALSO
* SoJpegDataCompressor, SoDataCompressor
*
*
*/
class LDM_API SoGzipDataCompressor : public SoDataCompressor
{
  SO_TYPED_CLASS_HEADER();

public:
  /**
   * Constructor.
   */
  SoGzipDataCompressor();

  /**
   * Destructor.
   */
  virtual ~SoGzipDataCompressor();

  /**
   * Compresses the given buffer into the internal buffer.
   * @param src a pointer to the data to compress.
   * @param srcLen the size of the source buffer in bytes.
   * @param tileInfo contains information about the tile being processed.
   * @return The size in bytes of the compressed buffer.
   */
  virtual size_t compress(void *src, size_t srcLen, const TileInfo &tileInfo);

  /**
   * Uncompresses data from the internal buffer to the given buffer.
   * @param dest a pointer to the destination buffer.
   * @param destLen the size of the destination buffer.
   * @param tileInfo contains information about the tile being processed
   * @return The number of uncompressed bytes.
   */
  virtual size_t uncompress(void *dest, size_t destLen, const TileInfo &tileInfo);

  /**
   * Returns the name of the compression algorithm used by this class.
   * This is the name the user must pass to the "-c" option of the converter
   * to use this compression ("gzip" here).
   * @return An SbString containing "gzip".
   */
  virtual SbString getCompressionFormatName() const { return SbString("gzip"); }

  /**
   * This compression is lossless.
   * @return true, the compression is lossless.
   */
  virtual bool isLossless() { return true; }

private:
  size_t allocateNeededSpace(size_t srcLen);

  SoZlib* m_zlib;
};

#endif
