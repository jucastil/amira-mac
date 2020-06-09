/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/




#ifndef _SOPNGIMAGERW_
#define _SOPNGIMAGERW_

#include <Inventor/image/SoRasterImageRW.h>
#include <Inventor/threads/SbThreadMutex.h>


struct png_info_struct;
struct png_struct_def;


/**
 *
 * @VSGEXT Class for encoding and decoding a PNG raster image
 * 
 * @ingroup Image
 *
 * This class is used for encoding and decoding a PNG raster image.
 *
 * The writeCapability is WRITE_SCANLINES and isMultipleBufferInverted is TRUE.
 * See SoRasterImageRW for more information.
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 


class INVENTOR_API SoPNGImageRW : public SoRasterImageRW {

  SO_IMAGE_RASTER_RW_HEADER()

public:

  /**
   * Constructor.
   */
  SoPNGImageRW();

  
  /**
   * Destructor.
   */ 
  virtual ~SoPNGImageRW();


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
  static SbThreadMutex s_mutex;

  png_struct_def*   m_pngpW;
  png_info_struct*  m_infopW;

  int loadPNG(FILE* fp, void* pb, int infoOnly);

  int loadPNG( const SbString& file_name, void* pb, int infoOnly );

  void cleanPNG(void* pb, int isBuffer);
  SbBool m_isLibraryLoaded;
};

#endif
