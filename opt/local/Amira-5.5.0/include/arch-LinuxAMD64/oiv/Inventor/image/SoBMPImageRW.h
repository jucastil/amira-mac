/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/



#ifndef _SOBMPIMAGERW_
#define _SOBMPIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>


class SoJasperImage;


/**
 *
 * @VSGEXT Class for encoding and decoding a BMP raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a BMP raster image.
 *
 * The writeCapability is WRITE_FULL_IMAGE and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 




class INVENTOR_API SoBMPImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoBMPImageRW();

  /**
   * Destructor.
   */
  virtual ~SoBMPImageRW();


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);
  
  
  /**
   * Closes the reader/writer.
   */
  virtual void close();

  /**
   * Writes the given data in this specific format.
   */
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);

  /**
   * Writes and encodes the footer of this specific format.
   */
  virtual SbBool writeFooter();

  /**
   * Reads, decodes, and fills the @I rasterImage@i parameter.
   * If @I infoOnly@i is TRUE, then the buffer will not be read; the parameter @I rasterImage@i will be
   * set with raster size and raster number of components, the buffer will be NULL.
   */
  virtual SbBool read(SbRasterImage* rasterImage, SbBool infoOnly = FALSE);
  
  /**
   * Returns the write direction when using multiple buffers.
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

SoINTERNAL public:
  static SbBool checkWriteFormatAbility( SbRasterImage::Components _comp ); 

protected:
  virtual void createSuffixList();

private:
  SbBool writeImage(SbRasterImage* rasterImage);
  SbBool writeMultipleImages(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);  

#if defined(_WIN32)
  SbBool internalBitmapReader( SbRasterImage* rasterImage, const SbString& fname );
#endif

  unsigned char*  m_imageBuffer;
  SbBool          m_writeMode;

};

#endif
