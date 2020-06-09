/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/

#ifndef _SOGIFIMAGERW_
#define _SOGIFIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>

/**
 *
 * @VSGEXT Class for decoding a GIF raster image.
 * 
 * @ingroup Image
 *
 * This class is used for decoding a GIF raster image.
 * File encoding and writing is not currently supported.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoGIFImageRW : public SoRasterImageRW {

    SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoGIFImageRW();


  /**
   * Destructor.
   */
  virtual ~SoGIFImageRW();


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);


  /**
   * Writes and encodes the given data in the specific format. <BR>
   * Not currently supported for this format.
   */
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);


  /**
   * Reads, decodes, and fills the @I rasterImage@i parameter.
   * If @I infoOnly@i is TRUE, then the buffer will not be read, the parameter @I rasterImage@i will be
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
};

#endif 
