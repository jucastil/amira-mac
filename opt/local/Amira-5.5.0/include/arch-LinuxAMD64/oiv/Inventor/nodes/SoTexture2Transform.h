/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Thaddeus Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_2_TRANSFORM_
#define  _SO_TEXTURE_2_TRANSFORM_

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture2Transform
//
//  2D Texture transformation node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * 2D texture transformation node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node defines a 2D transformation applied to texture coordinates. If
 *   you are using multiple textures, note that this transformation is applied
 *   to the texture coordinates of the current texture unit (SoTextureUnit). 
 *   This transformation affects the way textures are applied to the surfaces 
 *   of subsequent shapes. The
 *   transformation consists of (in order) a non-uniform scale about an arbitrary
 *   center point, a rotation about that same point, and a translation. (Note: while
 *   the transformations can be thought of as being applied in that order, the GL
 *   matrices are actually premultiplied in the opposite order. Therefore, the
 *   operations are listed in the reverse order throughout this reference page.) This
 *   allows a user to change the size and position of the textures on objects.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Texture2Transform {
 *    @TABLE_FILE_FORMAT
 *       @TR translation   @TD 0 0
 *       @TR rotation      @TD 0
 *       @TR scaleFactor   @TD 1 1
 *       @TR center        @TD 0 0
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
 *    SoTextureCoordinateFunction,
 *    SoTextureUnit
 * 
 * 
 */ 

class INVENTOR_API SoTexture2Transform : public SoNode {

  SO_NODE_HEADER(SoTexture2Transform);

 public:
  // Fields
  /**
   * Translation in S and T.
   * 
   */
  SoSFVec2f           translation;
  /**
   * Counterclockwise rotation of the coordinate space, in radians. This results in
   * a clockwise rotation of the texture on the object.
   * 
   */
  SoSFFloat           rotation;
  /**
   * Scaling factors in S and T.
   * 
   */
  SoSFVec2f           scaleFactor;
  /**
   * Center point used for scaling and rotation.
   * 
   */
  SoSFVec2f           center;

  /**
   * Creates a texture transformation node with default settings.
   */
  SoTexture2Transform();

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
  virtual ~SoTexture2Transform();
};

#endif /* _SO_TEXTURE_2_TRANSFORM_ */

