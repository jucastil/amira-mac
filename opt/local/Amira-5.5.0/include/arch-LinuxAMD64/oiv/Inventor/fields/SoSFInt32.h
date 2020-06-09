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


#ifndef  _SO_SF_INT32_
#define  _SO_SF_INT32_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFInt32 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a int32_t integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a single long (32-bit) integer.
 *   
 *   SoSFInt32s are written to file as an integer in decimal, hexadecimal (beginning
 *   with '0x') or octal (beginning with '0') format.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFInt32,
 *    SoSFUInt32
 * 
 * 
 */ 

class INVENTOR_API SoSFInt32 : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFInt32, int32_t, int32_t);

 SoINTERNAL public:
#ifndef IV_STRICT
#if (_MIPS_SZLONG == 32)
  //
  //  If the system long has exactly 32 bits, support methods that have "long" 
  //  in the argument list.
  //
  long  operator =(long newValue)                               // System long
  { setValue((int32_t)newValue); return (newValue); }
  void  setValue(long newValue)                                 // System long
    { setValue((int32_t)newValue); }
#endif
#endif

  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_INT32_ */

