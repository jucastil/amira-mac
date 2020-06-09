/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_VERTEX_SHADER_H_
#define _SO_VERTEX_SHADER_H_

#include <Inventor/nodes/SoShaderObject.h>

/*----------------------------------------------------------------------------*/

/**
 *
 * @VSGEXT Node that defines a vertex shader.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node defines a vertex shader. See parent class SoShaderObject for details.
 *  
 *
 * @FILE_FORMAT_DEFAULT
 *    VertexShader {
 *      @TABLE_FILE_FORMAT
 *        @TR sourceProgram    @TD ""
 *        @TR sourceType       @TD FILENAME
 *        @TR isActive         @TD TRUE
 *        @TR parameter        @TD NULL
 *      @TABLE_END
 *    }
 * 
 * 
 * @SEE_ALSO
 *    SoShaderObject, SoFragmentShader, SoGeometryShader, SoShaderProgram. 
 *
 * 
 */ 

class INVENTOR_API SoVertexShader : public SoShaderObject
{
  SO_NODE_HEADER(SoVertexShader);

public:
  /**
   * Constructor.
   */
  SoVertexShader();

  /**
   * Indicates if vertex shaders in the specified language are supported by 
   * your graphics board.
   */
  static SbBool isSupported(SoShaderObject::SourceType sourceType, SoState* state=NULL) ;

  /** Returns the shader type */
  virtual ShaderType getShaderType() const
  { return VERTEX_SHADER; }

SoINTERNAL public:

  /** register class in database */
  static void initClass();

  /** unregister class in database */
  static void exitClass();

protected:
  /** Destructor. */
  virtual ~SoVertexShader();
private:
  static int s_vertex_program_ARB_extensionID;
};

#endif
