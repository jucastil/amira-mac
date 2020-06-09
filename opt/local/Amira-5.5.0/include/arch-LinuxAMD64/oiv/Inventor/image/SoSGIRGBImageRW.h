/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/




#ifndef _SOSGIRGBIMAGERW_
#define _SOSGIRGBIMAGERW_

#include <Inventor/image/SoRasterImageRW.h>

extern "C" {
  struct IMAGE;
}

/**
 *
 * @VSGEXT Class for encoding and decoding an SGI raster image
 *
 * @ingroup Image
 *
 * This class is used for encoding and decoding an SGI raster image.
 *
 * The writeCapability is WRITE_SCANLINES and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 *
 * @SEE_ALSO
 *    SoRasterImageRW
 *
 *
 */
class INVENTOR_API SoSGIRGBImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoSGIRGBImageRW();


  /**
   * Destructor.
   */
  virtual ~SoSGIRGBImageRW();


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);

  /**
   * Writes and encodes the given data in this specific format.
   * If you are using the multiple writing mode, then you can give the
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


protected:
  virtual void createSuffixList();

private:
  IMAGE* m_imageW;
  SbBool          m_writeMode;
  int             m_scanTileOffset;
};

#endif

