/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SOTIFFIMAGERW_
#define _SOTIFFIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadMutex.h>

struct tiff;

/**
 *
 * @VSGEXT Class for encoding and decoding a TIFF raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a TIFF raster image.
 *
 * The writeCapability is WRITE_SCANLINES and isMultipleBufferInverted is TRUE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoTIFFImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:
   
    /** CompressionMode */
  enum CompressionMode {
    /**
     * No compression
     */
    NO_COMPRESSION,
    /**
     *  Default compression
     */
    PACKBITS_COMPRESSION
  };



  /**
   * Constructor.
   */
  SoTIFFImageRW();

  
  /**
   * Destructor.
   */ 
  virtual ~SoTIFFImageRW();

  
  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);


  /**
   * Writes and encodes the given data in the specific format.
   * If you are using the multiple writing mode, then you can specify the 
   * offset (with xPos,yPos) you want to write to.
   */  
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);

  
  /**
   * Writes and encodes the footer for this specific format.
   */  
  virtual SbBool writeFooter();


  /**
   * Reads, decodes, and fills the @I rasterImage@i parameter.
   * If @I infoOnly@i is TRUE, then the buffer will not be read; the parameter @I rasterImage@i will be
   * set with raster size and raster number of components, the buffer will be NULL.
   */
  virtual SbBool read(SbRasterImage* rasterImage, SbBool infoOnly = FALSE);
  
  
  /**
   * Specifies the write direction when using multiple buffers.
   * Returns FALSE if buffers are written from top to bottom.
   * Returns TRUE if buffers are written from bottom to top.
   */
  virtual SbBool isMultipleBufferInverted() const;


  /**
   * Returns the write capability of the raster format.
   */
  virtual SoRasterImageRW::WriteCapability getWriteCapability() const;
  
  
  /**
   * Returns the read capability of the raster format.
   */
  virtual SoRasterImageRW::ReadCapability getReadCapability() const;
  

  /**
   * Sets the compression mode to use when encoding the image.
   * Default compression is PACKBITS_COMPRESSION.
   */
  void setCompressionMode(SoTIFFImageRW::CompressionMode compressionMode);


  /**
   * Gets the compression mode used for encoding.
   */
  SoTIFFImageRW::CompressionMode getCompressionMode() const;

protected:
  virtual void createSuffixList();
  
private:
  static SbThreadMutex s_mutex;

  int m_multipleScanLineOffset;
  CompressionMode  m_compressionMode;
  struct tiff* m_tifW;
  SbBool m_isLibraryLoaded;

};

#endif

