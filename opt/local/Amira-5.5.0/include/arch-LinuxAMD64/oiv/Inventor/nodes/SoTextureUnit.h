/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Oct 2002)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_TEXTURE_UNIT_
#define  _SO_TEXTURE_UNIT_

#include <Inventor/fields/SoSFUInt32.h>
#include <Inventor/fields/SoSFEnum.h>

#include <Inventor/nodes/SoNode.h>

#include <Inventor/elements/SoTextureUnitElement.h>

class SoGLRenderAction ;
class SoCallbackAction ;

/*----------------------------------------------------------------------------*/

/**
 * 
 * @VSGEXT Node that specifies the current texture unit and the associated mapping
 * method.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node specifies the current texture unit for all subsequent 2D and 3D texture nodes
 *   (for example, SoTexture2,
 *   SoTexture2Transform, SoTextureCoordinate2, SoTextureCoordinateBinding, and
 *   SoTextureCoordinateFunction).
 *
 *   If the graphics board supports multitexturing (OpenGL 1.5
 *   or GL_ARB_multitexture extension), then multiple textures,
 *   each defined by a texture unit, can be applied to the same shape. The
 *   maximum number of texture units depends on the board and can be queried
 *   using #getMaxTextureUnit.
 *
 *   
 *   Multitexturing is supported by the following shapes:
 *      - SoCone
 *      - SoCube
 *      - SoCylinder
 *      - SoFaceSet
 *      - SoIndexedFaceSet
 *      - SoIndexedQuadMesh
 *      - SoIndexedTriangleStripSet
 *      - SoQuadMesh
 *      - SoSphere
 *      - SoTriangleStripSet
 *   
 *   Each texture unit is defined by the following texture properties:
 *      - image of the texture (derived from SoTexture)
 *      - texture coordinates (SoTextureCoordinate2, SoTextureCoordinate3, SoTextureCoordinateBinding, etc.)
 *      - automatic texture coordinates generation (derived from SoTextureCoordinateFunction)
 *      - stack of matrix transforms (SoTexture2Transform, SoTexture3Transform, SoMatrixTransform, etc.)
 *      - mapping method: image mapping or bump mapping.
 *
 *   @B Limitations@b:
 *    
 *     - Multitexturing is not supported for non convex shapes (SoShapeHints::UNKNOWN_FACE_TYPE).
 *     - Automatic texture coordinate generation (SoTextureCoordinateFunction) is not possible 
 *     for the bump mapping method.
 *     
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureUnit {
 *      @TABLE_FILE_FORMAT
 *        @TR unit             @TD 0
 *        @TR mappingMethod    @TD IMAGE_MAPPING
 *      @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction, SoCallbackAction @BR
 *        Sets the current texture unit and the associated mapping method. 
 *        Sets: SoTextureUnitElement
 * 
 * @SEE_ALSO
 *    SoBumpMappingProperty, SoTexture2, SoTexture2Transform, SoTextureCoordinate2, 
 *    SoTextureCoordinateBinding, SoTextureCoordinateFunction.
 *
 * 
 */ 

class INVENTOR_API SoTextureUnit : public SoNode {  
  SO_NODE_HEADER(SoTextureUnit) ;


 public:
  
  /** Mapping method possible values. */
  enum MappingMethod {
    /**
     * The texture stored in SoTexture2 is used as a bump map texture.
     */
    BUMP_MAPPING = SoTextureUnitElement::BUMP_MAPPING,

    /**
     * The texture stored in SoTexture2 is used as an image map texture.
     */
    IMAGE_MAPPING  = SoTextureUnitElement::IMAGE_MAPPING
  } ;

  /**
   * Specifies the texture unit identifier. Can range from
   * 0 to the largest texture unit, which is getMaxTextureUnit()-1. 
   * Values greater than the largest texture unit are
   * clamped at the largest texture unit.
   */
  SoSFUInt32 unit ;

  /**
   * Specifies the mapping method used for texture mapping.
   * Use enum #MappingMethod. Default is IMAGE_MAPPING.
   */
  SoSFEnum mappingMethod ;

  /**
   * Constructor.
   */
  SoTextureUnit() ;

  /**
   *  Returns the maximum number of texture units.
   */
  static unsigned int getMaxTextureUnit(SoState* state=NULL) ;
   
 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;

  
  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;
  
 protected:
  // Destructor
  virtual ~SoTextureUnit() ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_TEXTURE_UNIT_ */

