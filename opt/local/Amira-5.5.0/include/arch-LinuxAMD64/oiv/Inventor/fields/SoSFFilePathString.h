/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2006)
**=======================================================================*/


#ifndef  _SO_SF_FILE_PATH_STRING_
#define  _SO_SF_FILE_PATH_STRING_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoSFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFFilePathString subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/** 
 * @VSGEXT Field containing a file path string.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A field containing a file path string (sequence of characters).
 *   
 *   SoSFFilePathString is equivalent to SoSFString.
 *   Using this type of field provides a way for Open Inventor to do conversion and
 *   filtering operations on distributed heterogeneous systems.
 *
 * @SEE_ALSO
 *    SbString,
 *    SoField,
 *    SoSField,
 *    SoSFString
 *    SoMFString
 *    SoMFFilePathString
 * 
 * 
 */ 

class INVENTOR_API SoSFFilePathString : public SoSFString {
  // Use standard field stuff
  SO_SFIELD_DERIVED_HEADER(SoSFFilePathString, SbString, const SbString &);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // do some filtering on filePath value before read/write
  static void cleanupValue(SbString &filePath);

  private:
  // store some path info about the field
  SbStringList directories_stack;
};

#endif /* _SO_SF_FILE_PATH_STRING_ */

