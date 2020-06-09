/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_VERTEX_SHADER_PARAMETER_ELEMENT_
#define  _SO_VERTEX_SHADER_PARAMETER_ELEMENT_

/* include files */
#include <Inventor/SoLists.h>
#include <Inventor/elements/SoAccumulatedElement.h>

class SoVertexShaderParameter;

/**
*   @VSGEXT Stores SoVertexShaderParameter nodes encountered during traversal.
* 
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores SoVertexShaderParameter nodes encountered during traversal.
*
*   @SEE_ALSO
*   SoShaderParameter
*/

SoEXTENDER_Documented class INVENTOR_API SoVertexShaderParameterElement : public SoAccumulatedElement {
  SO_ELEMENT_HEADER(SoVertexShaderParameterElement);

 public:
  /**
  *  Add to the current vertex attribs list.
  */
  static void add(SoState *state, SoVertexShaderParameter * vertexAttrib);
  
  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state);

  /**
  *  Pop method.
  */
  virtual void pop(SoState *, const SoElement *prevTopElement);
  
  /**
  *  Returns the current list of vertex attribs nodes from the state.
  */
  static const SoNodeList * getVertexAttribs(SoState *state);

 SoINTERNAL public:
  
  // Initializes the SoLightElement class
  static void initClass();
  static void exitClass();
 
  // Initializes element.
  virtual void init(SoState *state);
  
 protected:
  // list of light nodes
  SoNodeList m_vertexAttribs;

  virtual ~SoVertexShaderParameterElement();
};
/*----------------------------------------------------------------------------*/

#endif // _SO_VERTEX_SHADER_PARAMETER_ELEMENT_
