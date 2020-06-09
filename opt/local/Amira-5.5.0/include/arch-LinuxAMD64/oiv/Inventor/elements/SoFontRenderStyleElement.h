/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (May 2003)
**=======================================================================*/

#ifndef  _SO_FONT_RENDERSTYLE_ELEMENT
#define  _SO_FONT_RENDERSTYLE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>
/**
* @VSGEXT Stores the current font render style.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current font render style.
*   @SEE_ALSO
*   SoFont
*/

SoEXTENDER_Documented class INVENTOR_API SoFontRenderStyleElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoFontRenderStyleElement);

 public:
/**
*  These are the available render styles.
*/
  enum RenderStyle {
    POLYGON,
    TEXTURE,
    TEXTURE_DELAYED,
    POLYGON_AND_OUTLINE
  };

  /**
  *  Sets the current render style in the state.
  */
  static void         set(SoState *state, RenderStyle style);

#ifndef IV_STRICT
  /**
  *  Sets the current render style in the state.
  */
  static void         set(SoState *state, SoNode *, RenderStyle style) { set(state, style); }
#endif

  /**
  *  Returns current render style from the state.
  */
  static RenderStyle      get(SoState *state) { return (RenderStyle)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default render style.
  */
  static RenderStyle     getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void           print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoDrawStyleElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoFontRenderStyleElement();

private:
  static RenderStyle s_defaultRenderStyle;
  static bool s_isSet;
};

#endif /* _SO_FONT_RENDERSTYLE_ELEMENT */
