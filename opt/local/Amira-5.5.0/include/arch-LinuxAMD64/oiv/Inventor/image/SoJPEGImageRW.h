/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SOJPEGIMAGERW_
#define _SOJPEGIMAGERW_

#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadMutex.h>

struct jpeg_compress_struct;

/**
 *
 * @VSGEXT Class for encoding and decoding a JPEG raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a JPEG raster image.
 *
 * The writeCapability is WRITE_SCANLINES and isMultipleBufferInverted is TRUE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoJPEGImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoJPEGImageRW();


  /**
   * Destructor.
   */ 
  virtual ~SoJPEGImageRW();


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);


  /**
   * Closes the reader/writer.
   */
  virtual void close();

  /**
   * Writes and encodes the given data in this specific format.
   * If you are using the multiple writing mode, then you can specify the 
   * offset (with xPos,yPos) you want to write to.
   */
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);


  /**
   * Writes and encodes the header for this specific format.
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
   * Sets the output quality of the image, from 0.0 (lowest quality)
   * to 1.0 (highest quality).  Default is 0.7
   */
  void  setOutputQuality(float quality);


  /**
   * Returns the output quality.
   */
  float getOutputQuality() const;


SoINTERNAL public:
  unsigned char* getBuffer(size_t& size) const;


protected:
  virtual void createSuffixList();


private:
  static SbThreadMutex s_mutex;

  struct jpeg_compress_struct* m_cinfoW;
  float  m_quality;
  SbBool m_writeToBuffer;
  size_t m_jpegBufferSize;
  unsigned char* m_jpegBuffer;
  bool m_isJpegLibraryLoaded;
};

#endif
