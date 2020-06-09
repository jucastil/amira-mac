/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MF_IMAGE_
#define  _SO_MF_IMAGE_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFImage subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing multiple 2D images.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing two-dimensional images. Images can be grayscale (intensity),
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
 *   SoMFImages are written to file as three integers representing the width, height
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
 *    SoMField
 * 
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTOR_API SoMFImage : public SoMField {

  // Uses only some of the standard field stuff 
  // (because there is no SbImage type):
  SO_MFIELD_REQUIRED_HEADER(SoMFImage);
  SO__MFIELD_RW_HEADER(SoMFImage);
  SO_MFIELD_CONSTRUCTOR_HEADER(SoMFImage);
  
 public:
  /** SoMFImage may be manipulating some large amounts of memory.
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
    /**
     *  Passed buffer used, user will delete 
     */
    NO_COPY = 1,
    /**
     *  Passed buffer used, SoMFImage will delete.
     * Use this if memory is allocated with "new". 
     */
    NO_COPY_AND_DELETE = 2,
    /**
     *  Passed buffer used, SoMFImage will free.
     * Use this if memory is allocated with "malloc". 
     */
    NO_COPY_AND_FREE = 3
  };

  // getValue returns the size, number of components and a constant
  // pointer to the image.

  /**
   * Returns the pixels in the image as an array of unsigned chars. The size and nc
   * arguments are filled in with the dimensions of the image and the number of
   * components in the image; the number of bytes in the array returned will be
   * @B size@b[0]*@B size@b[1]*@B nc@b.
   */
  const unsigned char *getValue(SbVec2s &size, int &nc) const;

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
   * Sets the value of this field to be an image of the given size, with the given
   * number of components, and with the given pixel values.
   * @B size@b[0]*@B size@b[1]*@B nc@b bytes from the given array will be
   * copied into internal storage maintained by the SoMFImage field.
   * 
   * At times, SoMFImage may need to manipulate large amounts of memory. Therefore, it
   * is useful to be able to specify the memory usage policy dynamically. By default,
   * the memory policy is COPY, which is consistent with other Open Inventor fields.
   * The most likely to be efficient is NO_COPY. See also setNeverWrite().
   */
  void setValue(const SbVec2s &size, int nc,
                const unsigned char *bytes, 
                CopyPolicy copy = COPY);    
#ifdef NOTNOW
  /**
   * This method can be used for subtexturing. Instead of
   * replacing the texture in texture memory, only parts of it are
   * replaced. This is much faster and uses less memory. In any case
   * this method affects the texture in processor memory. Note that
   * the sub-image must have the same number of components as
   * the one contained in this object. The texture in texture memory
   * will not actually be modified until the next render traversal.
   * See also startEditing(), finishEditing().
   */
  void setSubValue(const SbVec2s &subSize, 
                   const SbVec2s &offset,
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
   */
  void setSubValues(const SbVec2s *subSizes, 
                    const SbVec2s *offsets,
                    int num, unsigned char **bytes);   
  /**
   * Equality test.
   */
  int operator ==(const SoMFImage &f) const;

  /**
   * Inequality test.
   */
  int operator !=(const SoMFImage &f) const
  { return ! ((*this) == f); }

  /**
   * This method (along with finishEditing()) can be used to efficiently
   * edit the values in an image field.
   * It returns the size of the image in the @B size@b and @B nc@b
   * arguments; writing past the end of the array returned is a good way to cause
   * hard-to-find core dumps.
   */
  unsigned char *startEditing(SbVec2s &size, int &nc);

  /**
   * This method (along with startEditing())can be used to efficiently
   * edit the values in an image field.
   */
  void finishEditing();

  /**
   * Returns a pointer to a given subTexture set by setSubValue() or setSubValues(). 
   * These two methods append subTextures to a list.  Also returns the size of 
   * the subtexture and the offset from the beginning of the image of the 
   * requested subImage.
   */
  unsigned char *getSubTexture(int index, SbVec2s &size, SbVec2s &offset);

  /**
   * Returns TRUE if subTextures have been defined or FALSE if none have been defined.
   * Also returns the number of subTextures defined.  
   */
  SbBool hasSubTextures(int &numSubTextures);
#endif
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
    { return neverWrite ; }

  /**
   * Returns TRUE if the image contains any transparent pixels.
   * Specifically if the image has 2 or 4 components and at least
   * one pixel has an alpha value less then 255.
   */
  SbBool hasTransparency() const;

 SoINTERNAL public:

  static void initClass();
 //
 void resetSubTextures();
  
 private:

  // Width and height of image
  SbVec2s size;

  // Number of components per pixel
  int numComponents;

  // Array of pixels
  unsigned char *bytes;

  CopyPolicy copyPolicy;

  // list of [subSize, offset, bytes]
 // SbPList subTexList;
  SbBool neverWrite;

  // -1 = don't know yet, 0 = no transp, 1 = has transp
  int m_hasTransparency;
  
  // Reading and writing
  virtual SbBool readValue(SoInput *in);
  virtual void writeValue(SoOutput *out) const;
};

#endif /* _SO_MF_IMAGE_ */

