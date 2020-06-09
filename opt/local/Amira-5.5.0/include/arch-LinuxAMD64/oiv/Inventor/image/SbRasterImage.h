/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Jun 2003)
**=======================================================================*/

#ifndef _SBRASTERIMAGE_
#define _SBRASTERIMAGE_


#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoGLType.h>
#include <Inventor/fields/SoSFImage.h>


/**
 *
 *
 * @VSGEXT Class encapsulating a raster image and its attributes.
 * 
 * @ingroup Image
 *
 * This class encapsulates a raster image, including its size and 
 * number of color components.
 *
 * 
 * @SEE_ALSO
 *    SoRasterImageRW
 * 
 * 
 */ 



class INVENTORIMAGE_API SbRasterImage {


public:

  /**
   * Components type.
   */
  enum Components {
    /**
     *  Unknown number of components.
     */
    UNKNOWN = -1,
    
    /**
     *  Number of components 1 (luminance).
     */  
    LUMINANCE = 1,

    /**
     *  Number of components 2 (luminance + transparency).
     */  
    LUMINANCE_TRANSPARENCY = 2,

    /**
     *  Number of components 3 (RGB) (default). 
     */  
    RGB = 3, // The default
    
    /**
     *  Number of components 4 (RGB + transparency).
     */  
    RGB_TRANSPARENCY = 4,

    /**
     *  Number of components 4 (RGBE).
     *  This is used by some HDR formats.
     */  
    RGBE = 5
  };


  /**
   * Copy policy.
   */
  enum CopyPolicy {
    /**
     *  Open Inventor will make a copy of the data (default). 
     */
    COPY = 0,
#ifdef OIV_NET_DOC
	/**
	*  Passed buffer used
	*/

#else
	/**
	*  Passed buffer used, user will delete. 
	*/

#endif //OIV_NET_DOC
			  NO_COPY = 1,
    /**
     *  Passed buffer used, SbRasterImage will delete.
     * Use this if memory is allocated with "new". 
     */
    NO_COPY_AND_DELETE = 2,
    /**
     *  Passed buffer used, SbRasterImage will free.
     * Use this if memory is allocated with "malloc". 
     */
    NO_COPY_AND_FREE = 3
  };


  /**
   * Constructor that creates an empty image.
   */
  SbRasterImage();

  /**
   * Constructor that initializes with an image.
   */
  SbRasterImage( const SbVec2s &size, Components components,
                 const unsigned char *bytes, CopyPolicy copy=COPY );
  /**
   * Constructor that initializes with a large image.
   */
  SbRasterImage( const SbVec2i32 &size, Components components,
                 const unsigned char *bytes, CopyPolicy copy=COPY );
  /**
   * Destructor.
   */
  virtual ~SbRasterImage();
 
  /**
   * Sets the raster image size in pixels. @BR
   * The parameter is the size of the whole raster image. 
   * The maximum size that can be specified using this method is
   * 32767 by 32767 (because the parameter is an SbVec2s).  To
   * specify a larger image size use the method setSize_i32.
   */
  void setSize(const SbVec2s& size);

   /**
   * Sets the raster image size in pixels. @BR
   * The parameter is the size of the whole raster image to be saved.
   * Use for sizes with at least one side greater than 32767.
   */
  void setSize_i32(const SbVec2i32& size);

  /**
   * Returns the raster image size in pixels.
   */
  SbVec2s getSize() const;

  /**
   * Returns the raster image size in pixels for large images.
   */
  SbVec2i32 getSize_i32() const;

  /**
   * Sets the number of components of the raster image. @BR
   * For example, an RGB image has 3 components.
   */
  void setComponents(SbRasterImage::Components comp);


  /**
   * Returns the number of components of each pixel as an enum. @BR
   * For example, an RGBA image returns RGB_TRANSPARENCY.
   */
  SbRasterImage::Components getComponents() const;

  /**
   * Returns the size in bytes of each pixel in the image. @BR
   * Returns -1 in case of invalid or unknown components type.
   *
   * E.g: For an RGB image, the pixel size is 3 * sizeof( unsigned char ) = 3 bytes.
   */
  int getComponentsSize() const;

  /**
   * Returns the number of components of each pixel. @BR
   * Returns -1 in case of invalid or unknown components type.
   *
   * E.g: For an RGB image it returns 3 (R, G and B).
   */
  int getComponentsCount() const;

  /**
   * Sets the pixel buffer of the raster image. @BR
   * By default, the memory policy is COPY.
   * One of the NO_COPY options is the most likely to be efficient.
   * For interoperability with other classes, pixel buffer must be packed and
   * must respect the RGB ordering.
   */
  void setBuffer(unsigned char* buffer, CopyPolicy copy = COPY);
  
  /**
   * Returns the pixel buffer of the raster image.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize_i32().Value[0]*GetSize_i32().Value[1]*((int)GetComponentsCount())}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getSize_i32()[0]*getSize_i32()[1]*(int)getComponentsCount()}]
   */
  unsigned char* getBuffer() const;

  /**
   * 
   * Returns the number of mipmaps contained by the buffer.
   */ 
  int getNumMipmaps() {return m_numMipmaps;};

  /**
   * Returns the current buffer copy policy.
   */
  CopyPolicy getCopyPolicy() const;

  /** 
   * Removes the Alpha channel from the current raster image.
   * If the copy policy is COPY (Open Inventor owns the memory) then the buffer
   * is reallocated with the correct size.
   * Otherwise the content of the buffer is just modified. 
   * 
   * @return True if the format contains an alpha channel and it was possible to remove it.
   */
  SbBool removeAlphaChannel();

SoINTERNAL public:

  /**
   * Constructor that initializes with an image, with an SoSFImage::DataType parameter.
   */
  SbRasterImage( const SbVec2i32 &size, Components components, SoSFImage::DataType dataType,
                 const void *bytes, CopyPolicy copy=COPY );


  void setNumMipmaps(int nmm) {m_numMipmaps = nmm;};

  void setDataType(SoSFImage::DataType dataType) {m_dataType = dataType;};
  SoSFImage::DataType getDataType() {return m_dataType;};

  void setCompressedInternalFormat(GLenum intFormat) {m_compressedInternalFormat = intFormat;};
  GLenum getCompressedInternalFormat() {return m_compressedInternalFormat;};

protected:
  
  /** 
   * This function returns the size in bytes of the current data type.
   */
  int getDataTypeSizeInBytes() const;

private:

  void commonConstructor( const SbVec2i32 &size, Components components, SoSFImage::DataType dataType,
                 const void *bytes, CopyPolicy copy );


  SbVec2i32 m_size;
  Components m_components;
  unsigned char* m_buffer;
  CopyPolicy m_copy;
  int m_numMipmaps;
  GLenum m_compressedInternalFormat;

  SoSFImage::DataType m_dataType;
};

inline SbRasterImage::CopyPolicy 
SbRasterImage::getCopyPolicy() const
{
  return m_copy;
}

#endif
