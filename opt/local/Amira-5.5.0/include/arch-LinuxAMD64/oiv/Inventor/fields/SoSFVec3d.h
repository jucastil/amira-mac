/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_VEC3D_
#define  _SO_SF_VEC3D_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFVec3d subclass of SoSField.
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
 *   SoSFVec3ds are written to file as three doubleing point values separated by
 *   whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFVec3d
 * 
 * 
 */ 

class INVENTOR_API SoSFVec3d : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFVec3d, SbVec3d, const SbVec3d &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the field to the given value.
   */
  void        setValue(double x, double y, double z);

  /**
   * Sets the field to the given value.
   */
  void        setValue(const double xyz[3]);


 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

};

#endif /* _SO_SF_VEC3D_ */

