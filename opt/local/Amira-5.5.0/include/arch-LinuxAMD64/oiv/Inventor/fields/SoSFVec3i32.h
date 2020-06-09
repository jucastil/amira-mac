/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_SF_VEC3I32_
#define  _SO_SF_VEC3I32_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

/**
 * @VSGEXT Field containing a three-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   Field containing a three-dimensional vector, each component being an integer.
 *   
 *   SoSFVec3i32s are written to file as three integer values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec3i32
 * 
 * 
 */ 

class INVENTOR_API SoSFVec3i32 : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec3i32, SbVec3i32, const SbVec3i32 &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given values.
   */
  void        setValue(int32_t x, int32_t y, int32_t z);

  /**
   * Sets the field to the given values.
   */
  void        setValue(const int32_t xyz[3]);

  /**
   * Convenience method that allows you to specify a field value using a single
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec3f &vec3f);
  
  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. The specified value is converted to int value, then stored.
   */
  void setValue(const SbVec3d &vec3d);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC3I32_ */
