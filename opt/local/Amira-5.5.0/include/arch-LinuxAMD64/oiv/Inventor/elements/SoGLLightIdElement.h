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


#ifndef  _SO_GL_LIGHT_ID_ELEMENT
#define  _SO_GL_LIGHT_ID_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/elements/SoInt32Element.h>

/**
*  Stores the id of the current light.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the id of the current light. The first light
*   active in a scene has id 0, the next has 1, and so on. This
*   element can be used to determine how many lights are currently
*   active. The initial value of this element is -1 to indicate that
*   there are no lights active.
*
*   Note that even though the effects of this element accumulate (each
*   light source increments the id), it is derived from
*   SoInt32Element. This is because each call to increment()
*   effectively does a "get" of the current top instance, so caching
*   knows about the dependency of each instance on the previous one.
*
*   @SEE_ALSO
*   SoDirectionalLight, SoPointLight, SoSpotLight,
*   SoVRMLDirectionalLight, SoVRMLPointLight, SoVRMLSpotLight
*/

SoEXTENDER_Documented class INVENTOR_API SoGLLightIdElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoGLLightIdElement);

 public:
  /**
  *  Increments the current light id. This should be called when a
  *  light source becomes active. This returns the new id, or -1 if
  *  the maximum number of GL light sources has been exceeded.
  *  Otherwise, enables light source.
  */
  static int          increment(SoState *state);

#ifndef IV_STRICT
  /**
  *  Increments the current light id. This should be called when a
  *  light source becomes active. This returns the new id, or -1 if
  *  the maximum number of GL light sources has been exceeded.
  *  Otherwise, enables light source.
  */
  static int          increment(SoState *state, SoNode *)
    { return increment(state); }
#endif

  /**
  *  Returns current light id from the state.
  */
  static int          get(SoState *state)
    { return (int)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default light id.
  */
  static int          getDefault()                    { return -1; }

  /**
  *  Returns the maximum number of concurrent light sources
  *  supported by GL implementation.
  */
  static int          getMaxGLSources();

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoGLLightIdElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoGLLightIdElement();

 private:
  /** Disable light n in fixed pipeline shader */
  void disableShaderLight(SoState *state, int num);

  // Holds max number of GL sources
  static int         maxGLSources;
};

#endif /* _SO_GL_LIGHT_ID_ELEMENT */
