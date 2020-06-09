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


#ifndef  _SO_GL_CLIP_PLANE_ELEMENT
#define  _SO_GL_CLIP_PLANE_ELEMENT

#include <Inventor/elements/SoClipPlaneElement.h>

/**
*  Adds a clipping plane to the set currently in GL.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element adds a clipping plane to the set currently in GL.
*   Overrides the virtual methods on SoClipPlaneElement to send the
*   clipping plane to GL.
* 
*   Note that this class relies on SoClipPlaneElement to store the
*   plane in the instance.
* 
*   @SEE_ALSO
*   SoClipPlaneElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLClipPlaneElement : public SoClipPlaneElement {

  SO_ELEMENT_HEADER(SoGLClipPlaneElement);

 public:
  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Returns the maximum number of concurrent clipping planes
  *  supported by GL implementation.
  */
  static int          getMaxGLPlanes();

 SoINTERNAL public:
  // Initializes the SoGLClipPlaneElement class
  static void         initClass();
  static void         exitClass();

  /**
   * Enable or disable OpenGL clip planes
   */
  static void enable(SoState* state, SbBool activate);

 protected:
  // Adds the clipping plane to an instance. Has GL side effects.
  virtual void        addToElt(const SbPlane &plane,
                               const SbMatrix &modelMatrix);

  virtual ~SoGLClipPlaneElement();

 private:
  // Holds max number of GL clip planes
#ifdef _WIN32
  static int         maxGLPlanes;
#else
  static int          maxGLPlanes;
#endif

  // Sends clipping plane in element to GL
  void                send();
};

#endif /* _SO_GL_CLIP_PLANE_ELEMENT */
