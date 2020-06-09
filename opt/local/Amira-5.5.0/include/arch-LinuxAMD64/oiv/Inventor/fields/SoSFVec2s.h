/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_SF_VEC2S_
#define  _SO_SF_VEC2S_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec2s subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a two-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoSFVec2ss are written to file as a pair of short values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec2f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec2s : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec2s, SbVec2s, const SbVec2s &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void                setValue(short x, short y);

  /**
   * Sets the field to the given value.
   */
  void                setValue(const short xy[2]);

  /**
   * Convenience method that allows you to specify a field value using a float
   * variable. The specified value is converted short precision, then stored.
   */
  void            setValue(const SbVec2f &vec2f);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC2S_ */

