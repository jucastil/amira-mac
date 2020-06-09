/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jan 2005)
**=======================================================================*/

#ifndef _SODDSIMAGERW_
#define _SODDSIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadMutex.h>

/**
 * @VSGEXT Class for decoding a DDS raster image.
 * 
 * @ingroup Image
 *
 * This class is used for decoding a DDS (DirectDraw Surface) raster image.
 * DDS files are faster to load than other file formats since the 
 * compressed buffer is directly sent to the graphics device.
 * This class is able to read DDS files compressed with DXT1, DXT3, 
 * and DXT5 compressions. DXT2 and DXT4 compression are
 * not supported.
 * This format can also embed mipmaps (levels of resolution), 
 * but all levels (from higher resolution to a 1*1 pixel image) are 
 * not necessarily required.
 * The SoComplexity::textureQuality field has no effect on 
 * mipmap generation if the DDS file already embeds mipmaps.
 * File encoding and writing is not currently supported.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 *    SoComplexity
 * 
 * 
 */ 
class INVENTOR_API SoDDSImageRW : public SoRasterImageRW {

    SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoDDSImageRW();


  /**
   * Destructor.
   */
  virtual ~SoDDSImageRW();


  /**
   * Opens the reader/writer in the specified open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);

  /**
   * Closes the reader/writer.
   */
  virtual void close();


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

  void readAndConvert(void* dd, FILE* fp);


  struct DDS_IMAGE_DATA
  {
    int32_t  width;
    int32_t  height;
    int32_t  components;
    int32_t  format;
    int32_t  numMipMaps;
    unsigned char* pixels;
  };
  DDS_IMAGE_DATA *m_pDDSImageData;

private:
  static SbThreadMutex s_mutex;
};

#endif 
