/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SO_DIRECTVIZ_SPOTLIGHT_
#define  _SO_DIRECTVIZ_SPOTLIGHT_

#include <Inventor/VRMLnodes/SoVRMLSpotLight.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizSpotLight
//
//  specific DirectViz spot light node
//
//////////////////////////////////////////////////////////////////////////////

/**
* DirectViz spot light node.
* 
* @DESCRIPTION
*   
* SoDirectVizSpotLight node containing an SoDirectVizLightShader
* ONLY USED FOR COMPATIBILITY WITH OPENRTRT INVIEW FILE FORMAT
*
* @SEE_ALSO
* SoDirectVizLightShader,SoDirectVizManager.
*/ 

class INVENTOR_API SoDirectVizSpotLight : public SoVRMLSpotLight {

  SO_NODE_HEADER(SoDirectVizSpotLight);

 public:
  // Fields

  /**
   * name
   */
  SoMFString name;

  /**
   * shader
   */
  SoSFNode shader;

  /**
   * Options
   */
  SoMFString          options;

  /**
   * Constructor.
   */
  SoDirectVizSpotLight();


  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

  virtual void doAction(SoAction *action);

  virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizSpotLight();
};

#endif /* _SO_DIRECTVIZ_SPOTLIGHT_ */
