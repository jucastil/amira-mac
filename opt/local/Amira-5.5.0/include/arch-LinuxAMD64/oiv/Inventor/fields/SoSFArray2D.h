/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 2005)
**=======================================================================*/

#ifndef  _SO_SF_ARRAY_2D_
#define  _SO_SF_ARRAY_2D_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFArray.h>

class SoMemoryObject;

/**
 * Field containing a 2D array value.
 *
 * @ingroup fields
 *
 * @DESCRIPTION
 * This field contains a 2D array of values of a specified type.
 * The #setValue method allows you to specify the dimensions and type of data
 * the array will contain.
 * The CopyPolicy allows you to control whether Open Inventor will make a copy
 * of the data and, if not, whether the application or Open Inventor is 
 * responsible for managing the memory.
 *
 * In ASCII format, an SoSFArray2D is written to file in the following format:
 * @UL
 * @LI Two numbers define the dimensions of the array
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
 * @ul
 * The example below shows the definition of a 2x2 array of unsigned bytes with
 * data values 0, 1, 2 and 3:
 *<PRE>
 * 2 2 UBYTE
 * 0 1
 * 2 3
 * </PRE>
 * Below is a 2x3 array of floats:
 *<PRE>
 * 2 3 FLOAT
 * 0.5 1 .72
 * 0.33 6.2e4 0.9
 * </PRE>
 *
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *
 *
 */

class INVENTOR_API SoSFArray2D : public SoSFArray
{
  // Uses only some of the standard field stuff
  // (because there is no SbArray2D type):
  SO_SFIELD_REQUIRED_HEADER(SoSFArray2D);
  SO_SFIELD_CONSTRUCTOR_HEADER(SoSFArray2D);

public:
  /**
   * Fill the 2D array with data of the specified dimensions and type using the specified copy policy.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,IN]
   */
  void setValue(const SbVec2s &size, DataType dataType,
                const void* data, CopyPolicy copy=COPY);

  /**
   * Fill the 2D array with data of the specified dimensions and type using the specified copy policy.
   * [OIV-WRAPPER-ARG IN,IN,ARRAY,IN]
   */
  void setValue(const SbVec2i32 &size, DataType dataType,
                const void* data, CopyPolicy copy=COPY);

  /**
   * Returns a read-only pointer to the 2D array's values and its dimensions and data type.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*GetValueSize()}]
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  const void* getValue(SbVec2s &size, DataType &dataType) const ;

  /**
   * Returns a read-only pointer to the 2D array's values and its dimensions and data type.
   * [OIV-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size.Value[0]*size.Value[1]*GetValueSize()}]
   * [OIVJAVA-WRAPPER NAME{get2DValue},PACK{Array2D}]
   */
  const void* getValue(SbVec2i32 &size, DataType &dataType) const ;

  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed.
   * It is illegal to call any other editing methods between startEditing() and finishEditing()
   * (e.g. setValue(), etc.). Fields,  engines or sensors connected to this field
   * are not triggered until finishEditing() is called.
   * Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines and sensors that
   * the field changed, even if none of the values actually were changed.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*GetValueSize()}]
   */
  void* startEditing(SbVec2s &size, DataType &dataType);

  /**
   * Returns a pointer to the internally maintained array that can be modified.
   * The values in the array may be changed, but values cannot be added or removed.
   * It is illegal to call any other editing methods between startEditing() and finishEditing()
   * (e.g. setValue(), etc.). Fields,  engines or sensors connected to this field
   * are not triggered until finishEditing() is called.
   * Calling finishEditing() always sets the isDefault() flag to FALSE and informs engines and sensors that
   * the field changed, even if none of the values actually were changed.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*GetValueSize()}]
   */
  void* startEditing(SbVec2i32 &size, DataType &dataType);

  /**
   * Returns the dimensions of the array.
   * [OIVJAVA-WRAPPER NAME{get2DSize}]
   */
  inline SbVec2i32 getSize() const;

private:
  using SoSFArray::setValue;
  using SoSFArray::getValue;
  using SoSFArray::startEditing;

SoINTERNAL public:
  static void initClass();
  static void exitClass();
};
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
SbVec2i32
SoSFArray2D::getSize() const
{
  return SbVec2i32(m_size[0], m_size[1]);
}

#endif /* _SO_SF_ARRAY_2D_ */
