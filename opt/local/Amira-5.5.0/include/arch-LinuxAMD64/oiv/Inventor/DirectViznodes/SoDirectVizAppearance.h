/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : G.TALLEC (Oct 2006)
**=======================================================================*/



#ifndef  _SO_DIRECTVIZ_APPEARANCE_
#define  _SO_DIRECTVIZ_APPEARANCE_

#include <Inventor/VRMLnodes/SoVRMLAppearance.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFString.h>

class SoFieldSensor;
class SoSensor;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectVizAppearance
//
//  DirectViz Appearance VRML node
//
//////////////////////////////////////////////////////////////////////////////

/**
 *
 * DirectViz Appearance VRML node.
 * 
 * @DESCRIPTION
 *   
 * SoDirectVizAppearance is inherited from SoVRMLAppearance node. 
 * It contains an SoDirectVizGeneralShader node specifying material properties.
 *
 * @see SoDirectVizShader
 * 
 */ 

class INVENTOR_API SoDirectVizAppearance : public SoVRMLAppearance {
  
  SO_NODE_HEADER(SoDirectVizAppearance);
  
 public:
  // Fields
  
  /**
   * Associated shader.
   */
  SoSFNode shader;

  /**
   * Texture projection (NOT USED).
   */
  SoSFNode textureProjection; 

  /**
   * Instance name (NOT USED).
   */
  SoMFString instanceName;

  /**
   * Constructor.
   */
  SoDirectVizAppearance();

  SoEXTENDER public:
    // Implements actions
    virtual void GLRender(SoGLRenderAction *action);

  virtual void doAction(SoAction *action);

  virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
    static void         initClass();
  static void           exitClass();

 protected:

  virtual ~SoDirectVizAppearance();
};

#endif /* _SO_DIRECTVIZ_APPEARANCE_ */
