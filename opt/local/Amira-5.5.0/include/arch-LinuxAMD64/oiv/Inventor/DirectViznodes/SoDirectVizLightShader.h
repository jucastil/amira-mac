/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SO_DIRECTVIZ_LIGHTSHADER_
#define  _SO_DIRECTVIZ_LIGHTSHADER_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/DirectViznodes/SoDirectVizShader.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizLightShader
//
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Simulates DirectViz light shader.
 * 
 * @DESCRIPTION
 *   
 * node specifying a light shader used for DirectViz rendering
 * 
 */ 

class INVENTOR_API SoDirectVizLightShader : public SoDirectVizShader {

  SO_NODE_HEADER(SoDirectVizLightShader);

 public:
  /**
   * Constructor.
   */
  SoDirectVizLightShader();

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

  SoEXTENDER public:
    virtual void doAction(SoAction *action);

 protected:
    
  virtual ~SoDirectVizLightShader();
};

#endif /* _SO_DIRECTVIZ_LIGHTSHADER_ */
