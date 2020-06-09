/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Damien DALLA ROSA (Apr 2011)
**=======================================================================*/

#if !defined(SO_VERTEXATTRIBFEEDBACK_H)
#define SO_VERTEXATTRIBFEEDBACK_H

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoSeparator.h>

class SoGLBufferObject;
class SoVertexAttribFeedbackImpl;


/**
* @VSGEXT Node to record vertex attributes from shaders into buffer objects.
* 
* @ingroup GroupNodes
* 
* @DESCRIPTION
* 
* This node is used to record selected vertex attributes for each primitive processed by the OpenGL
* system. The recorded vertex attributes may be stored in separate SoGLBufferObjects or interleaved 
* into a single buffer object.
*
* This node can only be used when an GLSL shader is enabled on the Open Inventor state. If the active
* shader contains a geometry shader the attributes are recorded from the varyings declared in it, 
* otherwise it records the attributes from the vertex shader.
* 
* The function registerFeedback is used to specify the buffer object, which will receive the 
* data, attached to a specified varying. 
*
* The scene graph which will be rendered during the traversal (can be any shape used as input of the
* geometry or vertex shader) is specified using the regular addChild function from the class
* SoSeparator.
*
* This node provides a mechanism for the following features:
* - Rasterizer can be disabled to prevent rendering the generated primitives. This is useful
*   when the main behavior is to record computed primitives from the geometry or vertex shader.
* - The SoGLBufferObject can be automatically resized to be able to record all the data.
* - The number of generated primitives can be retrieved after the traversal.
*
* @B Limitations @b
*
* - The automatic resize of the buffer objects requires two traversal of the children, one to 
*   compute the number of primitives which will be generated and the actual traversal.
*
* - Most of the regular actions (except Render and Write) don't traverse the children.
*
*  @FILE_FORMAT_DEFAULT
*    VertexAttribFeedback {
*    @TABLE_FILE_FORMAT
*       @TR disableFragmentProcessing       @TD TRUE
*       @TR autoResizeBuffers               @TD FALSE
*       @TR queryGeneratedPrimitivesCount   @TD FALSE
*       @TR buffersMode                     @TD SEPARATE
*       @TR primitiveType                   @TD TRIANGLES
*    @TABLE_END
*    }
*
* @ACTION_BEHAVIOR
*    SoGLRenderAction @BR
*        Do the actual vertex attributes feedback operation.
* 
* @SEE_ALSO
*    SoBufferObject, SoShaderProgram, SoBufferedShape
* 
* 
*/ 

class INVENTOR_API SoVertexAttribFeedback : public SoSeparator
{
  SO_NODE_HEADER( SoVertexAttribFeedback );

  // ----------------------- Public usage --------------------------------------

public:

  /**
   * This enum is used by the field buffersMode to
   * describe the data packing format in the buffer objects.
   */
  enum BufferMode
  {
    /** 
     * All varyings are recorded, interleaved, in a single buffer object. 
     */
    INTERLEAVED,

    /** Each varying is recorded in a separate buffer object. */
    SEPARATE
  };

  /**
   * This enum is used to setup the expected recorded primitive type from the shaders.
   */
  enum PrimitiveType
  {
    /** The shader is supposed to generate LINES */
    LINES,
    /** The shader is supposed to generate POINTS */
    POINTS,
    /** The shader is supposed to generate TRIANGLES */
    TRIANGLES
  };

  /**
   * Turn off the fragment rasterizer.
   * It means that the result of the shader is not rendered.
   *
   * Most of the time the main goal of this node is to record the result of varyings
   * from the geometry shaders and the recorded primitives are not supposed to be rendered.
   *
   * Default value is TRUE.
   */
  SoSFBool disableFragmentProcessing;

  /**
   * Set this field to TRUE when the size of the recorded varyings is not known.
   * It provides a mechanism to automatically resize the buffer objects.
   *
   * This is implemented by performing a first traversal of the children with OpenGL queries enabled
   * to record the number of generated primitives during this traversal. Then the value of the query is
   * used to compute the size in bytes of the buffer object and a second traversal is performed for the 
   * actual primitives recording.
   *
   * Default value is FALSE.
   */
  SoSFBool autoResizeBuffers;
  
  /**
   * Read back the number of recorded primitives.
   * The read back is performed only when this field is set to TRUE and the method getGeneratedPrimitivesCount
   * returns the value.
   *
   * Default value is FALSE.
   */
  SoSFBool queryGeneratedPrimitivesCount;

  /**
   * The buffer mode used to record the primitives.
   * Use enum #BufferMode. Default is SEPARATE.
   */
  SoSFEnum buffersMode;

  /**
   * The type of primitive recorded during traversal.
   * Use enum #PrimitiveType. Default is TRIANGLES.
   */
  SoSFEnum primitiveType;

  /**
  * Default constructor.
  */
  SoVertexAttribFeedback();

  /**
   * This function allows to attach a buffer object to a specific varying of the shader pushed on the state.
   * When the buffersMode field is set to INTERLEAVED only the first specified bufferObject is used.
   *
   * The primitiveSize parameter is used to compute the actual size of buffer objects when 
   * autoResizeBuffers is set to TRUE, it is ignored otherwise; It must be the size of each primitive, in bytes.
   * When the buffer mode is set to INTERLEAVED the value must be the accumulated size in bytes for all the varyings.
   * The actual buffer size is computed by multiplying the primitiveSize by the number of primitives and by the 
   * size of the data type (float).
   * When the value is -1 (the default value) Open Inventor uses 3 * sizeof(float) * numVerticesPerPrimtive,
   * which is the size of a basic triangle with 3 vertices of 3 float-components, for a triangle the computed 
   * value is 3 * sizeof(float) * 3. 
   *
   * NOTE: When the buffer mode is set to INTERLEAVED only the first specified buffer object is used
   * the following ones are ignored.
   *
   * @param varyingName The name of the varying which must will be added to the list of recorded varyings.
   * @param bufferObject The buffer object which will receive the recorded values from the varying.
   * @param primitiveSize The size, in bytes, of one primitive, used when the autoResizeBuffers field is set to TRUE.
   */
  void registerFeedback(const SbString& varyingName, SoGLBufferObject* bufferObject, int primitiveSize = -1);

  /**
   * This function is used to unregister a varying registered with the registerFeedback function.
   *
   * @param varyingName The name of the varying to unregister, previously registered using the registerFeeback function.
   */
  void unregisterFeedback(const SbString& varyingName);

  /**
   * This function returns the number of generated primitives during the traversal of the sub scene graph.
   *
   * NOTE: The returned value is undefined if the field queryGeneratedPrimitivesCount is not set to TRUE.
   *
   * @return The number of generated primitives.
   */
  int getGeneratedPrimitivesCount() const;

  /**
   * This function indicates if the vertex attributes feedback feature is available on this system.
   *
   * @return TRUE if vertex attributes feedback is supported.
   */
  static SbBool isSupported(SoState* state);

SoEXTENDER public:

  virtual void        callback(SoCallbackAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void        distribute(SoDistributeAction* action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);
  virtual void        GLRenderBelowPath(SoGLRenderAction*);

SoINTERNAL public:
  
  /** Static init function called during the OpenInventor init. */
  static void initClass();

  /** Static init function called by OpenInventor during the finish function. */
  static void exitClass();

protected:

  /** Protected destructor */
  virtual ~SoVertexAttribFeedback();

private:

  SoVertexAttribFeedbackImpl* m_impl;
};

#endif // SO_VERTEXATTRIBFEEDBACK_H
