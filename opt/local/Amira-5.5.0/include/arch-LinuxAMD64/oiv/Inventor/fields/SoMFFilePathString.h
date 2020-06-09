/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2006)
**=======================================================================*/


#ifndef  _SO_MF_FILE_PATH_STRING_
#define  _SO_MF_FILE_PATH_STRING_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoMFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFFilePathString subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Multiple-value field containing any number of file path strings.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of file path strings.
 *   
 *   SoMFFilePathString is equivalent to SoMFString.
 *   Using this type of field provides a way for Open Inventor to do conversion and
 *   filtering operations on distributed heterogeneous systems.
 * 
 * 
 */ 

class INVENTOR_API SoMFFilePathString : public SoMFString {

  // Use standard field stuff
  SO_MFIELD_DERIVED_HEADER(SoMFFilePathString, SbString, const SbString &);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  private:
  // store some path info about the field
  SbStringList directories_stack;
};

#endif /* _SO_MF_FILE_PATH_STRING_ */

