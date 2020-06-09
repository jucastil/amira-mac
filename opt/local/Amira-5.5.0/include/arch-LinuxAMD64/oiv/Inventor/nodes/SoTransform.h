/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORM_
#define  _SO_TRANSFORM_

#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransform
//
//  Geometric transformation node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * General 3D geometric transformation node.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a geometric 3D transformation consisting of (in order) a
 *   (possibly) non-uniform scale about an arbitrary point, a rotation about an
 *   arbitrary point and axis, and a translation. (While the transformations can be
 *   thought of as being applied in that order, matrices are actually premultiplied
 *   in the opposite order. Therefore, the operations are listed in the reverse order
 *   throughout this reference page.)
 * 
 * @FILE_FORMAT_DEFAULT
 *    Transform {
 *    @TABLE_FILE_FORMAT
 *       @TR translation        @TD 0 0 0
 *       @TR rotation           @TD 0 0 1 0
 *       @TR scaleFactor        @TD 1 1 1
 *       @TR scaleOrientation   @TD 0 0 1 0
 *       @TR center             @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates transformation into the current transformation.
 *        Sets: SoModelMatrixElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the total transformation.
 * 
 * 
 * @SEE_ALSO
 *    SoMatrixTransform,
 *    SoResetTransform,
 *    SoRotation,
 *    SoRotationXYZ,
 *    SoScale,
 *    SoTransformManip,
 *    SoTransformSeparator,
 *    SoTranslation
 * 
 * 
 */ 

class INVENTOR_API SoTransform : public SoTransformation {

  SO_NODE_HEADER(SoTransform);

 public:
  // Fields
  /**
   * Translation vector.
   * 
   */
  SoSFVec3f           translation;
  /**
   * Rotation specification.
   * 
   */
  SoSFRotation        rotation;
  /**
   * Scale factors.
   * Non-positive values may cause undesirable results.
   */
  SoSFVec3f           scaleFactor;
  /**
   * Rotational orientation for scale.
   * 
   */
  SoSFRotation        scaleOrientation;
  /**
   * Origin for scale and rotation.
   * 
   */
  SoSFVec3f           center;

  /**
   * Creates a transformation node with default settings.
   */
  SoTransform();

  /**
   * Sets the node to translate the origin to the @B fromPoint @b and rotate the
   * negative z-axis (0,0,-1) to lie on the vector from @B fromPoint @b to
   * @B toPoint @b. This always tries to keep the "up" direction the positive
   * y-axis, unless that is impossible. All current field values in the node are
   * replaced.
   */
  void                pointAt(const SbVec3f &fromPoint,
                              const SbVec3f &toPoint);

  /**
   * Returns composite matrix that transforms from object space to
   * scale space (the space after the scale).
   */
  void                getScaleSpaceMatrix(SbMatrix &mat, SbMatrix &inv) const;
  /**
   * Returns composite matrix that transforms from object space to
   * rotation space (the space after the scale and rotation).
   */
  void                getRotationSpaceMatrix(SbMatrix &mat,
                                             SbMatrix &inv) const;
  /**
   * Returns composite matrix that transforms from object space to
   * translation space (the space after scale, rotation, and translation).
   */
  void                getTranslationSpaceMatrix(SbMatrix &mat,
                                                SbMatrix &inv) const;

  /**
   * Convenience function that combines the effects of a matrix
   * transformation into the current transformation stored in this node. This
   * method premultiplies the transformation.
   */
  void                multLeft(const SbMatrix &mat);
  /**
   * Convenience function that combines the effects of a matrix
   * transformation into the current transformation stored in this node. This
   * method postmultiplies the transformation.
   */
  void                multRight(const SbMatrix &mat);

  /**
   * Convenience function that combines the effects of another
   * transformation node into the current transformation stored in this node. This
   * method premultiplies the transformation.
   */
  void                combineLeft(SoTransformation *nodeOnLeft);
  /**
   * Convenience function that combines the effects of another
   * transformation node into the current transformation stored in this node. This
   * method postmultiplies the transformation.
   */
  void                combineRight(SoTransformation *nodeOnRight);

  /**
   * Sets the fields in the node to implement the transformation represented by the
   * given matrix. Note that invalid matrices (such as singular ones) have undefined
   * results.
   */
  void                setMatrix(const SbMatrix &mat);

  /**
   * Changes the center of the transformation to the given point without affecting
   * the overall effect of the transformation.
   */
  void                recenter(const SbVec3f &newCenter);

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
  virtual ~SoTransform();

};

#endif /* _SO_TRANSFORM_ */

