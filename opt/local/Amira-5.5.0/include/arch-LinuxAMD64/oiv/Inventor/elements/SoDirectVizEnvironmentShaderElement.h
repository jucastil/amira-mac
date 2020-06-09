/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/

#ifndef  _SO_DIRECT_VIZ_ENVIRONMENT_SHADER_ELEMENT
#define  _SO_DIRECT_VIZ_ENVIRONMENT_SHADER_ELEMENT

#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoLists.h>

class SoDirectVizEnvironmentShader;

SoEXTENDER class INVENTOR_API SoDirectVizEnvironmentShaderElement :public SoReplacedElement{

  SO_ELEMENT_HEADER(SoDirectVizEnvironmentShaderElement);

 public:
 
  // Initializes element.

  virtual void        init(SoState *state);

  static void  set(SoState *state, SoNode *node);

  static const SoDirectVizEnvironmentShader *get(SoState *state);

  void setShader(SoDirectVizEnvironmentShader *shader){

      _shader = shader;
  }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
     
  // list of shaders nodes
  SoDirectVizEnvironmentShader  *_shader;

  virtual ~SoDirectVizEnvironmentShaderElement();
};

#endif 
