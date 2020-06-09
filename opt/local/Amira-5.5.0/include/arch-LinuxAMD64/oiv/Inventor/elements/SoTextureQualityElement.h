/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_QUALITY_ELEMENT
#define  _SO_TEXTURE_QUALITY_ELEMENT

#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/SoPreferences.h>

/**
*  Stores the current texture quality.
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture quality.
*
*   @SEE_ALSO
*   SoShapeHints
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureQualityElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoTextureQualityElement);

 public:
  /**
  *  Sets the current texture quality in the state.
  */
  static void         set(SoState *state, float qual)
  { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, qual); }

  /** Sets the current complexity in the state. */
  virtual void setElt(float value);

  /**
  *  Returns current texture quality from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default texture quality.
  */
  static float  getDefault()                    { return SoPreferences::getFloat ("OIV_TEXTURE_QUALITY", 0.5); }

  /** Returns TRUE if element has been set in set. */
  static bool isSetInState(SoState *state);

  /**
  *  Comparison based on value of floats
  */
  virtual SbBool matches(const SoElement *elt) const;

 SoINTERNAL public:
  // Initializes the SoTextureQualityElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Copy method, takes care copying the data.
  virtual SoElement* copyMatchInfo() const;

 protected:
  virtual ~SoTextureQualityElement();

  bool m_isSetInState;
};

/**
*  Stores the current texture override.
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores a flag for each type of element which can be
*   overridden.  Nodes implement override by setting the appropriate
*   bit if their override flag is on, and ignoring overridden elements
*   if the corresponding bit in the state's SoTextureOverrideElement is set.
*
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureOverrideElement : public SoElement {

  SO_ELEMENT_HEADER(SoTextureOverrideElement);

  enum {
    TEXTURE_QUALITY = 0x1,
    TEXTURE_IMAGE   = 0x2
  };

 public:
  /**
  *  Comparison based on value of int32_ts.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Overrides push() method to copy values from next instance in
  *  the stack, and set up cache dependencies correctly.
  */
  virtual void        push(SoState *state);

  //
  // "get" methods for each element which can be overridden.
  //

  /**
  *  Returns TRUE iff SoTextureQualityElement is overridden.
  */
  static SbBool       getQualityOverride(SoState *state);

  /**
  *  Returns TRUE iff SoTextureImageElement is overridden.
  */
  static SbBool       getImageOverride(SoState *state);

  //
  // "set" methods for each element which can be overridden.
  //

  /**
  *  Sets override flag for SoTextureQualityElement.
  */
  static void         setQualityOverride(SoState *state,
                                         SbBool override);

  /**
  *  Sets override flag for SoTextureImageElement.
  */
  static void         setImageOverride(SoState *state,
                                       SbBool override);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoTextureOverrideElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  // Copy method, copies flags
  virtual SoElement   *copyMatchInfo() const;

 private:
  // Used by ::print method
  void pFlag(FILE *, const char *, int) const;

  uint32_t flags;
};

#endif /* _SO_TEXTURE_QUALITY_ELEMENT */
