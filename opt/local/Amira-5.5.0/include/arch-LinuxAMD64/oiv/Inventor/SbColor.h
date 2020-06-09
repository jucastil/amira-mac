/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SB_COLOR_H_
#define  _SB_COLOR_H_

#include <Inventor/SbLinear.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbColor
//
//  3D vector used to represent an RGB color. Each component of the vector is 
// a floating-point number between 0.0 and 1.0 .
//
//////////////////////////////////////////////////////////////////////////////

class SbColor;

/**
 * Color vector class.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION
 *   This class is used to represent an RGB color. Each component of the vector is a
 *   floating-point number between 0.0 and 1.0. There are routines to convert back
 *   and forth between RGB and HSV.
 * 
 * @SEE_ALSO
 *    SbVec3f
 * 
 * [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,3}]
 */ 

class INVENTORBASE_API SbColor : public SbVec3f {
 public:
  /**
   * Default constructor.  The color value is not initialized.
   */
  SbColor();

  /**
   * Constructor that takes a vector value.
   */
  SbColor(const SbVec3f vec3f) 
    { setValue(vec3f.getValue()); }

  /**
   * Constructor that takes an array of 3 floats.
   */
  SbColor(const float rgb[3])
    { setValue(rgb); }

  /**
   * Constructor that takes 3 floats.
   */
  SbColor(float r, float g, float b)
    { setValue(r, g, b); }

  //
  // HSV routines. Those are 3 floats containing the Hue, Saturation and
  // Value (same as brightness) of the color.
  //

  /**
   * Sets value of color vector from 3 HSV (Hue, Saturation, and Value) components.
   * Value is the same as brightness of the color.
   */
  SbColor &   setHSVValue(float h, float s, float v);

  /**
   * Sets value of color vector from array of 3 HSV components
   */
  SbColor &   setHSVValue(const float hsv[3])
    { return setHSVValue(hsv[0], hsv[1], hsv[2]); }

  /**
   * Returns 3 individual HSV components
   */
  void        getHSVValue(float &h, float &s, float &v) const;

  /**
   * Returns an array of 3 HSV components
   */
  void        getHSVValue(float hsv[3]) const
    { getHSVValue(hsv[0], hsv[1], hsv[2]); }
    
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
   * RGBA component values range from 0 to 0xFF (255). The returned transparency value
   * is a floating point value between 0.0 (opaque) and 1.0 (completely transparent).
   * It is derived from the alpha component of the RGBA color.
   */
  SbColor &setPackedValue(uint32_t orderedRGBA, float& transparency);

  /**
   * Returns an RGBA packed color value, derived from the color vector and the passed
   * transparency value. The alpha component is set to (1.0 - transparency) * 255,
   * resulting in a hex value between 0 and 0xFF. If transparency not specified,
   * alpha is set to 0xFF (opaque).
   */
  uint32_t   getPackedValue(float transparency = 0.0) const;
  uint32_t   getPackedValueInternal(float transparency = 0.0) const;

};

#endif /* _SB_COLOR_H_ */


