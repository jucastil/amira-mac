/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SF_COLORRGBA_
#define  _SO_SF_COLORRGBA_

#include <Inventor/fields/SoSubField.h>
#include <Inventor/SbColorRGBA.h>

//////////////////////////////////////////////////////////////////////////////
//
//  SoSFColorRGBA subclass of SoSField.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Field containing an RGBA color.
 * 
 * @ingroup fields
 * 
 * @DESCRIPTION
 *   A single-value field containing an SbColorRGBA. Values are set in RGBA
 *   (red, green, blue, alpha) color space.
 *   
 *   SoSFColorRGBAs are written to file as an RGBA quadruple of floating point
 *   numbers in standard scientific notation, in the range 0.0 to 1.0.
 * 
 * @SEE_ALSO
 *    SoField,
 *    SoSField,
 *    SoMFColorRGBA,
 *    SbColorRGBA
 * 
 * 
 */ 

class INVENTOR_API SoSFColorRGBA : public SoSField {

  // Use standard field stuff
  SO_SFIELD_HEADER(SoSFColorRGBA, SbColorRGBA, const SbColorRGBA &);

 public:
  //
  // Some additional convenience functions
  //

  /**
   * Convenience method for setting the value.
   */
  void setValue(const SbVec4f &vec);

  /**
   * Convenience method for setting the value.
   */
  void setValue(float r, float g, float b, float a);

  /**
   * Convenience method for setting the value.
   */
  void setValue(const float rgba[4]);

  /**
   * Convenience method for setting the value.
   */
  void setHSVAValue(float h, float s, float v, float a);

  /**
   * Convenience method for setting the value.
   */
  void setHSVAValue(const float hsva[4]);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

};

#endif /* _SO_SF_COLORRGBA_ */

