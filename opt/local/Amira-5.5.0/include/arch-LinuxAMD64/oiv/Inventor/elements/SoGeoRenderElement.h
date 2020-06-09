/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien SALLANNE (Apr 2009)
**=======================================================================*/

#ifndef  _SO_GEO_RENDER_ELEMENT
#define  _SO_GEO_RENDER_ELEMENT

#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/projection/SbProj4Projection.h>

/**
* @VSGEXT Stores the current render projection
*
* @ingroup elements
*
*   @DESCRIPTION
*
*
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoGeoRenderElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoGeoRenderElement);

 public:
  /**
  *  Sets the current render mode in the state.
  */
  static void         set(SoState *state, SbProj4Projection::Projection renderProjection)
    { SoInt32Element::set(getClassTypeId(), getClassStackIndex(), state, (int32_t)renderProjection); }

#ifndef IV_STRICT
  /**
  *  Sets the current render mode in the state.
  */
  static void         set(SoState *state, SoNode *, SbProj4Projection::Projection renderProjection)
    { set(state, renderProjection); }
#endif

  /**
  *  Returns current render mode in the state.
  */
  static SbProj4Projection::Projection    get(SoState *state)
    { return (SbProj4Projection::Projection)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default render mode.
  */
  static SbProj4Projection::Projection    getDefault()   { return SbProj4Projection::GEOCENTRIC_PROJ; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoGeoRenderElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);
 protected:
  virtual ~SoGeoRenderElement();
};

#endif /* _SO_GEO_RENDER_ELEMENT */
