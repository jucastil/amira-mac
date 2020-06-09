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


#ifndef  _SO_LIGHT_ATTENUATION_ELEMENT
#define  _SO_LIGHT_ATTENUATION_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/SoPreferences.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
* Stores the light attenuation(s) of the current
*   environment.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the light attenuation(s) of the current
*   environment. This used to set up subsequent light sources. The
*   attenuation is stored as an SbVec3f, where the first component of
*   the vector is the quadratic term of the attenuation, the second is
*   the linear term, and the third is the constant.
* 
*   @SEE_ALSO
*   SoEnvironment
*/

SoEXTENDER_Documented class INVENTOR_API SoLightAttenuationElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoLightAttenuationElement);

 public:
  /**
  *  Sets the current light attenuation(s).
  */
  static void         set(SoState *state, SoNode *node,
                          const SbVec3f &attenuation);

  /**
  *  Returns the current light attenuation from the state.
  */
  static const SbVec3f & get(SoState *state);

  /**
  *  Returns the default light attenuation.
  */
  static SbVec3f      getDefault()            { return SoPreferences::getVec3f ("OIV_LIGHT_ATTENUATION", SbVec3f(0., 0., 1.)); }

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Returns TRUE if the attenuations match in both elements.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoLightAttenuationElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbVec3f             attenuation;

  virtual ~SoLightAttenuationElement();
};

#endif /* _SO_LIGHT_ATTENUATION_ELEMENT */
