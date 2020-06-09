/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_UNIFORM_SHADER_PARAMETER_ELEMENT_
#define  _SO_UNIFORM_SHADER_PARAMETER_ELEMENT_

#include <Inventor/fields/SoMFNode.h> 
#include <Inventor/SbPList.h>
#include <Inventor/elements/SoAccumulatedElement.h>

class SoShaderParameter;

/*----------------------------------------------------------------------------*/

/**
*   @VSGEXT Stores the current uniform shader parameter.
* 
*   @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current uniform shader parameter.
* 
*   @SEE_ALSO
*   SoShaderParameter
*/
SoEXTENDER_Documented class INVENTOR_API SoUniformShaderParameterElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER(SoUniformShaderParameterElement) ;

public:
  /**
  *  Adds a shader parameter.
  */
  static void add(SoState *state, SoShaderParameter *param, SoMFNode *shaderObjects) ;

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  const SoUniformShaderParameterElement *getInstance(SoState *state);

  SoINTERNAL public:

  // Initializes the SoUniformShaderParameterElement class
  static void initClass() ;
  static void exitClass() ;

  // Initializes element.
  virtual void init(SoState *state);

protected:
  //List of SoUniformShaderParameter
  SoNodeList parameters;
  //List of SoMFNode * of SoShaderObject
  SbPList shaderObjs;

  virtual ~SoUniformShaderParameterElement() ;
} ;
/*----------------------------------------------------------------------------*/

#endif // _SO_UNIFORM_SHADER_PARAMETER_ELEMENT_
