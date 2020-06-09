/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef SO_VOLUME_SHAPE_H
#define SO_VOLUME_SHAPE_H

#include <Inventor/nodes/SoShape.h>

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFNode.h>

#include <Inventor/STL/vector>

#include <Inventor/sys/SoGLType.h>

#include <Inventor/SbViewportRegion.h>

#include <LDM/nodes/SoTransferFunction.h>
#include <LDM/nodes/SoLdmShape.h>

class SoState;
class SoVolumeData;
class SoVolumeRenderingQuality;
class SoVolumeShader;
class SoVolumeShaderARB;
class SoVolumeState;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif


/**
*
* @VREXT Abstract base class for slices, SoVolumeSkin, SoHeightFieldRender,
* and SoVolumeRender nodes.
*
* @ingroup VolumeVizNodes
*
* @DESCRIPTION
*
*   This class defines common properties for the SoOrthoSlice, SoObliqueSlice,
*   SoFenceSlice, SoVolumeSkin, SoHeightFieldRender and SoVolumeRender nodes.
*
*   The #interpolation field controls how the texture is interpolated.
*
*   The #composition field controls how the slice is blended with other objects
*   in the scene.
*
* @SEE_ALSO
*    SoObliqueSlice,
*    SoOrthoSlice,
*    SoFenceSlice,
*    SoVolumeRender,
*    SoVolumeSkin,
*    SoHeightFieldRender
*
*
*/
class VOLUMEVIZ_API SoVolumeShape : public SoLdmShape {
  SO_NODE_ABSTRACT_HEADER(SoVolumeShape);

public:

  /** Composition mode */
  enum Composition {
    /** Max intensity */
    MAX_INTENSITY,
    /** Min intensity */
    MIN_INTENSITY,
    /** Sum intensity */
    SUM_INTENSITY,
    /** Alpha blending (Default) */
    ALPHA_BLENDING
  };

  /**
  * Specifies color composition mode.
  * Use enum #Composition. Default is ALPHA_BLENDING.
  *
  * ALPHA_BLENDING blends the R, G, and B components for each pixel based on the
  * their alpha values.
  *
  * SUM_INTENSITY draws the sum of the R, G, and B components for each pixel.
  *
  * MAX_INTENSITY draws the maximum R, G, and B components for each pixel.
  *
  * MIN_INTENSITY draws the minimum R, G, and B components for each pixel.
  *
  * @B Note: @b
  * In all modes, blending is done against the background color of the scene (or
  * the object behind the volume). This means that, using MIN_INTENSITY for example,
  * if the background color is black then 0,0,0 is already the minimum RGB value
  * and the volume will not be visible.  Generally when using MIN_INTENSITY the
  * background color should be set to white (1,1,1) and when using MAX_INTENSITY
  * or SUM_INTENSITY the background color should be set to black (0,0,0).  To set
  * the background color see the setBackgroundColor method of the appropriate
  * RenderArea class, for example SoWinRenderArea on Windows.
  *
  * @FIELD_SINCE_OIV 5.0.3
  */
  SoSFEnum composition;

  /** Interpolation mode */
  enum Interpolation {
    /** OpenGL "nearest neighbor" interpolation */
    NEAREST,
    /** OpenGL linear interpolation (Default).
     *  This implies bi-linear interpolation for 2D textures
     *  (e.g. SoOrthoSlice, SoObliqueSlice, SoVolumeSkin) and
     *  tri-linear interpolation for 3D textures (SoVolumeRender). */
    LINEAR,
    /**
     * Tri-linear interpolation for SoObliqueSlice
     * (better image quality).  Same as LINEAR for other nodes.
     * @BR @BR
     * @ENUM_SINCE_OIV 6.0
     */
    TRILINEAR,
    /**
     * Interpolate volume data values using 12 nearest neighbors
     * (better image quality).
     * Only supported for slices and SoVolumeSkin.
     * @BR @BR
     * @ENUM_SINCE_OIV 7.0
     */
    MULTISAMPLE_12
  };

  /**
  * Texture interpolation. 
  * Use enum #Interpolation. Default is LINEAR.
  * NOTE: In most cases on modern graphics boards, indexed textures will
  * be used, so this is actually interpolation of volume data values.
  */
  SoSFEnum interpolation;

SoEXTENDER public:

  /** @copydoc SoLdmShape::GLRender */
  virtual void GLRender(SoGLRenderAction *action);

  /** @copydoc SoLdmShape::computeBBox */
  virtual void computeBBox(SoAction *action, SbBox3f &box, SbVec3f &center);

  /** @copydoc SoLdmShape::getBoundingBox */
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

SoINTERNAL public:

  /** @copydoc SoLdmShape::initClass */
  static void initClass();

  /** @copydoc SoLdmShape::initClass */
  static void exitClass();

  // ScaleViz specific : force rendering on all oiru in depth compositing mode
  // As VolumeViz shape nodes are considered as transparent (alpha)
  virtual int32_t getRenderUnitID() const;

  /**
   * Set all VViz uniforms.
   */
  void setVVizUniforms(const SbVec3i32 &tileSize,
                       const float *sliceTangent, const float *sliceBinormal,
                       int sliceAxis, float scale, float sliceSpacing,
                       SbBool doMultiVolume, const SbVec3f& scaleFactor,
                       const SbVec3f& lowResScaleFactor, SbBool doTexGen = TRUE);

  /**
   * Set axis along which slices are drawn
   */
  void setVVizZAxis(const SbVec3f& zAxis);

  /**
   * Install the colormap according to its type.
   * Return TRUE if an external shader is used.
   * textype is not modified for volume
   */
  virtual bool enableColorMap(SoState *state,
                              SoTransferFunction::GLColorMapType colorMapInstalled,
                              int &texType);

  /**
   * Disable color map.
   */
  virtual void disableColorMap(SoState *state,
                               SoTransferFunction::GLColorMapType colorMapInstalled,
                               bool useExternalShaderProg);


  /**
   * Return the type of installed colormap
   */
  SoTransferFunction::GLColorMapType getInstalledColorMap() const;

  /**
   * Return GL_NEAREST or GL_LINEAR according to interpolation field.
   */
  int getGLInterpolation();


  /**
   * Returns TRUE if a volume shader is being applied on the slice.
   */
  virtual SbBool isUsingExternalShaderProg();

  /**
   * Activate blending according to composition field.
   */
  virtual void enableBlending(SoState *state);

    /**
   * Called when the viewport size change.
   */
  virtual void onViewportChange(SoState*state);

  /**
   * Called when user stops or starts moving.
   */
  virtual void onUserInteractionChange(SoState* state, bool stopMoving);

  /**
   * Return interpolation value accoriding to the SoInteractiveComplexityElement
   */
  SoVolumeShape::Interpolation getInteractiveInterpolationValue(SoState* state) const;

protected:
  SoVolumeState* m_volumeState;

  SoVolumeShape();
  virtual ~SoVolumeShape();

  /**
   * True if the shape is transparent.
   */
  virtual bool isTransparent(SoState *state);

  /**
   * Delay rendering as needed by VViz.
   */
  virtual void delayRendering();

  /**
   * @return true if the shape is going to be delayed
   */
  bool isDelayed();

  /**
   * Return the volume shader in the state, NULL otherwise.
   */
  SoVolumeShader* getVolumeShader(SoState *state);

  /**
   * Get locations of all VViz uniform, in order to avoid calling
   * the expensive glGetUniformLocation all the time.
   */
  void getVVizUniformLocation();

  /**
   * Enable or disable vertices generation.
   * Default implementation disable it.
   */
  virtual void setVVizVertexGenUniforms();

  /**
   * Blend alpha with (1, 1-alpha) or (alpha, 1-alpha)
   * if m_useSeparateAlpha is false
   */
  void setGLAlphaBlendingFunc();

  /**
   * Blending will use (1, 1-alpha) instead of (alpha, 1-alpha)
   * for alpha channel composition. (glBlendFuncSeparateEXT must be available)
   */
  void useSeparateAlphaBlend(bool flag);

  /**
   * Returns the supported openGL depth internal format.
   */
  GLenum getDepthInternalFormat();

  /**
   * Return true if there is user interaction.
   */
  bool isMoving();

  /**
   * Save the current volume shader in m_volumeShader and set m_isUsingExternalShaderProg.
   */
  virtual void fetchVolumeShader(SoState *state);

  /**
   * Do the actual rendering.
   */
  virtual void doRendering(SoGLRenderAction* action) = 0;

  /**
   * Fetch volume clipping and uniform grid clipping nodes.
   */
  void getClippingNodes();

  /** Register ldm geometry to octree */
  virtual void ldmAction(SoLdmValuationAction* action);

  static void onViewportChangeCb(SoNode* node);
  static void onUserInteractionChangeCb(SoNode* node, bool moving);

  friend class SoSliceInterface;
};

#if defined(_WIN32)
#pragma warning( pop )
#pragma warning(disable:4251)
#endif

#endif
