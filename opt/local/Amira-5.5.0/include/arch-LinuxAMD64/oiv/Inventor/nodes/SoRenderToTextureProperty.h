/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Dec 2004)
**=======================================================================*/


#ifndef  _SO_RENDER_TO_TEXTURE_PROPERTY_
#define  _SO_RENDER_TO_TEXTURE_PROPERTY_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFNode.h> 
#include <Inventor/fields/SoSFEnum.h> 
#include <Inventor/fields/SoSFColor.h> 
#include <Inventor/fields/SoMFPath.h> 
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFTrigger.h>
#include <Inventor/actions/SoGLRenderAction.h> 
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/components/SoGLGraphicConfigTemplate.h>
#include <Inventor/sys/SoGLType.h>
#include <Inventor/helpers/SbGlContextHelper.h>

class SoGLRenderToBuffer;

/**
 * 
 * @VSGEXT Class for creating a texture by rendering a scene graph
 * 
 * @ingroup General
 * 
 * @DESCRIPTION
 * This class is used to define an image for texture mapping which is 
 * created by rendering a scene graph. It can be used with
 * the classes SoTexture2 and SoTextureCubeMap. 
 *
 * One of the two fields, node or path, must be defined.
 *
 * The scene graph should normally contain a camera and at least one light.
 *
 * Note that the default image size is 0,0 (effectively disables rendering).
 * 
 * @FILE_FORMAT_DEFAULT
 *    RenderToTextureProperty {
 *    @TABLE_FILE_FORMAT
 *       @TR node                @TD []
 *       @TR path                @TD ""
 *       @TR updatePolicy        @TD WHEN_NEEDED
 *       @TR backgroundColor     @TD 0 0 0
 *       @TR size                @TD 0 0
 *       @TR component           @TD RGB
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *  SoTexture2,
 *  SoTextureCubeMap
 *
 */ 

class INVENTOR_API SoRenderToTextureProperty : public SoNode {

 SO_NODE_HEADER(SoRenderToTextureProperty);
  
 public:
  
 SoRenderToTextureProperty();
 
 /** Update Policy enumeration values. */
 enum UpdatePolicy {
    /**
     * The texture is updated at each traversal of the shape it is mapped to.
     */
    EACH_FRAME,
    /**
     * Default.
     * The texture is updated only if the path or node fields have changed.
     */
    WHEN_NEEDED,
    /**
     * The texture is updated only if the trigger field is touched.
     */
    ON_TRIGGER
  };

 /** Rendering component enumeration values. */
  enum Component {
    /**
     * Default.
     * The RGB components are rendered to the texture.
     */
    RGB,
    /**
     * The RGB and alpha components are rendered to the texture.
     */
    RGB_TRANSPARENCY,
    RGB_ALPHA = RGB_TRANSPARENCY,
    /**
     * The depth component is rendered to the texture.
     */
    DEPTH
  };


  // Fields
  /** 
   * Specifies the scene graph(s) (SoNode(s)) to be rendered into the texture.
   * For use with SoTexture2, only one scene graph should be specified.
   * For use with SoTextureCube map, six scene graphs must be specified,
   * one for each face of the cube in the order:
   *
   * - imagePosX (left)
   * - imagePosY (bottom)
   * - imagePosZ (back)
   * - imageNegX (right)
   * - imageNegY (top)
   * - imageNegZ (front)
   *
   * The node field has priority over the path field. Null by default.
   */
  SoMFNode node;

  /** 
   * Specifies the scene graph(s) (SoPath(s)) to be rendered into the texture. 
   * For use with SoTexture2, only one path should be specified.
   * For use with SoTextureCube map, six paths must be specified,
   * one for each face of the cube in the order:
   *
   * - imagePosX (left)
   * - imagePosY (right)
   * - imagePosZ (top)
   * - imageNegX (bottom)
   * - imageNegY (back)
   * - imageNegZ (front)
   *
   * The node field has priority over the path field. Null by default.
   */
  SoMFPath path;

  /**
   * Specifies the policy for rendering to the texture. 
   * Use enum #UpdatePolicy. Default is WHEN_NEEDED.
   */
  SoSFEnum updatePolicy;

  /**
   * Background color used when rendering the scene graph. Black by default.
   */
  SoSFColor backgroundColor;

  /**
   * Size in pixels of the rendered texture. 
   * If the size is not a power of two couple of values and the extension texture_non_power_of_two is not 
   * present on board, the size will be automatically scaled to the next power of two (less effective).
   * (0, 0) by default.
   */
  SoSFVec2s size;

  /**
   * Specifies the type of component(s) for the rendering. 
   * Use enum #Component. Default is RGB.
   */
  SoSFEnum component;

  /**
   * Trigger field to render the scene into the Pbuffer.
   * Effective only if updatePolicy is ON_TRIGGER.
   */
  SoSFTrigger trigger;

  /**
   * Specifies a custom render action to use for rendering the scene.
   */
  void setGLRenderAction(SoGLRenderAction* ra);

  /**
   * Returns the render action used for rendering the scene.
   */
  SoGLRenderAction* getGLRenderAction() const;

  /**
   * Specifies a custom graphic config template to use for rendering the scene.
   */
  void setGraphicConfigTemplate(SoGLGraphicConfigTemplate* gct);

  /**
   * Returns the graphic config template used for rendering the scene.
   */
  SoGLGraphicConfigTemplate* getGraphicConfigTemplate();


  /** 
   * Set OpenGL render context for display list sharing.
   * Must be set before calling the create() method.
   * There is no guarantee that sharing will be allowed.
   */
  void setContextForSharing(SoGLContext *context);


SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  bool needDelayedTriggering() const;
  
  SbBool triggerRender();
  void deleteCurrentPBuffer();
  void setGCParams(SbVec4i32 params);

  void setForTextureCubeMap(SbBool isCubeMap);
  void setFaceTarget(int faceTarget);
  void useAutoMipmap(SbBool mm);
  SbBool isAutoMipmap() {return m_autoMipmap;};
  SbBool bindTexture(GLuint texObj);
  SbBool releaseTexture();
  void makePBufferCurrent() const;
  void disablePBuffer();
  void setTexImageSize(SbVec2s texImgSize) {m_texImgSize = texImgSize;};
  SbVec2s getTexImageSize() const {return m_texImgSize;};

  void setDisplay(SbGlContextHelper::Display  handle);

protected:
  ~SoRenderToTextureProperty();

private:
  SbBool anySceneGraph();
  SbBool doRendering();
  static void triggerCB(void *data, SoSensor *);
  static void componentChangedCB(void *data, SoSensor *);

  static int s_renderingEngine;

  SoFieldSensor* m_triggerSensor;
  SoFieldSensor* m_componentSensor;

  SbBool m_textureCubeMapEnabled;
  SbBool m_autoMipmap;

  SoGLContext *m_shareContext;
  SbBool   m_userShareContext;

  
  SoGLRenderToBuffer* m_renderBuffer;
  SoGLGraphicConfigTemplate* m_gTemplate;
  SoGLRenderAction* m_renderAction;
  SbBool m_userRA;
  SbBool m_userGT;
  SbVec4i32 m_gtParams;
  SbVec2s m_texImgSize;  
  SbBool m_triggerCalled;

  SbGlContextHelper::Display m_dpyHandle;

  unsigned int m_bindToTexture;
};

#endif /* _SO_RENDER_TO_TEXTURE_PROPERTY_ */
