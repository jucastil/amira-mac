/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_GL_SHADER_PROGRAM_ELEMENT_
#define  _SO_GL_SHADER_PROGRAM_ELEMENT_

#include <Inventor/elements/SoShaderProgramElement.h>

class SoGLShaderProgram ;
class SoShaderProgram ;

/**
* @VSGEXT Stores the current shader program.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current shader program.
*
*   @SEE_ALSO
*   SoShaderProgram
*/
SoEXTENDER_Documented class INVENTOR_API SoGLShaderProgramElement : public SoShaderProgramElement {

  SO_ELEMENT_HEADER(SoGLShaderProgramElement);

public:
  /**
  *  Sets the current shader program in the state.
  */
  static void set(SoState *state, SoNode *node);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Returns the maximum image texture unit.
  */
  static int getMaxTextureImageUnit(SoState*state=NULL);

  /**
   * Returns the maximum number of texture coordinates.
   */
  static int getMaxTextureCoords(SoState* state=NULL);

SoINTERNAL public:
  // Initializes the classes.
  static void initClass();
  static void exitClass();

  static SoGLShaderProgramElement * getCurrentElement(SoState *);

  /** Return true if shader was enabled before */
  static SbBool setShaderEnabled(SoState * state, SbBool value);

  /** Return the current shader element */
  static SoGLShaderProgramElement* pushShader(SoState *state);

  /** Set shaderElt as the new active shader only if internalShader is on the state
   * Used to hide internal shaders.
   */
  static void popShader(SoState *state, const SoGLShaderProgramElement* shaderElt,
                        SoShaderProgram* internalShader);

  /** Return the shader program which is currently in OpenGL state*
   * (only for GLRenderAction) */
  static SoShaderProgram* getActiveProgram(SoState *state);

private:
  // Destructor
  virtual ~SoGLShaderProgramElement();

};
#endif /* _SO_GL_SHADER_PROGRAM_ELEMENT_ */
