/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_DIRECT_VIZ_LIGHT_SHADER_ELEMENT
#define  _SO_DIRECT_VIZ_LIGHT_SHADER_ELEMENT

#include <Inventor/elements/SoElement.h>

#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/SoLists.h>


class SoDirectVizShader;

SoEXTENDER class INVENTOR_API SoDirectVizLightShaderElement :public SoAccumulatedElement{

  SO_ELEMENT_HEADER(SoDirectVizLightShaderElement);

 public:
 
  // Initializes element.

  virtual void        init(SoState *state);

  virtual void        pop(SoState *state, const SoElement *prevTopElement);
  virtual void        push(SoState *state);

  static void         add(SoState *state, SoDirectVizShader *profile);

  static const SoNodeList &   get(SoState *state);

 SoINTERNAL public:
  // Initializes the SoDirectVizShaderElement class
  static void         initClass();
  static void         exitClass();

 protected:
     
  // list of profile nodes
  SoNodeList          _shaders;

  virtual ~SoDirectVizLightShaderElement();
};

#endif 
