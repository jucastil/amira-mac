/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#if !defined(SO_RENDERTOTARGET_H)
#define SO_RENDERTOTARGET_H

#include <Inventor/fields/SoMFEnum.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2i32.h>
#include <Inventor/nodes/SoSeparator.h>

class SoRenderToTargetImpl;

//@TOBEWRAPPED
/** 
 * @VSGEXT Group node that renders its children to one or more "targets".
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *  This group node renders its children to one or more render targets.
 *  
 *  Multiple targets can be "attached" to the different outputs of the node.
 *  
 *  This node also provides antialiasing. When FrameBufferObjects (FBO) are used 
 *  (this is the default mode if they are available) multisampling can be configured 
 *  in order to perform antialiasing on the FBO. This MSAA feature is not related 
 *  to the viewer's FSAA. The quality factor is set between 0.f(default value) and 1.f. 
 *  The underlying system will setup the FBO with the correct number of samples according 
 *  to the quality value and according to the attachments configuration.
 *
 *  By default the node clears the targets when the rendering is started. It is possible
 *  to disable this feature by setting the field #clearTargets to FALSE.
 *
 *  During rendering, the viewport from the Open Inventor state is used, which means that
 *  the current size of the render area is used. It is possible to change this default 
 *  behavior by setting the #size field. Setting it to (-1, -1) will switch back to the 
 *  default mode, other values will be used as the custom rendering size in pixels. 
 *  The targets are automatically resized to the correct size.
 *
 *  NOTES:
 *  - Performance:
 *    - Using the TARGET_COPY mode at each frame really reduces performance because a 
 *      transfer from GPU memory to CPU memory is performed to transfer the data to the 
 *      SoSFImage field of the texture.
 *    - Antialiasing (MSAA) can really reduce performance and increase memory consumption. 
 *      It can even be impossible to use antialiasing with large FLOAT color attachments.
 *  
 *  - Target limitations: At this time only SoTexture2 nodes are supported. Using other 
 *    types in the targets field will result in SoDebugErrors.
 * 
 *  - By default the textures are resized using the following rules:
 *    - RBGA uint8 for the color attachements. (Internal mode is RGBA8)
 *    - Luminance float32 for the depth attachment. (Internal mode is DEPTH_COMPONENT24).
 *    - Luminance uint8 for the stencil attachment.
 *  It is possible to override the default internal mode for the textures by using the internalFormat field of SoTexture.
 *
 *  - Hardware compatibility:
 *    - All the exposed features are supported by the FBO rendering subsystem. PBuffer and 
 *      pixmap might not support some of them. For example it is not possible to have multiple 
 *      color attachments in PBuffer mode. Those alternative modes are supported only for 
 *      compatibility with legacy hardware.
 *
 * @NODE_SINCE_OIV 8.6
 *    
 * @FILE_FORMAT_DEFAULT
 *    RenderToTarget {
 *    @TABLE_FILE_FORMAT
 *       @TR modes                     @TD AUTO
 *       @TR targets                   @TD NULL
 *       @TR clearTargets              @TD TRUE
 *       @TR antialiasingQuality       @TD 0.F
 *       @TR size                      @TD (-1, -1)
 *       @TR enableFragmentsQuery      @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Performs an offscreen rendering using either FBO, PBuffer or pixmap.
 *        Sets: SoCacheElement
 * 
 * @SEE_ALSO
 *    SoTexture,
 *    SoTexture2.
 * 
 * 
 */ 


class INVENTOR_API SoRenderToTarget : public SoSeparator
{
  SO_NODE_HEADER( SoRenderToTarget );

public:

  /** Attachment 
   *
   * This enum is used to specify which output of the rasterizer is considered.
   * Use these values as indices when setting the #targets and #modes fields.
   */
  enum Attachment
  {
    /** Default framebuffer used for rendering. */
    COLOR0,
    COLOR1,
    COLOR2,
    COLOR3,
    COLOR4,
    COLOR5,
    COLOR6,
    COLOR7,
    COLOR8,
    COLOR9,
    COLOR10,
    COLOR11,
    COLOR12,
    COLOR13,
    COLOR14,
    COLOR15,
    DEPTH,
    STENCIL,
    /** Not used, for security only */
    LAST_ENTRY
  };

  /**
   * This enum defines modifiers for the auto detection mechanism.
   */
  enum Mode
  {
    /** Default value, use OIV auto detection algorithm.
     * The detection algorithm checks the content of the #targets field.
     * NOTE: The node will use INTERNAL for DEPTH and COLOR0, NONE for the others.
     */
    AUTO,

    /** Use an internal buffer for the rendering.
     * Some buffers are useful only for shaders or for correct rendering (like depth buffer
     * for the depth tests) but they don't need to be attached to a specific target.
     */
    INTERNAL,

    /** 
     * After the rendering the rendered content is copied back to the node in CPU memory (SoTexture2 only).
     */
    TARGET_COPY,

    /**
     * Do not use any target.
     */
    NONE
  };

  /** 
   * This defines the mode modifier for the targets.
   * For each target it is possible to specify a mode. Use enum #Mode. Default is AUTO.
   *
   * NOTE: This field is indexed using the Attachment enum.
   * For example (in pseudo-code):
   * - modes[COLOR0] = TARGET_AND_COPY;
   * - modes[STENCIL] = INTERNAL;
   */
  SoMFEnum modes;

  /**
   * This field allows to attach a texture to a specific attachment. Default is empty (no targets).
   * If the modes field is set to TARGET_COPY for this attachment
   * then after rendering the resulting image is stored in the texture node's image field.
   * The texture must be of type SoTexture2.
   *
   * NOTE: This field is indexed using the Attachment enum.
   * For example (in pseudo-code):
   * - targets[COLOR0] = rgbaTexture;
   * - targets[STENCIL] = stencilTexture;
   */
  SoMFNode targets;

  /**
   * If this field is set the targets are cleared before the rendering. Default is TRUE.
   */
  SoSFBool clearTargets;

  /**
   * This field defines the antialiasing quality between 0.0 and 1.0 for the rendering.
   * The value 1.0 represents the maximun quality possible on this hardware.
   * Default is 0.
   *
   * NOTE:
   *   Hardware limitations: The result depends on the support for multisampling in FBO or the FSAA support for PBuffers.
   */
  SoSFFloat antialiasingQuality;

  /**
   * This field allows a custom rendering size for the render to texture.
   * When this field is set to the default value (-1, -1) the global viewport size from the viewer
   * is used. The size is in pixels.
   */
  SoSFVec2i32 size;

  /**
   * This field enables or disables the query counter used to count the number of fragments
   * rasterized during the render to texture operation. Default is FALSE.
   *
   * The method getRasterizedSamplesCount() can be used to get the result of the query.
   */
  SoSFBool enableFragmentsQuery;

  /**
   * Default constructor.
   */
  SoRenderToTarget();

  /**
   * Indicates if this node can be used on the actual hardware.
   */
  static SbBool isSupported(SoState* state = NULL);

  /**
   * Returns the number of samples generated by the rasterizer during the last GLRender action.
   *
   * To enable this feature the enableFragmentsQuery field must be set to TRUE.
   * Otherwise the result is undefined.
   */
  int getRasterizedSamplesCount() const;

SoINTERNAL public:

  /** @copydoc SoNode::initClass */
  static void initClass();

  /** @copydoc SoNode::exitClass */
  static void exitClass();

  /** Reset the render buffer when this is called. */
  virtual void notify(SoNotList *list);
 
SoEXTENDER public:

  /** @copydoc SoSeparator::GLRenderBelowPath */
  virtual void GLRenderBelowPath(SoGLRenderAction *action);

  /** @copydoc SoSeparator::GLRenderInPath */
  virtual void GLRenderInPath(SoGLRenderAction *action);

  /** @copydoc SoSeparator::GLRenderOffPath */
  virtual void GLRenderOffPath(SoGLRenderAction *action);

protected:
  /** Destructor. */
  virtual ~SoRenderToTarget();

private:
  SoRenderToTargetImpl* m_impl;
};

#endif // SO_RENDERTOTEXTURE_H
