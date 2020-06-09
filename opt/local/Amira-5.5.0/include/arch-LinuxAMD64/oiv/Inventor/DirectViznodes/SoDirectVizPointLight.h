/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/


#ifndef  _SO_DIRECTVIZ_POINTLIGHT_
#define  _SO_DIRECTVIZ_POINTLIGHT_

#include <Inventor/VRMLnodes/SoVRMLPointLight.h>
#include <Inventor/DirectViznodes/SoDirectVizShader.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizPointLight
//
//  specific DirectViz point light node
//
//////////////////////////////////////////////////////////////////////////////

/**
* DirectViz Point Light node.
* 
* @DESCRIPTION
*   
* SoVRMLPointLight node containing an SoDirectVizLightShader
* ONLY USED FOR COMPATIBILITY WITH OPENRTRT INVIEW FILE FORMAT
*
* @SEE_ALSO
* SoDirectVizLightShader,SoDirectVizManager.
*/ 

class INVENTOR_API SoDirectVizPointLight : public SoVRMLPointLight {

  SO_NODE_HEADER(SoDirectVizPointLight);

 public:
  // Fields

  /**
   * Name
   */
  SoMFString name;

  /**
   * Associated light shader
   */
  SoSFNode shader;

  /**
   * Constructor.
   */
  SoDirectVizPointLight();

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

  virtual void doAction(SoAction *action);

  virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizPointLight();
};

#endif /* _SO_DIRECTVIZ_POINTLIGHT_ */
