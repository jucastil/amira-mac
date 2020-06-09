/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Aug 2003)
**=======================================================================*/

#ifndef  _SO_TEXTURE_MATRIX_
#define  _SO_TEXTURE_MATRIX_

#include <Inventor/fields/SoSFMatrix.h> 
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureMatrix
//
//  Texture matrix node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Texture matrix node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node defines the current texture matrix applied to texture coordinates. If
 *   you are using multiple textures, note that this transformation is applied
 *   to the texture coordinates of the current texture unit (SoTextureUnit). 
 *   This transformation affects the way textures are applied to the surfaces 
 *   of subsequent shapes. This allows a user to change the size and position of 
 *   the textures on objects.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureMatrix {
 *    @TABLE_FILE_FORMAT
 *       @TR matrix   @TD 1 0 0 0
 *       @TR          @TD 0 1 0 0    
 *       @TR          @TD 0 0 1 0    
 *       @TR          @TD 0 0 0 1   
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Concatenates transformation with the current texture transformation.
 *        Sets: SoTextureMatrixElement
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTextureCoordinate2,
 *    SoTexture2Transform,
 *    SoTextureCoordinateFunction,
 *    SoTextureUnit
 * 
 * 
 */ 

class INVENTOR_API SoTextureMatrix : public SoNode {

  SO_NODE_HEADER(SoTextureMatrix);

 public:
  // Fields
  SoSFMatrix matrix ;
 
  /**
   * Creates a texture transformation node with default settings.
   */
  SoTextureMatrix();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureMatrix();
};

#endif /* _SO_TEXTURE_MATRIX_ */

