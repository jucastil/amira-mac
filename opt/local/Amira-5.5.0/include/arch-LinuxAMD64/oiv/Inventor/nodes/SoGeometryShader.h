/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_GEOMETRY_SHADER_H_
#define _SO_GEOMETRY_SHADER_H_

#include <Inventor/nodes/SoShaderObject.h>

/**
 * @VSGEXT Node that defines a geometry shader.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a geometry shader. See parent class SoShaderObject for details.
 *  
 *
 * @FILE_FORMAT_DEFAULT
 *    GeometryShader {
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
 *    SoShaderObject, SoFragmentShader, SoVertexShader, SoSoShaderProgram. 
 *
 * 
 */ 

class INVENTOR_API SoGeometryShader : public SoShaderObject 
{
  SO_NODE_HEADER(SoGeometryShader);

public:
  /**
   * Constructor.
   */
  SoGeometryShader();

  /**
   * Indicates if geometry shaders in the specified language are supported by 
   * your graphics board.
   */
  static SbBool isSupported(SoShaderObject::SourceType sourceType, SoState* state=NULL) ;

  /** Returns the shader type */
  virtual ShaderType getShaderType() const
  { return GEOMETRY_SHADER; }

SoINTERNAL public:

  /** register class in database */
  static void initClass();

  /** unregister class in database */
  static void exitClass();

protected:
  /** Destructor */
  virtual ~SoGeometryShader();

private:
  static int s_geometry_shader4_EXT_extensionID;
  static int s_geometry_shader4_ARB_extensionID;
};

#endif
