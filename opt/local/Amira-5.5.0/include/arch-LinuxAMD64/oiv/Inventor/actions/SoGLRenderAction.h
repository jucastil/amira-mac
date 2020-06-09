/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GL_RENDER_ACTION_
#define  _SO_GL_RENDER_ACTION_

#include <Inventor/SbViewportRegion.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoDecimationTypeElement.h>
#include <Inventor/nodes/SoTransparencyType.h>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SbBox3f;
class SoGetBoundingBoxAction;
class SoGLDepthPeeling ;
class SoCamera ;
class SoNodeSensor;
class SoBufferRegion;
class SoSeparator;
class SoSearchStepAction;
class SoGLSortTriangles;
class SoGLRenderActionSync;
class SoGLRenderActionImpl;
/**
 * Callback functions used between rendering passes should be of this type.
 * [OIV-WRAPPER NAME{PassCB}]
 */
typedef void    SoGLRenderPassCB(void *userData);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLRenderAction
//
//  GL rendering action.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Renders a scene graph using OpenGL.
 *
 * @ingroup actions
 *
 * @DESCRIPTION
 *   This class traverses a scene graph and renders it using the OpenGL graphics
 *   library. It assumes that a valid window has been created and initialized for
 *   proper OpenGL rendering. The SoWinRenderArea class or any of its subclasses may
 *   be used to create such a window.
 *
 *   This class has many options for rendering, but the most commonly used
 *   methods are exposed by the viewer classes (SoWin, SoXt, SoQt) for convenience.
 *   The viewer classes automatically create a render action for you.
 *
 *   @B Traversal order @b @BR
 *   In most cases objects are rendered during the SoGLRenderAction
 *   traversal of the scene graph, in the order they are encountered
 *   during the traversal. However rendering of some objects may be
 *   delayed until after the scene graph traversal, particularly
 *   transparent objects.
 *
 *   A transparent object is an object:
 *   - With a material that has a transparency value set
 *     either by a material node or a vertex property node.@BR
 *     or @BR
 *   - With a texture that has an alpha value < 1.@BR
 *
 *  Open Inventor automatically detects these cases.
 *
 *   The rendering order for transparent
 *   objects depends on the transparency "type" (transparency
 *   rendering method) assigned to each object. A transparency
 *   type may be set for the entire scene graph using the
 *   SoGLRenderAction or SoWinRenderArea method. The transparency
 *   type may also be modified during traversal using the
 *   SoTransparencyType node.
 *
 * There are several special cases including:
 *
 *   - Transparency type SORTED_LAYERS_BLEND.@BR
 *     The environment variable OIV_NO_SHADER_LAYERS_BLEND allows you to disable the use
 *     of a fragment shader for this technique.
 *
 *   - SoRenderList nodes, e.g. SoOctreeOrdering.@BR
 *     Objects that are delayed are generally rendered in the sequence below,
 *     but other objects are rendered in various specific orders, not in scene
 *     graph order. See the specific node for details.
 *
 * The general rendering order is:

 * @OL
 *  @LI Scene graph traversal @BR
 *     All objects not in one of the following categories, specifically
 *     including transparent
 *     objects using the SCREEN_DOOR, ADD, or BLEND transparency types.
 *
 *  @LI FastEdit KEEP_ZBUFFER objects @BR
 *     Objects under an SoSeparator node with fastEditing field set to
 *     KEEP_ZBUFFER.
 *
 *  @LI Transparent delayed objects @BR
 *     Objects using transparency types DELAYED_BLEND or DELAYED_ADD. Note that
 *     by default the OpenGL depth buffer is not updated while rendering these
 *     objects.
 *
 *  @LI Transparent sorted objects @BR
 *     Objects using transparency types SORTED_OBJECT_BLEND or
 *     SORTED_OBJECT_ADD.
 *     These objects are sorted by the distance of their bounding box from the
 *     camera, then rendered in back-to-front order. Note that
 *     by default the OpenGL depth buffer is not updated while rendering these
 *     objects.
 *
 *  @LI Transparent sorted triangles by object @BR
 *     Objects using transparency types SORTED_OBJECT_TRIANGLES_ADD
 *     or SORTED_OBJECT_TRIANGLES_BLEND. First, objects are sorted according to their
 *     projected position on the current sorting axis. Then the
 *     triangles are sorted within each object and rendered object by object.
 *
 *  @LI Transparent sorted triangles @BR
 *     Objects using transparency types SORTED_TRIANGLES_ADD
 *     or SORTED_TRIANGLES_BLEND. All of the triangles for all of the objects
 *     in the scene are sorted according to their projected position on the current
 *     sorting axis. The triangles are rendered in order, triangle by triangle,
 *     regardless of the object they belong to.
 *
 *  @LI Annotation delayed objects @BR
 *     Objects under an SoAnnotation node.
 *
 *  @LI FastEdit CLEAR_ZBUFFER objects @BR
 *     Objects under an SoSeparator node with fastEditing field set to
 *     CLEAR_ZBUFFER.
 *
 * @LI Front buffer objects @BR
 *     Objects under an SoFrontBufferGroup (after the buffer swap).
 *
 * @ol
 *
 * @B Elements @b @BR
 * Sets: SoDecimationTypeElement, SoDecimationPercentageElement,
 *       SoGLUpdateAreaElement, SoGLRenderPassElement,
 *       SoViewportRegionElement, SoLogicalViewportElement
 *
 * @SEE_ALSO
 *    SoSeparator,
 *    SoWinRenderArea
 *
 *
 */

class INVENTOR_API SoGLRenderAction : public SoAction {

  SO_ACTION_HEADER(SoGLRenderAction);

 public:

  /** Various levels of transparency rendering quality */
  enum TransparencyType {
    /**
     * Uses stipple patterns for screen-door transparency. @BR
     */
    SCREEN_DOOR = SoTransparencyType::SCREEN_DOOR,

    /**
     * Uses additive alpha blending. @BR
     */
    ADD = SoTransparencyType::ADD,

    /**
     * Uses multiplicative alpha blending. @BR
     */
    BLEND = SoTransparencyType::BLEND,

    /**
     * Uses additive blending, rendering all transparent objects after opaque ones. @BR
     */
    DELAYED_ADD = SoTransparencyType::DELAYED_ADD,

    /**
     * Uses multiplicative alpha blending, rendering all transparent objects after
     * opaque ones. @BR
     */
    DELAYED_BLEND = SoTransparencyType::DELAYED_BLEND,

    /**
     * Same as DELAYED_ADD, but sorts transparent objects by distances of bounding
     * boxes from camera. @BR
     */
    SORTED_OBJECT_ADD = SoTransparencyType::SORTED_OBJECT_ADD,

    /**
     * Same as DELAYED_BLEND, but sorts transparent objects by distances of bounding
     * boxes from camera. @BR
     */
    SORTED_OBJECT_BLEND = SoTransparencyType::SORTED_OBJECT_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the transparent triangles of all objects of the scene are collected,
     * and then sorted by triangle position.
     * - We recommend this transparency type when transparent objects may
     * intersect other transparent objects.
     * - Performance for this type of transparency depends on the current
     * axis sorting and on the number of triangles that intersect the
     * triangles of other objects.
     * - Best performance is comparable to other delayed transparency types and
     * occurs when the objects are sorted in the same way as they are in the scene graph,
     * and when there is no intersection between objects.
     * - In the worst case, this kind of transparency is very time consuming. Unfavorable
     * cases occur when the projection of objects on the current sorting axis
     * lets appear a lot of mixed triangles between each objects.
     * In this case
     * the object rendering is fragmented and the number of traversals to render
     * transparent objects scene is the number of fragments. In the worst case, the number of
     * fragments is equal to the number of transparent triangles in these objects.
     * - See setSortedTrianglesSortFrequency() and setSortedTrianglesNumCaches()
     * for information on managing the triangle sorting caches and the sorting frequency.
     *
     * @BR
     */
    SORTED_TRIANGLES_ADD = SoTransparencyType::SORTED_TRIANGLES_ADD,

    /**
     * Same as SORTED_TRIANGLES_ADD, but uses multiplicative alpha blending.
     *
     * NOTE: Triangles are sorted according to their barycenter; in some cases
     * this sort can fail.
     *
     * @BR
     */
    SORTED_TRIANGLES_BLEND = SoTransparencyType::SORTED_TRIANGLES_BLEND,

    /**
     * Renders all the transparent triangles of the scene using additive blending.
     * All of the triangles of all transparent objects of the scene are
     * collected and then sorted by object.
     * - We recommend this transparency type when the different transparent objects
     * are not intersecting.
     * - In the best case, performance for this type of transparency is comparable to
     * the other delayed transparency types. This case happens when the sorted objects
     * are found in the same order as the scene graph order. In this best case, the rendering
     * is made by only one traversal.
     * - In the worst case (object sorting is reverse of scene graph traversal), performance
     * depends on the number of independent transparent objects to render. In this worst case,
     * the number of traversal to render the scene is equal to the number of transparent objects.
     * - See setSortedTrianglesSortFrequency() and setSortedTrianglesNumCaches()
     * for information on managing the triangle sorting caches and the sorting frequency.
     *
     * @BR
     */
    SORTED_OBJECT_TRIANGLES_ADD = SoTransparencyType::SORTED_OBJECT_TRIANGLES_ADD,

    /**
     * Same as SORTED_OBJECT_TRIANGLES_ADD, but uses multiplicative alpha blending.
     *
     * NOTE: Triangles are sorted according to their barycenter; in some cases
     * this sort can fail.
     *
     * @BR
     */
    SORTED_OBJECT_TRIANGLES_BLEND = SoTransparencyType::SORTED_OBJECT_TRIANGLES_BLEND,

    /**
     * Uses a fragment-level depth sorting technique. This gives good results
     * for complex transparent objects.
     * @B Multi-Texture@b, @B Texture Environment Combine@b, @B Depth texture@b,
     * and @B Shadow @b OpenGL extensions
     * must be supported by your graphics board.
     * All these extensions are standard with OpenGL 1.4.
     * If the graphics board does not support these extensions,
     * behaves as if SORTED_OBJECT_BLEND was set. @BR
     * The method setSortedLayersNumPasses() allows you to set the number of
     * rendering passes for more correct transparency. Usually, four passes
     * gives good results.
     *
     * Reserved texture units: @BR
     * This mode reserves some texture units for internal use.  When fragment
     * programs are available (the usual case), two texture units are reserved,
     * else one unit is reserved. The first reserved texture unit may be specified
     * using environment variable OIV_SORTED_LAYERS_TEXTURE_UNIT (see SoPreferences).
     * The second unit is firstUnit-1.  If OIV_SORTED_LAYERS_TEXTURE_UNIT is not
     * set, the first unit is SoFragmentShader::getMaxTextureImageUnit()-1 when
     * fragment programs are available, else SoTextureUnit::getMaxTextureUnit()-1.
     *
     * @B Limitations: @b
     *  - This transparency type does not work with VolumeViz nodes. @BR
     *    Use DELAYED_SORTED_LAYERS_BLEND instead.
     *  - This transparency type is not compatible with interlaced stereo.
     *  - Texturing on transparent objects is limited to one texture and to MODULATE mode.
     *
     * @BR
     */
    SORTED_LAYERS_BLEND = SoTransparencyType::SORTED_LAYERS_BLEND,

    /**
     * Same as SORTED_LAYERS_BLEND but rendering all transparent objects after opaque ones.
     *
     * Reserved texture units: @BR
     * Same as SORTED_LAYERS_BLEND except use OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT to
     * specify the first reserved texture unit. If OIV_DELAYED_SORTED_LAYERS_TEXTURE_UNIT
     * is not set, uses OIV_SORTED_LAYERS_TEXTURE_UNIT.
     */
    DELAYED_SORTED_LAYERS_BLEND = SoTransparencyType::DELAYED_SORTED_LAYERS_BLEND
  };

  /**
   * Fast edit traversal types. See SoSeparator for additional info on
   * fast editing. @BR
   * In the following description, we will call @B FE the sub-scene graph
   * allowing the fast editing@b feature,@BR
   * and @B NFE the non-fast editing sub-scene graph@b and consider the following scene graph:
   * <PRE>
   * Separator {
   *   Separator {
	 *     fastEditing # ( != DISABLE to activate )
   *     Translation {}
   *     Cube{}
   *   }
   *   Separator {
   *     Translation {} Sphere{}
   *     Translation {} Sphere{}
   *     Translation {} Sphere{}
   *   }
   * }
   * </PRE>
   */
  enum FastEditSavePolicy {
    /**
     * Fast editing is disabled.
     * @BR
     * @IMAGE FE_Disable.jpg
     * @BR
     */
    DISABLE,

    /**
     * The fast edit feature is available. The image buffer
     * (and possibly the depth buffer, depending on the value
     * of the SoSeparator::fastEditing field) is saved each time
     * the scene graph is redrawn.
     *
     * We recommend using the EACH_FRAME flag when manipulating a very large
     * main scene graph. In this case, the time used for saving the buffer(s)
     * is insignificant compared to the time to draw the scene.
     * EACH_FRAME is recommended as well when the fast editing sub-scene graph
     * is frequently modified: the user interactivity is better with the fast edit
     * sub-scene graph even though the global scene frame rate may slow down.
     * @BR
     * @IMAGE FE_Each_Frame.jpg
     * @BR
     */
    EACH_FRAME,

    /**
     * The fast edit feature is available. No buffer save is made during ordinary scene rendering.
     * When a change to the fast editing sub-scene graph occurs, the entire scene is first
     * rendered and saved, and then the fast edit nodes are drawn. During the next rendering,
     * only the fast edit nodes are drawn. So, using this flag implies you need one more
     * full scene rendering before starting to move your fast edit sub-scene graph interactively.
     * It would be better to use WHEN_NEEDED when the fast editing sub-scene graph changes
     * very rarely. In this case you will be able to render the scene at full speed
     * because extra time will not be spent saving the image buffer.
     * @BR
     * @IMAGE FE_When_Needed.jpg
     * @BR
     */
    WHEN_NEEDED
  };

  /** Possible return codes from a render abort callback */
  enum AbortCode {
    /**
     * Continue traversal as usual
     */
    CONTINUE,

    /**
     *  Stop traversing the rest of the graph
     */
    ABORT,

    /**
     *  Do not traverse this node or its children, but continue
     */
    PRUNE,

    /**
     *  Delay rendering of this node until the second pass
     */
    DELAY
  };

  /** Callback functions for render abort should be of this type.
   * This typedef is defined within the class, since it needs to
   * refer to the AbortCode enumerated type.
   * [OIV-WRAPPER NAME{AbortCB}]
   */
  typedef AbortCode SoGLRenderAbortCB(void *userData);

  /** Invalidate cache mode */
    enum InvalidateCacheMode {
    /**
     * (Default) Render caches are handled normally. See #setInvalidateCacheMode().
     */
    OFF,

    /**
     *  Render caches are invalidated for each SoSeparator node before
     *  its children are traversed. The invalidate
     *  cache mode is automatically set to OFF after traversal. See #setInvalidateCacheMode().
     */
    ONCE,

    /**
     * Render caches are invalidated for each SoSeparator node before
     * its children are traversed. See #setInvalidateCacheMode().
     */
    ALWAYS
  };

  /**
   * Constructor. The parameter defines the viewport region into which rendering will
   * take place.
   */
  SoGLRenderAction(const SbViewportRegion &viewportRegion);

#ifndef HIDDEN_FROM_DOC
  // Destructor
  virtual ~SoGLRenderAction();
#endif // HIDDEN_FROM_DOC

  /**
   * Changes viewport region to use for rendering.
   */
  void                setViewportRegion(const SbViewportRegion &newRegion);

  /**
   * Returns viewport region to use for rendering.
   */
  const SbViewportRegion &getViewportRegion() const   { return vpRegion; }

  /**
   * Sets current logical viewport region to use for rendering.
   * Setting an empty viewport region (0,0) unsets the logical viewport.
   */
  void                setLogicalViewportRegion(const SbViewportRegion &newLogicalRegion);

  /**
   * Returns current logical viewport region
   */
  const SbViewportRegion &getLogicalViewportRegion() const    { return vpLogicalRegion; }

  /**
   * Sets the current update area, which is the rectangular area of the
   * viewport region that will actually be rendered into. This can be used for
   * partial updates in applications that can manage them. The update area is
   * specified in normalized viewport coordinates, where (0,0) is the lower left
   * corner of the viewport and (1,1) is the upper right corner. The area is
   * specified or returned as an origin and a size.
   */
  void setUpdateArea(const SbVec2f &origin, const SbVec2f &size);

  /**
   * Returns the current update area. See setUpdateArea() for details.
   */
  void                getUpdateArea(SbVec2f &origin, SbVec2f &size) const;

  /**
   * Sets callback to call during rendering to test for an abort condition. It will
   * be called for each node that is traversed. This allows applications to terminate
   * rendering prematurely if some condition occurs. The callback function should
   * return one of the AbortCode codes to indicate whether traversal should continue.
   * Use of the various codes in a callback can allow applications to modify Open
   * Inventor's default order of rendering objects in a scene graph.
   */
  void setAbortCallback(SoGLRenderAbortCB *func, void *userData)
    { abortCB = func; abortData = userData; }

  /**
   * Sets transparency quality level to use when rendering. The default is
   * SCREEN_DOOR. Note that SCREEN_DOOR transparency does not work when
   * transparency values are specified for each vertex of a shape nor when
   * transparent textures are used. In these cases, use one of the other
   * transparency types.
   *
   * The default value can be set using the environment variable OIV_TRANSPARENCY_TYPE.
   * Valid values are: SCREEN_DOOR, ADD, DELAYED_ADD, SORTED_OBJECT_ADD, BLEND,
   * DELAYED_BLEND, SORTED_OBJECT_BLEND, SORTED_TRIANGLES_ADD,
   * SORTED_TRIANGLES_BLEND, SORTED_OBJECT_TRIANGLES_ADD,
   * SORTED_OBJECT_TRIANGLES_BLEND, SORTED_LAYERS_BLEND.
   */
  void                setTransparencyType(TransparencyType type);

  /**
   * Returns transparency quality level to use when rendering.
   */
  TransparencyType    getTransparencyType() const     { return transpType; }

  /**
   * Sets fast editing save policy to use when rendering. The default is DISABLE.
   * Valid values are DISABLE, EACH_FRAME, and WHEN_NEEDED. See SoSeparator.
   *
   * If fastEditDelayedObjects is set to TRUE, delayed objects won't be redrawn
   * when editing the scene graph. It means that the composition between delayed
   * transparent objects and the fast edit scene graph won't be correct, but
   * rendering will be much faster if there are a lot of transparent objects.
   *
   * @B Limitations:@b
   * Using fast edit can lead to visual artifacts when overlay support is enabled.
   * In this case, we recommend to set the OIV_BUFFER_REGION_ENABLE environment
   * variable to 0. The rendering performance of fast edit will be somewhat lower, but
   * resulting rendering will be correct.
   */
  void setFastEditSavePolicy(FastEditSavePolicy policy, SbBool fastEditDelayedObjects = FALSE);

  /**
   * Returns fast editing save policy used when rendering.
   */
  FastEditSavePolicy  getFastEditSavePolicy() const { return fastEditPolicy; }


  /**
   *
   * Sets smoothing flag. When on, smoothing uses OpenGL's line- and
   * point-smoothing features to provide cheap antialiasing of lines and points. The
   * default is FALSE.
   *
   * The default value can be set using the environment variable
   * OIV_GL_SMOOTHING (0 = FALSE, 1 = TRUE).
   */
  void                setSmoothing(SbBool smooth);

  /**
   * Returns smoothing flag.
   */
  SbBool              isSmoothing() const             { return doSmooth; }

  /**
   * Sets number of rendering passes for multipass antialiasing. Specifying more
   * than one pass will result in antialiasing of the rendered scene, using OpenGL's
   * accumulation buffer. (Camera nodes typically move their viewpoints a little bit
   * for each pass to achieve the antialiasing.) Each additional pass provides better
   * antialiasing, but requires more rendering time. The default is 1.
   *
   * The default value can be set using the environment variable
   * OIV_NUM_RENDER_PASSES.
   *
   * NOTE: Multipass antialiasing can have very poor performance for large scenes.
   * Full-scene antialiasing (multi-sample) is recommended when the hardware
   * supports it. See SoFullSceneAntialiasing.
   */
  void                setNumPasses(int num)           { numPasses = num; }

  /**
   * Gets number of rendering passes for multipass rendering.
   */
  int                 getNumPasses() const            { return numPasses; }

  /**
   * Sets a flag indicating whether intermediate results are displayed after
   * each antialiasing pass for progressive improvement (default is FALSE).
   */
  void                setPassUpdate(SbBool flag)      { passUpdate = flag; }

  /**
   * Returns a flag indicating whether intermediate results are displayed after
   * each antialiasing pass for progressive improvement.
   *
   * The default value can be set using the environment variable
   * OIV_ANTIALIAS_PASS_UPDATE.
   */
  SbBool              isPassUpdate() const            { return passUpdate; }

  /**
   * Sets a callback function to invoke between passes when antialiasing. Passing
   * NULL (which is the default state) will cause a clear of the color and depth
   * buffers to be performed.
   */
  void                setPassCallback(SoGLRenderPassCB *func, void *userData)
    { passCB = func; passData = userData; }

  /**
   * Sets the OpenGL cache context. A cache context is just an integer
   * identifying when OpenGL display lists (which are used for render caching) can be
   * shared between render actions; for example, see the documentation on GLX
   * contexts for information on when OpenGL display lists can be shared between GLX
   * windows.  See generateCacheContext().
   * Note: The value 0xFFFFFFFF (~0) is reserved to represent an undefined id.
   */
  void setCacheContext(uint32_t context);

  /**
   * Returns the OpenGL cache context id for this action.
   */
  uint32_t getCacheContext() const;

  /**
   * Generates and returns a new cache context id. The returned cache context id can then be
   * used to pass to the setCacheContext() method call.
   */
  static uint32_t generateCacheContext();

  /**
   * Returns TRUE if the specified cache context id is currently used by any SoGLRenderAction.
   */
  static bool isUsedCacheContext( uint32_t context );

  /**
   *
   * Sets the number of rendering passes used when
   * transparency type is #SORTED_LAYERS_BLEND or #DELAYED_SORTED_LAYERS_BLEND. Use more
   * passes for more correct transparency. Usually four passes (which is the default value)
   * gives good results.
   *
   * For example,
   * the number of passes needed for rendering an opaque sphere behind two cubes is the number
   * of planes separating the sphere from the viewer (plus 1 in #SORTED_LAYERS_BLEND).
   * So, when backface culling is enabled, 2 faces
   * separate the sphere from the viewer: the front face of the first cube and the front face of
   * the second cube. The number of passes needed in this case is 3 in #SORTED_LAYERS_BLEND and
   * 2 in #DELAYED_SORTED_LAYERS_BLEND.
   *
   * The default value can be set using the environment variable
   * OIV_NUM_SORTED_LAYERS_PASSES.
   */
  void setSortedLayersNumPasses(int num)
    { m_sortedLayersNumPasses = num; }


  /**
   *
   * Returns the number of rendering passes used
   * when transparency type is #SORTED_LAYERS_BLEND.
   */
  int getSortedLayersNumPasses() const
    { return m_sortedLayersNumPasses ; }

  /**
   * Indicates if #SORTED_LAYERS_BLEND transparency is supported by
   * your graphics board on the current context.
   *
   */
  static SbBool isSortedLayersSupported(SoState* state=NULL) ;

  /**
   * Enable or disable the OpenGL alpha test for rendering.
   * Default is FALSE (alpha test disabled) and the default test is
   * "not equal to zero".  The alpha test operates on all pixel writes,
   * including those resulting from the scan conversion of points, lines,
   * polygons, and bitmaps, and from pixel draw and copy operations.
   * It does not affect screen clear operations.
   *
   * For example, if rendering
   * with textures containing "binary" alpha values (0 or 1), the alpha test may
   * be faster than blended transparency and does not require the use of
   * delayed rendering transparency types.
   *
   * The default value can be set using the environment variable
   * OIV_ALPHA_TEST (0 = FALSE, 1 = TRUE).
   */
  void setAlphaTest( SbBool flag );

  /**
   * Returns whether the OpenGL alpha test is enabled for rendering.
   */
  SbBool isAlphaTest() const
    { return m_alphaTest; }


  /**
   * Sets whether or not "remote" rendering is done.
   * Inventor's auto-render-caching algorithm will choose to cache
   * more often when rendering is remote (the assumption being that
   * performance will be better with display lists stored on the
   * remote machine). By default, it is assumed rendering is NOT
   * remote.
   */
  void                  setRenderingIsRemote(SbBool flag);
  /**
   * Returns TRUE if remote rendering is being done.
   */

  SbBool              getRenderingIsRemote() const;

  /**
   * Invalidate the state, forcing it to be recreated at the next apply
   */
  virtual void        invalidateState();

  /** Sets decimation percentage, the value should be a
   * number between 0.0 and 1.0
   * Useful for reducing the number of triangles rendered
   * in the scene.
   */
  void setDecimationValue(SoDecimationTypeElement::Type type,
                          float percentage = 1.0);

  /**
   * Gets decimation type.
   */
  SoDecimationTypeElement::Type getDecimationType() { return decType; };

  /**
   * Gets decimation percentage, the value should be a
   * number between 0.0 and 1.0.
   */
  float               getDecimationPercentage() { return decPercent; };

  /**
   * This method specifies the angle between each sorting axis when using the
   * transparency type SORTED_TRIANGLES_XXX or SORTED_OBJECT_TRIANGLES_XXX.
   * @BR
   * Transparent triangles are sorted based on the nearest axis.
   * (in terms of the dot (inner) product). If the triangles have
   * already been sorted on this axis (or the opposite), and the sort result is cached,
   * the triangles are rendered using the cached information.
   *
   * The default value for sort frequency is 90, meaning that a sorting is made every 90 degrees.
   * If the value is 0, sorting is always done
   * and the camera orientation vector is the axis used for sorting. In this case, no
   * cache is made.
   *
   * The allowable angular increments for the sort angle
   * are the integer divisors of 90: { 1, 2, 3, 5, 6, 9,
   *10, 15, 18, 30, 45, 90 }. If the input value is
   * not an integer divisor of 90, Open Inventor will use
   * the next highest integer divisor of 90.
   *
   * Examples:
   * - angle=67 => sort axes every 90 degrees
   * - angle=45 => sort axes every 45 degrees
   * - angle=37 => sort axes every 45 degrees
   *
   * Input values will be clamped to the range 0 to 90.
   *
   * The following figures show the sort axes used for sort frequencies
   * of 90 degrees and 45 degrees.
   *
   *  @IMAGE angle90.gif
   *  @IMAGE angle45.gif
   */
  void setSortedTrianglesSortFrequency(int angle);

  /**
   * Returns the sort frequency used for the SORTED_TRIANGLES_XXX and
   * SORTED_OBJECT_TRIANGLES_XXX transparency types.
   */
  int getSortedTrianglesSortFrequency();

  /**
   * Sets the number of caches to use when the transparency type is
   * SORTED_TRIANGLES_XXX or SORTED_OBJECT_TRIANGLES_XXX. This specifies the number
   * of lists of sorted triangles to keep in memory in order to render
   * transparent triangles more quickly.
   *
   * When computing a new list of sorted triangles, if an empty cache is available,
   * it is used.
   * Else, the farthest axis
   * from the camera orientation axis is replaced in the cache.
   * The default number of caches is 3.
   */
  void setSortedTrianglesNumCaches(int numCaches);

  /**
   * Returns the maximum number of caches allowed for the sorted triangles transparency types.
   */
  int getSortedTrianglesNumCaches();

  /**
   * Enables or disables the invalidation of render caches.
   * - When set to ALWAYS, the caches are invalidated for each SoSeparator node before
   *   its children are traversed. No new caches will be built. This value forces
   *   all nodes to be visited during each render traversal.
   *
   * - When set to ONCE, the caches are invalidated for each SoSeparator node before
   *   its children are traversed. The
   *   invalidate cache mode is automatically changed to OFF at the end of the traversal.
   *
   * - When set to OFF (default), caches are managed by their respective render caching
   *   nodes in the usual way.
   *
   * This method is useful to force all nodes to be visited during render traversal.
   */
  void setInvalidateCacheMode(InvalidateCacheMode icm);

  /**
   * Returns the current cache invalidation mode.
   */
  InvalidateCacheMode getInvalidateCacheMode();

  /**
   * Returns the current frame counter.
   * The frame counter starts at zero and is automatically incremented
   * each time the action is applied.  The frame counter will have the
   * same value throughout a single apply, even if there are multiple
   * render passes, delayed rendering, etc.
   */
  uint32_t getFrameCounter() const { return m_frameCounter; }

  /**
   * Reset the frame counter.
   * Do not call this method during a traversal.
   */
  void resetFrameCounter( uint32_t count = 0 ) { m_frameCounter = count; }

SoEXTENDER public:
  /** Return true if depth peeling is active*/
  inline bool isDoingDepthPeeling() const { return m_isDoingDepthPeeling; }

  /**
   * Get the current pass of depth peeling, -1 if not doing depth peeling
   */
  int getDepthPeelingPass();

  /**
   * Use 3D texturing instead of 2D for the fixed functionality emulation
   * in depth peeling
   */
  void enableDepthPeeling3D(bool flag) const;

  // Returns current rendering pass number
  int getCurPass() const              { return curPass; }

  // Returns TRUE if render action should abort - checks user callback
  SbBool abortNow()
    { return (hasTerminated() || (abortCB != NULL && checkAbort())); }

  // Returns TRUE if render action handles processing of a
  // transparent object (if it is to be sorted and rendered later).
  // If this returns FALSE, the object should just go ahead and
  // render itself.
  // The optional argument isTransparent ensures that the object being
  // rendered will be taken as transparent, regardless of transparency
  // in the state.  If it is false, the state is checked for transparency.
  virtual SbBool handleTransparency(SbBool isTransparent = FALSE, SbBool isLinesOrPoints = FALSE);

  virtual void setUpState();

  // Control whether delayed transparent objects update the depth buffer.
  // By default they do not (historical behavior)
  void setDelayedObjDepthWrite( SbBool flag )
    { m_delayedObjDepthWrite = flag; }

  SbBool getDelayedObjDepthWrite() const
    { return m_delayedObjDepthWrite; }


 SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual void apply(SoNode* node);
  virtual void apply(SoPath* path) { SoAction::apply(path); }
  virtual void apply(const SoPathList &pathList, SbBool obeysRules = FALSE) { SoAction::apply(pathList, obeysRules); }

  /** True if rendering into a floating point framebuffer */
  inline bool isFloatingPointFramebuffer() const { return m_floatingPointFramebuffer; }
  inline void setFloatingPointFramebuffer(bool flag) { m_floatingPointFramebuffer = flag; }

  // Returns TRUE if rendering is being delayed because of
  // transparency sorting or delaying
  SbBool              isDelaying() const
  { return delayObjs; }

  // Adds to the list of paths to render after all other stuff
  // (including delayed/sorted transparent objects) have been
  // rendered. (Used for annotation nodes.)
  void                addDelayedPath(SoPath *path);

  // Remove a path containing the node (if exists) from the lists of delayed transparency paths to render
  // after all other stuff.
  void                removeDelayedTranspPath(SoNode *node) ;

  // Used in SoLocateHighlight in order to clear the transparent path cache
  void removeAllDelayedPath();

  /** Returns TRUE if currently rendering any kind of delayed paths */
  bool isRenderingDelayed() const;

  // Returns TRUE if currently rendering delayed paths
  SbBool              isRenderingDelayedPaths() const
    { return renderingDelPaths; }

  // Returns TRUE if currently rendering transparents objects
  SbBool              isRenderingTranspObjs() const
  { return renderingTranspObjs||renderingTranspDelayedObjs; }

  // Gets the list of paths to render in the front buffer
  const SoPathList &getDelayedPaths() const { return delayedPaths; }

  void clearFastEditState();

  void addDelayedFastEditPath(SoNode* node, SoFullPath* path);

  SbBool isRenderingFastEditPaths() const { return renderingFastEditNodes; }

  const SoPathList &getDelayedFastEditPaths() const { return delayedFastEditPaths; }

  SbBool handleFastEdit(SoSeparator* sep);

  // Returns TRUE if currently rendering delayed paths
  SbBool              isRenderingTranspPaths() const
    { return renderingTranspObjs||renderingTranspDelayedObjs; }

  // Adds to the list of paths to render in the front buffer,
  // ie. after the buffer swap  (see SoFrontBufferGroup node).
  void        addFBufPath( SoPath *path );

  // Returns TRUE if currently rendering front buffer paths
  SbBool      isRenderingFBufPaths() const
    { return renderingFBufPaths; }

  // Gets the list of paths to render in the front buffer
  const SoPathList &getFBufPaths() const
    { return frontBufferPaths; };

  // Renders the front buffer paths
  void        renderFBufPaths( SbBool clearPaths = TRUE );


  int                 getCullTestResults() { return cullBits; }
  void                setCullTestResults(int b) { cullBits = b; }

  // Indicates if the action ignores back face culling.
  void setBackFaceCullingIgnored(SbBool flag)
    { m_isBackFaceCullingIgnored = flag; }

  SbBool isBackFaceCullingIgnored() const
    { return m_isBackFaceCullingIgnored; }

  SbBool isLogicalRegionSet() const;

/* FAST EDIT METHODS*/
  // Retrieve the current triggered node
  SoNode* getTriggerNode() const;
  // Set the triggered node.
  void setTriggerNode(SoNode* node);
  // set the buffer type.
  void setDoubleBuffer(SbBool db);
  // is the buffer region is saved ?
  SbBool isBufferSaved() const;
  // The main scene must be redrawn.
  void setForceRender(SbBool force);
  // is the main scene must be redrawn.
  SbBool getForceRender() const;
  // Called when something change in scene. Is it a fast edit node ?
  void howToRenderScene(SoSensor* sensor, SbBool newRender);
  // Set viewing mode (from viewer).
  void setViewing(SbBool viewing);
  // Is there any fast nodes to render ?
  SbBool hasFastEditNodesToRender() const;
  // Is there any delayed object to render ?
  SbBool hasDelayedNodesToRender() const;
  // Clear the fastedit paths list.
  void removeAllDelayedFastEditPath();
  // Rebuild new list.
  void buildDelayedFastEditPathList();
  // callback function for SoSearchStepAction.
  static SbBool sepNodeFilter(SoFullPath*, void *, SoSearchStepAction*);
  // initialize the start of a stereo pass.
  void setFirstStereoPass(SbBool first);

  SoGLSortTriangles* getGLSortTriangles() const;
  SoPathList& getTranspPathsList();

  void setRenderingFromOffscreen(SbBool renderFromOffscreen)
  { m_renderingFromOffscreen = renderFromOffscreen; }

  SbBool getRenderingFromOffscreen() const
  { return m_renderingFromOffscreen; }

  // Updates the list of transparency paths according to the reason which has triggered
  // the sensor. Setting forceRebuilding to TRUE, deletes all the transparency list
  // and the associated caches, forcing them to be rebuilt at the next traversal.
  // If nodeKitToRemove is non null, the path containing it will be removed from the cache
  // list (This is used in PoBase where scenegraph is modified and notifications disabled,
  // causing a corruption of the transparent cache).
  void updateTranspList(SoSensor* sensor, SbBool forceRebuilding=FALSE, SoNode *nodeKitToRemove = NULL);

  //Return true after an apply if there were transparent objects
  //(used in SoLocateHighlight in order to redraw the whole scene only in this case)
  SbBool hasDrawnTransparentObjs() const
  { return m_hasDrawnTransparentObjs; }

  // Set the fullscene antialiasing element
  void setFullSceneAntialiasingElement( SbBool enable, int filterMask );

  /** Render mode */
  enum RenderMode {
    /**
     * Eveything is rendered as usual (default).
     */
    ALL_OBJECTS,
    /**
     * Delayed objects are not rendered.
     */
    OPAQUE_OBJECTS,
    /**
     * Only delayed objects are rendered.
     */
    DELAYED_OBJECTS
  };

  //
  // Allow to restrict which object will be render during the next ::render call.
  // After the ::render call, this mode is reset to its default value.
  // Note :  this is used by ScaleViz Depth compositing to manage delayed object.
  void setRestrictObjectRenderingMode( const RenderMode mode = ALL_OBJECTS )
  { m_restrictObjectRendering = mode; };

  int getRestrictObjectRenderingMode() const
  { return m_restrictObjectRendering; };

  SoGLRenderActionSync* getSynchronizer();
  void setSynchronizer( SoGLRenderActionSync* );

  virtual void updateParametersFrom( SoGLRenderAction* );
  SoGLRenderPassCB* getPassCallback( void*& data )
  {
    data = passData;
    return passCB;
  }

  SoGLRenderActionImpl* m_soGLRenderActionImpl;

 protected:
  // Initiates action on graph
  virtual void        beginTraversal(SoNode *node);
  // End of a traversal
  virtual void        endTraversal(SoNode *node);

  SoGLRenderActionSync* m_synchronizer;

SoINTERNAL protected:
  FastEditSavePolicy  fastEditPolicy;     // Transparency quality type
  TransparencyType    transpType;     // Transparency quality type

private:
  /** Remove paths selected during the updateTranspList
   (paths which don't exist anymore because of a switch change, a group removeChild...)
  */
  void removeInvalidPaths();

  /** Render/save fast edit scene */
  void doFastEdit(SoPathList& clearZBufferlist, SbBool& mustRenderFastEdt, SbBool& mustBeRestored);

  /** If true, render delayed object before fast edit */
  SbBool m_fastEditDelayedObjects;

  /** True if doing depth peeling */
  bool m_isDoingDepthPeeling;

  SbBool m_hasDrawnTransparentObjs;
  SbBool m_isDoubleBuffer;
  SbBool m_forceRender;
  SbBool m_isViewing;
  SbBool m_mustSaveBuffers;
  SoNode* m_appliedNode;
  SoSearchStepAction* m_searchStepAction;
  SbBool m_isFirstApply;
  SbBool m_firstStereoPass;
  int m_lastStereoMode;

  int    m_useCacheOpt;
  int    m_useCompactPaths;
  static void delayedNodeSensorCallback(SoGLRenderAction*, SoNodeSensor*);

  SbViewportRegion    vpRegion;       // Current viewport region
  /* OIV_MULTI_THREADS */
  SbViewportRegion    vpLogicalRegion;// Current logical viewport region
  int                 logicalRegionIsSet;  // for the MP to work properly under windows

  SbVec2f             updateOrigin;   // Origin of update area
  SbVec2f             updateSize;     // Size of update area


  // Variables for render abort:
  SoGLRenderAbortCB   *abortCB;       // Callback to test abort
  void                *abortData;     // User data for abort callback

  // Variables for transparency, smoothing, and multi-pass rendering:
  SbBool              doSmooth;       // Doing smoothing ?
  int                 numPasses;      // Number of rendering passes
  int                 curPass;        // Current pass
  SbBool              passUpdate;     // Whether to update after each pass
  SoGLRenderPassCB    *passCB;        // Callback between passes
  void                *passData;      // User data for pass callback

  // For SORTED_OBJECT_ADD or SORTED_OBJECT_BLEND transparency:
  SbBool              renderingTranspDelayedObjs; // TRUE when rendering transp objs
  SbBool              renderingTranspObjs; // TRUE when rendering transp objs
  SbBool              delayObjs;           // TRUE if transp objects are to be delayed until after opaque ones
  SbBool              fastEditObjs;        // TRUE if fast edit objects are to be delayed

  SbBool              m_shouldSortTranspPaths ; // TRUE is transparency paths should be sorted
  SbBool              sortObjs;                 // TRUE if objects are to be sorted
  SoPathList          transpPaths;              // Paths to transparent objects
  SoPathList          transpDelayedPaths;       // Paths to transparent objects in DELAYED_SORTED_LAYERS_BLEND mode
  SoPathList          transpPathsSortObj;       // Paths to sorted transparent objects
  SoPathList          transpPathsCached;        // Paths to transparent objects
  SoPathList          transpDelayedPathsCached;  // Paths to transparent delayed objects

  SoGetBoundingBoxAction *ba;         // For computing bounding boxes
  SbBox3f                *bboxes;     // Bounding boxes of objects
  int                    numBBoxes;   // Number of bboxes allocated
  SbBool              transpPathsSortObjPerspectiveMode; // Indicates if the objects to sort are rendered using perspective or ortho camera

  SbBool              remoteRendering;// Remote rendering?

  // Stuff needed to implement rendering of delayed paths
  SoPathList          delayedPaths;       // List of paths to render
  SoPathList          delayedPathsCached; // List of paths to render
  SbBool              renderingDelPaths;  // TRUE when rendering them

  // Stuff needed to implement rendering of compact delayed paths
  // (useful in some cases where we need to do a collection during normal traversal
  // followed by the actual rendering of compact objects. For this case we'll need the delay
  // mecanism. The delayedPaths list is not used since it is rendered after transparent objects)

  SoNode* m_triggerNode;
  SoBufferRegion *m_bufferRegion, *m_bufferRegionLZ;
  SoSensorList m_fastEditNodeSensors;
  SoPathList delayedFastEditPaths; // List of paths to render
  SoPathList delayedFastEditPathsSave;
  SbBool renderingFastEditNodes; // TRUE when rendering them

  // Stuff needed to implement rendering "front buffer" paths
  // (objects to be rendered after the buffer swap) --mmh Dec-2000
  SoPathList  frontBufferPaths;    // List of paths to render
  SbBool      renderingFBufPaths;  // TRUE when rendering them

  // BA 2/98 - added decimation variables
  SoDecimationTypeElement::Type decType;    // Decimation type
  float                         decPercent; // Decimation percentage

  // These flags determine which things have to be sent to GL when
  // the action is applied. They indicate what's changed since the
  // last time the action was applied.
  enum flags {
    TRANSPARENCY_TYPE = 0x01,
    SMOOTHING         = 0x02,
    ALPHA_TEST        = 0x04,
    FASTEDIT_SAVE_POLICY = 0x08,
    SCENE_GRAPH       = 0x10,
    ANTIALIASING      = 0x20,
    ALL               = 0x3F  // Initial value
  };
  uint32_t whatChanged;

  // Renders all passes starting at a node
  void renderAllPasses(SoNode *node);

  // Renders one pass starting at a node
  void renderPass(SoNode *node, int pass);

  // Renders objects that have been marked as transparent in same or
  // sorted order
  void renderTransparentObjs();

  // Enables or disables GL blending
  void enableBlending(SbBool enable);

  // Enables or disables GL smoothing
  void enableSmoothing(SbBool enable);

  // Returns TRUE if render action should abort based on callback
  SbBool checkAbort();

  // Keep track of which planes we need to view-volume cull test
  // against:
  int cullBits;

  // Indicates if the action ignores back face culling.
  SbBool m_isBackFaceCullingIgnored;

  SbBool m_delayedObjDepthWrite;

  // Indicates if the next render is asked for Offscreen
  SbBool m_renderingFromOffscreen;

  SbBool m_alphaTest;

  // Count frames rendered with this action (for debugging)
  uint32_t  m_frameCounter;

  //================== Begin sorted layers rendering ========================

  int m_sortedLayersNumPasses ;

  // Realizes a sorted layers rendering using depth peeling technics.
  void renderSortedLayers(SoNode *node) ;
  void initDepthPeeling(SoNode *node);

  // Rendering callback for sorted layers rendering.
  static void renderSortedLayersCB(void *userData, SoGLDepthPeeling *mgr) ;

  SoGLDepthPeeling *m_glDepthPeeling ;

  static void cameraPostCB( SoCamera *camera, SoGLRenderAction* renderAction );
  bool m_ignoreCameraPostCB;
  //================== End orted layers rendering ========================

  SoGLSortTriangles* m_glSortTriangles;
  int m_sortedAxisPrecision;
  int m_numSortedVectorCaches;
  SoPathList transpPathsSortTri; // Paths to transparent shapes in sorted triangles mode

  InvalidateCacheMode m_invalidateAllCaches;

  RenderMode m_restrictObjectRendering;

  static char s_separateSpecularMode;

  bool m_floatingPointFramebuffer;
  //List of paths to remove because they don't exist anymore
  //(eg:  a switch changed, a group removeChild...)
  std::vector<SoPath*> m_pathsToRemove;

  // Indicates if something changed in the fast edit state.
  // Can be a scene graph modification or any operation that 
  // require the creation of the paths list.
  bool m_rebuildDelayedFastEditPathList;

  //================ FSAA element management ============================
  SbBool m_fsaaEnable;
  int m_fsaaFilterMask;
};


// INLINE METHODS
inline SoGLRenderActionSync*
SoGLRenderAction::getSynchronizer()
{
  return m_synchronizer;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif
#endif /* _SO_GL_RENDER_ACTION_ */

