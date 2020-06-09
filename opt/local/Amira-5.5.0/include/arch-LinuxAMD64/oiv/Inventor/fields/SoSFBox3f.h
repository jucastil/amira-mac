/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : B. GRANGE (Aug 2006)
**=======================================================================*/

#ifndef  _SO_SF_BOX3F_
#define  _SO_SF_BOX3F_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbLinear.h>

#include <Inventor/SbBox.h> // To Suppress in the VERSION

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFBox3f subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////


/**
 * @VSGEXT Field containing a three-dimensional box.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   This field defines a three-dimensional box.
 *   
 *   SoSFBox3f fields are written to file as 6 floats separated by whitespace.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField
 * 
 * 
 */ 

class INVENTOR_API SoSFBox3f : public SoSField {
  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFBox3f, SbBox3f, const SbBox3f &);

 public:
  //
  // Some additional convenience functions:
  //

  /**
   * Sets the box dimensions.
   */
  void                setValue(float xmin, float ymin, float zmin,
                               float xmax, float ymax, float zmax);

  /**
   * Sets the box dimensions.
   */
  void                setValue(const SbVec3f &_min, const SbVec3f &_max);


 SoINTERNAL public:
  static void initClass();
  static void exitClass();
};

#endif

