/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/

#ifndef  _SO_RTSHADER_ELEMENT
#define  _SO_RTSHADER_ELEMENT

#include <Inventor/elements/SoElement.h>

#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoReplacedElement.h>
#include <Inventor/errors/SoDebugError.h>

#include <Inventor/SoLists.h>


class SoDirectVizShader;

SoEXTENDER class INVENTOR_API SoDirectVizShaderElement :public SoReplacedElement{

    SO_ELEMENT_HEADER(SoDirectVizShaderElement);

public:

    // Initializes element.
    virtual void init(SoState *state);

    static void set(SoState *state,SoNode *node,SoDirectVizShader *shader);

    static SoDirectVizShader *get(SoState *state);

    SoINTERNAL public:
    // Initializes the SoDirectVizShaderElement class
    static void initClass();
    static void exitClass();

protected:

    virtual void setShader(SoDirectVizShader *shader){_shader = shader;}

    // list of shaders nodes
    SoDirectVizShader *_shader;

    virtual ~SoDirectVizShaderElement();
};

#endif 
