/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_SF_VEC2I32_
#define  _SO_SF_VEC2I32_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec2i32 subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a two-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   SoSFVec2i32s are written to file as a pair of int values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec2f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec2i32 : public SoSField {
  
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec2i32, SbVec2i32, const SbVec2i32 &);
  
 public:

  //
  // Some additional convenience functions:
  //
  
  /**
   * Sets the field to the given value.
   */
  void setValue(int32_t x, int32_t y);
  
  /**
   * Sets the field to the given value.
   */
  void setValue(const int32_t xy[2]);
  
  /**
   * Convenience method that allows you to specify a field value using a single
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec2f &vec2f);
  
  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec2d &vec2d);
  
 SoINTERNAL public:

  static void initClass();
  static void exitClass();
};

#endif /* _SO_SF_VEC2I32_ */

