/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2006)
** Modified    : David BEILLOIN (Mar 2011)
**=======================================================================*/
#ifndef  _SO_VOLUME_CLIPPING_GROUP_
#define  _SO_VOLUME_CLIPPING_GROUP_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/SbBox.h>

class SoGLDepthPeeling;
class SoState;
class SoROI;
class SoVolumeData;
class SoShaderProgram;
class SoShapeHints;

/**
* @VREXT Clipping a volume with a 3D object.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
* All geometry nodes under an SoVolumeClippingGroup will be used to clip the volume.
* The whole geometry defined under SoVolumeClippingGroup must represent a list of closed 
* surfaces otherwise the result is unpredictable.
* Clipping result is based on odd-winding rule, as a matter of fact the result is not 
* the union neither the intersection of the closed surfaces.
* If the goal is to define a clipping shape which is the results of the intersection/union of
* multiple closed surfaces, application can use SoCSGShape.
*
*@TABLE_1B
*      @TR Clipping object @TD Clipping applied to a volume
*         @TR  @IMAGE volumeclipping_object.jpg
*                   @TD @IMAGE volumeclipping.jpg
*      @TABLE_END
*
* The following code clips a volume with a cone:
* \oivnetdoc
*   \code
*   SoVolumeClippingGroup volClip = new SoVolumeClippingGroup();
*   volClip.AddChild(new SoCone());
*   root.AddChild(volClip)
*   root.AddChild(volumeData)
*   root.AddChild(transferFunction)
*   root.AddChild(volumeRender)
*   \endcode
* \else
*   \code
*   SoVolumeClippingGroup *volClip = new SoVolumeClippingGroup;
*   volClip->addChild(new SoCone);
*   root->addChild(volClip)
*   root->addChild(volumeData)
*   root->addChild(transferFunction)
*   root->addChild(volumeRender)
*   \endcode
* \endoivnetdoc
*
* @B Note:  @b 
* @UL 
* @LI When using a custom SoVolumeShader with this node and redefining the @I main() @i
* function, you must call @I VVizClipVoxel() @i in the @I main() @i function if you are writing a
* fragment shader. If you don't do this you will get a GLSL compilation error or clipping won't work.
*
* @LI This node uses predefined shaders internally and searches for them in the
* following directories in this order: current directory, $IVVR_SHADERS_PATH, and
* $OIVHOME/data/volumeviz/shaders. On Windows, the directory containing the VolumeViz DLL
* is searched last.
*
* @LI Because this node uses special textures, all texture units between IVVR_FIRST_RESERVED_TEXTURE_UNIT
* (or SoFragmentShader::getMaxTextureImageUnit()-SoVolumeShader::getNumReservedTextures() if this
* variable is not set) and :
*   - IVVR_FIRST_RESERVED_TEXTURE_UNIT-2*numPasses are reserved if GL_EXT_texture_array is not supported.
*   - IVVR_FIRST_RESERVED_TEXTURE_UNIT-2 are reserved if GL_EXT_texture_array is supported.
*
* @LI SoVolumeClippingGroup requires the following OpenGL extensions.
* Use the isSupported() static method to check for support on the current graphics board
* or use the IvReport tool to print a report about the graphics board.
*   - GL_ARB_depth_texture
*   - GL_ARB_fragment_program_shadow,
*   - GL_ARB_framebuffer_object,
*   - GL_ARB_shading_language_100
* @ul
*
* @FILE_FORMAT_DEFAULT
*    VolumeClippingGroup {
*    @TABLE_FILE_FORMAT
*       @TR numPasses      @TD 2
*       @TR clipOutside    @TD TRUE
*    @TABLE_END
*    }
* @SEE_ALSO
*  SoVolumeRender,
*  SoUniformGridClipping,
*  SoShaderProgram,
*  SoVolumeRenderingQuality,
*  SoVolumeIsosurface,
*  SoCSGShape,
*  SoPreferences
*
*/
class VOLUMEVIZ_API SoVolumeClippingGroup : public SoGroup {
  SO_NODE_HEADER( SoVolumeClippingGroup );

 public:

  /**
   * Default constructor.
   */
  SoVolumeClippingGroup();

  /**
   * Number of passes used to do the clipping. Increasing this number increases the image
   * quality but decreases performance. Default is 2 and maximum is SoVolumeClippingGroup::getMaxNumPasses().
   */
  SoSFInt32 numPasses;

  /**
   * If TRUE, voxels inside the clipping object will be drawn,
   * voxels outside will be clipped. Default is TRUE.
   */
  SoSFBool clipOutside;

  /**
   * Indicates if volume clipping is supported by your graphics board.
   */
  static SbBool isSupported(SoState* state=NULL) ;

  /**
   * Returns the maximum number of passes supported by the hardware.
   */
  static unsigned int getMaxNumPasses(SoState* state=NULL);

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void doAction(SoAction *action);
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  /** @copydoc SoGroup::rayPick */
  virtual void rayPick(SoRayPickAction *action);

  /** Handle field change*/
  virtual void notify(SoNotList *list);

 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  //Install a ROI box in the state in order to act like a ROI
  void installFakeROIBox(SoAction *action, SoVolumeData *vd);

  //Set depth textures and activate shaders in SoVolumeRender
  void activeShaderAndBindTextures(SoGLRenderAction *action);

  //Get the texture unit number where the first depth layer is binded
  int getFistDepthTextureUnit() const;

  //Return the number of depth textures pairs
  int getNumPairs() const;

  //Return 1/DepthTexSize
  SbVec3f getTexScaleFactor() const;

  // Return TRUE if using 2D texture array
  SbBool isUsingTextureArray() const;

  //Return the real number of depth layer passes used
  int getNumPassUsed() const;

  //TRUE if box is not into the clipping volume
  SbBool isCulled(const SbBox3f &box);


  //Used by SoVolumeShader to update its uniforms
  SbBool needViewportSizeUpdate() const { return m_needViewportSizeUpdate; }
  SbBool needNumPassesUpdate() const { return m_needNumPassesUpdate; }
  SbBool needExclusiveModeUpdate() const { return m_needExclusiveModeUpdate; }
  SbBool isInClippingVolume() const { return m_viewerInClipVolume; }

  void numPassesUpdated() { m_needNumPassesUpdate = FALSE; }
  void exclusiveModeUpdated() { m_needExclusiveModeUpdate = FALSE; }



 protected:
  virtual ~SoVolumeClippingGroup();

private:
  // max pass when texture_array is not supported.
  static const int MAX_NUM_PASSES = 5;


  void commonInit() ;

  SbBool initDepthPeeling(SoGLRenderAction *action, const SbVec2s &vpSize);

  SbBool m_depthRendered;
  SoGLDepthPeeling *m_glDepthPeeling;


  SbVec2s m_previousViewportSize;

  SbBool m_needViewportSizeUpdate;
  SbBool m_needNumPassesUpdate;
  SbBool m_needExclusiveModeUpdate;

  //Change shader when viewer go out or in the clip volume
  SbBool m_viewerInClipVolume;
  SbBool m_viewerWasInClipVolume;
  SbBool isViewerInClipVolumeBBox(SoState *state, const SbBox3f &bbox) const;

  // update bbox of the clipping volume
  void updateChildBBox();
  // get bbox of the clipping volume
  const SbXfBox3f& getBBox();

  SbBool m_applyTochild;
  SbXfBox3f m_bbox;
  bool m_bboxCacheClean;

  SbXfBox3f m_worldBbox;

  //Make the volume clipping act like a roi box
  SoROI *m_roi;

  struct SoVolumeClippingInfos {
    SoVolumeClippingGroup *cg;
    SoGLRenderAction *ra;
  } m_clippingInfos;
  static void renderCB(void *userData, SoGLDepthPeeling *mgr);

  /** shape hints to disable culling */
  SoShapeHints* m_shapeHintOverride;

  /** members used for debug rendering purpose */
  static bool s_debugVolumeClipping;
  SoShaderProgram* m_showDepthShader;
  void debugGLRender(SoGLRenderAction *action);
  void createDebugShader();

};
/*----------------------------------------------------------------------------*/
#endif
