/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SO_DIRECTVIZ__CAMERA_SHADER_
#define  _SO_DIRECTVIZ__CAMERA_SHADER_

#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/DirectViznodes/SoDirectVizShader.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizCameraShader
//
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @DVEXT DirectViz Camera shader.\ @NO_ACTION
 * 
 * @ingroup DirectViz
 *
 * @DESCRIPTION
 *   node specifying a camera shader used for DirectViz rendering
 * 
 * 
*/ 

class INVENTOR_API SoDirectVizCameraShader : public SoDirectVizShader {

  SO_NODE_HEADER(SoDirectVizCameraShader);

 public:

  /**
   * Constructor
   */
  SoDirectVizCameraShader();

  SoEXTENDER public:
    virtual void doAction(SoAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  /**
   * Destructor
   */
  virtual ~SoDirectVizCameraShader();
};

#endif /* _SO_DIRECTVIZ_GENERALSHADER_ */

