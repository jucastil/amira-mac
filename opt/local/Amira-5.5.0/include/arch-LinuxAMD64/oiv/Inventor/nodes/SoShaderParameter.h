/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_SHADER_PARAMETER_H_
#define _SO_SHADER_PARAMETER_H_

#include <Inventor/SbBasic.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFBufferObject.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFloat.h> 
#include <Inventor/fields/SoSFInt32.h> 
#include <Inventor/fields/SoSFVec2f.h> 
#include <Inventor/fields/SoSFVec2i32.h> 
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec3i32.h>  
#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFVec4i32.h>  
#include <Inventor/fields/SoSFBool.h>  
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoMFShort.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFVec2s.h>
#include <Inventor/fields/SoMFVec2i32.h>  
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoMFVec3s.h>
#include <Inventor/fields/SoMFVec3i32.h> 
#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/fields/SoMFVec4i32.h> 
#include <Inventor/fields/SoMFVec4s.h> 
#include <Inventor/fields/SoMFVec4b.h> 
#include <Inventor/fields/SoMFVec4ui32.h> 
#include <Inventor/fields/SoMFVec4us.h> 
#include <Inventor/fields/SoMFVec4ub.h> 
#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/fields/SoMFMatrix.h>
#include <Inventor/fields/SoSFNode.h> 
#include <Inventor/fields/SoMFNode.h> 
#include <Inventor/fields/SoSFEnum.h> 

// Vertex attribs
#include <Inventor/caches/SoVertexPropertyCache.h>

class SoGLShaderObject ;
class SoShaderObject ;
class SoShaderProgram ;

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Abstract base class for all shader parameter nodes. 
 *
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This is the abstract class from which all the shader parameter nodes are
 *   derived.
 *
 *   Each parameter is defined by one or both of the following properties:
 *     - name,
 *     - identifier,
 *
 *   There are two ways to specify the name of a parameter: using the field #name to specify
 *   a string, or using the field #identifier to specify an integer.
 *   This is because assembly languages (e.g., ARB_vertex_program/ARB_fragment_program) have 
 *   index naming conventions rather than string naming conventions,
 *   whereas with Cg/GLSL, it is exactly the opposite. The two fields (#name and #identifier)
 *   allow specification of uniform parameters for both types of language.
 *   Depending on the language (ARB_, Cg, or GLSL), only one of the two fields will be used.
 *
 *   Specific subclasses add fields to hold a specific type of value.
 *    
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the 
 *    format and default values. 
 *
 * @ACTION_BEHAVIOR
 *    Sets: SoUniformShaderParameterElement, SoVertexShaderParameterElement
 *  
 * @SEE_ALSO
 *    SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoVertexShaderParameter, SoVertexShaderParameter1f, SoVertexShaderParameter1s, 
 *    SoVertexShaderParameter2f, SoVertexShaderParameter2s, SoVertexShaderParameter3f, 
 *    SoVertexShaderParameter3s, SoVertexShaderParameter4f, SoVertexShaderParameter4i, 
 *    SoVertexShaderParameter4s, SoVertexShaderParameter4b, SoVertexShaderParameter4ui, 
 *    SoVertexShaderParameter4us, SoVertexShaderParameter4ub, SoVertexShaderParameterMatrix, 
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoShaderParameter : public SoNode {
  
  SO_NODE_ABSTRACT_HEADER(SoShaderParameter);
  
public:
  /**
   * Specifies the parameter's string name which is declared and used within high-level 
   * shading programs. 
   */
  SoSFString name;

  /**
   * Specifies the parameter's integer name which is declared and used within low-level 
   * shading programs.
   */
  SoSFInt32 identifier;


SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

protected:
  /**
   * Constructor.
   */
  SoShaderParameter();

  // Destructor
  virtual ~SoShaderParameter();
  
};

/**
 * 
 * @VSGEXT Abstract base class for all uniform shader parameter nodes. 
 *
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This is the abstract class from which all the uniform shader parameter nodes are
 *   derived.
 *
 *   These nodes allow users to provide uniform parameters to a given shader object (see
 *   SoShaderObject).
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   Each parameter is defined by the following properties:
 *     - name and/or identifier,
 *     - value.
 *
 *   See the base class SoShaderParameter to get information about
 *   how to specify the name and/or identifier of a parameter.
 *
 *   The following examples show how to set a parameter named "scale" in two different ways.
 *   This code sets the parameter with an SoShaderParameter included in the scene graph:
 *   \oivnetdoc
 *   \code
 *     SoShaderParameter3f parameterNode = new SoShaderParameter3f();
 *     parameterNode.name.SetValue("scale");
 *     parameterNode.value.SetValue(2, 2, 2);
 *     root.AddChild(shaderNode);   //shader is an SoShaderProgram
 *     root.AddChild(parameterNode);
 *     root.AddChild(geometryNode);
 *   \endcode
 *   \else
 *   \code 
 *     SoShaderParameter3f *parameterNode = new SoShaderParameter3f;
 *     parameterNode->name = "scale";
 *     parameterNode->value.setValue(2,2,2);
 *     root->addChild(shaderNode);   //shaderNode is an SoShaderProgram
 *     root->addChild(parameterNode);
 *     root->addChild(geometryNode);
 *   \endcode
 *   \endoivnetdoc
 *
 *   In this case, the parameter is added to the multiple field #SoShaderObject::parameter:
 *   \oivnetdoc
 *   \code
 *     SoShaderParameter3f parameterNode = new SoShaderParameter3f();
 *     parameterNode.name.SetValue("scale");
 *     parameterNode.value.SetValue(2, 2, 2);
 *     vertexShader.parameter.Set1Value(0, parameterNode);  //vertexShader is an SoVertexShader
 *     shaderNode.shaderObject.Set1Value(0, vertexShader);  //shader is an SoShaderProgram
 *     root.AddChild(shaderNode);
 *     root.AddChild(geometryNode);
 *   \endcode
 *   \else
 *   \code
 *     SoShaderParameter3f *parameterNode = new SoShaderParameter3f;
 *     parameterNode->name = "scale";
 *     parameterNode->value.setValue(2,2,2);
 *     vertexShader->parameter.set1Value(0, parameterNode);  //vertexShader is an SoVertexShader
 *     shader->shaderObject.set1Value(0, vertexShader);  //shader is an SoShaderProgram
 *     root->addChild(shaderNode);
 *     root->addChild(geometryNode);
 *   \endcode
 *   \endoivnetdoc
 *
 *    
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the 
 *    format and default values. 
 *
 *  
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoShaderParameter1f, 
 *    SoShaderParameter1i, SoShaderParameter2f, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoUniformShaderParameter : public SoShaderParameter {
  
  SO_NODE_ABSTRACT_HEADER(SoUniformShaderParameter);
public:
  enum ShaderType {
    /**
    * Parameters of the vertex shader will be modified by this node when the shader source
    * type is ARB/CG_PROGRAM.
    */
    VERTEX,
   /**
    * Parameters of the fragment shader will be modified by this node when the shader source
    * type is ARB/CG_PROGRAM.
    */
    FRAGMENT
  };

  /**
   *
   * ARB and CG shaders allow a vertex and a shader program to use the same name for a parameter.
   * When the SoShaderParameter is inserted in the scene graph, this field allows you to 
   * specify if this parameter applies to the vertex shader or the fragment shader.
   * It has no effect on GLSL shaders. Use enum #ShaderType. Default is VERTEX.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFEnum shaderType;

  virtual bool isEqual(const SoUniformShaderParameter* param) const = 0;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates a parameter's value  
  virtual void updateParameter(SoGLShaderObject *glShadObj)=0;

  // Indicates if this parameter has a regular behavior.
  // A parameter has a regular behavior if as soon as it is modified
  // the value should be sent to the vertex/fragment shader.
  // This is not the case of some parameters such as SoShaderStateMatrixParameter or 
  // SoShaderTextureParameter which depends on the state.
  SbBool isRegularBehavior() const
  { return m_isRegularBehavior ; }
SoEXTENDER public:
  void GLRender(SoGLRenderAction *action);

protected:
  /**
   * Constructor.
   */
  SoUniformShaderParameter();

  SbBool m_isRegularBehavior ;

  // Destructor
  virtual ~SoUniformShaderParameter();
  
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a float value.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type float to a given shader 
 *   object. See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter1f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter. SoShaderParameter1i, 
 *    SoShaderParameter2f, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoShaderParameter1f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter1f);
  
public:

  /**
   * Specifies the parameter's value. Default is zero.
   */

  SoSFFloat value;

  /**
   * Constructor
   */
  SoShaderParameter1f();
  
  /**
   * Equality operator.
   */
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:

  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
 
protected:
  // Destructor
  virtual ~SoShaderParameter1f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing an integer.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type integer to a given shader 
 *   object. See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter1i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter2f, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter1i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter1i);
  
public:
  /**
   * Specifies the parameter's value. Default is zero.
   */
  SoSFInt32 value;

  /**
   * Constructor
   */
  SoShaderParameter1i();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter1i();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a two-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type two-dimensional vector 
 *   of floats to a given shader object. See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter2f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter2f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter2f);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0).
   */
  SoSFVec2f value;

  /**
   * Constructor
   */
  SoShaderParameter2f();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter2f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a two-dimensional (integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type two-dimensional vector 
 *   of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter2i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter, 
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter2i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter2i);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0).
   */
  SoSFVec2i32 value;

  /**
   * Constructor
   */
  SoShaderParameter2i();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter2i();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a three-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type three-dimensional vector 
 *   of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter3f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter3f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter3f);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0,0).
   */
  SoSFVec3f value;

  /**
   * Constructor
   */
  SoShaderParameter3f();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter3f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a three-dimensional (integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type three-dimensional vector 
 *   of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter3i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter3i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter3i);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0,0).
   */
  SoSFVec3i32 value;

  /**
   * Constructor
   */
  SoShaderParameter3i();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter3i();
  
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a four-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type four-dimensional vector 
 *   of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter4f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter4f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter4f);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0,0,0).
   */
  SoSFVec4f value;

  /**
   * Constructor
   */
  SoShaderParameter4f();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameter4f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a four-dimensional (integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type four-dimensional vector 
 *   of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameter4i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameter4i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameter4i);
  
public:
  /**
   * Specifies the parameter's value. Default is (0,0,0,0).
   */
  SoSFVec4i32 value;

  /**
   * Constructor
   */
  SoShaderParameter4i();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);

protected:
  // Destructor
  virtual ~SoShaderParameter4i();
};
/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Uniform shader parameter node storing an array of float values.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of floats 
 *   to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray1f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray1f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray1f);
  
public:
  /**
   * Specifies the parameter's value. Default is one value of zero.
   */
  SoMFFloat value;

  /**
   * Constructor
   */
  SoShaderParameterArray1f();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray1f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing an array of integers.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of integers 
 *   to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray1i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray1i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray1i);
  
public:
  /**
   * Specifies the parameter's value. Default is one value of zero.
   */
  SoMFInt32 value;

  /**
   * Constructor
   */
  SoShaderParameterArray1i();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray1i();
};
/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Uniform shader parameter node storing an array of two-dimensional (float) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   two-dimensional vectors of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray2f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray2f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray2f);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0).
   */
  SoMFVec2f value;

  /**
   * Constructor
   */
  SoShaderParameterArray2f();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray2f();
};
/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Uniform shader parameter node storing an array of two-dimensional (integer) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   two-dimensional vectors of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray2i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray2i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray2i);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0).
   */
  SoMFVec2i32 value;

  /**
   * Constructor
   */
  SoShaderParameterArray2i();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray2i();
};
/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Uniform shader parameter node storing an array of three-dimensional (float) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   three-dimensional vectors of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray3f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray3f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray3f);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0,0).
   */
  SoMFVec3f value;

  /**
   * Constructor
   */
  SoShaderParameterArray3f();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray3f();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * 
 * @VSGEXT Uniform shader parameter node storing an array of three-dimensional (integer) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   three-dimensional vectors of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray3i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray3i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray3i);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0,0).
   */
  SoMFVec3i32 value;

  /**
   * Constructor
   */
  SoShaderParameterArray3i();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray3i();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * 
 * @VSGEXT Uniform shader parameter node storing an array of four-dimensional (float) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   four-dimensional vectors of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 * 
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray4f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray3i, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray4f : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray4f);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0,0,0).
   */
  SoMFVec4f value;

  /**
   * Constructor
   */
  SoShaderParameterArray4f();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray4f();
  
};
/*----------------------------------------------------------------------------*/

/**
 *
 * 
 * @VSGEXT Uniform shader parameter node storing an array of four-dimensional (integer) vectors.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   four-dimensional vectors of integers to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported with programs written using the ARB_ language.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterArray4i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 0
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray3i, SoShaderParameterArray4f, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterArray4i : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterArray4i);
  
public:
  /**
   * Specifies the parameter's value. Default is one value (0,0,0,0).
   */
  SoMFVec4i32 value;

  /**
   * Constructor
   */
  SoShaderParameterArray4i();  

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterArray4i();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * 
 * @VSGEXT Uniform shader parameter node storing a 4x4 matrix.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type 4x4 matrix of floats 
 *   to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B Caution: @b With shader programs written using the ARB_ language, identifier, identifier + 1,
 *   identifier + 2, identifier + 3 will automatically refer to 
 *   columns 0, 1, 2, and 3 of the matrix.
 *
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterMatrix {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 1 0 0 0
 *        @TR                      0 1 0 0   @TD 
 *        @TR                      0 0 1 0   @TD 
 *        @TR                      0 0 0 1   @TD 
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray3i, SoShaderParameterArray4f, SoShaderParameter4i,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterMatrix : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterMatrix);
  
public:
  /**
   * Specifies the parameter's value. Default is identity matrix.
   */
  SoSFMatrix value;

  /**
   * Constructor
   */
  SoShaderParameterMatrix();

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterMatrix();
  
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing an array of 4x4 matrices.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type array of 
 *   4x4 matrices of floats to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   @B NOTE: @b This parameter is not supported by programs witten using the ARB_ language.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterMatrixArray {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 1 0 0 0
 *        @TR                      0 1 0 0   @TD 
 *        @TR                      0 0 1 0   @TD 
 *        @TR                      0 0 0 1   @TD 
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 *
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray3i, SoShaderParameterArray4f, SoShaderParameter4i,
 *    SoShaderParameterMatrix, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterMatrixArray : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterMatrixArray);
  
public:
  /**
   * Specifies the parameter's value
   */
  SoMFMatrix value;

  /**
   * Constructor
   */
  SoShaderParameterMatrixArray();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterMatrixArray();
};
/*----------------------------------------------------------------------------*/

/**
 *
 * 
 * @VSGEXT Uniform shader parameter node storing an OpenGL state matrix.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type OpenGL state matrix
 *   to a given shader object. See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 *   This parameter @B should be only used with NVIDIA Cg @b (has no effect otherwise) and only
 *   if the profile is neither @B arbvp1 @b nor @B arbfp1@b.
 *   With either of the profiles @B arbvp1 @b and @B arbfp1@b, the OpenGL state matrix is
 *   directly accessible from the variable glstate.matrix.
 *   
 *   @B NOTE: @b Using this parameter may slow down the rendering process because each
 *   SoTransform node in the scene graph below the SoShaderProgram will break the render cache.
 *
 * @FILE_FORMAT_DEFAULT
 *    ShaderStateMatrixParameter {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR matrixType       @TD MODELVIEW
 *        @TR matrixTransform  @TD 1 0 0 0
 *       @TR                @TD 0 1 0 0
 *       @TR                @TD 0 0 1 0
 *       @TR                @TD 0 0 0 1
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2f, 
 *    SoShaderParameter2i, SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f,
 *    SoShaderParameter4i, SoShaderParameterArray1f, SoShaderParameterArray1i, 
 *    SoShaderParameterArray2f, SoShaderParameterArray2i, SoShaderParameterArray3f,
 *    SoShaderParameterArray3i, SoShaderParameterArray4f, SoShaderParameter4i,
 *    SoShaderParameterMatrix, SoShaderParameterMatrixArray, 
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderStateMatrixParameter : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderStateMatrixParameter);
  
public:

  /** Matrix type possible values. */
  enum MatrixType { 
    /**
     * The state matrix is the modelview matrix.  
     */
    MODELVIEW,

    /**
     * The state matrix is the the projection matrix.
     */
    PROJECTION,

    /**
     * The state matrix is the current texture matrix.
     */
    TEXTURE,

    /**
     * The state matrix is the modelview projection matrix (default value).
     */
    MODELVIEW_PROJECTION
  };

  /** Matrix transformation possible values. */
   enum MatrixTransform { 
   /**
    * The state matrix is unchanged (default).
    */
    IDENTITY,

    /**
     * Transpose the state matrix.
     */
    TRANSPOSE,

    /**
     * Invert the state matrix.
     */
    INVERSE,

    /**
     * Invert the transposed state matrix.
     */
    INVERSE_TRANSPOSE
  };
  
  /**
   * Specifies the type of the state matrix.
   */
  SoSFEnum matrixType;

  /**
   * Specifies the transformation to be applied to the state matrix.
   */
  SoSFEnum matrixTransform;

  /**
   * Constructor
   */
  SoShaderStateMatrixParameter();
  
  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);

protected:
  // Destructor
  virtual ~SoShaderStateMatrixParameter();

};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Uniform shader parameter node storing a user-defined structure.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a uniform parameter of type struct
 *   that they have defined in their shader source to a given shader object. 
 *   See the base class SoUniformShaderParameter for details.
 *
 *   Uniform shader parameter nodes can be inserted in the scene graph and affect all
 *   subsequent shader programs or (more commonly) can be added to the multiple field 
 *   #SoShaderObject::parameter to affect only that specific shader program.
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShaderParameterStruct {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD []
 *        @TR shaderType       @TD VERTEX
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter,
 *    SoShaderParameter1f, SoShaderParameter1i, SoShaderParameter2i, 
 *    SoShaderParameter3f, SoShaderParameter3i, SoShaderParameter4f, SoShaderParameter4i,
 *    SoShaderParameterArray1f, SoShaderParameterArray1i, SoShaderParameterArray2f, 
 *    SoShaderParameterArray2i, SoShaderParameterArray3f, SoShaderParameterArray3i,
 *    SoShaderParameterArray4f, SoShaderParameterArray4i, SoShaderParameterMatrix,
 *    SoShaderParameterMatrixArray, SoShaderStateMatrixParameter,
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */

class INVENTOR_API SoShaderParameterStruct : public SoUniformShaderParameter {
  
  SO_NODE_HEADER(SoShaderParameterStruct);
  
public:
  /**
   * Constructor
   */
  SoShaderParameterStruct();
  /**
   * The SoUniformShaderParameter nodes that fill the structure.
   */
  SoMFNode value;

  virtual bool isEqual(const SoUniformShaderParameter* param) const;

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  // Sets or updates the parameter's value 
  virtual void updateParameter(SoGLShaderObject *glShadObj);
  
protected:
  // Destructor
  virtual ~SoShaderParameterStruct();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Abstract base class for all vertex shader parameter nodes. 
 *
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This is the abstract class from which all the vertex shader parameter nodes are
 *   derived.
 *
 *   These nodes allow applications to provide per-vertex parameters to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   Each parameter is defined by the following properties:
 *     - name and/or identifier,
 *     - value.
 *
 *   See the base class SoShaderParameter for information about
 *   how to specify the name and/or identifier of a parameter.

 *   The following example shows how to set a vertex shader parameter named "scale".
 *   \oivnetdoc
 *   \code
 *     SoShaderParameter3f parameterNode = new SoShaderParameter3f();
 *     parameterNode.name.SetValue("scale");
 *     parameterNode.value.SetValue(2, 2, 2);
 *     root.AddChild(shaderNode);   //shader is an SoShaderProgram
 *     root.AddChild(parameterNode);
 *     root.AddChild(geometryNode);
 *   \endcode
 *   \else
 *   \code 
 *     SoShaderParameter3f *parameterNode = new SoShaderParameter3f;
 *     parameterNode->name = "scale";
 *     parameterNode->value.setValue(2,2,2);
 *     root->addChild(shaderNode);   //shaderNode is an SoShaderProgram
 *     root->addChild(parameterNode);
 *     root->addChild(geometryNode);
 *   \endcode
 *   \endoivnetdoc
 *
 *    
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the 
 *    format and default values. 
 *
 *  
 * @SEE_ALSO
 *    SoShaderParameter, SoUniformShaderParameter, 
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, 
 *    SoVertexShaderParameter2f, SoVertexShaderParameter2s, SoVertexShaderParameter3f, 
 *    SoVertexShaderParameter3s, SoVertexShaderParameter4f, SoVertexShaderParameter4i, 
 *    SoVertexShaderParameter4s, SoVertexShaderParameter4b, SoVertexShaderParameter4ui, 
 *    SoVertexShaderParameter4us, SoVertexShaderParameter4ub, SoVertexShaderParameterMatrix, 
 *    SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter : public SoShaderParameter {
  
  SO_NODE_ABSTRACT_HEADER(SoVertexShaderParameter);
  
SoEXTENDER public:
  virtual void doAction(SoAction *action);
  void GLRender(SoGLRenderAction *action);
  void callback(SoCallbackAction *action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  static SbBool areVertexAttribFuncAvailable();

  void getVertexAttribIndex(SoState * state, int& firstInd, int& size);

  virtual SoVPCacheFunc2 * getVertexAttribFunc() = 0;

  virtual const char * getVertexAttribPtr(int i=0)    = 0;
  virtual size_t       getVertexAttribStride()        = 0;
  virtual int          getVertexAttribNum()           = 0;
  virtual GLenum       getVertexAttribType()          = 0;
  virtual int          getVertexAttribSize()          = 0;
  virtual SbBool       getVertexAttribIsToNormalize() = 0;

protected:
  /**
   * Constructor.
   */
  SoVertexShaderParameter();

  // Destructor
  virtual ~SoVertexShaderParameter();
  
};
/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a float value.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   float to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter1f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1s, SoVertexShaderParameter2f, SoVertexShaderParameter2s,
 *    SoVertexShaderParameter3f, SoVertexShaderParameter3s, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter1f : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter1f);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter1f();

  /**
   * Specifies the parameter's values
   */
  SoMFFloat value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr( int )      { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 1; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter1f();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a short integer value.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   short to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter1s {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter2f, SoVertexShaderParameter2s,
 *    SoVertexShaderParameter3f, SoVertexShaderParameter3s, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter1s : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter1s);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter1s();

  /**
   * Specifies the parameter's values
   */
  SoMFShort value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 1; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter1s();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a two-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   two-dimensional vector of floats to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter2f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2s,
 *    SoVertexShaderParameter3f, SoVertexShaderParameter3s, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter2f : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter2f);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter2f();

  /**
   * Specifies the parameter's values
   */
  SoMFVec2f value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 2; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter2f();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a two-dimensional (short integers) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   two-dimensional vector of short integers to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter2s {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter3f, SoVertexShaderParameter3s, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter2s : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter2s);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter2s();

  /**
   * Specifies the parameter's values
   */
  SoMFVec2s value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 *  getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 2; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter2s();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a three-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   three-dimensional vector of floats to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter3f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3s, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter3f : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter3f);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter3f();

  /**
   * Specifies the parameter's values
   */
  SoMFVec3f value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 3; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter3f();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a three-dimensional (short integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   three-dimensional vector of short integers to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter3s {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter4f,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter3s : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter3s);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter3s();

  /**
   * Specifies the parameter's values
   */
  SoMFVec3s value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 3; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter3s();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional (float) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of floats to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4f {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4f : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4f);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4f();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4f value;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4f();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional (integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *     (2*c+1)/(2^32-1), 
 *   i.e., scaling from [-2^31;2^31-1] to [-1;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4i {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4i : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4i);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4i();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4i32   value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4i();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional (short integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of short integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *     (2*c+1)/(2^16-1), 
 *   i.e., scaling from [-2^15;2^15-1] to [-1;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4s {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4s : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4s);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4s();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4s     value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 *  getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4s();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional (8-bit integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of 8-bit integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *     (2*c+1)/(2^8-1), 
 *   i.e., scaling from [-2^7;2^7-1] to [-1;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4b {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4s,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4b : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4b);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4b();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4b     value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 *  getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4b();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional (unsigned integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of unsigned integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *     c/(2^32-1), 
 *   i.e., scaling from [0;2^32-1] to [0;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4ui {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4s,
 *    SoVertexShaderParameter4b, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4ui : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4ui);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4ui();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4ui32  value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4ui();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional 
 *   (unsigned short integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of unsigned short integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *     c/(2^16-1), 
 *   i.e., scaling from [0;2^16-1] to [0;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4us {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4s,
 *    SoVertexShaderParameter4b, SoVertexShaderParameter4ui, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4us : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4us);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4us();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4us    value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4us();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a four-dimensional 
 *   (unsigned 8-bit integer) vector.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   four-dimensional vector of unsigned 8-bit integers to shader objects.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *   The #rangeScaling field indicates if values shall be scaled to a normalized range 
 *   when they are loaded. Setting #rangeScaling to TRUE implies the following conversion
 *   for each component c of the vector: 
 *         c/(2^8-1), 
 *   i.e., scaling from [0;2^8-1] to [0;+1].
 *
 *   See the base class SoVertexShaderParameter for details.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameter4ub {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 0 0 0 1
 *        @TR rangeScaling     @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4s,
 *    SoVertexShaderParameter4b, SoVertexShaderParameter4ui, SoVertexShaderParameter4us,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameter4ub : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameter4ub);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameter4ub();

  /**
   * Specifies the parameter's values
   */
  SoMFVec4ub    value;

  /**
   * Indicates if values shall be scaled to a normalized range when they are loaded
   */
  SoSFBool      rangeScaling;
  
SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)value.getValues(0); }
  virtual size_t       getVertexAttribStride()        { return value.getValueSize(); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return rangeScaling.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameter4ub();
};

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Vertex shader parameter node storing a matrix.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of type 
 *   4x4 float matrix to shader objects.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameterMatrix {
 *      @TABLE_FILE_FORMAT
 *        @TR name             @TD ""
 *        @TR identifier       @TD 0
 *        @TR value            @TD 1 0 0 0
 *        @TR                      0 1 0 0   @TD 
 *        @TR                      0 0 1 0   @TD 
 *        @TR                      0 0 0 1   @TD 
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4f, SoVertexShaderParameter4i, SoVertexShaderParameter4s,
 *    SoVertexShaderParameter4b, SoVertexShaderParameter4ui, SoVertexShaderParameter4us,
 *    SoVertexShaderParameter4ub, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameterMatrix : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameterMatrix);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameterMatrix();

  /**
   * Specifies the parameter's values
   */
  SoMFMatrix    value;
  
SoEXTENDER public:
  virtual void doAction(SoAction *action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 *  getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int i=0);
  virtual size_t       getVertexAttribStride()        { return sizeof(SbMat); }
  virtual int          getVertexAttribNum()           { return value.getNum(); }
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return 4; }
  virtual SbBool       getVertexAttribIsToNormalize() { return FALSE; }

protected:
  // Destructor
  virtual ~SoVertexShaderParameterMatrix();

private:
  // Storing a list of the transposed matrices of the value field is necessary 
  // because Open Inventor stores matrices in row major order whereas OpenGL
  // load them in column major order. Consequently, this list is necessary, to provide 
  // values sequentially stored in column major order.
  SbMat * m_columnMajorOrderMatrices;
  int     m_matricesNumber;
  void    storeColumnMajorOrderMatrices(int startIndex);
};

/*----------------------------------------------------------------------------*/

//@TOBEWRAPPED
/**
 * @VSGEXT Vertex shader parameter node storing a buffer object.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node allows the application to provide a per-vertex parameter of any type using
 *   an SoBufferObject.
 *   See the base class SoVertexShaderParameter for details.
 *
 *   Vertex shader parameter nodes must be inserted in the scene graph.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShaderParameterBufferObject {
 *      @TABLE_FILE_FORMAT
 *        @TR name                  @TD ""
 *        @TR identifier            @TD 0
 *        @TR value                 @TD NULL
 *        @TR components            @TD 4
 *        @TR type                  @TD SbDataType::FLOAT
 *        @TR stride                @TD 0
 *        @TR shouldBeNormalized    @TD FALSE
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderParameter, SoVertexShaderParameter, SoUniformShaderParameter,
 *    SoVertexShaderParameter1f, SoVertexShaderParameter1s, SoVertexShaderParameter2f,
 *    SoVertexShaderParameter2s, SoVertexShaderParameter3f, SoVertexShaderParameter3s,
 *    SoVertexShaderParameter4i, SoVertexShaderParameter4s, SoVertexShaderParameter4b,
 *    SoVertexShaderParameter4ui, SoVertexShaderParameter4us, SoVertexShaderParameter4ub,
 *    SoVertexShaderParameterMatrix, SoShaderObject, SoShaderProgram.
 *
 * 
 */ 

class INVENTOR_API SoVertexShaderParameterBufferObject : public SoVertexShaderParameter {

  SO_NODE_HEADER(SoVertexShaderParameterBufferObject);

public:
  /**
   * Constructor
   */
  SoVertexShaderParameterBufferObject();

  /**
   * Specifies the parameter's values
   */
  SoSFBufferObject value;

  /**
   * Specifies the number of components per generic vertex parameter.
   * Must be 1, 2, 3 or 4. The default value is 4.
   */
  SoSFInt32 components;

  /**
   * Specifies the data type from the class SbDataType of each generic vertex parameter component.
   * SbDataType::Unknown is not allowed, the default value is SbDataType::FLOAT
   */
  SoSFEnum type;

  /**
   * Specifies the byte offset between consecutive generic vertex parameter. If stride is 0, the values
   * are understood to be tightly packed in the buffer object.
   * The default value is 0.
   */
  SoSFInt32 stride;
  
  /**
   * Specifies if the fixed-point data in the buffer object should be normalized when they are accessed.
   * The default value is FALSE.
   */
  SoSFBool shouldBeNormalized;

SoEXTENDER public:
  virtual void doAction(SoAction *action);

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  virtual SoVPCacheFunc2 * getVertexAttribFunc();

  virtual const char * getVertexAttribPtr(int)        { return (char *)NULL; }
  virtual size_t       getVertexAttribStride();
  virtual int          getVertexAttribNum();
  virtual GLenum       getVertexAttribType();
  virtual int          getVertexAttribSize()          { return components.getValue(); }
  virtual SbBool       getVertexAttribIsToNormalize() { return shouldBeNormalized.getValue(); }

protected:
  // Destructor
  virtual ~SoVertexShaderParameterBufferObject();
};

/*----------------------------------------------------------------------------*/



#endif /*_SO_SHADER_PARAMETER_H_*/

