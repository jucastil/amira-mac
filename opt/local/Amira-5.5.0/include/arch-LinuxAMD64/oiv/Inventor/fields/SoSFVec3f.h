/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_VEC3F_
#define  _SO_SF_VEC3F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec3f subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing a three-dimensional vector.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   Field containing a three-dimensional vector.
 *   
 *   SoSFVec3fs are written to file as three floating point values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec3f
 * 
 * 
 */ 

class INVENTOR_API SoSFVec3f : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec3f, SbVec3f, const SbVec3f &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void        setValue(float x, float y, float z);

  /**
   * Sets the field to the given value.
   */
  void        setValue(const float xyz[3]);

  /**
   * Convenience method that allows you to specify a field value using a double
   * precision variable. Note that Open Inventor fields still store only single
   * precision values, not double precision values. The specified value is converted
   * to single precision, then stored.
   */
  void            setValue(const SbVec3d &vec3d);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

};

#endif /* _SO_SF_VEC3F_ */

