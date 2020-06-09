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


#ifndef  _SO_SF_SHORT_
#define  _SO_SF_SHORT_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFShort subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a short integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a short (16-bit) integer.
 *   
 *   SoSFShorts are written to file as a single short integer value, represented as
 *   decimal, hexadecimal (beginning with '0x') or octal (beginning with '0') value.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFShort,
 *    SoSFUShort,
 *    SoSFInt32
 * 
 * 
 */ 

class INVENTOR_API SoSFShort : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFShort, short, short);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_SHORT_ */

