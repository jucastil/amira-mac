/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_SF_VEC4I32_
#define  _SO_SF_VEC4I32_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

/**
 * @VSGEXT Field containing a homogeneous four-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   Field containing a homogeneous four-dimensional vector, each component being an integer.
 *   
 *   SoSFVec4i32s are written to file as four integer values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec4i32
 * 
 * 
 */ 

class INVENTOR_API SoSFVec4i32 : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec4i32, SbVec4i32, const SbVec4i32 &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given values.
   */
  void        setValue(int32_t x, int32_t y, int32_t z, int32_t w);

  /**
   * Sets the field to the given values.
   */
  void        setValue(const int32_t xyzw[4]);

  /**
   * Convenience method that allows you to specify a field value using a single
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec4f &vec4f);
  
  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec4d &vec4d);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC4I32_ */
