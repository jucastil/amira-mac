/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_VOLUME_RENDER_
#define  _SO_VOLUME_RENDER_

#include <Inventor/sensors/SoTimerSensor.h>
#include <Inventor/caches/SoCache.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbBox.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/map>

#include <VolumeViz/nodes/SoVolumeShape.h>

#include <VolumeViz/LDM/SoLDMTileID.h>

class SbProjection;
class SoFrameBufferObject;
class SoGLProgramGLSL;
class SoGLTexture;
class SoImageSpaceEdgeDetect;
class SoLDMTileID;
class SoLdmSubDivisionIsosurfacePolicy;
class SoLdmSubDivisionPolicy;
class SoLdmSubDivisionTransferFunctionPolicy;
class SoShaderParameter1f;
class SoShaderParameter1i;
class SoShaderParameter2f;
class SoShaderProgram;
class SoVolumeGroup;
class SoVolumeIsosurface;
class SoVolumeRenderInterface;
class SoVolumeRenderLdm;
class SoVolumeRenderPaging;
class SoVolumeRenderingQuality;
class SoVolumeStateVr;
class SoVolumeRenderDetail;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @VREXT Renders a data volume using direct volume rendering
 *
 * @ingroup VolumeVizNodes
 *
 * @DESCRIPTION
 *   This node draws the volume data defined by the current SoVolumeData node. For
 *   TEX3D and TEX2D rendering, this consists of drawing "slices" from the back to the
 *   front and compositing them according to the #composition field.
 *
 *   For a non-RGBA (scalar valued) volume,
 *   each voxel's RGBA value is determined by the current SoDataRange and SoTransferFunction.
 *   The current @B diffuse color @b and @B transparency @b (set, for example, with
 *   an SoMaterial node) modify the appearance of the slice.  This means that, for
 *   example, the current transparency can be used as a @I global alpha @i value
 *   to modulate the overall opacity of the slice.
 *   For an RGBA volume each voxel's RGBA value comes directly from the volume data.
 *
 *   Whether 2D or 3D textures are used is controlled by the SoVolumeData::storageHint field.
 *   Generally 3D textures should be used (better use of GPU memory).
 *   Using an SoVolumeRenderingQuality node or SoProjection node will automatically
 *   switch to 3D textures.
 *
 *   The #interpolation field controls how the textures are interpolated.
 *   The #numSlicesControl and #numSlices fields control how many slices are drawn.
 *   This effectively controls the "sampling rate" for the volume. Higher sampling
 *   rates (more slices) produce higher quality images, but reduce performance.
 *
 *   When using 3D textures for rendering, the #viewAlignedSlices field controls whether
 *   the slices are axis-aligned or view-aligned (perpendicular to the view vector).
 *   Generally view-aligned slices should be used (better image quality).
 *   Using SoVolumeIsoSurface, SoVolumeRenderingQuality or SoProjection nodes will
 *   automatically switch to view-aligned slices.
 *
 *   The SoVolumeRenderingQuality property node allows you to to enable GPU
 *   computed lighting (based on the first SoLight node in the scene graph),
 *   as well controlling rendering quality settings and edge enhancement options.
 *
 *   The SoVolumeIsosurface property node causes SoVolumeRender to actually display
 *   a GPU computed isosurface instead of volume rendering.
 *
 *   If rendering with a completely opaque color map, consider using an SoVolumeSkin node.
 *   It generates the same image with higher performance and less memory.
 *
 *   If using multiple SoVolumeRender nodes in the same scene (with non-opaque color
 *   map), consider using an SoVolumeGroup to ensure that the rendering of the volumes
 *   is merged correctly.  If combining multiple volumes using a single SoVolumeRender
 *   node see SoDataCompositor for data combining on the CPU and SoVolumeShader for
 *   combining (e.g. co-blending) on the GPU.  Also note that SoLDMDataTransform and
 *   SoVolumeTransform can be used to modify volume data "on the fly" for rendering.
 *
 *   Custom shaders: @BR
 *   The SoVolumeShader
 *   node allows custom shaders to be defined for special computation or rendering
 *   effects, including blending multiple volumes.  All of these features
 *   require programmable shader support on the GPU.  Be sure to use an
 *   SoMultiDataSeparator (instead of SoSeparator) when combining multiple volumes.
 *
 *   Lighting: @BR
 *   CPU computed lighting can be enabled using the #lighting field.  In this case
 *   the #lightDirection and #lightIntensity fields control the light.  Note that
 *   when lighting is computed on the CPU, RGBA textures are loaded on the GPU,
 *   so color map changes generally require re-loading all the data textures. @BR
 *   @B NOTE: @b This feature is obsolete. Use SoVolumeRenderingQuality::lighting instead.
 *
 *   Region of Interest: @BR
 *   The current SoROI (Region of Interest) node, if any, limits rendering to a
 *   subvolume.  The SoROI node's EXCLUSION_BOX mode can also be used to exclude
 *   a sub-region, forming what is sometimes called a "chair cut".  Note that the
 *   Region of Interest also limits @I data loading @i, so it is valuable when
 *   the total size of the volume exceeds the available system memory.
 *
 *   Clipping: @BR
 *   The SoUniformGridClipping and SoVolumeClippingGroup nodes may be used to clip
 *   the volume rendering against, respectively, a surface (defined by a height field)
 *   or any closed shape defined by a group of Open Inventor geometry nodes.
 *
 *   SoVolumeMask can be used to clip the data volume on a per-voxel basis. But the mask
 *   mechanism is much more powerful than that. Each region can have its own transfer
 *   function (color map) using SoTransferFunction nodes. Each region can also have its
 *   own draw style (volume rendering, isosurface or boundary) using SoVolumeDataDrawStyle
 *   nodes. Each region, including the original unmasked volume, is only visible if there
 *   exists a transfer function (SoTransferFunction) with the same id value.
 *
 *   Example rendering: @BR
 *
 *      @TABLE_1B
 *         @TR lighting = FALSE              @TD lighting = TRUE
 *         @TR @IMAGE lightoff.jpg
 *                   @TD @IMAGE lighton.jpg
 *         @TR composition = ALPHA_BLENDING  @TD composition = MAX_INTENSITY
 *         @TR @IMAGE compalpha.jpg
 *                   @TD @IMAGE compmax.jpg
 *      @TABLE_END
 *
 *  Geometric transforms: @BR
 *     The volume size (extent in 3D space) and orientation can be modified by
 *     transformation nodes in the scene graph just like any geometry.  For a volume
 *     this in turn modifies the appearance of volume rendering nodes like SoVolumeRender.
 *     However please @B note: @b The same transformation must be applied to the volume data node
 *     and all volume rendering nodes associated with that volume.  So effectively
 *     any transformation nodes that affect the volume must be placed @B before @b
 *     the volume data node.
 *
 *  Picking: @BR
 *  Since Open Inventor 8.6, the SoVolumeRender node (by default) uses the GPU to 
 *  compute the picked voxel during an SoRayPickAction. For this to work, the SoRayPickAction 
 *  must have its scene manager initialised using the method SoAction::setSceneManager().
 *  SoHandleEventAction does this automatically, so it is not necessary for the application
 *  to take any action when using (for example) an SoEventCallback node and calling the
 *  getPickedPoint() method.  However if the application creates its own SoRayPickAction
 *  then it should set the scene manager.  If no scene manager is specified, a warning
 *  message is issued and software picking is done.
 *  If necessary, using the GPU for volume picking may be disabled by setting the
 *  environment variable IVVR_GPU_PICKING to 0 (see SoPreferences).
 *
 *   Projection: @BR
 *   The SoVolumeRender node supports projected volume rendering, for example
 *   rendering a volume defined on a grid of latitude / longitude coordinates.
 *   Projection is enabled by adding an SoProjection node before the SoVolumeRender
 *   node (see SoProjection for more information about supported coordinate systems,
 *   ellipsoids and map projections). The projection quality versus speed ratio can
 *   be controlled using the new #projectedTileSubdivision field that defines how
 *   often each tile's geometry will be subdivided when projected.  This is important
 *   because only the corner points of the tiles are projected, not the individual
 *   voxels.  So subdividing the tiles provides a better approximation of the
 *   actual shape of the grid. Volume projection works with both regular (uniform
 *   voxel spacing) and rectilinear (non-uniform voxel spacing) grids.  SoProjection
 *   automatically selects 3D textures and view-aligned slices.
 *
 *   \warning 
 *   - Volume projection is incompatible with some rendering options enabled by this node. @BR
 *            The useEarlyZ and gpuVertexGen fields are ignored.
 *   - Volume projection is incompatible with some options enabled by
 *            the VolumeRenderingQuality node. @BR
 *            Do not enable the preIntegrated, jittering or edgeDetect2D fields.
 *   - Volume projection requires all culling to be disabled. @BR
 *            The following options in class SoLDMGlobalResourceParameters
 *            should be disabled: setScreenResolutionCulling (default is false), 
 *            setViewpointRefinement (default is TRUE) and setViewCulling (default is TRUE).
 *
 * @FILE_FORMAT_DEFAULT
 *    VolumeRender {
 *    @TABLE_FILE_FORMAT
 *       @TR interpolation      @TD LINEAR
 *       @TR composition        @TD ALPHA_BLENDING
 *       @TR lighting           @TD FALSE
 *       @TR lightDirection     @TD -1, -1, -1
 *       @TR lightIntensity     @TD 1
 *       @TR numSlices          @TD 0
 *       @TR numSlicesControl   @TD ALL
 *       @TR viewAlignedSlices  @TD FALSE
 *       @TR lowResMode         @TD DECREASE_NONE
 *       @TR lowScreenResolutionScale @TD 1
 *       @TR useEarlyZ          @TD FALSE
 *       @TR numEarlyZPasses    @TD 30
 *       @TR subdivideTile      @TD FALSE
 *       @TR gpuVertexGen       @TD FALSE
 *       @TR projectedTileSubdivision @TD 1
 *       @TR fixedNumSlicesInRoi @TD FALSE
 *       @TR opacityCorrection @TD TRUE
 *    @TABLE_END
 *    }
 *
 *
 * @ACTION_BEHAVIOR
 *    @B SoGLRenderAction @b @BR
 *       Draws a volume-rendered image based on current SoVolumeData.
 *
 *    @B SoGetBoundingBoxAction @b @BR
 *       Computes the bounding box that encloses the volume.
 *
 *    @B SoRayPickAction @b @BR
 *    Since Open Inventor version 8.5, picking always returns the first
 *    non-transparent voxel intersected by the pick ray. The old behavior
 *    can be restored by using an SoPickStyle node set to BOUNDING_BOX.
 *
 * @SEE_ALSO
 *    SoVolumeData,
 *    SoTransferFunction,
 *    SoROI,
 *    SoVolumeShader,
 *    SoVolumeIsosurface,
 *    SoVolumeRenderingQuality,
 *    SoProjection,
 *    SoVolumeRendering,
 *    SoUniformGridClipping,
 *    SoVolumeClippingGroup
 *
 *
 */

class VOLUMEVIZ_API SoVolumeRender : public SoVolumeShape {
  SO_NODE_HEADER( SoVolumeRender );

 public:

   /**
    * Method to use when moving in low resolution.
    */
   enum LowResMode
   {
  /**
   * No low resolution mode when moving.
   */
     DECREASE_NONE = 1,
  /**
   * Decrease the number of slices according to the SoComplexity
   * node only when moving. It has no effect if #numSlicesControl
   * is set to AUTOMATIC because this mode always uses
   *  the SoComplexity node to compute the number of slices to draw.
   */
     DECREASE_SLICES = 1 << 1,
  /**
   * Downscale the screen resolution of the volume when
   * moving by the factor defined in #lowScreenResolutionScale.
   */
     DECREASE_SCREEN_RESOLUTION = 1 << 2
   } ;

  /**
   * @deprecated. Use SoVolumeRenderingQuality::lighting field instead.
   * Indicates if lighting is required. Default is FALSE. @BR
   * NOTE: Better performance for lighting can be obtained using the SoVolumeRenderingQuality
   * node. Using SoVolumeRenderingQuality, lighting is determined by the first light
   * in the scene graph (similar to other geometry) and the lighting computation is done on
   * the GPU (therefore SoVolumeRenderingQuality requires programmable shaders).
   *
   * Using the #lighting field, lighting is determined by the #lightDirection field and
   * the lighting computation is done on the CPU. This requires RGBA textures to be loaded
   * on the GPU which uses more texture memory and requires more time to modify the
   * transfer function (color map) because textures must be reloaded.  Note that activating
   * or deactivating lighting when using TEX3D or TEX2D rendering will also normally force
   * the textures to be recreated, which may be slow.
   *
   * NOTE: Only set the lighting field to TRUE in SoVolumeRenderingQuality or
   * SoVolumeRender. Do not set both #lighting fields to TRUE.
   *
   * @DEPRECATED_SINCE_OIV 8.5
   */
  SoSFBool  lighting;

  /**
   * @deprecated. Use SoVolumeRenderingQuality::lighting field instead.
   * Light direction (relative to the volume). The default is (-1,-1,-1).
   * Only affects CPU computed lighting (i.e. when the #lighting field is TRUE).
   *
   * @DEPRECATED_SINCE_OIV 8.5
   */
  SoSFVec3f lightDirection;

  /**
   * @deprecated. Use SoVolumeRenderingQuality::lighting field instead.
   * Light intensity in the range [0-1]. The default is 1.
   * Only affects CPU computed lighting (i.e. when the #lighting field is TRUE).
   *
   * @DEPRECATED_SINCE_OIV 8.5
   */
  SoSFFloat lightIntensity;

  /** Number of Slices control mode */
    enum NumSlicesControl {
    /**
     *  Draw all slices @BR
     *  The number of slices depends on the viewing direction.
     */
    ALL,
    /**
     *  Draw the number of slices specified by the #numSlices field @BR
     *  The number of slices does not depend on the viewing direction.
     */
    MANUAL,
    /**
     * Draw the number of slices computed as follows: @BR
     * If @I numSlices @i is greater than zero, then @BR
     * n = @I complexity @i * 2 * @I numSlices @i @BR
     * where @I complexity @i comes from the #value field of the SoComplexity node
     * and @I numSlices @i comes from the #numSlices field.
     * The number of slices does not depend on the viewing direction.
     *
     * If @I numSlices @i is any value less than or equal to 0, the dimension of
     * the volume data is used instead of numSlices, so @BR
     * n = @I complexity @i * 2 * @I volumeDimension @i @BR
     * The number of slices depends on the viewing direction.
     *
     * The factor 2 is used because by default complexity is equal to
     * 0.5. So, by default, the behavior for numSlices greater than zero is the
     * same as MANUAL and the default behavior for numSlices less than or equal
     * to zero is the same as ALL. @BR
     * You can increase the complexity up to 1.0, which would double the number of
     * slices drawn.  You can decrease the complexity to reduce the number of
     * slices drawn.  The global alpha is corrected so that the brightness looks
     * the same.
     */
    AUTOMATIC,
    /**
     * Draw the number of slices computed as follows: @BR
     * n = @I complexity @i * 2 * @I volumeDataDimension[mainVisibleAxis] @i @BR
     * where @I complexity @i comes from the #value field of the SoComplexity node.
     * The number of slices depends on the viewing direction.
     * @ENUM_SINCE_OIV 8.1
     */
    MAIN_AXIS
  };

  /**
   * Controls how the number of slices to render is determined. @BR
   * Use enum #NumSlicesControl. Default is ALL.
   * Note that the number of "slices" in this context means the number
   * of texture mapped polygons that will be drawn to render the volume.
   * Generally increasing the number of polygons drawn will increase
   * the image quality, but (eventually) decrease the performance (frames
   * per second).
   */
  SoSFEnum  numSlicesControl;

  /**
   * Specifies the number of slices to render. @BR
   * The default is zero, which means to use the volume dimension when the
   * #numSlicesControl field is set to AUTOMATIC.
   *
   * NOTE: This value is not used if the #numSlicesControl field is set to ALL
   * (the default for that field).
   */
  SoSFInt32 numSlices;

  /**
   * Indicates if slices must be drawn in a view-aligned manner. This value is used
   * for 3D texturing only. Default is FALSE.
   *
   * NOTE: If an SoVolumeIsosurface, SoVolumeRenderingQuality or SoProjection node
   * applies to this node, this field is ignored and view-aligned slices are used.
   */
  SoSFBool viewAlignedSlices;

  /**
   * Sets the methods to use when moving in low resolution.
   *
   * - DECREASE_NONE: Default. Do not use low resolution mode when moving (i.e., when the
   *   viewer is moving the camera).
   *
   * - DECREASE_SLICES: Decrease the number of slices according to the SoComplexity node only when moving.
   *  It has no effect if #numSlicesControl is set to AUTOMATIC because in this case, VolumeViz always uses
   *  the SoComplexity node to compute the number of slices to draw.
   *
   * - DECREASE_SCREEN_RESOLUTION: Downscale the screen resolution of the volume when
   *   moving by the factor specified in #lowScreenResolutionScale.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBitMask lowResMode;

  /**
   * If #lowResMode is DECREASE_SCREEN_RESOLUTION, render the volume at a lower screen resolution.
   * when moving. The resolution used is the current screen resolution divided by
   * lowScreenResolutionScale.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFInt32 lowScreenResolutionScale;

  /**
   * If TRUE, stop computing when the pixel's cumulative opacity reaches 1.
   * This can increase performance when an expensive shader is being used.
   *
   * NOTE: When doing volume projection (SoProjection or subclasses), this field is ignored.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool useEarlyZ;

  /**
   * When #useEarlyZ is TRUE, pixels are tested for full opacity every N slices, where
   * N is the value of this field.
   *
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFInt32 numEarlyZPasses;

  /**
   * If TRUE, LDM tiles will be subdivided for rendering. Fully transparent sub-tiles won't
   * be rendered, thus increasing the speed of the rendering if an
   * expensive shader is being used. You should set #gpuVertexGen to TRUE when
   * using this option.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool subdivideTile;

  /**
   * If TRUE, slice vertices used for volume rendering are generated by the GPU instead of the
   * CPU. This can increase performance when a large number of slices is being used.
   *
   * NOTE: When doing volume projection (SoProjection or subclasses), this field is ignored.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFBool gpuVertexGen;

  /**
   * When this field is set to FALSE (the default), the number of slices
   * set by #numSlices is the number of slices visible in the ROI.
   * Therefore the number of slices drawn may change when the ROI size changes.
   * When TRUE, #numSlices is the number of slices in the whole volume.
   * So the slice density is constant, independent of the ROI size.
   *
   * By default value is set to FALSE.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.1
   */
  SoSFBool fixedNumSlicesInRoi;

  /**
   * When doing volume projection (see SoProjection), only the geometry (corner
   * vertices) of the LDM tiles are projected, not the individual voxels.
   * This can produce an imprecise projected volume when using large LDM tiles or
   * low resolution levels (where the LDM tiles are larger).
   *
   * This field controls how many times the tile geometry will be subdivided
   * (producing more vertices) before being projected. Subdivision gives a smoother,
   * more accurage shape, but requires much more computational power and may
   * reduce rendering performance.  The default value is 1 (subdivide once).
   *
   * @BR @BR
   * @FIELD_SINCE_OIV 7.1
   */
  SoSFInt32 projectedTileSubdivision;

  /**
   * Controls whether opacity correction is done. @BR
   * If TRUE, opacity is automatically adjusted to give similar appearance
   * no matter how many slices are drawn. If FALSE, opacity is not corrected
   * and increasing the number of slices will increase the opacity. Default is TRUE.
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBool opacityCorrection;

  /**
   * Constructor.
   */
  SoVolumeRender();


  /**
   * Abort code for callback
   */
  enum AbortCode {
    /**
     *  Continue rendering as usual.
     */
    CONTINUE,
    /**
     *  The render action of the SoVolumeRender node is aborted. The render action
     * continues for the remaining part of the scene graph.
     */
    ABORT,
    /**
     *  The current slice is not drawn. Rendering continues with the next slice.
     */
    SKIP
  };

  /**
   * [OIV-WRAPPER NAME{RenderAbortCB}]
   */
  typedef AbortCode SoVolumeRenderAbortCB(int totalElems, int thisElem, void *userData);

  /**
   * Sets \oivnetdoc delegate \else callback \endoivnetdoc to call during texture map rendering to test for an abort
   * condition. When 2D or 3D texture maps are used for rendering, it will be called for each element that is rendered.
   *
   * In the case of LDM, an element is a tile, @B totalElems @b is the number of tiles that
   * will be drawn, and @B thisElem @b is the number (counting from one) of the next tile
   * to be drawn. The quotient @B thisElem @b / @B totalElems @b represents the progress of
   * the volume rendering process.
   *
   * In the non-LDM case, an element is a slice, @B totalElems @b is the number of slices
   * that will be drawn, and @B thisElem @b is the number (counting from one) of the next
   * slice to be drawn. The quotient @B thisElem @b / @B totalElems@b represents the progress
   * of the volume rendering process.
   *
   * This allows applications to terminate rendering of this node prematurely if some
   * condition occurs. It does not terminate traversal of the scene graph. (For that
   * use the SoGLRenderAction abort callback.) The callback function should return
   * one of the AbortCode codes to indicate whether rendering should continue.
   */
  void setAbortCallback( SoVolumeRenderAbortCB *func, void *userData = NULL);

/*****************************************************************************/
SoEXTENDER public:
  /** @copydoc SoVolumeShape::computeBBox */
  virtual void computeBBox(SoAction *, SbBox3f &box, SbVec3f &center);

  /** @copydoc SoVolumeShape::rayPick */
  virtual void rayPick(SoRayPickAction *action);

/*****************************************************************************/
SoINTERNAL public:

  /** @copydoc SoVolumeShape::initClass */
  static void initClass();

  /** @copydoc SoVolumeShape::exitClass */
  static void exitClass();

  /**
  * Return the fbo used for rendering
  */
  inline SoFrameBufferObject* getRenderingFbo();

  /**
   * Return the volume rendering quality currently in the state if any.
   */
  SoVolumeRenderingQuality* getVolumeRenderingQuality();

  /**
   * Return the min and max of Z in viewspace
   */
  inline SbVec2f getMinMaxViewSpaceZ();

  /**
   * Se slice density uniform
   */
  void setSliceDensityUniform(const float density) const;

/*****************************************************************************/
 protected:
   // Destructor
   virtual ~SoVolumeRender();

   void generatePrimitives(SoAction *action);

   void doRendering(SoGLRenderAction *action);

   void setupVolumeRenderInterface(SoState* state);

   SoDetail *createTriangleDetail(SoRayPickAction *,
                                  const SoPrimitiveVertex *v1,
                                  const SoPrimitiveVertex *,
                                  const SoPrimitiveVertex *,
                                  SoPickedPoint *);

   /**
    * Begin offscreen rendering
    */
   void beginOffscreenRendering();

   /**
    * End offscreen rendering
    */
   void endOffscreenRendering();

   /**
    * Activate front to back rendering
    */
   void setupFrontToBackGlState();

SoINTERNAL protected:
   /** Setup the fake roi for volume clipping */
  virtual void ldmAction(SoLdmValuationAction* action);

/*****************************************************************************/
private:
   /** Return the current volume data */
   static SoVolumeData* getVolumeData(SoState* state);

   /** Fill detail with all necessary infos*/
   void fillDetail(SoRayPickAction* rpa, SoVolumeRenderDetail* detail, SoVolumeData* vd);

   /** Draw volume bbox in zbuffer */
   void drawBboxInDepthBuffer(SoGLRenderAction* action, SoGLTexture* renderedVolume);

   /** Return true if subtiles can be used */
   static bool canSubdivideTiles(SoState* state);

  /**
   * True if earlyZ can be used
   */
  bool m_useEarlyZ;

  SoVolumeGroup* m_volumeGroup;

  SoVolumeRenderAbortCB	*m_abortCBfunc;
  void  *m_abortCBuserData;
  void   GLRenderTex2D3D(SoGLRenderAction* action);

  /**
   * Update textures dependent of viewport
   */
  void onViewportChange(SoState* state);

  /**
   * Called when user stop or start interaction
   */
   void onUserInteractionChange(SoState*state, bool stopMoving);

   /**
    * Do volume rendering in a fbo if needed (earlyZ, low res move)
    */
   void useOffscreenRendering(SoState* state);

   /**
    * Update all needed texture for offscreen rendering
    */
   void updateRttTextures(SoState* state);

   /**
    * Create all needed textures
    */
   void initTextures(SoState* state);

   /**
    * Copy z-buffer to the specified texture
    */
   void copyZBufferToTexture(SoGLTexture* tex);

   /**
    * Copy texture to z-buffer
    */
   void copyTextureToZbuffer(SoGLTexture* tex);

   /**
    * Increase size of the specified texture if needed
    */
   void updateTexSize(SoState* state, SoGLTexture* tex, const SbVec2i32 &size);

   /**
    * Create a RGBA or depth texture.
    */
   void createTexture(SoState* state, SoGLTexture* tex, const SbVec2i32 &size,
                      GLenum format);

   /**
    * Attach color buffer
    */
   void setUpFboForColor(SoState* state);

  /**
   * Create internal shaders
   */
   void initInternalShaders();

  /**
   * Merge final render with current scene
   */
   void composeWithScene(SoGLRenderAction* action, SoGLTexture* tex);

  void GLRenderTex2D3DLDMSortedTiles(SoState* state, const SbMatrix& mpvmx,
                                     int Zaxis, float sliceSpacing, float sliceOffset,
                                     const SoLDM::TileIdVector& tiles,
                                     const std::vector<SbBox3i32>& boxes,
                                     const SbVec3f& eyeAxis, int textype,
                                     const SbVec3f& scale);
  void GLRenderTex2D3DLDMUnsortedTiles(SoState* state, const SbMatrix& mpvmx,
                                       int Zaxis, float sliceSpacing, float sliceOffset,
                                       const SoLDM::TileIdVector& tiles,
                                       const SbBox3i32 * const boxes, int numBoxes,
                                       const SbVec3f& eyeAxis, int textype, int numSliceToDraw,
                                       float min, float max,
                                       const SbVec3f& scale);

  /**
   * Return true if near plane intersect given bbox
   */
  bool intersectBboxNearPlane(const SbBox3f &bbox);

  void checkEarlyZ();

  /** Return true if rendering offscreen */
  bool isUsingOffscreenRendering() const;

  /**
   * Z Min and max in viewspace
   */
  SbVec2f m_minMaxViewSpaceZ;

  SoImageSpaceEdgeDetect* m_imageSpaceEdgeDetect;
  static void imageSpaceEdgeDetectCb(SoGLRenderAction* action, void* data);

  // Used for SoVolumeIsosurface and SoVolumeRenderingQuality
  bool m_forceViewAligned;

  bool m_useVertexArray; // whether draw tile should pack all vertices in one opengl call.

  bool m_useOffscreenRendering;
  SoFrameBufferObject* m_fbo;
  SoGLTexture* m_rttColor;
  SoGLTexture* m_rttDepth;
  SoGLTexture* m_copiedDepth;

  SoShaderProgram* m_copyZShader;

  /** Render at 1/m_vpScale of the viewport size */
  int m_vpScale;
  int m_lowScreenResScale;

  SoShaderProgram* m_composeShader;
  SoShaderProgram* m_earlyZShader;
  SoShaderParameter1i *m_opacityTex;
  SoGLProgramGLSL* m_binaryOpacityComposeShader;

  SoShaderProgram* m_earlyZInBBoxShader;

  SoShaderParameter2f* m_vpSizeParameter;
  SoShaderParameter1f* m_vvizZNear;

  size_t m_numEarlyPasses;

  SoVolumeIsosurface* m_volumeIsosurface;

  //Check if not moving
  SoTimerSensor m_checkMoveTimer;
  static void checkMoveCB(void *data, SoSensor *sensor);

  /**
   * Delete all shaders, fbo and textures used for some effects
   */
  void deleteShadersFboTextures();

  /**
   * Compute the min and max of the distance between the eye and the volume
   * bounding box
   */
  void computeMinMaxViewSpaceZ();

  /**
   * Update texture size if lowScreenResolutionScale has changed
   */
  void updateLowResScale();

  /**
   * Fetch texture unit number for earlyz
   */
  void initTextureUnits();

  /** Return true if framebuffer precision changed */
  bool hasFramebufferPrecisionChanged() const;

  bool m_useLowResMove;
  bool m_useLowNumSliceMove;

  bool m_showEarlyZ;

  SoVolumeRenderLdm* m_vrLdm;
  SoVolumeRenderPaging* m_vrPaging;
  SoVolumeRenderInterface* m_vri;

  bool m_initTextureUnitsDone;

  bool m_frontToBackComposition;
  int m_texType;

  SoVolumeStateVr* m_vs;

  SoFrameBufferObject* m_fboMultisampleBlit;

  friend class SoVolumeRenderInterface;
};

/*****************************************************************************/
SoFrameBufferObject*
SoVolumeRender::getRenderingFbo()
{
  return m_fbo;
}

/*****************************************************************************/
SbVec2f
SoVolumeRender::getMinMaxViewSpaceZ()
{
  return m_minMaxViewSpaceZ;
}

#if defined(_WIN32)
#pragma warning( pop )
#endif

#endif // _SO_VOLUME_RENDER_
