/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Feb 2008)
**=======================================================================*/


#ifndef  _SO_SF_UBYTE_
#define  _SO_SF_UBYTE_

#include <Inventor/fields/SoSubField.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFByte subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a uint8_t integer.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a single unsigned byte (8-bit) integer.
 *   
 *   SoSFUBytes are written to file as an integer in decimal, hexadecimal (beginning
 *   with '0x') or octal (beginning with '0') format.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFUByte
 * 
 * 
 */ 

class INVENTOR_API SoSFUByte : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFUByte, uint8_t, uint8_t);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif // !_SO_SF_UBYTE
