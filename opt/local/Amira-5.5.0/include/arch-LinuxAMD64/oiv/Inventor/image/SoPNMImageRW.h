/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/




#ifndef _SOPNMIMAGERW_
#define _SOPNMIMAGERW_


#include <Inventor/image/SoRasterImageRW.h>


class SoJasperImage;



/**
 *
 * @VSGEXT Class for encoding and decoding a PNM raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a PNM raster image.
 *
 * The writeCapability is WRITE_FULL_IMAGE and isMultipleBufferInverted is FALSE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 

class INVENTOR_API SoPNMImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:


  /**
   * Constructor.
   */
  SoPNMImageRW();

  /**
   * Destructor.
   */ 
  virtual ~SoPNMImageRW();


  /**
   * Tells if you are using multiple buffers to write a single image.
   */
  void enableMultipleWriting(SbBool state);


  /**
   * Opens the reader/writer in the given open mode.
   */
  virtual SbBool open(SoRasterImageIO* rasterImageIO, SoRasterImageRW::OpenMode openMode);

  
  /**
   * Closes the reader/writer.
   */
  virtual void   close();
  
  /**
   * Writes and encodes the given data in the specific format.
   * If you are using the multiple writing mode, then you can give the 
   * offset with (xPos,yPos) you want to write to.
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

  
protected:
  virtual void createSuffixList();

private:
  SoJasperImage*   m_jasperImage;

};

#endif
