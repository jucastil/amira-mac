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


#ifndef  _SO_MF_BIT_MASK_
#define  _SO_MF_BIT_MASK_

#include <Inventor/fields/SoMFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFBitMask subclass of SoMEnum
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of masks of bit flags.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of masks of bit flags, stored as
 *   ints. Nodes or engines that use this field class define mnemonic names for the
 *   bit flags. These names should be used when setting or testing the values of the
 *   field, even though the values are treated as integers in the methods.
 *   
 *   The bit-wise "&" and "|" operators should be used when testing and setting flags
 *   in a mask.
 *   
 *   SoMFBitMasks are written to file as one or more mnemonic enumerated type names,
 *   in this format:
 *   
 *   <PRE> 
 *    ( flag1 | flag2 | ... )
 *    </PRE>
 *    If only one flag is used in a mask, the parentheses are optional. These
 *   names differ among uses of this field in various node or engine classes. See the
 *   reference pages for specific nodes or engines for the names.
 *   
 *   The field values may also be represented as integers, but this is not guaranteed
 *   to be portable.
 *   
 *   When more than one value is present, all of the values are enclosed in square
 *   brackets and separated by commas.
 * 
 * 
 */ 

class INVENTOR_API SoMFBitMask : public SoMFEnum {
  // Use standard field stuff for derived class;
  // the rest is inherited from SoMFEnum
  SO_MFIELD_DERIVED_HEADER(SoMFBitMask, int, int);
  SO_MFIELD_SETVALUESPOINTER_HEADER(int);
    
    protected:
  // Looks up enum name, returns value. Returns FALSE if not found.
  virtual SbBool findEnumValue(const SbName &name, int &val);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_MF_BIT_MASK_ */

