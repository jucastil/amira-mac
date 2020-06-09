/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : D. DALLA-ROSA(Jul 2010)
**=======================================================================*/


#if !defined(SO_HDR_IMAGERW_H)
#define SO_HDR_IMAGERW_H

#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadMutex.h>


/**
 *
 * @VSGEXT Class for encoding and decoding an HDR raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding an HDR raster image.
 *
 * The writeCapability is WRITE_FULL_IMAGE and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 


class INVENTOR_API SoHDRImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoHDRImageRW();

  
  /**
   * Destructor.
   */ 
  virtual ~SoHDRImageRW();


  /**
   * Opens the reader/writer in the given open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, OpenMode openMode);

  
  /**
   * Writes and encodes the given data in the specific format.
   * If you are using the multiple writing mode, then you can give the 
   * offset with (xPos,yPos) you want to write to.
   */  
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);

  
  /**
   * Writes and encodes the footer of this specific format.
   */
  virtual SbBool writeFooter();

  
  /**
   * Reads, decodes, and fills the rasterImage parameter.
   * If infoOnly is TRUE, then the buffer will not be read, the parameter rasterImage will be
   * set with raster size and raster number of components, the buffer will be NULL.
   */  
  virtual SbBool read(SbRasterImage* rasterImage, SbBool infoOnly = FALSE); 
  
  
  /**
   * Specifies the write method when using multiple buffers.
   * Returns FALSE if buffers are written from top to bottom.
   * Returns TRUE if buffers are written from bottom to top.
   */
  virtual SbBool isMultipleBufferInverted() const;

  
  /**
   * Returns if the class can write in the specific raster format.
   */
  virtual SoRasterImageRW::WriteCapability getWriteCapability() const;


  /**
   * Returns if the class can read the specific raster format.
   */
  virtual SoRasterImageRW::ReadCapability getReadCapability() const;
  

protected:

  virtual void createSuffixList();
  
private:

  /**
   * This function reads the HDRI data from the file.
   */
  static SbBool readHDRIBuffer(FILE* file, unsigned char* scan, int xmax);

  /**
   * This function checks if the file is supported by this reader.
   */
  static SbBool checkHDRIHeader(FILE* file, int &ymax, int &xmax);

  /**
   * This function writes the data from SbRasterImage to the file
   * using RLE encoding if width >= 8 and < 0x7FFF.
   */
  static SbBool writeData(FILE* file, SbRasterImage* rasterImage );

  /**
   * This function writes pixels without using RLE. It is used 
   * when the width of the image is not acceptable for RLE encoding.
   */
  static SbBool writePixels(FILE* file, unsigned char* data, unsigned long size);

  /**
   * This functions encode the specified RGBE buffer using RLE to save room.
   */
  static SbBool writePixelsRLE(FILE* file, unsigned char* data, unsigned long size);
};

#endif // SO_HDR_IMAGERW_H
