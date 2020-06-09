/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_BIT_MASK_
#define  _SO_SF_BIT_MASK_

#include <Inventor/fields/SoSFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBitMask subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Single-value field containing a set of bit flags.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-value field that contains a mask of bit flags, stored as an integer.
 *   Nodes that use this field class define mnemonic names for the bit flags. These
 *   names should be used when setting or testing the values of the field, even
 *   though the values are treated as integers in the methods.
 *   
 *   The bit-wise "&" and "|" operators should be used when testing and setting flags
 *   in a mask. For example, to turn on the sides of a 3D text node and turn off the
 *   back you would write:
 *   
 *   <PRE>
 *    text3->parts = text3->parts.getValue() | SoText3::SIDES;
 *    text3->parts = text3->parts.getValue() & ~SoText3::BACK;
 *    </PRE>
 *    SoSFBitMasks are written to file as one or more mnemonic enumerated type
 *   names, in this format:
 *   
 *   <PRE>
 *    ( flag1 | flag2 | ... )
 *    </PRE>
 *    If only one flag is used in a mask, the parentheses are optional. These
 *   names differ among uses of this field in various node or engine classes. See
 *   their reference pages for the names.
 *   
 *   The field values may also be represented as integers, but this is not guaranteed
 *   to be portable.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFBitMask
 * 
 * 
 */ 

class INVENTOR_API SoSFBitMask : public SoSFEnum {

  // Use standard field stuff for derived class;
  // the rest is inherited from SoSFEnum
  SO_SFIELD_DERIVED_HEADER(SoSFBitMask, int, int);

  // Inherits other stuff from Enum field

 protected:
  // Looks up enum name, returns value. Returns FALSE if not found.
  virtual SbBool      findEnumValue(const SbName &name, int &val);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_BIT_MASK_ */

