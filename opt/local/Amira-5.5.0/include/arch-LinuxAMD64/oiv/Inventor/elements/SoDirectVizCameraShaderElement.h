/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/

#ifndef  _SO_DIRECT_VIZ_CAMERA_SHADER_ELEMENT
#define  _SO_DIRECT_VIZ_CAMERA_SHADER_ELEMENT

#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/SoLists.h>

class SoDirectVizCameraShader;

SoEXTENDER class INVENTOR_API SoDirectVizCameraShaderElement :public SoReplacedElement{

  SO_ELEMENT_HEADER(SoDirectVizCameraShaderElement);

 public:
 
  // Initializes element.

  virtual void        init(SoState *state);

  static void  set(SoState *state, SoNode *node);

  static const SoDirectVizCameraShader *get(SoState *state);

  void setShader(SoDirectVizCameraShader *shader){

      _shader = shader;
  }

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
     
  // list of shaders nodes
  SoDirectVizCameraShader  *_shader;

  virtual ~SoDirectVizCameraShaderElement();
};

#endif 
