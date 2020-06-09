/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_SF_IMAGE_3_
#define  _SO_SF_IMAGE_3_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>

class SoBufferObject;
class SoCpuBufferObject;

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFImage3 subclass of SoSField. This field handles 3 dimensional images,
// that is a set of same-type (number of components) and same-size images.
// It is basically useful for 3d texturing (see Inventor/nodes/SoTexture3.h).
// This field uses a lot of memory (a simple 256x256x256 image in
// grayscale already takes 16MB of memory). Therefore, as opposed to the
// other fields, this field provides a way to manage memory and avoid
// useless copies of data. This is essentially done through the CopyPolicy
// enumeration and the set/isNeverWrite methods. The CopyPolicy provides
// four types of memory management:
// COPY is the default and is consistent with all other fields: any buffer
// passed is copied and the memory management is done inside the field;
// NO_COPY only uses a pointer given by the application which remains
// responsible for the memory management;
// NO_COPY_AND_DELETE accepts pointers from the application (ie does not
// copy the buffer) but the field takes responsability for the memory
// management. Note that this case is only intended for buffers
// created with the operator 'new';
// NO_COPY_AND_FREE is essentially the same as above but applies the function
// 'free' on the pointer instead of the operator 'delete'.
// Furthermore, two methods, is/setNeverWrite allow to write or not write
// out the data stored in this field. By default, the 'never write' condition
// is TRUE.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Field containing a 3D image.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a three-dimensional image. A three-dimensional image can be
 *   thought of as a sequence of two-dimensional image "slices."
 *   
 *   Images can be grayscale (intensity), grayscale with transparency information,
 *   RGB, or RGB with transparency. Each component of the image (intensity, red,
 *   green, blue or transparency (alpha)) can have an unsigned one-byte value from 0
 *   to 255.
 *   
 *   Values are returned as arrays of unsigned chars. The image is stored in this
 *   array starting at the bottom left front corner of the image with the intensity
 *   or red component of that pixel, followed by either the alpha, the green and
 *   blue, or the green, blue and alpha components (depending on the number of
 *   components in the image). The next value is the first component of the next
 *   pixel to the right.
 *   
 *   SoSFImage3s are written to file as four integers representing the width, height,
 *   depth and number of components in the image, followed by width*height*depth
 *   hexadecimal values representing the pixels in the image, separated by
 *   whitespace. A one-component image will have one-byte hexadecimal values
 *   representing the intensity of the image. For example, 0xFF is full intensity,
 *   0x00 is no intensity. A two-component image puts the intensity in the first
 *   (high) byte and the transparency in the second (low) byte. Pixels in a
 *   three-component image have the red component in the first (high) byte, followed
 *   by the green and blue components (so 0xFF0000 is red). Four-component images put
 *   the transparency byte after red/green/blue (so 0x0000FF80 is semi-transparent
 *   blue). Note: each pixel is actually read as a single unsigned number, so a
 *   3-component pixel with value "0x0000FF" can also be written as "0xFF" or "255"
 *   (decimal).
 *   
 *   For example,
 *   
 *   <PRE>
 *    1 2 3 1 0xFF 0x00 0x00 0xFF 0xFF 0x00
 *    </PRE>
 *    is a 1 pixel wide by 2 pixel high by 3 pixel deep grayscale image, with
 *   the bottom pixel white and the top pixel black in the first (front-most) slice.
 *   In the second slice the bottom pixel is black and the top pixel is white. And:
 *   
 *   <PRE>
 *    2 4 3 3 0xFF0000 0xFF00 0 0 0 0 0xFFFFFF 0xFFFF00 ...
 *    </PRE>
 *    is a 2 pixel wide by 4 pixel high by 3 pixel deep RGB image, with the
 *   bottom left pixel red, the bottom right pixel green, the two middle rows of
 *   pixels black, the top left pixel white, and the top right pixel yellow in the
 *   first slice. Subsequent slices are not shown.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField
 * 
 * 
 */ 

class INVENTOR_API SoSFImage3 : public SoSField {

  // Uses only some of the standard field stuff (because there is no
  // SbImage type):
  SO_SFIELD_REQUIRED_HEADER(SoSFImage3);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFImage3);
  
public:

  /**
   * SoSFImage3 may be manipulating some large amounts of memory.
   * It is therefore convienent to be able to set the memory usage
   * policy dynamically (copying a small 256x256x256 image with
   * only 8 bits color already takes 16MB). By default, the memory
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
     *  Passed buffer used
     */
#else
    /**
     *  Passed buffer used, user will delete 
     */
#endif //OIV_NET_DOC
	  NO_COPY = 1,
    /**
     *  Passed buffer used, SoSFImage3 will delete . @BR
     * Use this if memory is allocated with "new". 
     */
    NO_COPY_AND_DELETE = 2,
    /**
     *  Passed buffer used, SoSFImage3 will free . @BR
     * Use this if memory is allocated with "malloc". 
     */
    NO_COPY_AND_FREE = 3
  };

  /**
   * Returns the pixels in the image as an array of unsigned chars. The @B size @b
   * and @B nc @b arguments are filled in with the dimensions of the image and the
   * number of components in the image; the number of bytes in the array returned
   * will be @B size @b[0]*@B size @b[1]*@B size @b[2]*@B nc @b.
   * [OIV-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size.Value[0]*size.Value[1]*size.Value[2]*nc}]
   * [OIVJAVA-WRAPPER PACK{TextureImage},DUPLICATE{getNumComponents}]
   * [OIVJAVA-WRAPPER-ARG APPLY_TO{getNumComponents} NO_WRAP,OUT]
   * [OIVJAVA-WRAPPER-RETURN-TYPE APPLY_TO{getNumComponents} NO_WRAP]
   */
  const unsigned char *getValue(SbVec3s &size, int &nc) const;

  /**
   * Returns the pixels in the image as a buffer object. The @B size @b
   * and @B nc @b arguments are filled in with the dimensions of the image and the
   * number of components in the image; the number of bytes in the array returned
   * will be @B size @b[0]*@B size @b[1]*@B size @b[2]*@B nc @b.
   * [OIVJAVA-WRAPPER PACK{BufferObject}]
   */
  SoBufferObject *getBufferObject(SbVec3s &size, int &nc) const;

#ifdef OIV_NET_DOC
  /**
  * SetValue copies the image given to it into internal storage.
  * See StartEditing() for a way of avoiding the copy if you are
  * doing a GetValue() followed immediately by a SetValue(). Set
  * 'copy' to NO_COPY or NO_COPY_AND_DELETE to pass directly the
  * reference on the images. Otherwise, the buffer 'bytes' will be
  * copied. If copy is set to COPY or NO_COPY_AND_DELETE or
  * NO_COPY_AND_FREE, this object will delete the buffer when
  * required. If a NULL reference is passed, a new bloc is allocated
  * according to the size and the number of components.
  */

#else
  /**
  * setValue copies the image given to it into internal storage.
  * See startEditing() for a way of avoiding the copy if you are
  * doing a getValue() followed immediately by a setValue(). Set
  * 'copy' to NO_COPY or NO_COPY_AND_DELETE to pass directly the
  * pointer on the images. Otherwise, the buffer 'bytes' will be
  * copied. If copy is set to COPY or NO_COPY_AND_DELETE or
  * NO_COPY_AND_FREE, this object will delete the buffer when
  * required. If a NULL pointer is passed, a new bloc is allocated
  * according to the size and the number of components.
  */

#endif //OIV_NET_DOC
  void setValue(const SbVec3s &size, 
                int nc,
                unsigned char *bytes, 
                CopyPolicy copy = COPY);


  void setValue(const SbVec3s &size, 
                int nc,
                SoBufferObject* bufferObject, 
                CopyPolicy copy = COPY);

  /**
   * These methods may be used for subtexturing: instead of replacing the entire
   * texture in texture memory, only parts of it are replaced. This is much faster
   * and uses less memory. In any case these methods affect the texture in system
   * memory. Note that the sub-images must have the same number of components as the
   * one contained in this object. The texture in texture memory will not actually be
   * modified until the next render traversal. 
   */
  void setSubValue(const SbVec3s &subSize, 
                   const SbVec3s &offset,
                   unsigned char *bytes, 
                   CopyPolicy copy = COPY);
  /**
   * These methods may be used for subtexturing: instead of replacing the entire
   * texture in texture memory, only parts of it are replaced. This is much faster
   * and uses less memory. In any case these methods affect the texture in system
   * memory. Note that the sub-images must have the same number of components as the
   * one contained in this object. The texture in texture memory will not actually be
   * modified until the next render traversal. 
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  void setSubValues(const SbVec3s *subSizes, 
                    const SbVec3s *offsets,
                    int num, 
                    unsigned char **bytes, 
                    CopyPolicy copy = COPY);

  /**
   * Equality/inequality tests
   */
  int operator==(const SoSFImage3 &f) const;
  /**
   * Equality/inequality tests
   */
  int operator!=(const SoSFImage3 &f) const
  { return ! ((*this) == f); }

#ifdef OIV_NET_DOC
  /**
  * These methods can be used to efficiently edit the values in an image field.
  * StartEditing() returns the size of the image in the size and nc
  * arguments; writing past the end of the array returned is a good way to cause
  * hard-to-find core dumps.
  * 
  * Avoid copying the values in/out, if you are just changing the bytes and not
  * changing the dimensions of the image. This is equivalent to GetValue(), but
  * returns a reference you can change. Using StartEditing() allows subtexturing,
  * which is a more efficient way of doing texture modification.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*size.Value[2]*nc}]
  */

#else
  /**
  * These methods can be used to efficiently edit the values in an image field.
  * startEditing() returns the size of the image in the size and nc
  * arguments; writing past the end of the array returned is a good way to cause
  * hard-to-find core dumps.
  * 
  * Avoid copying the values in/out, if you are just changing the bytes and not
  * changing the dimensions of the image. This is equivalent to getValue(), but
  * returns a pointer you can change. Using startEditing() allows subtexturing,
  * which is a more efficient way of doing texture modification.
  */

#endif //OIV_NET_DOC
  unsigned char *startEditing(SbVec3s &size, int &nc);

#ifdef OIV_NET_DOC
  /**
  * These methods can be used to efficiently edit the values in an image field.
  * StartEditing() returns the size of the image in the size and nc
  * arguments; writing past the end of the array returned is a good way to cause
  * hard-to-find core dumps.
  * 
  * Avoid copying the values in/out, if you are just changing the bytes and not
  * changing the dimensions of the image. This is equivalent to GetValue(), but
  * returns a reference you can change. Using StartEditing() allows subtexturing,
  * which is a more efficient way of doing texture modification.
  */

#else
  /**
  * These methods can be used to efficiently edit the values in an image field.
  * startEditing() returns the size of the image in the size and nc
  * arguments; writing past the end of the array returned is a good way to cause
  * hard-to-find core dumps.
  * 
  * Avoid copying the values in/out, if you are just changing the bytes and not
  * changing the dimensions of the image. This is equivalent to getValue(), but
  * returns a pointer you can change. Using startEditing() allows subtexturing,
  * which is a more efficient way of doing texture modification.
  */

#endif //OIV_NET_DOC
  void finishEditing();

  /**
  * Returns a buffer to a given subTexture set by setSubValue or setSubValues. 
  * These two methods append subTextures to a list.  Also returns the size of 
  * the subtexture and the offset from the beginning of the image of the 
  * requested subImage.
  * [OIVNET-WRAPPER-RETURN-TYPE ARRAY{UNKNOWN}]
  * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size[0]*size[1]*size[2]*getNumComponents()}]
  * [OIVJAVA-WRAPPER PACK{SubTextureImage}]
  */
  unsigned char *getSubTexture(int index, SbVec3s &size, SbVec3s &offset);

  /**
   * Returns TRUE if subTextures have been defined or FALSE if none have been defined.
   * Also returns the number of subTextures defined.  
   * [OIVJAVA-WRAPPER NAME{getNumSubTextures}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE SUCCESS_FLAG{return 0}]
   */
  SbBool hasSubTextures(int &numSubTextures);

  /**
   * As this field may have to handle large amounts of data and its representation in
   * an .iv file is not very efficient, it is often a good idea not to allow that
   * data to be written out when required by a write action. By default, the
   * "neverWrite" condition is TRUE.
   */
  void setNeverWrite(SbBool neverWrite);
  /**
   * As this field may have to handle large amounts of data and its representation in
   * an .iv file is not very efficient, it is often a good idea not to allow that
   * data to be written out when required by a write action. By default, the
   * "neverWrite" condition is TRUE.
   */
  SbBool isNeverWrite()
  { return m_neverWrite; }

  /** [OIVJAVA-WRAPPER NO_WRAP] */
  SoBufferObject* getBufferObject() const;

 SoINTERNAL public:

  static void initClass();
  static void exitClass();
  void resetSubTextures();

  void deleteBytesArray();
  
  int getNumComponents() const;

private:

  // Width, height and depth of image
  SbVec3s m_size;

  // Number of components per pixel
  int m_numComponents;

  // Buffer object which contains the data.
  SoBufferObject* m_bufferObject;

  SoCpuBufferObject* m_editingBufferObject;

  SbBool m_bufferObjectBringsUserPointer;
  SbBool m_mustDeleteBufferObject;

  CopyPolicy m_copyPolicy;

  // list of [subSize,offset,bytes,copypolicy]
  SbPList m_subTextures;

  SbBool m_neverWrite;
  
  // Reading and writing
  virtual SbBool readValue(SoInput *in);
  virtual void writeValue(SoOutput *out) const;
};

inline SoBufferObject* 
SoSFImage3::getBufferObject() const
{
  return m_bufferObject;
}

inline int 
SoSFImage3::getNumComponents() const
{
  return m_numComponents;
}

#endif /* _SO_SF_IMAGE_3_ */

