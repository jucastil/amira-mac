
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


#ifndef  _SO_SCALE_
#define  _SO_SCALE_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoScale
//
//  Node that scales by arbitrary x, y, and z scale factors.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a 3D geometric scaling.
 *
 * @ingroup TransformNodes
 *
 * @DESCRIPTION
 *   This node defines a 3D scaling about the origin. If the components of the
 *   scaling vector are not all the same, this produces a non-uniform scale.
 *
 * @FILE_FORMAT_DEFAULT
 *    Scale {
 *    @TABLE_FILE_FORMAT
 *       @TR scaleFactor   @TD 1 1 1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates scaling transformation into the current transformation.
 *        Sets: SoModelMatrixElement
 *
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the scaling.
 *
 *
 * @SEE_ALSO
 *    SoTransform,
 *    SoUnits
 *
 *
 */

class INVENTOR_API SoScale : public SoTransformation {

  SO_NODE_HEADER(SoScale);

 public:
  // Fields
  /**
   * The scaling factors in the x, y, and z dimensions. 
   * Non-positive values may cause undesirable results.
   *
   */
  SoSFVec3f           scaleFactor;

  /**
   * Creates a scale node with default settings.
   */
  SoScale();

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
  virtual ~SoScale();
};

#endif /* _SO_SCALE_ */

