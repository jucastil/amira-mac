/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2006)
**=======================================================================*/


#ifndef  _SO_MF_VEC2FILEPATHSTRING_
#define  _SO_MF_VEC2FILEPATHSTRING_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/fields/SoMFVec2String.h>
#include <Inventor/SbVec2String.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFVec2FilePathString subclass of SoMFVec2String.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of two-dimensional filePath string vectors.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of two-dimensional string vectors.
 *   
 *   SoMFVec2FilePathString are written to file as one or more pairs of SbString point values
 *   separated by whitespace. When more than one value is present, all of the values
 *   are enclosed in square brackets and separated by commas. When a string value 
 *   contains a white space it should be enclosed by double quote for example:
 *   
 *   <PRE>
 *    [ toto truc, "hello man" test ]
 *    </PRE>
 *    @H3 Using an Application-Supplied Array @h3
 *   
 * 
 * 
 */ 

class INVENTOR_API SoMFVec2FilePathString : public SoMFVec2String {

  // Use standard field stuff
  SO_MFIELD_DERIVED_HEADER(SoMFVec2FilePathString, SbVec2String, const SbVec2String &);

SoINTERNAL public:
  static void   initClass();
  static void   exitClass();
};

#endif /* _SO_MF_VEC2FILEPATHSTRING_ */
