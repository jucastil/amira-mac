/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (May 2002)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_GL_SHADOW_STYLE_ELEMENT_
#define  _SO_GL_SHADOW_STYLE_ELEMENT_

#include <Inventor/elements/SoGLDrawStyleElement.h>

class SoShadowStyle;
class SoGroup;

/**
* @VSGEXT Stores the current shadow style.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current shadow style.
*
*   @SEE_ALSO
*   SoShadowStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoGLShadowStyleElement : public SoGLDrawStyleElement
{
  SO_ELEMENT_HEADER(SoGLShadowStyleElement) ;

 public:
  enum ShadowStyle {
    NO_SHADOWING                  = 0x00,
    CASTS_SHADOW                  = 0x01,
    SHADOWED                      = 0x02,
    CASTS_SHADOW_AND_SHADOWED     = 0x03
  } ;

  // Initializes element
  virtual void init(SoState *state) ;

  // Override push() method to remember previous element's state so
  // we can sometimes generate more efficient GL calls
  virtual void push(SoState *state) ;

  // Override pop() method so side effects can occur in GL
  virtual void pop(SoState *state, const SoElement *prevTopElement) ;

  // Sets the current attributes (style) in the state
  static void set(SoState *state, SoShadowStyle *shadowStyle, ShadowStyle style) ;

  // Sets the current attributes (pass number) in the state
  static void setPassNumber(SoState *state, int passNumber) ;

  // Default values
  static void getDefault(ShadowStyle &shadowStyle, int &passNumber) ;

  // Returns TRUE if the attributes match in both elements
  SbBool matches(const SoElement *elt) const ;

  // Create and return a copy of this element
  SoElement *copyMatchInfo() const ;

  // get the pass number
  int getPassNumber(){return m_passNumber;}

  // Sets the current attributes (enable check lighting) in the state
  static void setCheckLightingEnabled(SoState *state, bool enable) ;

  // says wether can check the lighting
  bool enableCheckLighting(){return m_enableCheckLighting;}

 SoINTERNAL public:
  // Initializes the SoGLShadowStyleElement class
  static void initClass() ;
  static void exitClass() ;

  /** Return true if shadow are active */
  static bool isShadowed(SoState* state);

 protected:
  virtual ~SoGLShadowStyleElement() ;

  virtual void setElt(SoState *state, ShadowStyle style) ;
  virtual void setElt(SoState *state, int passNumber) ;
  virtual void setElt(SoState *state, bool enableCheckLighting);
  virtual void setElt(int32_t style) { SoGLDrawStyleElement::setElt(style); }; // no warning


 private:
  void sendOiv7(SoState *state);

  // We save the state to figure out if the hints were
  // copied from a parent element; if they were, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *copiedFromParent ;

  // Send OpenGL calls
  void send(SoState *state) ;

  ShadowStyle    m_style ;

  //If set to true , can disable/enable GL_LIGHTING
  bool m_enableCheckLighting;

  int            m_passNumber ;   // Shadow pass number :
  // 0=No shadow, 1= depth map computation
  // 2 or 3 unshadowed fragment computation.
} ;

#endif /* _SO_GL_SHADOW_STYLE_ELEMENT_ */
