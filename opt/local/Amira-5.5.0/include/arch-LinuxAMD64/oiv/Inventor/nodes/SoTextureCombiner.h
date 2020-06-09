/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_TEXTURE_COMBINER_
#define  _SO_TEXTURE_COMBINER_

/* include files */
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h> 
#include <Inventor/fields/SoSFVec4f.h> 
#include <Inventor/sys/SoGLType.h>

/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Texture combiner node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *
 * The Texture Combine Environment Mode is a texture environment function
 * that provides a wide range of programmable combiner functions using the
 * incoming fragment color, texture source color, texture constant color, and
 * the result of the previous texture environment stage as possible parameters.
 * Texture Dot3 Environment offers new combiner function to Texture Combine
 * Environment Mode. Texture Crossbar Environment Mode extends the Texture
 * Combine Environment Mode by allowing use of the texture color from different
 * texture units as sources to the texture combine function.
 *
 * @FILE_FORMAT_DEFAULT
 *    TextureCombiner {
 *    @TABLE_FILE_FORMAT
 *       @TR combineRGB                 @TD MODULATE
 *       @TR combineAlpha               @TD MODULATE
 *       @TR source0RGB                 @TD TEXTURE
 *       @TR source1RGB                 @TD PREVIOUS
 *       @TR source2RGB                 @TD CONSTANT
 *       @TR source0Alpha               @TD TEXTURE
 *       @TR source1Alpha               @TD PREVIOUS
 *       @TR source2Alpha               @TD CONSTANT
 *       @TR operand0RGB                @TD SRC_COLOR
 *       @TR operand1RGB                @TD SRC_COLOR
 *       @TR operand2RGB                @TD SRC_ALPHA
 *       @TR operand0Alpha              @TD SRC_ALPHA 
 *       @TR operand1Alpha              @TD SRC_ALPHA
 *       @TR operand2Alpha              @TD SRC_ALPHA
 *       @TR scaleRGB                   @TD 1.0
 *       @TR scaleAlpha                 @TD 1.0
 *       @TR constantColor              @TD 0.0 0.0 0.0 0.0
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    Sets: SoTextureCombinerElement
 * 
 * @SEE_ALSO
 *    SoComplexity,
 *    SoExtTexture2,
 *    SoMaterial,
 *    SoTexture,
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTexture3,
 *    SoTextureCoordinate2,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction,
 *    SoTextureCubeMap,
 *    SoTextureUnit
 *
 * 
 */ 

class INVENTOR_API SoTextureCombiner : public SoNode {  
  SO_NODE_HEADER(SoTextureCombiner) ;


 public:

  /** Texture Combiner Functions. */
  enum CombineFunction {
    /** 
     * Output fragment is source0
     */
    REPLACE = GL_REPLACE,
    /**
     * Output fragment is source0 * source1
     */
    MODULATE = GL_MODULATE,
    /**
     * Output fragment is source0 + source1
     */
    ADD = GL_ADD,
    /**
     * Output fragment is source0 + source1 - 0.5
     */
    ADD_SIGNED = GL_ADD_SIGNED,
    /**
     * Output fragment is source0 * source2 + source1 * (1 - source2)
     */
    INTERPOLATE = GL_INTERPOLATE,
    /**
     * Output fragment is source0 - source1
     */
    SUBTRACT = GL_SUBTRACT,
    /**
     * Output fragment R = G = B = @BR
     * 4*((source0r - 0.5) * (source1r -0.5) + @BR
     *    (source0g - 0.5) * (source1g -0.5) + @BR
     *    (source0b - 0.5) * (source1b -0.5) ) @BR
     * Requires GL_ARB_TEXTURE_ENV_DOT3
     */
    DOT3_RGB = GL_DOT3_RGB,
    /**
     * Output fragment R = G = B = A = @BR
     * 4*((source0r - 0.5) * (source1r -0.5) + @BR
     *    (source0g - 0.5) * (source1g -0.5) + @BR
     *    (source0b - 0.5) * (source1b -0.5) ) @BR
     * Requires GL_ARB_TEXTURE_ENV_DOT3
     */
    DOT3_RGBA = GL_DOT3_RGBA
  };
  
  /** Source Parameter enumeration values. */
  enum SourceParameter {
    /**
     * Texture environment constant color.@BR Use the #constantColor field to specify the color.
     */
  CONSTANT = GL_CONSTANT,
    /**
     * Primary color of the incoming fragment.
     */
  PRIMARY_COLOR = GL_PRIMARY_COLOR,
      /**
     * Result of previous texture combiner.@BR On texture
     * unit 0, corresponds to PRIMARY_COLOR.
     */
  PREVIOUS = GL_PREVIOUS,
    /**
     * Texture color of the current texture unit.
     */
  TEXTURE = GL_TEXTURE,
    /**
     * Texture color of texture unit 0.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE0,
    /**
     * Texture color of texture unit 1.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE1,
    /**
     * Texture color of texture unit 2.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE2,
    /**
     * Texture color of texture unit 3.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE3,
    /**
     * Texture color of texture unit 4.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE4,
    /**
     * Texture color of texture unit 5.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE5,
    /**
     * Texture color of texture unit 6.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE6,
    /**
     * Texture color of texture unit 7.@BR
     * Requires GL_ARB_texture_env_crossbar.
     */
  TEXTURE7
  };

  /**
   * Specifies the input mapping for the RGB and alpha portions of
   * operand n. See OpenGL documentation for details.
   */
  enum OperandRGBA{
  /**
   * (Cred, Cgreen, Cblue).@BR
   * Not accepted for alpha operands.
   */
  SRC_COLOR = GL_SRC_COLOR,
  
  /**
   * (1 - Cred, 1 - Cgreen, 1 - Cblue).@BR
   * Not accepted for alpha operands.
   */
  ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
  
  /**
   * (Calpha, Calpha, Calpha).
   */
  SRC_ALPHA = GL_SRC_ALPHA,
  
  /**
   * (1 - Calpha, 1 - Calpha, 1 - Calpha).
   */
  ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA
  
  };

    /**
     * Specifies the texture combiner function to apply on the source<n>RGB 
     * transformed by the operand<n>RGB. 
     * Use enum #CombineFunction. Default is MODULATE.
     */
  SoSFEnum combineRGB;
    /**
     * Specifies the texture combiner function to apply on the source<n>Alpha 
     * transformed by the operand<n>Alpha.
     * Use enum #CombineFunction. Default is MODULATE.
     */
  SoSFEnum combineAlpha;
    /**
     * Specifies one of the three sources for the RGB components.
     * Use enum #SourceParameter. Default is TEXTURE.
     */
  SoSFEnum source0RGB;
    /**
     * Specifies one of the three sources for the RGB components.
     * Use enum #SourceParameter. Default is PREVIOUS .
     */
  SoSFEnum source1RGB;
    /**
     * Specifies one of the three sources for the RGB components.
     * Use enum #SourceParameter. Default is CONSTANT.
     */
  SoSFEnum source2RGB;
  
    /**
     * Specifies one of the three sources for the alpha components.
     * Use enum #SourceParameter. Default is TEXTURE.
     */
  SoSFEnum source0Alpha;
    /**
     * Specifies one of the three sources for the alpha components.
     * Use enum #SourceParameter. Default is PREVIOUS .
     */
  SoSFEnum source1Alpha;
    /**
     * Specifies one of the three sources for the alpha components.
     * Use enum #SourceParameter. Default is CONSTANT.
     */
  SoSFEnum source2Alpha;

    /**
     * Specifies an operand to be applied on the source0RGB before applying the combiner.
     * Use enum #OperandRGBA. Default is SRC_COLOR.
     */
  SoSFEnum operand0RGB;
    /**
     * Specifies an operand to be applied on the source1RGB before applying the combiner.
     * Use enum #OperandRGBA. Default is SRC_COLOR.
     */
  SoSFEnum operand1RGB;
    /**
     * Specifies an operand to be applied on the source2RGB before applying the combiner.
     * Use enum #OperandRGBA. Default is SRC_ALPHA.
     */
  SoSFEnum operand2RGB;

    /**
     * Specifies an operand to be applied on the source0Alpha before applying the combiner.
     * Use one of the two last values of #OperandRGBA: SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
     * Default is SRC_ALPHA.
     */
  SoSFEnum operand0Alpha;
    /**
     * Specifies an operand to be applied on the source1Alpha before applying the combiner.
     * Use one of the two last values of #OperandRGBA: SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
     * Default is SRC_ALPHA.
     */
  SoSFEnum operand1Alpha;
    /**
     * Specifies an operand to be applied on the source2Alpha before applying the combiner.
     * Default is SRC_ALPHA.
     * Use one of the two last values of #OperandRGBA: SRC_ALPHA or ONE_MINUS_SRC_ALPHA.
     */
  SoSFEnum operand2Alpha;
    /**
     * Specifies the RGB scale for the entire texture operation and may be 1.0, 2.0, or 4.0.
     */
  SoSFFloat scaleRGB;
    /**
     * Specifies the alpha scale for the entire texture operation and may be 1.0, 2.0, or 4.0.
     */
  SoSFFloat scaleAlpha;
    /**
     * Specifies a constant color. Used when #SourceParameter enum is CONSTANT.
     */
  SoSFVec4f constantColor;

  /**
   * Constructor.
   */
  SoTextureCombiner() ;
   
 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;

  
  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  
 protected:
  // Destructor
  virtual ~SoTextureCombiner() ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_TEXTURE_COMBINER_ */

