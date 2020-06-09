/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/


#ifndef _SORASTERIMAGEFILE_
#define _SORASTERIMAGEFILE_


#include <Inventor/image/SoRasterImageIO.h>
#include <Inventor/image/SoRasterImageRW.h>

/**
 *
 * @VSGEXT Class for raster image file input and output.
 * 
 * @ingroup Image
 *
 * Class for raster image file input and output.
 *
 * 
 * @SEE_ALSO
 *    SoRasterImageIO
 *    SoRasterImageRW
 * 
 * 
 */ 
class INVENTOR_API SoRasterImageFile : public SoRasterImageIO 
{
  SO_IMAGE_RASTER_RW_HEADER()

public:
  /**
   * Constructor.
   */
  SoRasterImageFile();
  
  /**
   * Constructor that takes a filename.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE SoRasterImageFile(const char* fileName);

  /**
   * Constructor that takes a filename.
   */
  SoRasterImageFile( const SbString& fileName );

  /**
   * Constructor that takes a file pointer.
   */
  SoRasterImageFile(const FILE* fp);


  /**
   * Destructor.
   */
  virtual ~SoRasterImageFile();


  /** 
   * Returns the file name.
   */
  virtual const char* getFileName() const;

  /** 
   * Returns the file name.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE virtual SbString getStringFileName() const;

  /**
   * Sets the file name.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE virtual void setFileName(const char* fileName);  
  
 /**
   * Sets the file name.
   */
  virtual void setFileName( const SbString& fileName );  

  /**
   * Sets the file pointer.
   */
  
  virtual void setFilePointer(const FILE* fp);

  /**
   * Returns the file pointer.
   */
  virtual FILE* getFilePointer() const;


  /**
   * Opens the file with the specified open mode.
   */
  virtual SbBool openFile(SoRasterImageRW::OpenMode openMode);
  
  
  /**
   * Closes the file.
   */
  virtual void closeFile();

 /**
   * Sets the filePointer to NULL for files closed internally
   * such as RGB files.
   */
  virtual void nullFilePtr();
  
  /**
   * Sets the file open binary mode.
   */
  virtual void setBinary(SbBool isBinary);


  /**
   * Returns the file open binary mode.
   */
  virtual SbBool isBinary() const;


  /**
   * Returns the file suffix.
   */
  virtual SbString getFileSuffix() const;

protected:
  void constructorCommon();

  SbString m_fileName;
  SbString m_fileSuffix;
  FILE*  m_fp;
  SbBool m_isBinary;
  SoRasterImageRW::OpenMode m_openMode;
};

#endif
