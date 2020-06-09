/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SOJP2IMAGERW_
#define _SOJP2IMAGERW_

#include <Inventor/image/SoRasterImageRW.h>


class SoJasperImage;


/**
 *
 * @VSGEXT Class for encoding and decoding a JPEG2000 raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a JPEG2000 raster image.
 *
 * The writeCapability is WRITE_FULL_IMAGE and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 *
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoJP2ImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoJP2ImageRW();


  /**
   * Destructor.
   */ 
  virtual ~SoJP2ImageRW();


  /**
   * Enable writing image with multiple calls to write method.
   */
  void enableMultipleWriting(SbBool state);

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
   * @DEPRECATED
   * Writes and encodes the header for this specific format.
   * The parameter is the size of the whole raster image to be saved.
   * The size is limited to 32767 by 32767
   */
  virtual SbBool writeHeader(SbVec2s& size);

   /**
   * Writes and encodes the header for this specific format.
   * The parameter is the size of the whole raster image to be saved.
   * Use for sizes with at least one side greater than
   * 32767.
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


  /**
   * Sets the output quality of the image, from 0.0 (lowest quality)
   * to 1.0 (highest quality).  Default is 0.7
   */
  void  setOutputQuality(float quality);


  /**
   * Returns the output quality.
   */
  float getOutputQuality() const;


protected:
  virtual void createSuffixList();

private:
  SoJasperImage*   m_jasperImage;
  float  m_quality;
};
#endif
