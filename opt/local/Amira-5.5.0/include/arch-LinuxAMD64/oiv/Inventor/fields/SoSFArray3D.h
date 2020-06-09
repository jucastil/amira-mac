/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : B. Grange (Jan 2005)
**=======================================================================*/

#ifndef  _SO_SF_ARRAY_3D_
#define  _SO_SF_ARRAY_3D_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFArray.h>

class SoMemoryObject;

/**
 * Field containing a 3D array value.
 *
 * @ingroup fields
 *
 * @DESCRIPTION
 * This field contains a 3D array of values of a specified type.
 * The #setValue method allows you to specify the dimensions and type of data
 * the array will contain, as well as the number of significant bits.
 * The CopyPolicy allows you to control whether Open Inventor will make a copy
 * of the data and, if not, whether the application or Open Inventor is
 * responsible for managing the memory.
 *
 * In ASCII format, an SoSFArray3D is written to file in the following format:
 * @UL
 * @LI Three numbers define the dimensions of the array
 * @LI One string defines the type of the data:
 * @UL
 * @LI BYTE for signed bytes
 * @LI UBYTE for unsigned bytes
 * @LI SHORT for signed shorts
 * @LI USHORT for unsigned shorts
 * @LI INT32 for signed 32 bits ints
 * @LI UINT32 for unsigned 32 bits ints
 * @LI FLOAT for floating point values
 * @ul
 * @LI A list of values in decimal, hexadecimal, or octal format for integers or
 *     in standard scientific notation for float. Numbers are separated by a blank (space, tab, return...).
 * @LI One number defines the number of significant bits
 * @ul
 * The example below shows the definition of a 2x2x2 array of unsigned bytes with
 * data values 0, 1, 2, 3, 4, 5, 6, 7 and a number of significant bits of 8:
 *<PRE>
 * 2 2 2 UBYTE
 * 0 1
 * 2 3
 * 4 5
 * 6 7
 * 8
 * </PRE>
 *
 * An SoSFArray3D may be empty or contain only dimension and type information,
 * but no data values.  With no data values the previous example would be
 * written with the prefix "NODATA" like this:
 *<PRE>
 * NODATA 2 2 2 UBYTE
 * 8
 * </PRE>
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoSFArray,
 *    SoSFArray2D
 *
 *
 */

class INVENTOR_API SoSFArray3D : public SoSFArray
{
  SO_SFIELD_REQUIRED_HEADER(SoSFArray3D);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFArray3D);

public:
  using SoSFArray::getValue;
  using SoSFArray::startEditing;
  using SoSFArray::getSize;

  /**
   * Fill the array with data of the specified dimensions and type using the specified copy policy.
   * [OIV-WRAPPER-ARG IN,IN,IN,ARRAY,IN]
   */
  void setValue(const SbVec3i32 &size, const SbDataType& dataType,
                unsigned int numSigBits, const void* data,
                CopyPolicy copy);

  /**
   * Fill the array with data of the specified dimensions and type using the specified copy policy.
   * [OIV-WRAPPER-NOT-WRAP]
   */
  void setValue(const SbVec3i32 &size,
                unsigned int numSigBits, SoMemoryObject* memObj,
                CopyPolicy copy);

  /**
   * Returns the number of significant bits.
   */
  inline unsigned int getNumSigBits() const;

  /**
   * Returns TRUE if all of the values of this field equal those of the given field f.
   * If the fields are different types FALSE will always be returned.
   */
  virtual int operator ==(const SoSFArray3D &f) const;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

private:
  using SoSFArray::setValue;
  using SoSFArray::operator==;

  /**
   * Read the field
   */
  virtual SbBool readValue(SoInput *in);

  /**
   * Write the field
   */
  virtual void writeValue(SoOutput *out) const ;

  /** Number of significant bits */
  unsigned int m_numSigBits;

};

/*******************************************************************************/
unsigned int
SoSFArray3D::getNumSigBits() const
{
  return m_numSigBits;
}

#endif
