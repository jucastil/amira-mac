/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SB_COLORRGBA_H_
#define  _SB_COLORRGBA_H_

#include <Inventor/SbLinear.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbColorRGBA
//
//  4D vector used to represent an RGBA color. Each component of the vector is 
//  a floating-point number between 0.0 and 1.0 .
//
//////////////////////////////////////////////////////////////////////////////

class SbColorRGBA;

/**
 * ColorRGBA vector class.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   This class is used to represent an RGBA color. Each component of the vector is a
 *   floating-point number between 0.0 and 1.0.  RGBA stands for red, green, blue and
 *   alpha.  Alpha is the inverse of "transparency", in other words 0 is fully
 *   transparent and 1 is fully opaque.
 *
 *   Values may be specified in the HSV (hue, saturation and value) color space, but
 *   are stored internally as RGBA values.
 *
 * @SEE_ALSO
 *    SbVec4f
 * 
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
 */ 

class INVENTORBASE_API SbColorRGBA : public SbVec4f {
 public:
  /**
   * Default constructor.  The color value is not initialized.
   */
  SbColorRGBA();

  /**
   * Constructor that takes an RGBA vector value.
   */
  SbColorRGBA(const SbVec4f vec4f) 
    { setValue(vec4f.getValue()); }

  /**
   * Constructor that takes an RGBA value as an array of 4 floats.
   */
  SbColorRGBA(const float rgba[4])
    { setValue(rgba); }

  /**
   * Constructor that takes an RGBA value as 4 floats.
   */
  SbColorRGBA(float r, float g, float b, float a)
    { setValue(r, g, b, a); }

  //
  // RGBA Packed integer color routines. The color format expressed in 
  // hexadecimal is 0xrrggbbaa, where
  //      aa  is the alpha value
  //      bb  is the blue value
  //      gg  is the green value
  //      rr  is the red value
  // RGBA component values range from 0 to 0xFF (255).
  //
  
  /**
   * Sets value of color vector from an RGBA packed color value. The packed color
   * format expressed in hexadecimal is 0xrrggbbaa, where
   * 
   * - rr is the red value
   * 
   * - gg is the green value
   * 
   * - bb is the blue value
   * 
   * - aa is the alpha value
   * 
   * RGBA component values range from 0 to 0xFF (255). 
   */
  SbColorRGBA &setPackedValue(uint32_t orderedRGBA);

  /**
   * Returns an RGBA packed color value, derived from the color vector.
   */
  uint32_t   getPackedValue() const;

  /**
   * Sets value of color vector from an HSV (Hue, Saturation, and Value)
   * plus Alpha color value.  All components must be in the range 0 to 1.
   * 
   * Value is the same as brightness of the color.
   */
  SbColorRGBA &   setHSVAValue(float h, float s, float v, float a);

  /**
   * Sets value of color vector from an HSV (Hue, Saturation, and Value)
   * plus Alpha color value.  All components must be in the range 0 to 1.
   */
  SbColorRGBA &   setHSVAValue(const float hsva[4])
    { return setHSVAValue(hsva[0], hsva[1], hsva[2], hsva[3]); }

  /**
   * Returns color value in the HSV (hue, saturation and value) plus
   * Alpha color space.
   */
  void getHSVAValue(float &h, float &s, float &v, float& a) const;

  /**
   * Returns color value in the HSV (hue, saturation and value) plus
   * Alpha color space.
   */
  void getHSVAValue(float hsva[4]) const
    { getHSVAValue(hsva[0], hsva[1], hsva[2], hsva[3]); }
};

#endif /* _SB_COLORRGBA_H_ */


