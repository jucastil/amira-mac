/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/



#ifndef _SORASTERIMAGERW_
#define _SORASTERIMAGERW_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/image/SoRasterImageIO.h>
#include <Inventor/image/SbRasterImage.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/image/SoSubRasterImageRW.h>

#ifdef OIV_NET_DOC
/**
*
* @VSGEXT Abstract base class for encoding and decoding raster images.
*
* @ingroup Image
*
* SoRasterImageRW is the base class used for encoding and decoding raster images.
*
* The following file formats are supported for raster image input (i.e., read):
* - BMP (Windows only),
* - DDS,
* - GIF,
* - HDRI
* - JPEG 2000,
* - JPEG,
* - PGX,
* - PNG,
* - PNM,
* - SGI RGBA,
* - Sun,
* - TIFF.
*
* The following formats are supported for raster image output (i.e., write):
* - same as above except for GIF, which is available for reading only,
*   and PS (PostScript), which is available for writing only.
*
* Note that only the following image file formats can contain transparency
* information: DDS, GIF, PNG, SGI RGBA, and TIFF.
*
* SoRasterImageRW classes support two methods of writing out an image.
* The simplest one is writing out a complete image already assembled
* in memory.  This is the default method and is efficiently supported
* by all image formats.  SoRasterImageRW also supports assembling an
* image from multiple sub-images or "tiles".  The SoOffscreenRenderer
* class, for example, uses this feature when the requested image size
* is too large for OpenGL to render as a single image.  To use this
* feature call the enableMultipleWriting method with true.  Note that
* some image formats allow the image to be written (encoded) incrementally,
* so tiles provided in scan-line order can written immediately, with no
* intermediate storage. Other image formats cannot be encoded until the
* complete image is assembled in memory.
*
* Image formats that allow tiles to be written incrementally have the
* writeCapability WRITE_SCANLINES. This is the most memory efficient
* way to write large images.  Note that some image formats are encoded
* from top to bottom and some are encoded from bottom to top.  The
* method isMultipleBufferInverted returns true if the format should be
* encoded from bottom to top.
*
* Image formats that require a complete image before encoding have the
* writeCapability WRITE_FULL_IMAGE.  In this case the SoRasterImageRW
* subclass will automatically allocate enough memory to hold the
* complete image.  This may require a very large block of contiguous
* memory!  The image is not actually written until the writeFooter
* method is called.
*
* @SEE_ALSO
*    SoBMPImageRW,
*    SoDDSImageRW,
*    SoGIFImageRW,
*    SoJP2ImageRW,
*    SoJPEGImageRW,
*    SoPGXImageRW,
*    SoPNGImageRW,
*    SoPNMImageRW,
*    SoPSImageRW,
*    SoSGIRGBImageRW,
*    SoSUNImageRW,
*    SoTIFFImageRW,
*
*
*/
#else
/**
*
* @VSGEXT Abstract base class for encoding and decoding raster images.
*
* @ingroup Image
*
* SoRasterImageRW is the base class used for encoding and decoding raster images.
*
* The following file formats are supported for raster image input (i.e., read):
* - BMP (Windows only),
* - DDS,
* - GIF,
* - HDRI (with SoTextureCubeMap only)
* - JPEG 2000,
* - JPEG,
* - PGX,
* - PNG,
* - PNM,
* - SGI RGBA,
* - Sun,
* - TIFF.
*
* The following formats are supported for raster image output (i.e., write):
* - same as above except for GIF, which is available for reading only,
*   and PS (PostScript), which is available for writing only.
*
* Note that only the following image file formats can contain transparency
* information: DDS, GIF, PNG, SGI RGBA, and TIFF.
*
* SoRasterImageRW classes support two methods of writing out an image.
* The simplest one is writing out a complete image already assembled
* in memory.  This is the default method and is efficiently supported
* by all image formats.  SoRasterImageRW also supports assembling an
* image from multiple sub-images or "tiles".  The SoOffscreenRenderer
* class, for example, uses this feature when the requested image size
* is too large for OpenGL to render as a single image.  To use this
* feature call the enableMultipleWriting method with TRUE.  Note that
* some image formats allow the image to be written (encoded) incrementally,
* so tiles provided in scan-line order can written immediately, with no
* intermediate storage. Other image formats cannot be encoded until the
* complete image is assembled in memory.
*
* Image formats that allow tiles to be written incrementally have the
* writeCapability WRITE_SCANLINES. This is the most memory efficient
* way to write large images.  Note that some image formats are encoded
* from top to bottom and some are encoded from bottom to top.  The
* method isMultipleBufferInverted returns TRUE if the format should be
* encoded from bottom to top.
*
* Image formats that require a complete image before encoding have the
* writeCapability WRITE_FULL_IMAGE.  In this case the SoRasterImageRW
* subclass will automatically allocate enough memory to hold the
* complete image.  This may require a very large block of contiguous
* memory!  The image is not actually written until the writeFooter
* method is called.
*
* Example: Writing a complete image in JPEG format
*
* <PRE>
*    // Create an SbRasterImage
*    SbRasterImage image(size, SbRasterImage::RGB, bytes);
*
*    // Create a file IO object
*    SoRasterImageFile imageFile( "test.jpg" );
*
*    // Create an image writer and write the image
*    SoJPEGImageRW imageWriter;
*    imageWriter.open( &imageFile, SoRasterImageRW::OPEN_WRITE );
*    imageWriter.writeHeader( size );
*    imageWriter.write( &image );
*    imageWriter.writeFooter();
*    imageWriter.close();
* </PRE>
*
* @SEE_ALSO
*    SoBMPImageRW,
*    SoDDSImageRW,
*    SoGIFImageRW,
*    SoJP2ImageRW,
*    SoJPEGImageRW,
*    SoPGXImageRW,
*    SoPNGImageRW,
*    SoPNMImageRW,
*    SoPSImageRW,
*    SoSGIRGBImageRW,
*    SoSUNImageRW,
*    SoTIFFImageRW,
*
*
*/
#endif //OIV_NET_DOC

class INVENTOR_API SoRasterImageRW {

  SO_IMAGE_RASTER_RW_ABSTRACT_HEADER()

public:
    virtual ~SoRasterImageRW() {}

  /** Write Capability enumeration values. */
  enum WriteCapability {
    /**
     * Can write an image incrementally (e.g., by scan-line).
     */
    WRITE_SCANLINES,
    /**
     * Can only write a complete image.
     */
    WRITE_FULL_IMAGE,
    /**
     * No writing available.
     */
    WRITE_UNAVAILABLE
  };

  /** Read Capability enumeration values. */
  enum ReadCapability {
    /**
     * Read functionality available.
     */
    READ_AVAILABLE,
    /**
     * No reading available.
     */
    READ_UNAVAILABLE
  };

  /** open Mode enumeration values. */
  enum OpenMode {
    /**
     * Opened for reading.
     */
    OPEN_READ,
    /**
     * Opened for writing.
     */
    OPEN_WRITE
  };


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);

  /**
   * Closes the reader/writer.
   */
  virtual void close();

  /**
   * Writes and encodes the given data in the specific format.
   * If you are using the multiple writing mode, then you can give the
   * offset with (xPos,yPos) you want to write to.
   */
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0) = 0;


  /**
   * @DEPRECATED
   * Writes and encodes the header for this specific format.
   * The parameter is the size of the whole raster image to be saved.
   * The size is limited to 32767 by 32767
   * [OIV-WRAPPER-ARG CONST]
   */
  virtual SbBool writeHeader(SbVec2s& size);

   /**
   * Writes and encodes the header for this specific format.
   * The parameter is the size of the whole raster image to be saved.
   * Use for sizes with at least one side greater than
   * 32767.
   * [OIV-WRAPPER-ARG CONST]
   */
  virtual SbBool writeHeader(SbVec2i32& size);


  /**
   * Writes and encodes the footer for this specific format.
   */
  virtual SbBool writeFooter();


  /**
   * Reads, decodes, and fills the @I rasterImage@i parameter.
   * If @I infoOnly@i is TRUE, then the buffer will not be read; the parameter @I rasterImage@i will be
   * set with raster size and raster number of components, the buffer will be NULL.
   */
  virtual SbBool read(SbRasterImage* rasterImage, SbBool infoOnly = FALSE) = 0;


  /**
   * Returns the typical list of file suffixes supported.
   * [OIV-WRAPPER-ARG NO_WRAP]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{numSuffixes}] 
   */
  virtual SbString* getSuffixes(int& numSuffixes) const;


  /**
   * Specifies the write way when using multiple buffers.
   * Returns FALSE if buffers are written from top to bottom.
   * Returns TRUE if buffers are written from bottom to top.
   * Returns TRUE by default.
   */
  virtual SbBool isMultipleBufferInverted() const;


  /**
   * Returns the write capability of the raster format.
   * Returns WRITE_SCANLINES by default.
   */
  virtual SoRasterImageRW::WriteCapability getWriteCapability() const;


  /**
   * Returns the read capability of the raster format.
   * Returns READ_AVAILABLE by default.
   */
  virtual SoRasterImageRW::ReadCapability getReadCapability() const;


  /**
   * Enable writing image with multiple calls to write method.
   * Default is FALSE.
   */
  virtual void enableMultipleWriting(SbBool state);


  /**
   * Returns TRUE if multiple buffer writing is enabled.
   */
  virtual SbBool isMultipleWritingEnabled() const;

  SoINTERNAL public:

  virtual SbBool    getClosedOnRW(){ return m_closedOnRW;}


protected:
  // This method must fill m_suffixes and update m_numSuffixes
  virtual void createSuffixList() = 0;
  SoRasterImageRW();

  SoRasterImageIO* m_rasterImageIO;
  SbBool           m_multipleWriting;
  SbBool           m_writeMode;
  SbVec2i32        m_rasterSize;
  SbBool           m_closedOnRW;
  unsigned int     m_multipleWritingNumComponents;
  SbBool           m_firstMultipleImages;

  SbString*        m_suffixes;
  int              m_numSuffixes;
};

#endif
