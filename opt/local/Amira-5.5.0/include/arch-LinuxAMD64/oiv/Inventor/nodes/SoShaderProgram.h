/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                            /* include files */
#ifndef _SO_SHADER_PROGRAM_H_
#define _SO_SHADER_PROGRAM_H_

#include <Inventor/SbBasic.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFNode.h>
#include <Inventor/elements/SoGLShaderProgramElement.h>
#include <Inventor/nodes/SoShaderParameter.h>
#include <Inventor/nodes/SoFragmentShader.h>
#include <Inventor/nodes/SoVertexShader.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/nodes/SoGeometryShader.h>
#include <Inventor/STL/vector>
#include <Inventor/STL/cassert>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoGLRenderAction;
class SoGLShaderProgram ;
class SoGLShaderObject;
class SoFieldSensor ;
class SoLight;

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Shader program property node.
 *
 * @ingroup ShaderNodes
 *
 * @DESCRIPTION
 *   This property node defines the complete shader program for all subsequent shapes.
 *   A complete shader program may contain vertex shaders (SoVertexShader), geometry shaders
 *   (SoGeometryShader) and/or fragment shaders (SoFragmentShaders).  See SoShaderObject
 *   for information common to all these classes.
 *
 *   With some languages such as NVIDIA Cg or assembly language (ARB_vertex_program/ARB_fragment_program),
 *   only one vertex and one fragment program can be active at the same time.
 *   The field #shaderObject contains the vertex, geometry and fragment shader objects which form
 *   the shader program. Each shader object should be of type SoShaderObject.
 *   Modifications that occur in shader objects are dynamically detected and the state is updated.
 *
 *   @I Uniform @i parameters may be set for each shader object.  Uniform means, 
 *   in the case of a vertex or geometry program, a value which is the same for all vertices
 *   in a primitive, and, in the case of a fragment program, a value which is the same for all 
 *   fragments created by a primitive.
 *   Each uniform parameter is represented by an instance of a specific subclass of 
 *   SoUniformShaderParameter.  For example, an SoShaderParameter1i holds a single integer value.
 *
 *   @I Vertex @i parameters may be set for a vertex shader object. Vertex parameters are 
 *   per-vertex data passed from the application to the vertex shader.  Vertex parameters are
 *   represented by an instance of a specific subclass of SoVertexShaderParameter.
 *   For example, an SoVertexShaderParameter1f holds a set of floating point values
 *   and an SoVertexShaderParameter3f holds a set of SbVec3f values.
 *
 *   SoShaderProgram has specialized subclasses for volume visualization.  If you are using
 *   the VolumeViz extension, see SoVolumeShader and SoVolumeRenderingQuality.
 *
 *   @B TIP@b: If you set the environment variable OIV_SHADER_CHECK_INTERVAL, the
 *   shader source file is checked for a change every @I n @i seconds, where @I n @i is
 *   the value specified by the variable.
 *   This allows you to edit the shader source code without needing to restart your
 *   application after each shader modification.
 *
 *   NOTE: For geometry shaders the EXT_geometry_shader4 OpenGL extensions must be supported by
 *   your graphics board.
 *
 * @FILE_FORMAT_DEFAULT
 *    SoShaderProgram {
 *      @TABLE_FILE_FORMAT
 *        @TR shaderObject          @TD NULL
 *        @TR geometryInputType     @TD TRIANGLES_INPUT
 *        @TR geometryOutputType    @TD TRIANGLE_STRIP_OUTPUT
 *        @TR vertexProgramTwoSide  @TD FALSE
 *        @TR shadowShader          @TD FALSE
 *        @TR maxGeometryOutputVertices @TD -1
 *      @TABLE_END
 *    }
 *
 * @EXAMPLE
 * \oivnetdoc
 * \code
 *   // Shader program with one fragment shader with one uniform parameter.
 *   // First load the fragment shader code
 *   SoFragmentShader fragmentShader = new SoFragmentShader();
 *   fragmentShader.sourceProgram.SetValue(SHADER_FILENAME);
 *      
 *   // Set the shader parameter
 *   SoShaderParameter1i paramTex1 = new SoShaderParameter1i();
 *   paramTex1.name.SetValue("data1");
 *   paramTex1.value.SetValue(1);
 *   fragmentShader.parameter.Set1Value(0, paramTex1);
 *      
 *   // Associate fragment shader with a shader program node
 *   SoShaderProgram shaderProgram = new SoShaderProgram();
 *   shaderProgram.shaderObject.Set1Value(0, fragmentShader);
 *   root.AddChild(shaderProgram);
 * \endcode
 * \else
 * \code
 *   // Shader program with one fragment shader with one uniform parameter.
 *   // First load the fragment shader code
 *   SoFragmentShader* fragmentShader = new SoFragmentShader();
 *   fragmentShader->sourceProgram.setValue( SHADER_FILENAME );
 * 
 *   // Set the shader parameter
 *   // The addShaderParameter1i method is equivalent to:
 *   //     SoShaderParameter1i *paramTex1 = new SoShaderParameter1i;
 *   //     paramTex1->name = "data1";
 *   //     paramTex1->value.setValue(1);
 *   //     fragmentShader->parameter.set1Value(0, paramTex1);
 *   fragmentShader->addShaderParameter1i( "data1", 1 );
 * 
 *   // Associate fragment shader with a shader program node
 *   SoShaderProgram* pShaderProgram = new SoShaderProgram();
 *   pShaderProgram->shaderObject.set1Value(0, fragmentShader);
 *   pRootNode->addChild( pShaderProgram );
 * \endcode
 * \endoivnetdoc
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Sets the Open Inventor state with the active shader program.
 *        Sets: SoGLShaderProgramElement
 *
 * @SEE_ALSO
 *    SoShaderObject, SoVertexShader, SoGeometryShader, SoFragmentShader, SoShaderParameter.
 *
 *
 */

class INVENTOR_API SoShaderProgram : public SoNode
{

  SO_NODE_HEADER( SoShaderProgram );

public:
  /** Geometry input type. */
  enum GeometryInputType
  {
    /**
     * The input geometry should be interpreted as points.
     * Geometry shaders that operate on points are valid only for the SoPointSet and
     * SoIndexedPointSet nodes. There is only a single vertex available
     * for each geometry shader invocation.
     */
    POINTS_INPUT = GL_POINTS,

    /**
     * The input geometry should be interpreted as lines.
     * Geometry shaders that operate on line segments are valid only for the
     * SoLineSet or SoIndexedLineSet nodes.  There are two vertices
     * available for each geometry shader invocation. The first vertex refers to
     * the vertex at the beginning of the line segment and the second vertex
     * refers to the vertex at the end of the line segment.
     */
    LINES_INPUT = GL_LINES,

    /**
     * The input geometry should be interpreted as triangles.
     * Geometry shaders that operate on triangles are valid only
     * for geometry nodes that generate triangles, for example, SoTriangleStripSet.
     * There are three vertices available for each program invocation. The first,
     * second and third vertices refer to attributes of the first, second and
     * third vertex of the triangle, respectively. Default.
     */
    TRIANGLES_INPUT = GL_TRIANGLES
  };

  /**
   * Geometry ouput type.
   */
  enum GeometryOutputType
  {
    POINTS_OUTPUT = GL_POINTS,
    LINE_STRIP_OUTPUT = GL_LINE_STRIP,
    /**
     * Default.
     */
    TRIANGLE_STRIP_OUTPUT = GL_TRIANGLE_STRIP
  };

  /**
   * Specifies the list of shader objects (i.e., vertex shaders, geometry and fragment shaders)
   * which form the shader program. Be careful, with some languages (CG_PROGRAM or ARB_PROGRAM),
   * only one vertex program and one fragment program can be active at the same time.
   * In this case, only the first vertex shader and the first fragment shader are used.
   */
  SoMFNode shaderObject;

  /**
   * Specifies the input primitive type of the current geometry shader if any (not used otherwise).
   * Use enum #GeometryInputType. Default is TRIANGLES_INPUT.
   * 
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFEnum geometryInputType;

  /**
   * Specifies the output primitive type of the current geometry shader if any (not used otherwise).
   * Use enum #GeometryOutputType. Default is TRIANGLE_STRIP_OUTPUT.
   * 
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFEnum geometryOutputType;

  /**
   * If set to TRUE, vertex shaders will operate in two-sided color mode.
   * Default is FALSE.
   * 
   * @FIELD_SINCE_OIV 7.2
   */
  SoSFBool vertexProgramTwoSide;

  /**
   * Only used when an SoShadowGroup is active. @BR
   * If set to FALSE, a default shader will be used during
   * the shadowmap generation pass.
   * If TRUE, the shader will be used as is and must handle the
   * shadowmap pass correctly:
   * - If the uniform OivShadowPass is true, call OivGenerateShadowMap()
   * and output nothing into gl_FragColor, but discard fragments if needed.
   * - If the uniform OivShadowPass is false, follow the normal render path
   * If the shader doesn't modify the depth (with a discard or an alpha test),
   * Open Inventor will handle the shadowmap generation pass automatically.
   * Default is FALSE @BR
   * See also: SoShadowGroup
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBool shadowShader;

  /**
   * Set the maximum number of vertices the geometry shader will emit in one invocation.
   * Default is -1 which means it is set to the hardware limit.
   *
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFInt32 maxGeometryOutputVertices;

  /**
   * Constructor
   */
  SoShaderProgram();

  /**
  * Returns the fragment shader at the specified position.
  */
  inline SoFragmentShader* getFragmentShader(int pos) const;

  /**
  * Returns the vertex shader at the specified position.
  */
  inline SoVertexShader* getVertexShader(int pos) const;

  /**
   *
   * Returns the geometry shader at the specified position.
   */
  inline SoGeometryShader* getGeometryShader(int pos) const;

  /**
   * Convenience method to create a fragment shader with the specified filename and
   * add it at the specified position. Return value is the new fragment shader.
   */
  virtual SoFragmentShader* setFragmentShader(int pos, const SbString& filenameOrSource,
                                              SoShaderObject::SourceType sourceType = SoShaderObject::FILENAME);

  /**
  * Convenience method to create a vertex shader with the specified filename and
  * add it at the specified position. Return value is the new vertex shader.
  */
  virtual SoVertexShader* setVertexShader(int pos, const SbString& filenameOrSource,
                                          SoShaderObject::SourceType sourceType = SoShaderObject::FILENAME);

  /**
   *
   * Convenience method to create a geometry shader with the specified filename and
   * add it at the specified position. Return value is the new geometry shader.
   */
  virtual SoGeometryShader* setGeometryShader(int pos, const SbString& filenameOrSource,
                                              SoShaderObject::SourceType sourceType = SoShaderObject::FILENAME);

  /**
   * Returns the number of reserved texture units.
   */
  static unsigned int getNumReservedTextures();

  /*----------------------------------------------------------------------------*/

SoEXTENDER public:

  // GLRender
  virtual void GLRender( SoGLRenderAction *action );
  virtual void getBoundingBox( SoGetBoundingBoxAction *action );
  virtual void pick( SoPickAction *action );

SoINTERNAL public:
  /**Must be in sync with defines in fixedPipeline_vert.glsl*/
  enum LightType
  {
    LIGHT_TYPE_NONE,
    LIGHT_TYPE_POINT,
    LIGHT_TYPE_SPOT,
    LIGHT_TYPE_DIRECTIONAL
  };

  /**Must be in sync with defines in fixedPipeline_frag.glsl*/
  enum EnvMode
  {
    ENV_MODE_MODULATE,
    ENV_MODE_REPLACE,
    ENV_MODE_DECAL,
    ENV_MODE_BLEND,
    ENV_MODE_ADD,
    ENV_MODE_NONE
  };

  /**Must be in sync with defines in fixedPipeline_vert.glsl*/
  enum TexGenMode
  {
    TEXGEN_TYPE_NONE,
    TEXGEN_TYPE_OBJECT_PLANE
  };

  /**
  * Textures are put into texture unit: m_maxTextureImageUnit-offset-1
  */
  enum TextureUnitOffset
  {
    ISOSURFACE_TEXTURE_UNIT_OFFSET = 0,       /** FRAGMENT_TOOLS */
    MATPAL_TEXTURE_UNIT_OFFSET,               /** FRAGMENT_TOOLS */
    PREINT_TEXTURE_UNIT_OFFSET,               /** FRAGMENT_TOOLS */
    RECTILINEAR_MAPPING_TEXTURE_UNIT_OFFSET,  /** COMPUTE_COORDINATES */
    JITTER_TEXTURE_UNIT_OFFSET,               /** */
    EARLYZ_TEXTURE_UNIT_OFFSET,               /** Is binded to the current color buffer */
    INTERPOLATION_TEXTURE_UNIT_OFFSET,        /** */
    SHADOWMAP_TEXTURE_UNIT_OFFSET,
    VOLUMEMASKGROUP_TEXTURE_UNIT_OFFSET,
    LAST_USED_TEXTURE_UNIT_OFFSET             /** */
  };

  /** Handle field change */
  virtual void notify(SoNotList *list);

  /** Define name with the given value */
  void setDefine(const SbString& name, const SbString& value);

  /** Remove name from the define list */
  void removeDefine(const SbString& name);

  /**
   * Convert the offset into a GL_TEXTUREX
   */
  static GLint offsetToGLTextureUnit(int offset);

  /**
   * Return the texture unit number (the X of GL_TEXTUREX)
   */
  static int offsetToTextureUnit(int offset);

  // Initializes the classes.
  static void initClass();
  static void exitClass();

  // Update state matrix parameters of each shader object
  void updateStateMatrixParameters( SoState *state );

  // Returns TRUE if at least one parameter among all shader objects
  // is of SoShaderStateMatrixParameter type
  SbBool containStateMatrixParameters() const;

  void getAttribLocation( SbString paramName, int32_t identifier, int& firstInd );
  void getAttribSize( SoVertexShaderParameter * param, int& size );

  SoGLShaderProgram* getGLShaderProgram() const;

  /** Force shader program reconstruction */
  void invalidate();

  /** Set OivModelMatrix parameter */
  void setModelMatrix(SoGLRenderAction* actio, const SbMatrix& modelMatrix);

  /** Set OivTwoSidedLighting uniform */
  void setTwoSidedLighting(SoGLRenderAction* action);

  /** Set OivCCW uniform */
  void setCounterClockWise(SoGLRenderAction* action);

  /** Set OivViewMatrix parameter */
  void setViewMatrix(SoGLRenderAction* action, const SbMatrix& viewMatrix);

  /** Set light num to given type */
  void setLight(SoGLRenderAction* action, int num, LightType type);

  /** Set shadow intensity according to SoshadowGroup and SoShadowStyle*/
  void setShadowParameters(SoGLRenderAction* action);

  /** Return the internal OpenGL object of the first SoShaderObject */
  SoGLShaderObject* getFirstGLShaderObject(SoState* state) const;

  /** INTERNAL. Directly change uniforms values. The shader must be binded  */
  void setShaderParameter1i(SoGLRenderAction* action, const SbString& paramName,
                            int value);
  /** INTERNAL USE ONLY */
  void setShaderParameter2i(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec2i32& value);
  /** INTERNAL USE ONLY */
  void setShaderParameter3i(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec3i32& value);
  /** INTERNAL USE ONLY */
  void setShaderParameter4i(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec4i32& value);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray1i(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const int* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray2i(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec2i32* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray3i(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec3i32* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray4i(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec4i32* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray1f(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const float* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray2f(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec2f* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray3f(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec3f* values);
  /** INTERNAL USE ONLY */
  void setShaderParameterArray4f(SoGLRenderAction* action, const SbString& paramName,
                                 size_t numElem, const SbVec4f* values);
  /** INTERNAL USE ONLY */
  void setShaderParameter1f(SoGLRenderAction* action, const SbString& paramName,
                            float value);
  /** INTERNAL USE ONLY */
  void setShaderParameter2f(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec2f& value);
  /** INTERNAL USE ONLY */
  void setShaderParameter3f(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec3f& value);
  /** INTERNAL USE ONLY */
  void setShaderParameter4f(SoGLRenderAction* action, const SbString& paramName,
                            const SbVec4f& value);
  /** INTERNAL USE ONLY */
  void setShaderParameterMatrix4(SoGLRenderAction* action, const SbString& paramName,
                                 const SbMatrix& matrix);

  /** Set OIV uniforms related to OpenGL current material state */
  void sendLazyElementUniforms(SoState* state);

  /** Disable light n in shader */
  void disableLight(SoGLRenderAction* action, int num);

  /** enable given light in shader */
  void setLight(SoState* state, SoLight* light);

  /** Totally enable/disable lighting */
  void enableLighting(SoState* state, bool flag);

  /** Enable/disable color material mode in fixed pipeline shader */
  void enableColorMaterial(SoState* state, bool flag);

  /** Totally enable/disable texturing */
  void enableTexturing(SoState* state, bool flag);

  /** Disable or active object plane texgen */
  void enableTexGen(SoState* state, bool flag);

  /** Set needed texture env mode */
  void setTexEnv(SoState* state, SoTexture::Model model);

  /** Return true if it's a GLSL shader */
  bool isGlslProgram() const;

  /** Return true if shader used for shadowmap generation */
  bool isShadowShader() const;

  /** Return shader used during shadowmap pass */
  SoShaderProgram* getShadowPassShader() const;

  /** Return true if shader used for shadowmap generation */
  void setShadowShader(bool flag);

  /** This object will be added to the shader program but won't be displayed.
   * It also increases its ref count */
  void setHiddenShaderObject(const SbString& objName, SoShaderObject* obj);

  /** Remove the given object and decrease its ref count */
  void removeHiddenShaderObject(const SbString& objName);

protected:
  typedef std::vector<SoShaderObject*> ShaderObjectVector;
  typedef std::map<SbString, SoShaderObject*> ShaderObjectMap;
  /** Just for gcc 3.1 compat */
  typedef SoShaderObject::DefineMap DefineMap;

  /** Per threads member variables */
  struct Members
  {
    Members();
    ~Members();
    void unref();

    /** Create shaders needed for shadowing */
    void createShadowShaderLib();

    SoGLShaderProgram *m_glShaderProgram;
    /** True if this shader is for shadowmap rendering only */
    bool m_isShadowShader;
    std::vector<LightType> m_lights;

    /** List of shaders used for shadowing */
    ShaderObjectVector m_shadowShaderLib;

    /** List of shaders used for shadowing */
    ShaderObjectMap m_hiddenShaderObjects;

    // Contains the list of vertex and fragment shaders,
    // before modification.
    // Enable to track add/remove/change or shader objects.
    std::vector<SoShaderObject*> m_prevShaderObject;
    std::vector< SoNode * > m_toUnrefShaderObjects;

    // Checks dynamically the modifications geometry shader parameters
    bool m_geomParametersChanged;

    /** Shader used to generate the shadowmap */
    SoShaderProgram* m_shadowPassShader;

    /** Dependency on SoShadowGroupElement */
    SoCache* m_cache;

    /** List of defines */
    DefineMap m_defineMap;
  };
  SbThreadStorage<Members*> m_members;

  /** Install shader for shadowmap gen */
  void shadowMapGLRender(SoGLRenderAction* action);

  /** Create a shader suitable for shadowmap generation pass */
  virtual SoShaderProgram* generateShadowShader() const;

  // Destructor
  virtual ~SoShaderProgram();

  // Check if all shader objects are valid
  SbBool isValidShaderObjects() const;

  // Check if at least one of the shader objects has
  // its "isActive" field set to true
  SbBool isOneShaderObjectActive();

  /** Return per threads members  */
  static SoShaderProgram::Members* getMembers(const SoShaderProgram* prog);

private:
  // Required for compat with some old IV files. (cf ebug#3765)
  SoMFNode prevShaderObject;

  enum
  {
    SHADOW_LIBRARY_FRAG,
    GENERATE_SHADOWMAP_FRAG,
    SHADOW_LIBRARY_VERT,
    SHADER_LAST
  };

  /** Add a global defines to the shader object*/
  void addDefines(SoShaderObject* obj);

  /** Set needed define for shadows */
  void setShadowLibraryDefines(const ShaderObjectVector& shaderObjectsList);

  /** Check if cache is still valid */
  void updateCache(SoState *state);

  /** Add shaders needed for shadow to the given list */
  void addShadowLibrary(SoState* state, ShaderObjectVector& shaderObjectsList);

  /** If false, use empty methods for shadow function */
  void enableShadowLibrary(bool flag);

  /** Add hidden shaders to the given list  */
  void addHiddenShaderObjects(ShaderObjectVector& shaderObjectsList);

  /** Convert light into an enum used for shader uniform */
  static LightType lightToLightType(SoLight* light);

  /** Conver model into SoShaderProgram::EnvMode enum */
  static EnvMode modelToEnvMode(SoTexture::Model model);

  /** Update all entries of m_lights and send it to shader */
  void setLights(SoGLRenderAction* action);

  /** Update m_light */
  void updateLightState(SoLight* light);

  /** return true if obj1's version < obj2's version */
  static bool lessVersion(SoShaderObject* obj1, SoShaderObject* obj2);

  /** Return the max version of the shader object list */
  static SbString getMaxVersion(const ShaderObjectVector& objList);

  /** Return true if the given uniform name is not used */
  bool isUsingUniform(SoGLRenderAction* action, const SbString& uniformName);

  /** Return true if need oiv view matrix */
  bool needOivViewMatrixUniforms(SoGLRenderAction* action);

  /** Return true if need oiv model matrix */
  bool needOivModelMatrixUniforms(SoGLRenderAction* action);

  /** Return true if shaderObjects field has changed */
  bool hasShaderObjectsChanged() const;

  /** Copy shaderObjects into  m_prevShaderObject */
  void updatePrevShaderObject();

  // Checks dynamically the modifications of shaders objects
  void shaderObjectSensorCB( void *data, SoSensor *sensor);

  /** Helper method to invalidate a all objects in a ShaderObjectMap */
  static void invalidate(ShaderObjectMap::value_type& p);

  /** Add OIV_USE_ATI define if running on ATI */
  void addATIDefine();

  /** First texture unit used by internal shaders*/
  static int s_firstUsedTextureUnit;

  /** True if running on an ATI */
  static int s_useATI;
};
/*----------------------------------------------------------------------------*/

/*******************************************************************************/
SoFragmentShader*
SoShaderProgram::getFragmentShader(int pos) const
{
  assert(pos >= 0 && pos < shaderObject.getNum());
  SoShaderObject* obj = static_cast<SoShaderObject*>(shaderObject[pos]);

  if ( !obj )
    return NULL;

  assert(obj->getTypeId() == SoFragmentShader::getClassTypeId());

  return static_cast<SoFragmentShader*>(obj);
}

/*******************************************************************************/
SoVertexShader*
SoShaderProgram::getVertexShader(int pos) const
{
  assert(pos >= 0 && pos < shaderObject.getNum());
  SoShaderObject* obj = static_cast<SoShaderObject*>(shaderObject[pos]);

  if ( !obj )
    return NULL;

  assert(obj->getTypeId() == SoVertexShader::getClassTypeId());

  return static_cast<SoVertexShader*>(obj);
}

/*******************************************************************************/
SoGeometryShader*
SoShaderProgram::getGeometryShader(int pos) const
{
  assert(pos >= 0 && pos < shaderObject.getNum());
  SoShaderObject* obj = static_cast<SoShaderObject*>(shaderObject[pos]);

  if ( !obj )
    return NULL;

  assert(obj->getTypeId() == SoGeometryShader::getClassTypeId());

  return static_cast<SoGeometryShader*>(obj);
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif /*_SO_SHADER_PROGRAM_H_*/
