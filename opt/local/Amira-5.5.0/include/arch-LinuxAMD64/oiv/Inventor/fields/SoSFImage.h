/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_IMAGE_
#define  _SO_SF_IMAGE_

#include <Inventor/SbDataType.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>
#include <Inventor/fields/SoSubField.h>
#include <Inventor/sys/SoGLType.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFImage subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
* Field containing a 2D image.
*
* @ingroup fields
*
* @DESCRIPTION
*   A field containing a two-dimensional image. Images can be grayscale (intensity),
*   grayscale with transparency information, RGB, or RGB with transparency. Each
*   component of the image (intensity, red, green, blue or transparency (alpha)) can
*   have an unsigned one-byte value from 0 to 255.
*
*   Values are returned as arrays of unsigned chars. The image is stored in this
*   array starting at the bottom left corner of the image with the intensity or red
*   component of that pixel, followed by either the alpha, the green and blue, or
*   the green, blue and alpha components (depending on the number of components in
*   the image). The next value is the first component of the next pixel to the
*   right.
*
*   SoSFImages are written to file as three integers representing the width, height
*   and number of components in the image, followed by width*height hexadecimal
*   values representing the pixels in the image, separated by whitespace. A
*   one-component image will have one-byte hexadecimal values representing the
*   intensity of the image. For example, 0xFF is full intensity, 0x00 is no
*   intensity. A two-component image puts the intensity in the first (high) byte and
*   the transparency in the second (low) byte. Pixels in a three-component image
*   have the red component in the first (high) byte, followed by the green and blue
*   components (so 0xFF0000 is red). Four-component images put the transparency byte
*   after red/green/blue (so 0x0000FF80 is semi-transparent blue). Note: each pixel
*   is actually read as a single unsigned number, so a 3-component pixel with value
*   "0x0000FF" can also be written as "0xFF" or "255" (decimal).
*
*   For example,
*
*   <PRE>
*    1 2 1 0xFF 0x00
*    </PRE>
*    is a 1 pixel wide by 2 pixel high grayscale image, with the bottom pixel
*   white and the top pixel black. And:
*
*   <PRE>
*    2 4 3 0xFF0000 0xFF00 0 0 0 0 0xFFFFFF 0xFFFF00
*    </PRE>
*    is a 2 pixel wide by 4 pixel high RGB image, with the bottom left pixel
*   red, the bottom right pixel green, the two middle rows of pixels black, the top
*   left pixel white, and the top right pixel yellow.
*
* @SEE_ALSO
*    SoField,
*    SoSField
*
*
*/

class SoBufferObject;
class SoCpuBufferObject;
class SbRasterImage;

class INVENTOR_API SoSFImage : public SoSField {

  // Uses only some of the standard field stuff
  // (because there is no SbImage type):
  SO_SFIELD_REQUIRED_HEADER(SoSFImage);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFImage);

public:

#ifdef FLOAT
#undef FLOAT
#endif
  /**
   * Encoding data type. UNSIGNED_BYTE by default.
   */
  enum DataType {
     /** UNSIGNED_BYTE */
    UNSIGNED_BYTE = SbDataType::UNSIGNED_BYTE,
    /** UNSIGNED_SHORT */
    UNSIGNED_SHORT = SbDataType::UNSIGNED_SHORT,
    /** UNSIGNED_INT32 */
    UNSIGNED_INT32 = SbDataType::UNSIGNED_INT32,
    /** SIGNED_BYTE */
    SIGNED_BYTE = SbDataType::SIGNED_BYTE,
    /** SIGNED_SHORT */
    SIGNED_SHORT = SbDataType::SIGNED_SHORT,
    /** SIGNED_INT32 */
    SIGNED_INT32 = SbDataType::SIGNED_INT32,
    /** FLOAT */
    FLOAT = SbDataType::FLOAT
  };


  /**
   * SoSFImage may be manipulating some large amounts of memory.
   * It is therefore convienent to be able to set the memory usage
   * policy dynamically. By default, the memory
   * policy is COPY, which is consistent with other OIV fields.
   * The most likely to be efficient is NO_COPY. See also
   * setNeverWrite.
   */
  enum CopyPolicy {
    /**
     *  Open Inventor will make a copy of the data (default)
     */
    COPY = 0,
#ifdef OIV_NET_DOC
    /**
     *  Passed buffer used.
     */
#else
    /**
     *  Passed buffer used, user will delete
     */
#endif //OIV_NET_DOC
		NO_COPY = 1,
    /**
     *  Passed buffer used, SoSFImage will delete.
     * Use this if memory is allocated with "new".
     */
    NO_COPY_AND_DELETE = 2,
    /**
     *  Passed buffer used, SoSFImage will free.
     * Use this if memory is allocated with "malloc".
     */
    NO_COPY_AND_FREE = 3
  };

  // getValue returns the size, number of components and a constant
  // pointer to the image.

  /**
  *
  * Returns the pixels in the image as an array of values of type \<dataType>. The size and nc
  * arguments are filled in with the dimensions of the image and the number of
  * components in the image. The number of bytes in the array returned will be
  * @B size[0]*sizeof(@I\<dataType\>@i)*size[1]*sizeof(@I\<dataType\>@i)*nc@b.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*nc}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  const void* getValue(SbVec2s &size, int &nc, DataType &dataType) const;
  /**
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*nc}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  const void* getValue(SbVec2i32 &size, int &nc, DataType &dataType) const;

  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*nc}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  const unsigned char *getValue(SbVec2s &size, int &nc) const;
  /**
  * [OIV-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size.Value[0]*size.Value[1]*nc}]
  * [OIVJAVA-WRAPPER PACK{TextureImage}]
  */
  const unsigned char *getValue(SbVec2i32 &size, int &nc) const;



  // setValue copies the image given to it into internal storage.
  // See startEditing() for a way of avoiding the copy if you are
  // doing a getValue() followed immediately by a setValue(). Set
  // 'copy' to NO_COPY or NO_COPY_AND_DELETE to pass directly the
  // pointer on the images. Otherwise, the buffer 'bytes' will be
  // copied. If copy is set to COPY or NO_COPY_AND_DELETE or
  // NO_COPY_AND_FREE, this object will delete the buffer when
  // required. If a NULL pointer is passed, a new bloc is allocated
  // according to the size and the number of components.

  /**
  *
  * Sets the value of this field to be an image of the given size, with the given
  * number of components, and with the given pixel values.
  * @B size[0]*sizeof(@I\<dataType>@i)*size[1]*sizeof(@I\<dataType>@i)*nc@b bytes from
  * the given array will be copied into internal storage maintained by the SoSFImage field.
  *
  * At times, SoSFImage may need to manipulate large amounts of memory. Therefore, it
  * is useful to be able to specify the memory usage policy dynamically. By default,
  * the memory policy is COPY, which is consistent with other Open Inventor fields.
  * The most likely to be efficient is NO_COPY. See also setNeverWrite().
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setValue(const SbVec2s &size, int nc,
                DataType dataType,
                const void* data,
                CopyPolicy copy=COPY);

  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setValue(const SbVec2s &size, int nc,
                DataType dataType,
                SoBufferObject* bufferObject,
                CopyPolicy copy=COPY);

  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setValue (const SbVec2i32 &size, int nc,
                 DataType dataType,
                 const void* data,
                 CopyPolicy copy=COPY);

  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setValue (const SbVec2i32 &size, int nc,
                 DataType dataType,
                 SoBufferObject* bufferObject,
                 CopyPolicy copy=COPY);

  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  */
  void setValue(const SbVec2s &size, int nc,
                const unsigned char *bytes,
                CopyPolicy copy = COPY);

  void setValue(const SbVec2i32 &size, int nc,
                const unsigned char *bytes,
                CopyPolicy copy = COPY);


  /**
  * This method can be used for subtexturing. Instead of
  * replacing the texture in texture memory, only parts of it are
  * replaced. This is much faster and uses less memory. In any case
  * this method affects the texture in processor memory. Note that
  * the sub-image must have the same number of components as
  * the one contained in this object. The texture in texture memory
  * will not actually be modified until the next render traversal.
  * See also startEditing(), finishEditing().
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setSubValue(const SbVec2s &subSize,
                   const SbVec2s &offset,
                   void *data);
  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setSubValue (const SbVec2i32 &subSize,
                    const SbVec2i32 &offset,
                    void *data);


  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  void setSubValue(const SbVec2s &subSize,
                   const SbVec2s &offset,
                   unsigned char *bytes);
  /**
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  void setSubValue(const SbVec2i32 &subSize,
                   const SbVec2i32 &offset,
                   unsigned char *bytes);


  /**
   * This method can be used for subtexturing. Instead of
   * replacing the texture in texture memory, only parts of it are
   * replaced. This is much faster and uses less memory. In any case
   * this method affects the texture in processor memory. Note that
   * the sub-images must have the same number of components as
   * the one contained in this object. The texture in texture memory
   * will not actually be modified until the next render traversal.
   * See also startEditing(), finishEditing().
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void setSubValues(const SbVec2s *subSizes,
                    const SbVec2s *offsets,
                    int num, void **data);
  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  void setSubValues (const SbVec2i32 *subSizes,
                     const SbVec2i32 *offsets,
                     int num, void **data);


  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  void setSubValues(const SbVec2s *subSizes,
    const SbVec2s *offsets,
    int num, unsigned char **subBytes);

  /**
  * [OIV-WRAPPER-CUSTOM-CODE]
  */
  void setSubValues(const SbVec2i32 *subSizes,
    const SbVec2i32 *offsets,
    int num, unsigned char **subBytes);


  /**
  * Equality test.
  */
  int operator ==(const SoSFImage &f) const;

  /**
  * Inequality test.
  */
  int operator !=(const SoSFImage &f) const
  { return ! ((*this) == f); }

  /**
  * This method (along with finishEditing()) can be used to efficiently
  * edit the values in an image field.
  * It returns the size of the image in the @B size@b and @B nc@b
  * arguments; writing past the end of the array returned is a good way to cause
  * hard-to-find core dumps.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*nc}]
  */
  void* startEditing(SbVec2s &size, int &nc, DataType &dataType);
  /**
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*nc}]
  */
  void* startEditing(SbVec2i32 &size, int &nc, DataType &dataType);

  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  * [OIV-WRAPPER-NOT-WRAP]
  */
  unsigned char *startEditing(SbVec2s &size, int &nc);
  /**
  * [OIV-WRAPPER-NOT-WRAP]
  */
  unsigned char *startEditing(SbVec2i32 &size, int &nc);


  /**
  * This method (along with startEditing())can be used to efficiently
  * edit the values in an image field.
  */
  void finishEditing();

#ifdef OIV_NET_DOC
  /**
  * Returns a reference to a given subTexture set by SetSubValue() or SetSubValues().
  * These two methods append subTextures to a list.  Also returns the size of
  * the subtexture and the offset from the beginning of the image of the
  * requested subImage.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*((OIV::Inventor::SbDataType((OIV::Inventor::SbDataType::DataTypes) dataType)).Size)}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */

#else
  /**
  * Returns a pointer to a given subTexture set by setSubValue() or setSubValues().
  * These two methods append subTextures to a list.  Also returns the size of
  * the subtexture and the offset from the beginning of the image of the
  * requested subImage.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*((OIV::Inventor::SbDataType((OIV::Inventor::SbDataType::DataTypes) dataType)).Size)}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */

#endif //OIV_NET_DOC
  void*	getSubTexture(int index, SbVec2s &size, SbVec2s &offset, DataType &dataType);
  /**
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*((OIV::Inventor::SbDataType((OIV::Inventor::SbDataType::DataTypes) dataType)).Size)}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  void*	getSubTexture(int index, SbVec2i32 &size, SbVec2i32 &offset, DataType &dataType);

  /**
  *
  * Same as above.
  * Convenience method for the unsigned char datatype.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]}]
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  unsigned char *getSubTexture(int index, SbVec2s &size, SbVec2s &offset);
  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size[0]*size[1]}]
   * [OIVJAVA-WRAPPER PACK{SubTextureImage}]
   */
  unsigned char *getSubTexture(int index, SbVec2i32 &size, SbVec2i32 &offset);

  /**
  * Returns TRUE if subTextures have been defined or FALSE if none have been defined.
  * Also returns the number of subTextures defined.
  * [OIVJAVA-WRAPPER NAME{getNumSubTextures}]
  * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{return 0}]
  */
  SbBool hasSubTextures(int &numSubTextures);

  /**
  * Sets the "neverWrite" flag.
  * As this field may have to handle large amounts of data and its representation in
  * an .iv file is not very efficient, it is often a good idea not to allow that
  * data to be written out when required by a write action. By default, the
  * "neverWrite" condition is FALSE.
  */
  void setNeverWrite(SbBool neverWrite);

  /**
  * Queries the "neverWrite" flag.
  */
  SbBool isNeverWrite()
  { return m_neverWrite ; }

  /**
  * Returns TRUE if the image contains any transparent pixels.
  * Specifically if the image has 2 or 4 components and at least
  * one pixel has an alpha value less then 255.
  */
  SbBool hasTransparency() const;

  /**
   * Returns an instance of SbRasterImage filled with the content of this field.
   * It is useful to save the result of an SoRenderToTexture operation in feedback mode.
   * The caller is responsible of the release of the returned raster image.
   *
   * When the content is not of type UNSIGNED_BYTE the data is downsampled to UNSIGNED_BYTE
   * unless the downSample parameter is set to false.
   *
   * Returns NULL if the content cannot be converted to an SbRasterImage.
   */
  SbRasterImage* toRasterImage(bool downSample = true) const;

SoINTERNAL public:

  static void initClass();
  static void exitClass();
  void resetSubTextures();
  static GLenum getGLType(SoSFImage::DataType dataType);

  SoBufferObject* getBufferObject() const;

  enum HasTransparency
  {
    /**  hasTransparency always return TRUE. */
    ON,
    /**  hasTransparency always return FALSE. */
    OFF,
    /**  hasTransparency parses the buffer to figure out the result. */
    AUTO
  };

  /**
   * This function controls the value returned by the function hasTransparency.
   */
  void setHasTransparency( HasTransparency status );

  SbVec2i32 getSize() const
  {return m_size;}

private:

  // Width and height of image
  SbVec2i32 m_size;

  // Number of components per pixel
  int m_numComponents;

  // The SoBufferObject which contains the actual data.
  SoBufferObject* m_bufferObject;

  // This variable indicates if the buffer object was created by us to
  //  bring the specified void* pointer.
  // If the user use setValue with a SoBufferObject this variable is set to FALSE.
  SbBool m_bufferObjectBringsUserPointer;

  // This variable indicates if we must delete the SoBufferObject or if
  // it was specified by the user.
  SbBool m_mustDeleteBufferObject;

  // This buffer object is used between start/finish editing function.
  SoCpuBufferObject* m_editingBufferObject;

  CopyPolicy m_copyPolicy;

  // list of [subSize, offset, bytes]
  SbPList m_subTexList;
  SbBool m_neverWrite;

  // -1 = don't know yet, 0 = no transp, 1 = has transp
  int m_hasTransparency;

  HasTransparency m_hasTransparencyState;

  DataType m_dataType;

  unsigned int getImageValueSize() const;

  // Reading and writing
  virtual SbBool readValue(SoInput *in);
  virtual void writeValue(SoOutput *out) const;
  void deleteBytesArray();
  void setValue (int32_t w, int32_t h, int nc, DataType dataType,
                     const void* data, CopyPolicy copy);

  void setValue (int32_t w, int32_t h, int nc, DataType dataType,
                     SoBufferObject* bufferObject, CopyPolicy copy);

  const void* getValue(int32_t &w, int32_t &h , int &nc, DataType &dataType) const;
  void* startEditing(int32_t &w, int32_t &h, int &nc, DataType &dataType);


};

inline SoBufferObject*
SoSFImage::getBufferObject() const
{
  return m_bufferObject;
}

#endif /* _SO_SF_IMAGE_ */

