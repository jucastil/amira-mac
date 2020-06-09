/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_FRAGMENT_SHADER_H_
#define _SO_FRAGMENT_SHADER_H_

#include <Inventor/nodes/SoShaderObject.h>

/**
 *
 * @VSGEXT Node that defines a fragment shader.
 * 
 * @ingroup ShaderNodes
 * 
 * @DESCRIPTION
 *   This node defines a fragment shader. See parent class SoShaderObject for details. 
 *
 * @FILE_FORMAT_DEFAULT
 *    FragmentShader {
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
 *    SoShaderObject, SoVertexShader, SoGeometryShader, SoShaderProgram. 
 *
 * 
 */ 

class INVENTOR_API SoFragmentShader : public SoShaderObject
{
  SO_NODE_HEADER(SoFragmentShader);

public:
  /**
   * Constructor.
   */
  SoFragmentShader();

  /**
   * Indicates if fragment shaders in the specified language are supported by 
   * your graphics board.
   */
  static SbBool isSupported(SoShaderObject::SourceType sourceType, SoState* state=NULL) ;

  /**
  *  Returns the maximum number of texture image units.
  */
  static unsigned int getMaxTextureImageUnit() ;

  /** Returns the shader type */
  virtual ShaderType getShaderType() const
  { return FRAGMENT_SHADER; }

SoINTERNAL public:

  /** register class in database */
  static void initClass();

  /** unregister class in database */
  static void exitClass();

  /** return true if GL_ARB_fragment_program_shadow extensions is supported */
  static bool isFragmentShadowSupported(SoState* state);

  /** return true if GL_ARB_draw_buffers extensions is supported */
  static bool isDrawBuffersSupported(SoState* state);

protected:
  /** Destructor */
  virtual ~SoFragmentShader();

private:
  static int s_fragment_program_ARB_extensionID;
  static int s_fragment_program_shadow_ARB_extensionID;
  static int s_draw_buffers_ARB_extensionID;
};

#endif /* _SO_FRAGMENT_SHADER_ */
