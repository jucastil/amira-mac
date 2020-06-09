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


#ifndef  _SO_LINE_PATTERN_ELEMENT
#define  _SO_LINE_PATTERN_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>

/**
*  Stores the current line stipple pattern.
* 
* @ingroup elements
*
*   @DESCRIPTION
*   This slement stores the current line stipple pattern.
* 
*   @SEE_ALSO
*   SoDrawStyle,
*   SoVRMLLineProperties
*/

SoEXTENDER_Documented class INVENTOR_API SoLinePatternElement : public SoReplacedElement {
  
  SO_ELEMENT_HEADER(SoLinePatternElement);
  
 public:
  /**
  *  Sets the current line pattern in the state.
  */
  static void set(SoState *state, 
                  u_short pattern, int factor = 1);
  
#ifndef IV_STRICT
  /**
  *  Sets the current line pattern in the state.
  */
  static void set(SoState *state, SoNode *, 
                  u_short pattern, int factor = 1)
    { set(state, pattern, factor); }
#endif

  /**
  *  Returns current line pattern from the state. The current line
  *  pattern scale factor from the state is returned in factor.
  */
  static u_short get(SoState *state, int &factor);
  
  /**
  *  Deprecated: Returns the default line pattern.
  */
  static u_short getDefault()
    { return getDefaultPattern(); }
  
  /**
  *  Returns the default line pattern.
  */
  static u_short getDefaultPattern()
    { return 0xFFFF; }
  
  /**
  *  Returns the default line pattern scale factor.
  *  A multiplier for each bit in the line pattern.
  *  If factor is 3, for example, each bit in the
  *  pattern will be used three times before the
  *  next bit in the pattern is used. The factor
  *  parameter is clamped to the range [1, 256] and
  *  defaults to 1.
  */
  static int getDefaultScaleFactor()
    { return 1; }
  
  /**
  *  Returns TRUE if the line pattern and line
  *  pattern scale factor match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement     *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;
  
 SoINTERNAL public:
  // Initializes the SoLinePatternElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);
  
 protected:
  int m_pattern, m_factor;

  virtual ~SoLinePatternElement();
  virtual void setElt(u_short pattern, int factor);
};

#endif /* _SO_LINE_PATTERN_ELEMENT */
