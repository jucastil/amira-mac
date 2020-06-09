/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/




#ifndef _SOPSIMAGERW_
#define _SOPSIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>

/**
 *
 * @VSGEXT Class for encoding and decoding a PostScript raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a PostScript raster image.
 *
 * The writeCapability is WRITE_SCANLINES and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoPSImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:


  /**
   * Constructor.
   */
  SoPSImageRW();


  /**
   * Destructor.
   */ 
  virtual ~SoPSImageRW();


  /**
   * Writes and encodes the given data in the specific format.
   * If you are using the multiple writing mode, then you can give the 
   * offset with (xPos,yPos) you want to write to.
   */
  virtual SbBool write(SbRasterImage* rasterImage, unsigned int xPos = 0, unsigned int yPos = 0);


  /**
   * Writes and encodes the header of this specific format.
   */  
  virtual SbBool writeFooter();
  
  
  /**
   * Reads, decodes, and fills the rasterImage parameter.
   * If infoOnly is TRUE, then the buffer will not be read, the parameter rasterImage will be
   * set with raster size and raster number of components, the buffer will be NULL.
   */
  virtual SbBool read(SbRasterImage* rasterImage, SbBool infoOnly = FALSE);

  
  /**
   * Specifies the write way when using multiple buffers.
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

  
  /**
   * Sets the print size for output. The size is given in inches.
   */
  void setPrintSize(const SbVec2f& printSize);

  
  /** 
   * Returns the print size given, specified in inches.
   */
  SbVec2f getPrintSize() const;

protected:
  virtual void createSuffixList();

private:
  void    putHex(FILE *fp, unsigned char val, int &hexPos);
  SbBool  m_printSizeFlag;
  SbVec2f m_printSize;
  FILE*   m_fpW;
};

#endif
