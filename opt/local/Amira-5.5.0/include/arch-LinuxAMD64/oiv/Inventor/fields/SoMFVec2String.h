/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Oct 2006)
**=======================================================================*/


#ifndef  _SO_MF_VEC2STRING_
#define  _SO_MF_VEC2STRING_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbVec2String.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoMFVec2String subclass of SoMField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Multiple-value field containing any number of two-dimensional string vectors.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A multiple-value field that contains any number of two-dimensional string vectors.
 *   
 *   SoMFVec2String are written to file as one or more pairs of SbString point values
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

class INVENTOR_API SoMFVec2String : public SoMField {

  // Use standard field stuff
  SO_MFIELD_HEADER(SoMFVec2String, SbVec2String, const SbVec2String &);
  SO_MFIELD_SETVALUESPOINTER_HEADER(SbVec2String);
  
public:
  //
  // Some additional convenience functions:
  //
  
  /**
   * Sets one value from 2 SbString.
   */
  void set1Value(int index, SbString s1, SbString s2);
  
  /**
   * Sets one vector value from an array of 2 SbString.
   */
  void set1Value(int index, const SbString ss[2]);
  
  /**
   * Sets to one value from 2 SbString.
   */
  void setValue(SbString s1, SbString s2);
  /**
   * Sets to one vector value from array of 2 SbString
   */
  void setValue(const SbString ss[2]);

SoINTERNAL public:
  static void   initClass();
  static void   exitClass();
};

#endif /* _SO_MF_VEC2STRING_ */
