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


#ifndef  _SO_ROTATION_XYZ_
#define  _SO_ROTATION_XYZ_

#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoRotationXYZ
//
//  Node that rotates by an arbitrary angle around the x, y, or z axis.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a 3D rotation about the x-, y-, or z-axis.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a 3D rotation about one of the three principal axes. The
 *   rotation is accumulated into the current transformation, which is applied to
 *   subsequent shapes.
 * 
 * @FILE_FORMAT_DEFAULT
 *    RotationXYZ {
 *    @TABLE_FILE_FORMAT
 *       @TR axis    @TD X
 *       @TR angle   @TD 0
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
 *    SoRotation,
 *    SoTransform
 * 
 * 
 */ 

class INVENTOR_API SoRotationXYZ : public SoTransformation {

  SO_NODE_HEADER(SoRotationXYZ);

 public:

   /** Rotation axis enumeration values. */
  enum Axis {
    /**
     *  The X-axis 
     */
    X,
    /**
     *  The Y-axis 
     */
    Y,
    /**
     *  The Z-axis 
     */
    Z
  };

  /**
   * Rotation axis.
   * Use enum #Axis. Default is X.
   */
  SoSFEnum axis;
  /**
   * Rotation angle (in radians), using the right-hand rule.
   * 
   */
  SoSFFloat angle;

  /**
   * Creates a rotation node with default settings.
   */
  SoRotationXYZ();

  /**
   * Returns an SbRotation equivalent to the specified rotation.
   */
  SbRotation getRotation() const;

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
  virtual ~SoRotationXYZ();
};

#endif /* _SO_ROTATION_XYZ_ */

