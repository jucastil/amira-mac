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


#ifndef  _SO_SF_USHORT_
#define  _SO_SF_USHORT_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFUShort subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an unsigned short integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-value field containing a short (16-bit) integer.
 *   
 *   SoSFUShorts are written to file in decimal, hexadecimal (beginning with '0x') or
 *   octal (beginning with '0') values.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFUShort
 * 
 * 
 */ 

class INVENTOR_API SoSFUShort : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFUShort, unsigned short, unsigned short);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_USHORT_ */

