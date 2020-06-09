/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DIRECTVIZ_DIRECTIONALLIGHT_
#define  _SO_DIRECTVIZ_DIRECTIONALLIGHT_

#include <Inventor/VRMLnodes/SoVRMLDirectionalLight.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizDirectionalLight
//
//  specific DirectViz directional light node
//
//////////////////////////////////////////////////////////////////////////////

/**
* DirectViz directional light node.
* 
* @DESCRIPTION
*   
* SoDirectVizDirectionalLight node containing a SoDirectVizLightShader
* ONLY USED FOR COMPATIBILITY WITH OPENRTRT INVIEW FILE FORMAT
*
* @SEE_ALSO
* SoDirectVizLightShader,SoDirectVizManager.
*/ 

class INVENTOR_API SoDirectVizDirectionalLight : public SoVRMLDirectionalLight {

  SO_NODE_HEADER(SoDirectVizDirectionalLight);

 public:
  // Fields

  /**
   * Name
   */
  SoMFString name;

  /**
   * Shader
   */
  SoSFNode shader;

  /**
   * Constructor.
   */
  SoDirectVizDirectionalLight();

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

  virtual void doAction(SoAction *action);

  virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizDirectionalLight();
};

#endif /* _SO_DIRECTVIZ_DIRECTIONALLIGHT__ */
