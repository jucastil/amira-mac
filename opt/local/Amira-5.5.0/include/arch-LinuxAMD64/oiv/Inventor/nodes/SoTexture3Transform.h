/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Feb 2000)
**=======================================================================*/

#ifndef  _SO_TEXTURE_3_TRANSFORM_
#define  _SO_TEXTURE_3_TRANSFORM_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture3Transform
//
//  3D Texture transformation node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 3D texture transformation node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node defines a 3D transformation applied to texture coordinates. This
 *   affects the way textures are applied to the surfaces of subsequent shapes. The
 *   transformation consists of (in order) a non-uniform scale about an arbitrary
 *   center point, a rotation about that same point, and a translation. (Note: while
 *   the transformations can be thought of as being applied in that order, the GL
 *   matrices are actually premultiplied in the opposite order. Therefore, the
 *   operations are listed in the reverse order throughout this reference page.) This
 *   allows a user to change the size and position of the textures on objects.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Texture3Transform {
 *    @TABLE_FILE_FORMAT
 *       @TR translation   @TD 0 0 0
 *       @TR rotation      @TD 0
 *       @TR scaleFactor   @TD 1 1 1
 *       @TR center        @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Concatenates transformation with the current texture transformation.
 *        Sets: SoTextureMatrixElement
 * 
 * @SEE_ALSO
 *    SoTexture3,
 *    SoTextureCoordinate3,
 *    SoTextureCoordinateFunction
 * 
 * 
 */ 

class INVENTOR_API SoTexture3Transform : public SoNode {

  SO_NODE_HEADER(SoTexture3Transform);

public:
  // Fields
  /**
   * Translation in S, T, and R.
   * 
   */
  SoSFVec3f           translation;
  /**
   * Counterclockwise rotation of the coordinate space, in radians. This results in
   * a clockwise rotation of the texture on the object.
   * 
   */
  SoSFFloat           rotation;
  /**
   * Scaling factors in S, T, and R.
   * 
   */
  SoSFVec3f           scaleFactor;
  /**
   * Center point used for scaling and rotation.
   * 
   */
  SoSFVec3f           center;

  /**
   * Creates a texture transformation node with default settings.
   */
  SoTexture3Transform();

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
  virtual ~SoTexture3Transform();
};

#endif /* _SO_TEXTURE_3_TRANSFORM_ */

