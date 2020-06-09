/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Benjamin GRANGE (Aug 2005)
**=======================================================================*/


#ifndef _SO_VOLUME_QUALITY_H_
#define _SO_VOLUME_QUALITY_H_


#include <Inventor/SbBasic.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSubNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <VolumeViz/nodes/SoVolumeShader.h>

/*----------------------------------------------------------------------------*/
class SoFragmentShader;
class SoVertexShader;
class SoTransferFunction;
class SoVolumeShader;

/**
 *
 * @VREXT Volume rendering quality property mode
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 * This property node causes subsequent SoVolumeRender nodes to be drawn with different
 * levels of quality.
 *
 * @B NOTE@b:
 * - Only one (or none) of the following nodes can be active at a time:
 *   SoVolumeShader or SoVolumeRenderingQuality. However since Open Inventor 7.1, 
 *   both SoVolumeRenderingQuality and SoVolumeIsosurface may applied to the same
 *   SoVolumeRender node.
 *
 * - The #preIntegrated field has no effect on the SoVolumeIsosurface.
 *
 * - The SoVolumeRenderingQuality node must be before the SoVolumeRender and after the
 * SoTransferFunction.
 *
 * - This node forces the use of 3D textures and view-aligned slices.
 * It doesn't, however, actually modify the SoVolumeData::storageHint or
 * SoVolumeRender::viewAlignedSlices fields. Rather the values of these fields are
 * ignored during traversal.
 *
 * - Like SoVolumeShader, this node searches for its predefined shaders in the
 * following directories in this order: current directory, $OIV_FILE_SEARCH_PATHS, 
 * SoInput directory list, $IVVR_SHADERS_PATH, and $OIVHOME/data/volumeviz/shaders. 
 * On Windows, the directory containing the VolumeViz DLL is searched last.
 *
 * - This is a shader node! The effect will usually be undesirable if it is
 *   applied to standard geometry (polygons, lines, etc).  Therefore applications
 *   should generally keep the volume visualization nodes and standard geometry
 *   nodes separate in the scene graph (i.e. under different SoSeparator nodes).
 *
 * @H3 Pre-integrated and lighted rendering @h3
 * Various enhanced rendering modes for volume rendering are available:
 *  - Pre-integrated volume rendering
 *  - Lighted volume rendering
 *
 * In the case of lighting mode, the volume is lighted with the first directional light found
 * in the scene graph. No other lights affect the volume. The current SoMaterial specifies
 * the shininess and the ambient,
 *  specular, diffuse, and emissive color values. See also the #gradientQuality and
 * #lightingModel fields.
 *
 *   The following figures show the same volume data:
 *
 *      @TABLE_1B
 *         @TR Default volume rendering @TD Pre-integrated volume rendering @TD Lighted pre-integrated volume rendering
 *         @TR @IMAGE quality_volume.jpg
 *                   @TD @IMAGE quality_preintegrated.jpg
 *                   @TD @IMAGE quality_light.jpg
 *      @TABLE_END
 *
 * The pre-integrated mode is useful because it usually provides much higher image
 * quality for the same number of slices.
 * It is also useful when the transfer function has a lot of fast variations, i.e.,
 * the color changes very rapidly.
 *
 * @H3 Quality enhancement parameters @h3
 * @B Jittering@b:
 * When #jittering is set to true, a random offset is added to texture
 * coordinates in order to decrease ringing artifacts without the
 * cost of drawing a higher number of slices.
 *
 *      @TABLE_1B
 *         @TR No Jittering @TD With Jittering
 *         @TR @IMAGE volume_nojitter.jpg
 *         @TD @IMAGE volume_jitter.jpg
 *      @TABLE_END
 *
 * @B Gradient quality@b: When #lighting is enabled, the
 * #gradientQuality field allows you to choose between
 * various gradient computation techniques. The computational cost increases
 * with the quality.
 *      @TABLE_1B
 *         @TR Low quality @TD Medium quality @TD High quality
 *         @TR @IMAGE volume_forwarddiff.jpg
 *         @TD @IMAGE volume_centraldiff.jpg
 *         @TD @IMAGE volume_sobel.jpg
 *      @TABLE_END
 *
 * @B Surface scalar@b: When #lighting is enabled or #edgeDetect2DMethod is GRADIENT, the
 * #surfaceScalarExponent field disables lighting (or edge detection)
 * on uniform surfaces in order to avoid noise in these area. This
 * field should not be mixed with #unnormalizedGradientExponent.
 *      @TABLE_1B
 *         @TR Surface Scalar disabled  @TD Surface Scalar enabled
 *         @TR @IMAGE surfaceScalarOff.jpg
 *         @TD @IMAGE surfaceScalarOn.jpg
 *      @TABLE_END
 *
 * @B Unnormalized gradient @b: When #lighting is enabled, if
 * #unnormalizedGradientExponent is not 0, voxels with small gradients
 * will get more contribution from the ambient light than voxels
 * with high gradients. It is similar to #surfaceScalarExponent but
 * uses the ambient light instead of the transfer function color for
 * uniform surfaces.
 *
 * @B Lighting model@b: When #lighting is enabled, the #lightingModel field
 * allows you to choose between the lighting model used in Open Inventor 6 or
 * the full OpenGL lighting model. The OpenGL lighting model
 * allows better integration of a lighted volume with other lighted objects.
 * The following picture shows that in the case of OIV6,
 * the volume is much brighter than the sphere.
 * By setting the lighting model to OPENGL, the brightness of
 * the volume matches the brightness of the sphere.
 *
 *      @TABLE_1B
 *         @TR OIV6  @TD OPENGL
 *         @TR @IMAGE volume_oiv6light.jpg
 *         @TD @IMAGE volume_oiv7light.jpg
 *      @TABLE_END
 *
 * @B Gradient threshold@b: When lighting is enabled, gradients with a
 * length less than #gradientThreshold are ignored during the lighting
 * computation. This avoids doing lighting on noise while still lighting
 * important data. In the following screenshots, setting a threshold of 0.1
 * removed lighting on the noise surrounding the spheres.
 *
 *      @TABLE_1B
 *         @TR With #gradientThreshold set to 0 @TD With #gradientThreshold set to 0.1
 *         @TR @IMAGE volume_gradientThr0.jpg
 *         @TD @IMAGE volume_gradientThr1.jpg
 *      @TABLE_END
 *
 * @B Cubic interpolation@b: If #cubicInterpolation is set to TRUE, a
 * cubic interpolation is used instead of the usual linear interpolation. It
 * gives smoother results but its high cost usually makes it useful
 * only for still image rendering.
 *      @TABLE_1B
 *         @TR Linear interpolation @TD Cubic interpolation
 *         @TR @IMAGE volume_linear.jpg
 *         @TD @IMAGE volume_tricubic.jpg
 *      @TABLE_END
 *
 * @H3 Edge enhancement parameters @h3
 * Various edge enhancement techniques are available in this node and
 * in SoTransferFunction.
 * - #boundaryOpacity increases opacity depending on the length of the gradient vector.
 *   Areas with large gradient changes will have their opacity increased according to
 *   the #boundaryOpacityIntensity.
 *
 * - When #edgeColoring is on, the color of each voxel may be mixed
 *   with the #edgeColor. Areas where the normal (computed from the gradient)
 *   is facing the camera
 *   will have an unmodified color, whereas areas where the normal
 *   is more perpendicular to the view direction will tend towards
 *   #edgeColor.
 *
 * - When #edgeDetect2D is enabled, an image space filter is applied on
 *   the volume rendering image in order to detect edges, which will
 *   be highlighted. The results are affected by the #edgeDetect2DInnerThreshold
 *   and #edgeDetect2DOuterThreshold fields. The #edgeDetect2DMethod bitmask allows to
 *   apply the edge detection on the image's luminance, depth and/or gradient. The gradient
 *   method may give noisy result, the #surfaceScalarExponent may help to improve the result in this case.
 *
 * The following table shows the available edge detection techniques
 * (explanation of faux shading is in SoTransferFunction):
 *      @TABLE_1B
 *         @TR No Edges @TD Boundary Opacity @TD Edge 2D
 *         @TR     @IMAGE volume_noedges.jpg
 *             @TD @IMAGE boundary.jpg
 *             @TD @IMAGE edge2d.jpg
 *         @TR Edge Coloring @TD Faux Shading (see SoTransferFunction)
 *             @TR @IMAGE edgecoloring.jpg
 *             @TD @IMAGE fauxshading.jpg
 *      @TABLE_END
 *
 * Because this node is derived from SoVolumeShader, IVVR_FIRST_RESERVED_TEXTURE_UNIT applies
 * to it. See SoVolumeShader for more information.
 *
 * @H3 Volume projection @h3
 * Volume projection (SoProjection or derived classes) is incompatible with some 
 * options enabled by this node. @BR
 * Do not enable the preIntegrated, jittering or edgeDetect2D fields when using projection.
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeRenderingQuality {
 *    @TABLE_FILE_FORMAT
 *       @TR lighting           @TD FALSE
 *       @TR preIntegrated      @TD FALSE
 *       @TR jittering          @TD FALSE
 *       @TR gradientThreshold  @TD 0
 *       @TR edgeColoring       @TD FALSE
 *       @TR edgeColor          @TD (0, 0, 0)
 *       @TR edgeThreshold      @TD 0.2
 *       @TR boundaryOpacity    @TD FALSE
 *       @TR boundaryOpacityIntensity @TD 1.5
 *       @TR boundaryOpacityThreshold @TD 1.5
 *       @TR edgeDetect2D @TD FALSE
 *       @TR edgeDetect2DInnerThreshold @TD 0.1
 *       @TR edgeDetect2DOuterThreshold @TD 0.1
 *       @TR gradientQuality @TD MEDIUM
 *       @TR lightingModel @TD OIV6
 *       @TR cubicInterpolation @TD FALSE
 *       @TR colorInterpolation @TD TRUE
 *       @TR unnormalizedGradientExponent @TD 0
 *       @TR surfaceScalarExponent @TD 0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 * SoGLRenderAction @BR
 * Sets volume rendering quality parameters in the traversal state.
 *
 * @SEE_ALSO
 *  SoVolumeRender,
 *  SoVolumeShader,
 *  SoVolumeIsosurface,
 *  SoTransferFunction
 *
 *
 */
class VOLUMEVIZ_API SoVolumeRenderingQuality : public SoVolumeShader {

  SO_NODE_HEADER(SoVolumeRenderingQuality);

public:
  /** Gradient Quality mode */
  enum GradientQuality
  {
    /**
     *
     * Use the forward difference technique to compute the gradient.
     * This is a fast technique but it gives a lower quality gradient.
     */
    LOW = SoVolumeShader::GRADIENT_FORWARD_DIFF,

    /**
     *
     * Use the central difference technique to compute the gradient.
     * This is a compromise between quality and speed.
     */
    MEDIUM = SoVolumeShader::GRADIENT_CENTRAL_DIFF,

    /**
     *
     * Use a Sobel filter to compute the gradient.
     * This gives hiqh quality gradients at the expense of speed.
     */
    HIGH = SoVolumeShader::GRADIENT_SOBEL,
#ifndef HIDDEN_FROM_DOC
    LAST_GRADIENT_QUALITY
#endif
  };

  /** Available Lighting Model mode */
  enum LightingModel
  {
    /**
     *
     * Use Open Inventor 6 lighting model for volume and isosurface lighting.
     */
    OIV6 = SoVolumeShader::OIV6,
    /**
     *
     * Use the equation specified by OpenGL to do volume
     * and isosurface lighting. This model should be
     * preferred because it responds to SoMaterial in the usual Open Inventor
     * way.
     */
    OPENGL = SoVolumeShader::OPENGL
  };

  /**
   * The edge detection algorithm used when #edgeDetect2D is TRUE, can work
   * on the image luminance, depth buffer and/or gradient. These enums can be combined
   * in the field #edgeDetect2DMethod.
   */
  enum EdgeDetect2DMethod {
    /** Edge detection will use the image's luminance. This method has a very little impact on speed. */
    LUMINANCE = 1,

    /** Edge detection will use the image's depth buffer. */
    DEPTH = 1 << 1,

    /** Edge detection will use the volume's gradient. These gradients are affected by
     * the #surfaceScalarExponent fied. This method is the most computationally expensive.
     */
    GRADIENT = 1 << 2
  };

  /**
   * Constructor
   */
  SoVolumeRenderingQuality();

  /**
  * Enable lighting computed on the GPU. Default is FALSE. @BR
  * NOTE: Only set the lighting field to TRUE in SoVolumeRenderingQuality or
  * SoVolumeRender. Do not set both #lighting fields to TRUE.
  */
  SoSFBool lighting;

  /**
  * Enable pre-integrated volume rendering. @BR
  * Pre-integrated rendering can significantly increase image quality
  * (at the cost of slightly lower performance). Default is FALSE.
  */
  SoSFBool preIntegrated;

  /**
   * Enable jittering. @BR
   * If set to TRUE, a random offset is added to texture
   * coordinates in order to decrease ringing artifacts (boundary edge artifacts) without the
   * cost of drawing a higher number of slices. Note: Jittering is only available for
   * pre-integrated rendering. For standard volume rendering mode, it has no effect.
   * Default is FALSE.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool jittering;

  /**
   * Enable cubic interpolation of data values. @BR
   * @warning Heavy GPU usage. Primarily useful for still image rendering.
   * Default is FALSE.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool cubicInterpolation;

  /**
   * Ignore all gradients with a magnitude less than the specified threshold. @BR
   * Default is 0, meaning that all gradients are used in the lighting computation.
   * Maximum useful value is 1.0, because gradient vectors are normalized.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat gradientThreshold;

  /**
   * Enable edge coloring. @BR
   * If TRUE, changes the color based on the gradient direction (normal).
   * Edges will be highlighted with the color specified in #edgeColor.
   * Areas where the normal (computed from the gradient) is facing the camera
   * will have an unmodified color, whereas areas where the normal
   * is more perpendicular to the view direction will tend towards
   * #edgeColor.  Default is FALSE.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool edgeColoring;

  /**
   * Color used to draw edges when #edgeColoring or #edgeDetect2D is TRUE.
   * Default is black (0,0,0).
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFColor edgeColor;

  /**
   * If this value is low, more edges will be detected.
   * Default is 0.2.
   * Min value is 0.
   * There is no max, but most of the time a value between 0 and 1 is good.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat edgeThreshold;

  /**
   * Enable boundary opacity. @BR
   * If TRUE, increases boundary opacity based on the gradient magnitude.
   * Default is FALSE.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool boundaryOpacity;

  /**
   * Applies when #boundaryOpacity is TRUE. If > 1, this increases the boundary opacity globally. If < 1, decreases it.
   * Default is 1.5.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat boundaryOpacityIntensity;

  /**
   * Applies when #boundaryOpacity is TRUE.
   * If this value is low (near 0), only regions with a high gradient will be enhanced.
   * Default is 1.5.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat boundaryOpacityThreshold;

  /**
   * Enable 2D edge detection. @BR
   * If this field is TRUE, a 2D edge detection algorithm is used
   * to highlight edges in the rendered image of the volume. Default is FALSE.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool edgeDetect2D;

  /**
   * Increase this value to decrease noise on silhouette edges.
   * 1 = remove all edges, 0 = remove nothing.
   * Default is 0.1
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat edgeDetect2DInnerThreshold;

  /**
   * Increase this value to decrease noise on edges in the volume.
   * 1 = remove all edges, 0 = remove nothing.
   * Default is 0.1
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat edgeDetect2DOuterThreshold;

  /**
   * Method used for 2D edge detection. @BR
   * Specifies the edge detection algorithm used when #edgeDetect2D is TRUE.
   * Edge detection can work on the image luminance, depth buffer and/or gradient.
   * For example, gradients may be too noisy to give interesting edges
   * and may be ignored with this field. The gradient method is also the slowest
   * (luminance being the fastest) because it needs more texture fetchs.
   * See #EdgeDetect2DMethod. Default is LUMINANCE. @BR
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBitMask edgeDetect2DMethod;

  /**
   * Specifies the algorithm used to compute gradients, for example,
   * normals for lighting.  Use enum #GradientQuality. Default is MEDIUM.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFEnum gradientQuality;

  /**
   * Sets the lighting model. 
   * Use enum #LightingModel. Default is OIV6.
   * @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFEnum lightingModel;

  /**
   * Controls interpolation of data values used for color lookup. @BR
   * If FALSE, interpolation is not done on data values used to access the colormap
   * but is still done when computing gradient for lighting. This may be used
   * to render a segmented dataset where interpolation is not appropriate.
   * Default is TRUE.
   * @BR
   * @FIELD_SINCE_OIV 7.2
   */
  SoSFBool colorInterpolation;

  /**
   * If this field is greater than or equal to 1, a surface with a small gradient will be less lighted
   * than a surface with a high gradient. The resulting color is a mix between the lighted voxel color and
   * the non-lighted voxel color (ie: the corresponding entry in the colormap).
   * If the value is less than 1, the field is ignored.
   * Values higher than 256 will apply lighting on almost all surfaces. For most datasets,
   * values between 2 and 16 should be enough.  Default is 0. @BR
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFFloat surfaceScalarExponent;

  /**
   * When unnormalizedGradientExponent is not 0, surfaces with high gradients will
   * be more lighted than surfaces with small gradients.
   * Voxels with small gradients will have less diffuse and specular than other with high gradients
   * (ie: ambient color will be the biggest contributor).
   * This lighting contribution
   * can be controlled with this field. If this value is high, smaller gradients will
   * contribute to lighting.
   * Values higher than 256 will apply lighting on almost all surfaces.
   * For most dataset, values between 2 and 16 should be enough.  Default is 0. @BR
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFFloat unnormalizedGradientExponent;

  /**
   * Allow correct interpolation when rendering segmented data. @BR
   * NOTE: Only available on SoVolumeIsosurface.
   * @FIELD_SINCE_OIV 8.5
   */
  SoSFBool segmentedInterpolation;

  /** 
   * Defines the iso distance used when #segmentedInterpolation is true. @BR
   * Default is 0.5. value must be in the range [0 .. 1]
   * NOTE: Only available on SoVolumeIsosurface.
   * @FIELD_SINCE_OIV 8.6
   */
  SoSFFloat segmentedInterpolationThreshold;

#ifndef HIDDEN_FROM_DOC
  SoINTERNAL public:
  void GLRender(SoGLRenderAction *action);
  virtual void doAction(SoAction *action);
  virtual void notify(SoNotList* list);

  // Initializes the classes.
  static void initClass();
  static void exitClass();

  /** Return gradient quality according to SoInteractiveComplexity */
  SoVolumeShader::GradientMethod getGradientMethod(SoState* state) const;

  /** Return edgeDetect2D field value according to SoInteractiveComplexity */
  SbBool hasEdgeDetect2d(SoState* state) const;

  /** Install textures needed for shaders */
  virtual void installTextures(SoGLRenderAction* action);

  /** Return main fragment filename according to state */
  virtual SbString getNeededFragmentMainFilename(SoState* state);

protected:
  virtual ~SoVolumeRenderingQuality();

  virtual void handleFieldChange(SoField* f);
#endif

private:

  enum FragMainPos
  {
    FRAG_VOLUME_RENDERING = 0,
    FRAG_VOLUME_RENDERING_PREINTEGRATED,
    FRAG_VOLUME_RENDERING_PREINTEGRATED_LIGHTED,
    FRAG_VOLUME_RENDERING_LIGHTED,
    FRAG_LAST
  };

  static const float DEFAULT_INNER_EDGE_THRESHOLD;
  static const float DEFAULT_OUTTER_EDGE_THRESHOLD;

  /** Disable edge2D if not supported */
  void checkAndUpdateEdge2DSupport(SoGLRenderAction* action);

  /** Return true if tf cache needs to be updated */
  bool updateTransferFunctionCache(SoGLRenderAction* action);

  /** Return lighting field value according to SoInteractiveComplexity */
  SbBool isLighted(SoState* state) const;

  /** Return edgeColoring field value according to SoInteractiveComplexity */
  SbBool hasEdgeColoring(SoState* state) const;

  /** Return boundaryOpacity field value according to SoInteractiveComplexity */
  SbBool hasBoundaryOpacity(SoState* state) const;

  //Fragment programs for each rendering modes
  SoFragmentShader* m_fragMains[FRAG_LAST];

  /**
   * Return the good SoFragmentShader according to active fields
   * and isInternalFragment
   */
  SoFragmentShader* getFragmentMain(SoState* state);

  /**
   * Put edgeDetect2DInnerThreshold and edgeDetect2DOuterThreshold
   * between 0. and 1. if needed
   */
  void clampEdgeDetect2dFields();

  /** Call needed update methods for fields using SoInteractiveComplexity */
  void setupBoundedFields(SoState *state);

  SoCache *m_tfCache;
  void addCacheDependencies(SoCache *cache, SoState *state);

  bool m_needUpdate;

  SoGLTexture *m_texPreIntegrated;

  //Create the preintegrated texture into unit "texture image unit max"-2
  void createPreIntegratedTexture(SoState *state);
};
/*----------------------------------------------------------------------------*/

#endif /*_SO_VOLUME_QUALITY_H_*/
