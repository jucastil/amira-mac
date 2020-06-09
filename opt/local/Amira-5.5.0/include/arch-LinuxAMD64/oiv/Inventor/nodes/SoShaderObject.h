/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_SHADER_OBJECT_H_
#define _SO_SHADER_OBJECT_H_

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/fields/SoMFUniformShaderParameter.h>

#include <Inventor/STL/cassert>
#include <Inventor/STL/map>

class SoGLShaderContainer ;
class SoGLShaderObject ;
class SoFieldSensor ;
class SoNodeSensor ;
class SoFileSensor ;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

// This declaration should be inside the class declaration, but that
// does not compile on Solaris with Sun's compiler...
SoINTERNAL struct SoParamSensorData {
  SoShaderObject    *shaderObject ;
  SoUniformShaderParameter *param ;
} ;

/*----------------------------------------------------------------------------*/

/**
 *
 *
 * @VSGEXT Abstract node class which defines a shader object.
 *
 * @ingroup ShaderNodes
 *
 * @DESCRIPTION
 *   This abstract node class defines either a vertex shader (SoVertexShader), a geometry
 *   shader (SoGeometryShader), or a fragment
 *   shader (SoFragmentShader) program.
 *   A program at the vertex level is called a vertex program or a vertex shader and
 *   runs on the vertex processor of the GPU. A program at the geometry level is called a geometry program
 *   or a geometry shader and runs on the geometry processor unit.
 *   A program at the fragment level is called a fragment program, fragment shader, or pixel shader and runs
 *   on the fragment processor of the GPU.
 *   Shader object nodes should not be inserted directly within a scene graph but
 *   should be added to the @I shaderObject @i field of an SoShaderProgram node.
 *
 *   A shader object is defined by the following properties:
 *      - @B Source program@b, which is the shader's source code (see #sourceProgram field),
 *      - @B Uniform parameters @b set by the application (see #parameter field),
 *      - @B State @b (active or not) (see #isActive field).
 *
 *   The source program can be specified either by a string containing the program source
 *   code, or by a filename which contains the program source code. How the sourceProgram
 *   field is interpreted depends on the field #sourceType.
 *   The shading languages accepted
 *   for the source program are @B OpenGL Shader Language (GLSL) @b, @B Cg @b from NVIDIA
 *   (see @ref NOTE1 "NOTE 1") and assembly language
 *   (@B ARB_vertex_program@b, @B ARB_fragment_program@b).  Generally GLSL is recommended
 *   because it works on any OpenGL hardware and is much higher level than the ARB commands.
 *
 *   @I Uniform @i parameters can be set through the #parameter field.  Uniform means,
 *   in the case of a vertex or geometry program, a value which is the same for all vertices
 *   in a primitive, and, in the case of a fragment program, a value which is the same for all
 *   fragments created by a primitive.
 *   Each uniform parameter is represented by an instance of a specific subclass of
 *   SoUniformShaderParameter.  For example, an SoShaderParameter1i holds a single integer value.
 *   A uniform parameter has no effect if it is not valid, that is, if there is
 *   no corresponding name (identifier) in the CG/GLSL (ARB) source program.
 *   See @ref NOTE2 "NOTE 2" for info on retrieving a texture sampler
 *   uniform parameter within a GLSL program, an NVIDIA
 *   Cg fragment program, or an ARB_vertex_program/ARB_fragment_program program.
 *
 *   A vertex shader can also use @I vertex @i parameters, which are per-vertex
 *   data passed from the application to the vertex shader.  Vertex parameters are
 *   represented by an instance of a specific subclass of SoVertexShaderParameter.
 *   For example, an SoVertexShaderParameter1f holds a set of floating point values
 *   and an SoVertexShaderParameter3f holds a set of SbVec3f values.
 *
 *   @B TIP@b: If you set the environment variable OIV_SHADER_CHECK_INTERVAL, the
 *   shader source file is checked for a change every @I n @i seconds, where @I n @i is
 *   the value specified by the variable.
 *   This allows you to edit a shader source file without needing to restart your
 *   application after each shader modification.
 *
 *   @anchor NOTE1 @B NOTE 1@b: In case of Cg, the default profile used for the vertex shader
 *   is @B arbvp1@b, and @B arbfp1 @b for a fragment shader. The environment variables
 *   OIV_CG_VTX_PROFILE and
 *   OIV_CG_FRAG_PROFILE enable you to change the vertex and fragment profiles respectively.
 *   However, we advise users to use the default profile because it enables you to retrieve the OpenGL
 *   state directly in your vertex/fragment program instead of passing the OpenGL state as uniform parameters,
 *   which could be inefficient in terms of performance.
 *
 *   @anchor NOTE2 @B NOTE 2@b: With NVIDIA Cg and ARB_vertex_program/ARB_fragment_program, a texture sampler
 *   can be retrieved in your fragment program without specifying any SoShaderParameter parameter.
 *   - With ARB_vertex_program/ARB_fragment_program, @I texture[i] @i corresponds to the texture sampler of
 *      unit @I i@i.
 *
 *   - With NVIDIA Cg, the first texture sampler parameter in your fragment program corresponds to the texture
 *     sampler of the texture unit 0, the second texture sampler parameter to the texture sampler of the texture
 *     unit 1, and so on.@BR
 *     Example:
 *     <PRE>
 *     void  main(// Inputs
 *                Input IN,
 *                uniform sampler2D rampDiffuse,   // Texture sampler 2D of the texture unit 0
 *                uniform sampler2D rampSpecular,  // Texture sampler 2D of the texture unit 1
 *                uniform sampler2D rampEdge,      // Texture sampler 2D of the texture unit 2
 *                ...
 *     </PRE>
 *   - With GLSL, an SoShaderParameter1i must used for each texture
 *     sampler in order to specify the texture unit and texture sampler
 *     uniform parameter name pair.
 *
 *  @B NOTE 3@b: With Cg and ARB languages, at least the ARB_vertex_program and
 *  ARB_fragment_program, and with GLSL, at least GL_ARB_vertex_shader,
 *  GL_ARB_fragment_shader, and GL_ARB_shader_objects OpenGL extensions must be
 *  supported by your graphics board in order to be able to define a vertex
 *  shader and a fragment shader respectively. Otherwise no shader program will be
 *  executed.
 *
 *   @B NOTE 4@b: You should keep in mind that vertex and fragment programs modify the standard OpenGL pipeline.
 *   - @B Vertex programs @b replace the following parts of the OpenGL graphics pipeline:
 *      - Vertex transformation,
 *      - Normal transformation normalization and rescaling,
 *      - Lighting,
 *      - Color material application,
 *      - Clamping of colors,
 *      - Texture coordinate generation,
 *      - Texture coordinate transformation.
 *
 *   - @B But do not replace@b:
 *      - Perspective divide and viewport mapping,
 *      - Frustum and user clipping,
 *      - Backface culling,
 *      - Primitive assembly,
 *      - Two sided lighting selection,
 *      - Polygon offset,
 *      - Polygon mode.
 *
 *   - @B Fragment programs @b replace the following parts of the OpenGL graphics pipeline:
 *      - Operations on interpolated values,
 *      - Pixel zoom,
 *      - Texture access,
 *      - Scale and bias,
 *      - Texture application,
 *      - Color table lookup,
 *      - Fog convolution,
 *      - Color sum,
 *      - Color matrix.
 *
 *   - @B But do not replace@b:
 *      - Shading model,
 *      - Histogram,
 *      - Coverage,
 *      - Minmax,
 *      - Pixel ownership test,
 *      - Pixel packing and unpacking,
 *      - Scissor,
 *      - Stipple,
 *      - Alpha test,
 *      - Depth test,
 *      - Stencil test,
 *      - Alpha blending,
 *      - Logical ops,
 *      - Dithering,
 *      - Plane masking.
 *
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *    format and default values.
 *
 * @EXAMPLE
 * \oivnetdoc
 * \code
 *   // Simple fragment shader with one uniform parameter
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
 *   // Simple fragment shader with one uniform parameter
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
 * @SEE_ALSO
 *    SoVertexShader, SoGeometryShader, SoFragmentShader, SoShaderProgram, SoShaderParameter,
 *    SoUniformShaderParameter, SoVertexShaderParameter
 *
 *
 */

class INVENTOR_API SoShaderObject : public SoNode
{

  SO_NODE_ABSTRACT_HEADER(SoShaderObject);

public:

  /** Shader Object source type possible values. */
  enum SourceType
  {
      /**
       * The source is an ARB vertex or fragment program.
       */
      ARB_PROGRAM,

      /**
       * The source is a CG program.
       */
      CG_PROGRAM,

      /**
       * The source is an OpenGL Shading Language program.
       */
      GLSL_PROGRAM,

      /**
       * Only the name of the file containing the source is given (default).
       */
      FILENAME
  };

  /**
   * Specifies if the shader object is active or not.
   */
  SoSFBool isActive;

  /**
   * Specifies the shader object's source type.
   * The type of source can be either a filename containing the program (#FILENAME), or
   * a string containing the source program (#ARB_PROGRAM,
   * #CG_PROGRAM, or #GLSL_PROGRAM).  Use enum #SourceType. Defaule is FILENAME.
   *
   * NOTE: The source type must be specified before the source program (#sourceProgram)
   * is specified.
   *
   */
  SoSFEnum sourceType;

  /**
   * Contains the shader object's source program, specified by a
   * filename (#sourceType set to #FILENAME) or by the string containing
   * the program (#sourceType set to #ARB_PROGRAM, #CG_PROGRAM, or #GLSL_PROGRAM).
   *
   * If the
   * filename is not an absolute path name, the list of directories maintained by
   * SoInput is searched. If the source program is not found in any of those directories,
   * then the file is searched for relative to the directory from which the
   * SoShaderObject node was read.
   *
   * NOTE: The source type (#sourceType) must be specified before the source program
   * is specified.
   */
  SoSFFilePathString sourceProgram;

  /**
   * Contains the shader's uniform parameters.
   *
   */
  SoMFUniformShaderParameter parameter;

  /**
  * Convenience method to create an SoShaderUniformParameter with the specified name and value
  * and add it to the given shader object.
  * UniformParamType is the type of parameter to add.
  * This function also generates the following helper methods not visible in the documentation:
  *
  * - UniformParamType* addShaderParameter{1,2,3,4}i(const SbString&, ParamValueType)
  * - UniformParamType* addShaderParameter{1,2,3,4}f(const SbString&, ParamValueType)
  * - UniformParamType* addShaderParameterArray{1,2,3,4}i(const SbString&, ParamValueType)
  * - UniformParamType* addShaderParameterArray{1,2,3,4}f(const SbString&, ParamValueType)
  * - UniformParamType* addShaderParameterMatrix
  *
  * These are template methods, so ParamValueType must have an operator= compatible with
  * the field value of the corresponding SoShaderParameter
  * (for example, addShaderParameter2f can take an SbVec2f as ParamValueType)
  */
  template<typename UniformParamType, typename ParamValueType>
  UniformParamType* addShaderParameter(const SbString& name, ParamValueType val);

  /** Type of the shader */
  enum ShaderType
  {
    /** The shader is a vertex shader. */
    VERTEX_SHADER,
    /** The shader is a geometry shader. */
    GEOMETRY_SHADER,
    /** The shader is a fragment shader. */
    FRAGMENT_SHADER
  };

  /** must be redefined by inherited class */
  virtual ShaderType getShaderType() const = 0;

  /**
  * UniformParamType is the type of parameter to set.
  * This function also generates the following helper methods not visible in the documentation:
  *
  * - void setShaderParameter{1,2,3,4}i(const SbString&, ParamValueType)
  * - void setShaderParameter{1,2,3,4}f(const SbString&, ParamValueType)
  * - void setShaderParameterArray{1,2,3,4}i(const SbString&, ParamValueType)
  * - void setShaderParameterArray{1,2,3,4}f(const SbString&, ParamValueType)
  * - void setShaderParameterParameterMatrix
  *
  * These are template methods, so ParamValueType must have an operator= compatible with
  * the field value of the corresponding SoShaderParameter
  * (for example, setShaderParameter2f can take an SbVec2f as ParamValueType).
  */
  template<typename UniformParamType, typename ParamValueType>
  void setShaderParameter(const SbString& name, ParamValueType val);

#ifndef HIDDEN_FROM_DOC
  //Generate all setFragmentParameter* methods
#define MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(ParamType)\
  /** setShaderParameter[XXX] */ \
  template<typename ParamValueType>\
  void\
  setShaderParameter ## ParamType(const SbString& name, ParamValueType val)\
  {\
  setShaderParameter<SoShaderParameter ## ParamType>(name, val);\
  }
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(1i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(2i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(3i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(4i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(1f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(2f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(3f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(4f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array1f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array2f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array3f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array4f)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array1i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array2i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array3i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Array4i)
  MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER(Matrix)
#undef MAKE_HELPHER_FUNC_SET_SHADER_PARAMETER

//Generate all addShaderParameter* methods
#define MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(ParamType)\
  /** addShaderParameter[XXX] */ \
  template<typename ParamValueType>\
  SoShaderParameter ## ParamType *\
  addShaderParameter ## ParamType(const SbString& name, ParamValueType val)\
  {\
  return addShaderParameter<SoShaderParameter ## ParamType>(name, val);\
  }
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(1i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(2i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(3i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(4i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(1f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(2f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(3f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(4f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array1f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array2f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array3f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array4f)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array1i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array2i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array3i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Array4i)
  MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER(Matrix)
#undef MAKE_HELPHER_FUNC_ADD_SHADER_PARAMETER
#endif //HIDDEN_FROM_DOC

  /*----------------------------------------------------------------------------*/

SoINTERNAL public:

  /** Create the GL shader object from a GL shader container. */
  void createGLShaderObject(SoState* state, SoGLShaderContainer *glShaderContainer,
                            const SbString& shaderVersion);

  // void updateParameter(SoState *state);

  /** Returns the GL shader object. */
  SoGLShaderObject* getGLShaderObject() const
  { return m_glShaderObject; }

  /** Get the source type. */
  SourceType getSourceType();

  static void initClass();
  static void exitClass() ;

  // Really send the parameters from start to start + num to the shaders.
  void updateParameters(int start, int num) ;

  // Really send all the parameters to the shaders.
  void updateAllParameters() ;

  // Update state matrix paramaters
  void updateStateMatrixParameters() ;

  // Returns TRUE if at least one parameter is of SoShaderStateMatrixParameter type
  SbBool containStateMatrixParameters() const
  { return (m_stateMatrixParameters.getLength() != 0) ; }

  SbString getSourceProgram() const
  { return m_sourceProgram;}

  /**
   * True if the source file has been found or if source type is not a file
   */
  inline bool isFileFound() const;

  /** True if shaderprogram must update this object*/
  inline bool needUpdate() const { return m_needUpdate; }

  /** Force shader object reconstruction */
  void invalidate();

  /** Define name with the given value */
  void setDefine(const SbString& name, const SbString& value);

  /** Remove name from the define list */
  void removeDefine(const SbString& name);

  /** cleanup existing object if invalid */
  void checkValidity();

  /** Set shader version */
  inline void setVersion(const SbString& version) { m_version = version; }

  /** Get shader version */
  const SbString& getVersion();

  /** return shader_object availability on current contex */
  static bool isShaderObjectAvailable(SoState* state);

  /** Force source code to be reloaded */
  void invalidateSource();
  
  /** Return absolute path of given filename */
  SbString getFileAbsolutePath(const SbString& filename);

protected:

  /** catch fields changes */
  virtual void notify(SoNotList *list);

  friend class SoShaderProgram;
  /** A define and its value */
  typedef std::map<SbString, SbString> DefineMap;
  typedef DefineMap::iterator DefineMapIt;

  /** Define name with the given value */
  void setGlobalDefine(const DefineMap& map);

  /** Define name with the given value */
  void setDefine(DefineMap::value_type& p);

  // Extract the source from a given file if sourceType equals FILENAME.
  void readSource();

  /**
  * Constructor.
  */
  SoShaderObject();

  // Destructor
  virtual ~SoShaderObject();

  // Sensor data
  // If this declaration is inside the class declaration, then the following
  // declaration (SoNodeSensorList) does not compile on Solaris.
//  struct SoParamSensorData {
//    SoShaderObject    *shaderObject ;
//    SoShaderParameter *param ;
//  } ;

  // Structure of a list of sensors
  struct SoNodeSensorList
  {
    int               numSensors ;
    SoNodeSensor      **sensors ;
    SoParamSensorData  *sensorsData ;
  } ;

private:
  SoGLShaderObject *m_glShaderObject;
  SourceType        m_sourceType ;
  SbString          m_sourceProgram;

  /** Shader version */
  SbString m_version;
  SbString m_profile;

  typedef std::map<SbString, SbString> StrStrMap;

  /** Get the XXX of "#version XXX" in version and the rest of source code in source*/
  void removeVersionFromSource(SbString& version, SbString& source,
                               SbString& profile) const;

  /** Fill version with the number after "#version" */
  void extractVersion(const std::string& line, SbString& version, SbString& profile) const;

  /** Return true is line contains space-like characters oly*/
  bool isEmptyLine(const std::string& line) const;

  /** Add "#define p.first p.second" at the beginning of source */
  static SbString definesAcc(const SbString& source, DefineMap::value_type& p);

  /** From Internal data return the source code to load */
  void buildSourceToLoad(SbString &builtSource);

  // Manage a list of node sensors to track when the value of a shader parameter is modified
  // Unused until now.
  void deleteParamFieldSensorList() ;
  void updateParamFieldSensorList() ;
  SoNodeSensorList m_paramSensorList ;

  //void loadSource();
  static void fileSensorCB(void *data, SoSensor *) ;
  static void parameterSensorCB(void *data, SoSensor *) ;
  static void paramSensorCB(void *data, SoSensor *sensor) ;

  /** List of defines */
  DefineMap m_defineMap;

  /** Directly comes from the shader we are attached to */
  DefineMap m_defineGlobalMap;

  /** Check for shader source change*/
  SoFileSensor* m_fileSensor;

  /** Directory where the file has been found */
  SbString m_directoryFound;

  // Checks dynamically the parameters' modifications.
  SoFieldSensor *m_paramSensor ;

  // Update the list of state matrix parameters
  void updateStateMatrixList() ;

  // Store the list of state matrix parameters
  SoNodeList    m_stateMatrixParameters ;

  // True if the shader can't be read
  bool m_fileFound;

  /** True if shaderprogram must update this object*/
  bool m_needUpdate;

  /** True if shaderObject should reread data from disk */
  bool m_needRead;

  static int s_shader_objects_extensionID;

  /** Cache relative name to full path */
  static StrStrMap s_shadersPaths;
  static SbThreadRWMutex s_shadersPathsMutex;
};
/*----------------------------------------------------------------------------*/

/*******************************************************************************/
template<typename UniformParamType, typename ParamValueType>
UniformParamType*
SoShaderObject::addShaderParameter(const SbString& name, ParamValueType val)
{
  UniformParamType *param = dynamic_cast<UniformParamType *>(parameter.findUniformParameterByName(name));
  if (param)
  {
    // This parameter already exist => prefer to replace it
    param->value.setValue(val);
  }
  else
  {
    param = new UniformParamType;
    param->name = name;
    param->value.setValue(val);
    parameter.addShaderParameter(param);
  }

  return param;
}

/*****************************************************************************/
template<typename UniformParamType, typename ParamValueType>
void
SoShaderObject::setShaderParameter(const SbString& name, ParamValueType val)
{
  SoUniformShaderParameter* param = parameter.findUniformParameterByName(name);
  assert(param);
  assert(param->isOfType(UniformParamType::getClassTypeId()) == TRUE);
  UniformParamType* i = static_cast<UniformParamType*>(param);
  i->value = val;
}

/*****************************************************************************/
bool
SoShaderObject::isFileFound() const
{
  return m_fileFound;
}

#ifdef WIN32
#pragma warning( pop )
#endif

#endif /*_SO_SHADER_OBJECT_H_*/
