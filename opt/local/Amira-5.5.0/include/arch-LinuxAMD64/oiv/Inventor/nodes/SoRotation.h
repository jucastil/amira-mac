/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ROTATION_
#define  _SO_ROTATION_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoRotation
//
//  Node that rotates by an arbitrary angle around an arbitrary 3D
//  axis.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a 3D rotation about an arbitrary axis.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a 3D rotation about an arbitrary axis through the origin. The
 *   rotation is accumulated into the current transformation, which is applied to
 *   subsequent shapes. The #rotation field provides a variety of methods for
 *   specifying the rotation.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Rotation {
 *    @TABLE_FILE_FORMAT
 *       @TR rotation   @TD 0 0 1 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates rotation transformation into the current transformation.
 *        Sets: SoModelMatrixElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the rotation.
 * 
 * 
 * @SEE_ALSO
 *    SoRotationXYZ,
 *    SoTransform
 * 
 * 
 */ 

class INVENTOR_API SoRotation : public SoTransformation {

  SO_NODE_HEADER(SoRotation);

 public:
  // Fields
  /**
   * Rotation specification.
   * 
   */
  SoSFRotation        rotation;

  /**
   * Creates a rotation node with default settings.
   */
  SoRotation();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoRotation();
};

#endif /* _SO_ROTATION_ */

