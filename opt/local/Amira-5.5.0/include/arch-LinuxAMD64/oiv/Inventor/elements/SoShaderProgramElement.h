/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_SHADER_PROGRAM_ELEMENT_
#define  _SO_SHADER_PROGRAM_ELEMENT_

#include <Inventor/elements/SoReplacedElement.h>

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
SoEXTENDER_Documented class INVENTOR_API SoShaderProgramElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoShaderProgramElement);

public:
  /**
  *  Sets the current shader program in the state.
  */
  static void set(SoState *state, SoNode *node);

  /**
  *  Gets the current shader program in the state.
  */
  static void get(SoState *state, SoShaderProgram *&);

  /**
  *  Overrides push() method so side effects can occur in GL.
  */
  virtual void push(SoState *) ;

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);


SoINTERNAL public:
  // Initializes the classes.
  static void initClass();
  static void exitClass();

  // Initializes element.
  virtual void init(SoState *state);

  /**
   * Set a bigger priority than SoGLUniformShaderElement in order to be sure
   * to have the good active shader when doing the set uniform.
   */
  virtual void commonInit();

  /** Get the current pushed element if any */
  static const SoShaderProgramElement* get(SoState *state);

  /** True if shader is active for OpenGL */
  inline bool isEnabled() const { return m_enabled; }

  // Current shader storage
  SoShaderProgram   *m_shaderProgram ;

  static SoShaderProgramElement * getCurrentElement(SoState *);

protected:
  // Destructor
  virtual ~SoShaderProgramElement();

  /** True if shader is active */
  bool m_enabled;
};
#endif /* _SO_GL_SHADER_PROGRAM_ELEMENT_ */
