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


#ifndef  _SO_SF_COLOR_
#define  _SO_SF_COLOR_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColor.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFColor subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an RGB color.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-value field containing an SbColor. Values may be set in either RGB
 *   (red, green, blue) or HSV (hue, saturation, value) color spaces.
 *   
 *   SoSFColors are written to file as an RGB triple of floating point numbers in
 *   standard scientific notation, in the range 0.0 to 1.0.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFColor,
 *    SbColor
 * 
 * 
 */ 

class INVENTOR_API SoSFColor : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFColor, SbColor, const SbColor &);

 public:
  //
  // Some additional convenience functions
  //

  /**
   * Convenience method for setting the value.
   */
  void setValue(const SbVec3f &vec);

  /**
   * Convenience method for setting the value.
   */
  void setValue(float r, float g, float b);

  /**
   * Convenience method for setting the value.
   */
  void setHSVValue(float h, float s, float v);

  /**
   * Convenience method for setting the value.
   */
  void setValue(const float rgb[3]);

  /**
   * Convenience method for setting the value.
   */
  void setHSVValue(const float hsv[3]);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_COLOR_ */

