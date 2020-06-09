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


#ifndef  _SO_SF_UINT32_
#define  _SO_SF_UINT32_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFUInt32 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an unsigned int32_t integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-value field containing an unsigned 32-bit integer, representing a
 *   number from 0 to 4,294,967,295.
 *   
 *   SoSFUInt32s are written to file as a single uint32_t (32-bit) integer in decimal,
 *   hexadecimal or octal format.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFUInt32
 * 
 * 
 */ 

class INVENTOR_API SoSFUInt32 : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFUInt32, uint32_t, uint32_t);

 SoINTERNAL public:
#ifndef IV_STRICT
#if (_MIPS_SZLONG == 32)
  //
  //  If the system long has exactly 32 bits, support methods that have "long" 
  //  in the argument list.
  //
  unsigned long  operator =(unsigned long newValue)             // System long
  { setValue((uint32_t)newValue); return (newValue); }
  //
  //  Problems in SoFieldConverters.c++  (more than one instance matches ...)
  //    void  setValue(unsigned long newValue)                      // System long
  //              { setValue((uint32_t)newValue); }
#endif
#endif

  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_UINT32_ */

