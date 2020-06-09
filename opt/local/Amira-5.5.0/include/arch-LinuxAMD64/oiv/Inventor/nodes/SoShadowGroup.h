/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R.ALBOU (Sep 2001)
**=======================================================================*/
#ifndef  _SO_SHADOW_GROUP_
#define  _SO_SHADOW_GROUP_


#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/SbMatrix.h>

class SoGLShadowMapping ;
class SoCache ;
class SoShadowGroupImpl;

/**
* Shadow casting group node
*
* @ingroup GroupNodes
*
* @DESCRIPTION
* This group node performs real-time shadow casting. Because shadows depends on a lot of OpenInventor elements,
* it is recommended to put children of this group under a SoSeparator in order to have a cache.
* Each shape within this group will be included in the shadow casting computation. A shape
* may cast a shadow on other shapes or on itself (self-shadowing), and/or may be shadowed
* by other shapes within the group. The current shadow style is used to determine if
* shapes cast a shadow and/or can be shadowed (see SoShadowStyle).
*
* This class defines two shadowing methods which can be selected with the #method field:
* - SHADOW_MAP: In this mode, shadows are not filtered and will display aliasing. Futhermore,
* it is not compatbile with VolumeViz nodes. All directional lights and spotlights (but not point lights) above this
* group node are used for computing the shadows. Adding lights as children of this group
* node will give incorrect results (lights must be defined @I above@i this node).
* Even when using the best quality setting (see #quality), some aliasing artifacts
* will appear if you zoom in very close to the scene.
* Another way to increase the shadowing quality (decrease the aliasing effects),
* is to specify a spherical region centered at the camera position
* within which the shadowing will be computed
* (see #visibilityRadius).
* The smaller the radius of this sphere, the better the shadow quality.
* This parameter is particularly useful for walk-through scenes.
*
*- VARIANCE_SHADOW_MAP : This mode allows to display soft shadows. The #smoothFactor
* field can be used to increase or decrease the softness. Contrary to the SHADOW_MAP
* method, aliasing won't be displayed but on large scene, shadows will progressively fade away.
* Increasing #quality will reduce this problem. Only the last on state directional light is used
* during rendering, other lights are ignored.
*
* Shaders @BR
* Only the VARIANCE_SHADOW_MAP method is available with custom shaders. In order to use shadows
* with user defined GLSL shaders (SoShaderProgram or SoVolumeShader), the following functions must
* be used in the shader programs. @BR
* In the vertex shader:
* - void OivSetupShadowVertex(): Must be called in the vertex shader.
*
* In the fragment shader:
* - float OivComputeShadow(): Returns a scalar in [0-1].
*   0 means fragment is fully shadowed, 1 means no shadow.  Should be used to modify the
*   fragment color.
* - void OivGenerateShadowMap(): Must be called during the shadowmap pass in order to create the
*   shadowmap.  During this pass, the shader must not write to gl_FragColor.  Use the uniform
*   @I OivShadowPass @i to know when the shadowmap is being computed.
*
* The following uniform is available in vertex and fragment shaders:
* - uniform bool OivShadowPass: Is true if the shadowmap is currently being rendered
*
* The following code can be used as a skeleton for a shader that works with shadows:
* \code
* // The vertex shader:
* void OivSetupShadowVertex();
* void main()
* {
*   ..userCode..
*   //Needed for shadowing
*   OivSetupShadowVertex();
* }
*
* // The fragment shader:
* //If true we are in shadowmap generation pass
* uniform bool OivShadowPass;
*
* void OivGenerateShadowMap();
* float OivComputeShadow();
* void main()
* {
*   if ( !OivShadowPass ) {
*     ..compute fragment color here..
*     // Define the final color
*     gl_FragColor.xyz = fragColor.xyz * OivComputeShadow();
*     gl_FragColor.w = fragColor.w;
*   }
*   else {
*     // Output the shadowmap during the shadow map pass
*     OivGenerateShadowMap();
*   }
* } \endcode
*
* Transparency: @BR
* Transparent objects are treated as follows, depending on the transparency type:
*
*  - ADD, BLEND: Transparent objects cast a shadow and are shadowed but the shadow intensity doesn't
*    depend on the transparency value (the same shadow is displayed for full transparent shapes and
*    opaque shapes).
*
*  - ALL SORTED, ALL DELAYED, and SCREEN_DOOR: Same as previous case for VARIANCE_SHADOW_MAP.
*    For SHADOW_MAP method transparent objects neither cast a shadow nor are
*    shadowed.
*
*  - SORTED_LAYERS_BLEND: This transparency mode is not compatible with SoShadowGroup. No shadows
*    are computed.
*
* Texture units: @BR
* In SHADOW_MAP mode this node reserves texture units FXVIZ_SHADOW_TEXTURE_UNIT0 and FXVIZ_SHADOW_TEXTURE_UNIT1
* for its rendering (see SoPreferences to set these). If these values are not set, texture
* units 1 and 2 are used. These values cannot be greater than 3.
*
* In VARIANCE_SHADOW_MAP mode, this node reserves texture unit FXVIZ_SHADOW_TEXTURE_UNIT0
* for its rendering (see SoPreferences to set these). If this value is not set
* the application can specify which texture
* units OpenInventor should automatically use by setting environment variables (see SoPreferences).
* The texture units between OIV_FIRST_RESERVED_TEXTURE_UNIT and
* OIV_FIRST_RESERVED_TEXTURE_UNIT+SoShaderProgram::getNumReservedTextures()-1
* inclusive are reserved for internal OpenInventor use.
* If OIV_FIRST_RESERVED_TEXTURE_UNIT is not set, its default value is
* SoFragmentShader::getMaxTextureImageUnit()-SoShaderProgram::getNumReservedTextures().
* Note: The value returned by SoShaderProgram::getNumReservedTextures() may change between
* OpenInventor versions.  The total number of available texture units depends on the graphics
* hardware.
*
* Hardware requirements: @BR
* NOTE: In SHADOW_MAP mode, at least the @B Multi-Texture @b and @B Texture Environment Combine @b OpenGL extensions
* must be supported by your graphics board. Otherwise no shadows will be computed.
* These extensions are now standard in OpenGL 1.3 and later.<BR>
* The @B Shadow  @b and @B Depth Texture @b OpenGL extensions (standard in OpenGL 1.4) are
* used if they are available and generally improve performance.<BR>
* In order to increase quality and performance of the shadows, OpenGL PBuffers are used.
* PBuffers are a limited resource on some systems.  Set @B OIV_PBUFFER_ENABLE @b to 0 to
* disallow use of PBuffers.
*
* A DirectX 10 graphics board is needed to support VARIANCE_SHADOW_MAP.
*
* Use the isSupported() static method to determine if the current graphics board
* supports shadowing.
*
* Notes:
* - Geometry cannot receive shadows if lighting is disabled. @BR
*   For example if an SoLightModel node sets the lighting model to BASE_COLOR.
* - Geometry cannot receive shadows if a texture is applied using the
*   DECAL or REPLACE models.
*
* Potential problems: <BR>
* In SHADOW_MAP mode, performance issues and incorrect images have been observed with some OpenGL
* drivers due to the @B Texture Border Clamp @b OpenGL extension (standard in OpenGL 1.3),
* Try setting the @B OIV_TEXTURE_BORDER_CLAMP_ENABLE @b environment variable to 0 in this
* case.<BR>
* With some graphics boards, especially older hardware like GeForce2, it may be
* necessary to also set the @B OIV_FORCE_DUAL_TEX_SHADOW @b environment variable to 1.

* @FILE_FORMAT_DEFAULT
*    ShadowGroup {
*    @TABLE_FILE_FORMAT
*               @TR isActive             @TD TRUE
*               @TR isShapesBefore       @TD FALSE
*               @TR intensity            @TD 0.5
*               @TR precision            @TD 0.5
*               @TR quality              @TD 0.5
*               @TR shadowCachingEnabled @TD TRUE
*               @TR visibilityRadius     @TD 1.0
*               @TR visibilityFlag       @TD LONGEST_BBOX_EDGE_FACTOR
*               @TR smoothFactor         @TD 1
*               @TR minVariance          @TD 1e-5
*               @TR method               @TD SHADOW_MAP
*               @TR lightBleedingReduction @TD 0.01
*    @TABLE_END
*    }
*
* @SEE_ALSO
*    SoShadowStyle
*
*
*/

class INVENTOR_API SoShadowGroup : public SoGroup {
  SO_NODE_HEADER( SoShadowGroup );

public:
  /**
  * #visibilityRadius interpretation
  */
  enum VisibilityFlag {
    /**
    *
    * #visibilityRadius is interpreted as an
    * absolute value.
    */
    ABSOLUTE_RADIUS,

    /**
    * The longest edge of the scene
    * bounding box will be multiplied by the value of #visibilityRadius. The
    * resulting value
    * will be the radius within which shadows are computed.
    */
    LONGEST_BBOX_EDGE_FACTOR
  } ;

  /**
   * Shadowing techniques
   */
  enum ShadowingMethod {
    /**
     * Standard shadow mapping
     */
    SHADOW_MAP,

    /**
     * Shadows with soft edges
     */
    VARIANCE_SHADOW_MAP,
    #ifndef HIDDEN_FROM_DOC
    LAST_METHOD
    #endif
  };

  /**
  * Default constructor.
  */
  SoShadowGroup();

  /**
  * Constructor that takes approximate number of children.
  */
  SoShadowGroup(int nChildren);

  /**
  * Activates/deactivates the shadowing.
  * If deactivated, this #SoShadowGroup behaves like an #SoGroup.
  */
  SoSFBool        isActive ;

  /**
  * Indicates that there are shapes before this group.
  * Setting this value to TRUE may slow down the rendering
  * because it causes a depth buffer save at each frame.
  * Used only for SHADOW_MAP method.
  */
  SoSFBool        isShapesBefore ;

  /**
  * Specifies the intensity of the shadow.
  * 0 = lowest intensity (the shadow is invisible),
  * 1 = highest intensity (the shadow is solid black).
  */
  SoSFFloat   intensity ;

  /**
  * Specifies the precision of the shadow.
  * 0 = lowest precision, 1 = highest precision.
  * With lower precisions, some parts of the scene may be unlit where
  * they should be lit, or vice versa.
  * Increasing the precision will reduce performance.
  *
  * NOTE: If your graphics driver does not support
  * the required OpenGL extensions, you may see low precision results
  * even when this field is set to the highest precision.
  */
  SoSFFloat   precision ;

  /**
  * Specifies the quality of the shadow.
  * 0 = lower quality, 1 = best quality.
  *
  * For VARIANCE_SHADOW_MAP quality may be greater than 1
  * (texture used for shadowmap rendering will be of size 2*quality*ViewportSize)
  *
  * Increasing the quality will reduce performance and increase memory consumption.
  */
  SoSFFloat   quality ;

  /**
  * Indicates if a cache should be used for computing the shadows.
  * Using a cache will improve rendering performance if the lights of your
  * scene and your scene under this group node do not change.
  */
  SoSFBool    shadowCachingEnabled ;

  /**
  * Shadows are only computed within "visibility radius" distance
  * from the camera position.
  *
  * This radius equals:
  *   - the longest edge of the bounding box of the scene multiplied by #visibilityRadius
  *     if #visibilityFlag equals #LONGEST_BBOX_EDGE_FACTOR.
  *
  *   - #visibilityRadius if #visibilityFlag equals #ABSOLUTE_RADIUS.
  *
  * When #visibilityRadius = 1 and #visibilityFlag = #LONGEST_BBOX_EDGE_FACTOR
  * (default values), shadowing is computed throughout the entire scene.
  *
  * Note: With VARIANCE_SHADOW_MAP method, try to increase the #quality field first.
  */
  SoSFFloat   visibilityRadius ;

  /**
  * Specifies how #visibilityRadius is interpreted.
  * Use enum #VisibilityFlag. Default is LONGEST_BBOX_EDGE_FACTOR.
  */
  SoSFEnum    visibilityFlag ;


  /**
   * Set the smoothness of shadows. Higher values give smoother shadows.
   * Default is 1.
   * Used only for VARIANCE_SHADOW_MAP method.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFInt32 smoothFactor;

  /**
   * Used only for VARIANCE_SHADOW_MAP. Increasing this value will decrease
   * possible self-shadowing artifacts but will make shadows fade away. The default
   * value is safe for most scenes. Increasing the #quality field is also preferable before
   * tweaking this value.
   * A special case is for SoVolumeRender node which has a minimum of 0.001 or IVVR_SHADOW_MIN_VARIANCE if set.
   * Default is 1e-5 and range is [0-1].
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFFloat minVariance;

  /**
   * Used only for VARIANCE_SHADOW_MAP. In some cases, a halo may appear around shadows
   * intersecting each other. Increasing this value will decrease this effect.
   * Default value is safe for most scenes.
   * Default is 0.01 and range is [0-1].
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFFloat lightBleedingReduction;

  /**
   * Specifies the shadowing technique to use. 
   * Use enum #ShadowingMethod. Default is SHADOW_MAP.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFEnum method;

  /**
  * Indicates if shadow casting is supported by your graphic board.
  */
  static SbBool isSupported(SoShadowGroup::ShadowingMethod method = SoShadowGroup::SHADOW_MAP) ;


SoEXTENDER public:
  /** Called during GLRender action*/
  virtual void GLRender(SoGLRenderAction *action);

  /*----------------------------------------------------------------------------*/

SoINTERNAL public:
  typedef std::vector<int> StackIndexVector;

  static void initClass() ;
  static void exitClass() ;

  /** Return view projection matrix of the current light */
  const SbMatrix& getLightViewProjectionMatrix() const;

  /** Return texture map unit used for shadowmap */
  static int getShadowMapTextureUnit();

  /** Destroy light caches */
  void invalidateLightCaches();

  /** Return false if shadowmap needs to be recomputed
   *  and update cache as needed. Take passed elements index in account */
  bool isCacheValid(SoState* state, SoCache* &cache, const StackIndexVector& elemsToCheck);


  /** Return true if shadow is active according to SoInteractiveComplexity */
  bool isShadowActive(SoState* state) const;

  /** Return quality according to SoInteractiveComplexity */
  float getQuality(SoState* state) const;

  /**
   * Handle field change
   */
  virtual void notify(SoNotList *list);

protected:
  virtual ~SoShadowGroup();

private:
  struct Members
  {
    Members();
    ~Members();
    void unref();

    SoShadowGroupImpl* m_sgImpl;
    ShadowingMethod m_currentMethod;
    uint64_t m_lastNodeId;
  };
  SbThreadStorage<Members*> m_members;

  /** Add dependency on various elements */
  void addElementsToCache(SoState* state, SoCache* cache) const;

  /** Allocate the good SoShadowGroupImpl accordind to method field*/
  void chooseShadowingMethod();

  void commonInit();

  /** Return per threads members  */
  static SoShadowGroup::Members* getMembers(const SoShadowGroup* sg);

  /** Texture unit define by SoPreferences */
  static int s_defaultTextureUnit;
};
/*----------------------------------------------------------------------------*/
#endif // _SO_SHADOW_GROUP_
