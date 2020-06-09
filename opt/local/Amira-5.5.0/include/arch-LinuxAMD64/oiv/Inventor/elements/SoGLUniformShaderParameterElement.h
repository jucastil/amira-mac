/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_GL_UNIFORM_SHADER_PARAMETER_ELEMENT
#define  _SO_GL_UNIFORM_SHADER_PARAMETER_ELEMENT

#include <Inventor/elements/SoUniformShaderParameterElement.h>

class SoUniformShaderParameter;

/**
* @VSGEXT Stores uniform shader parameter values.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores uniform shader parameter values.
*
*   @SEE_ALSO
*   SoUniformShaderParameterElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLUniformShaderParameterElement : public SoUniformShaderParameterElement {

  SO_ELEMENT_HEADER(SoGLUniformShaderParameterElement);

 public:
  /**
  *  Override pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLUniformShaderParameterElement class
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoGLUniformShaderParameterElement();

  /**
   * Return true if the parameter need to be setted again:
   * param is in prevElt parameters list and its value is different
   */
  bool needToSetUniformParameter(const SoUniformShaderParameter* param,
                                 const SoGLUniformShaderParameterElement *prevElt);

  //In order to have access to the destructor
  friend class SoShaderProgramElement;
};

#endif /* _SO_GL_UNIFORM_SHADER_PARAMETER_ELEMENT */
