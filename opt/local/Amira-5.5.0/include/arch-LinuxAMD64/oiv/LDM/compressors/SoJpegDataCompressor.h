/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_LDM_JPEG_COMPRESSOR_H
#define SO_LDM_JPEG_COMPRESSOR_H

#include <LDM/compressors/SoDataCompressor.h>

struct jpeg_destination_mgr;
struct jpeg_source_mgr;
struct jpeg_compress_struct;
struct jpeg_decompress_struct;
struct jpeg_error_mgr;
struct jpeg_ldm_comp_destination_mgr;
struct jpeg_ldm_decomp_destination_mgr;

class SoLibJpeg;

typedef struct jpeg_compress_struct *j_compress_ptr;
typedef struct jpeg_decompress_struct * j_decompress_ptr;

/**
* @LDMEXT Jpeg data compression
* @ingroup LDMCompressor
*
* @DESCRIPTION
*
* This class implements a compression scheme based on libjpeg. It is a lossy compression.
*
* The setCompressionLevel method (inherited from SoDataCompressor)
* accepts values between 0 and 100.
*
* NOTE: It can be used only on 8-bit data sets.
*
* @SEE_ALSO
* SoGzipDataCompressor, SoDataCompressor
*
*
*/
class LDM_API SoJpegDataCompressor : public SoDataCompressor
{
  SO_TYPED_CLASS_HEADER();

public:
  /**
   * Constructor.
   */
  SoJpegDataCompressor();
   /**
   * Destructor.
   */
 virtual ~SoJpegDataCompressor();

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
   * @param destLen the size of the destination buffer in bytes.
   * @param tileInfo contains information about the tile being processed.
   * @return The number of uncompressed bytes.
   */
  virtual size_t uncompress(void *dest, size_t destLen, const TileInfo &tileInfo);

  /**
   * Returns the name of the compression algorithm used by this class.
   * This is the name the user must pass to the "-c" option of the converter
   * to use this compression ("jpeg" here).
   * @return An SbString containing "jpeg".
   */
  virtual SbString getCompressionFormatName() const { return SbString("jpeg"); }

  /**
   * This compression is lossy.
   * @return false, the compression is lossy.
   */
  virtual bool isLossless() { return false; }

private:
  SoLibJpeg *m_jpeg;

  struct jpeg_compress_struct *m_cinfo;
  struct jpeg_decompress_struct *m_dcinfo;

  size_t allocateNeededSpace(size_t srcLen);


  static void initDestination(j_compress_ptr cinfo);
  static unsigned char emptyOutputBuffer(j_compress_ptr cinfo);
  static void termDestination(j_compress_ptr cinfo);

  static void initSource(j_decompress_ptr cinfo);
  static unsigned char fillInputBuffer(j_decompress_ptr cinfo);
  static void skipInputData(j_decompress_ptr cinfo, long num_bytes);
  static void resyncToRestart(j_decompress_ptr cinfo, int desired);
  static void termSource(j_decompress_ptr cinfo);

  void createCompressInfo(jpeg_compress_struct *cinfo, jpeg_error_mgr *jerr,
                          jpeg_ldm_comp_destination_mgr *destMgr);
  void createDecompressInfo(jpeg_decompress_struct *cinfo,
                            jpeg_error_mgr *jerr,
                            jpeg_ldm_decomp_destination_mgr *srcMgr);
};

#endif
