/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Nov 1999)
**=======================================================================*/

  
#ifndef  _SO_PATTERN_ELEMENT_
#define  _SO_PATTERN_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/nodes/SoPattern.h>

/**
* @VSGEXT Stores current pattern value.
*
* @ingroup elements
*
*   @DESCRIPTION
*
*   @SEE_ALSO
*   SoPattern
*/

SoEXTENDER_Documented class INVENTOR_API SoPatternElement : public SoReplacedElement {
  SO_ELEMENT_HEADER( SoPatternElement );

 public:
  /** Initializes element */
  virtual void init( SoState* state );

  /**
   * Sets the current pattern attributes in the state
   */
  static void set(SoState* state, SoNode *node, SbString category, SbString name);

  /**
   * Gets the current pattern attributes in the state
   * [OIV-WRAPPER-ARG IN,OUT,OUT,OUT&ARRAY{128}]
   */
  static void get(SoState* state, SbString& category, SbString& name, unsigned char*& pattern);

  /** Push copies the values from the previous element */
  virtual void  push(SoState *state);

  /** Returns TRUE if the attributes of pattern  match in both elements */
  virtual SbBool matches(const SoElement *elt) const;

  /** Create and return a copy of this element */
  virtual SoElement *copyMatchInfo() const;

  /**
   * Default values
   * [OIV-WRAPPER-ARG OUT,OUT,OUT&ARRAY{128}]
   */
  static void getDefault(SbString& category, SbString& name, unsigned char*& pattern);

 SoINTERNAL public:
  // Initializes the SoPattern class
  static void initClass();
  static void exitClass();

 protected:
  SbString m_category;
  SbString m_name;
  unsigned char* m_pattern;

  virtual void setElt( SbString category, SbString name, unsigned char* pattern );

  virtual ~SoPatternElement() ;
};

#endif // _SO_PATTERN_ELEMENT_
