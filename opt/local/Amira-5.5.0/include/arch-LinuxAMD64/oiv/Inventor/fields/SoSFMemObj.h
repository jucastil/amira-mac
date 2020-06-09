/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2007)
**=======================================================================*/



#ifndef  _SO_SF_MEMOBJ_
#define  _SO_SF_MEMOBJ_

#include <Inventor/fields/SoSubField.h>

class SoMemoryObject;

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFMemObj subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a reference to a memory object.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a pointer to an SoMemoryObject memory object.
 *   
 *   SoSFMemObj are written to file as an integer in decimal, hexadecimal (beginning
 *   with '0x') or octal (beginning with '0') format.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMemoryObject
 * 
 * 
 */ 

class INVENTOR_API SoSFMemObj : public SoSField
{
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFMemObj, SoMemoryObject*, SoMemoryObject*);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_MEMOBJ_ */
