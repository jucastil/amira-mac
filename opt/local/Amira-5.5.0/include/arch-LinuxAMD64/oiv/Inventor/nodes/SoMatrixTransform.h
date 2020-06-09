/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MATRIX_TRANSFORM_
#define  _SO_MATRIX_TRANSFORM_

#include <Inventor/fields/SoSFMatrix.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMatrixTransform
//
//  Geometric transformation node, where the transformation is stored
//  as a matrix.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that specifies a 3D geometric transformation as a matrix.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a geometric 3D transformation with a single SbMatrix. Note
 *   that some matrices (such as singular ones) may result in errors in bounding
 *   boxes, picking, and lighting.
 * 
 * @FILE_FORMAT_DEFAULT
 *    MatrixTransform {
 *    @TABLE_FILE_FORMAT
 *       @TR matrix         @TD 1 0 0 0
 *       @TR                @TD 0 1 0 0
 *       @TR                @TD 0 0 1 0
 *       @TR                @TD 0 0 0 1
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Concatenates matrix given in the #matrix field with the current
 *        transformation matrix. Sets: SoModelMatrixElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns transformation matrix specified in the #matrix field.
 * 
 * 
 * @SEE_ALSO
 *    SoTransform,
 *    SoMultipleCopy
 * 
 * 
 */ 

class INVENTOR_API SoMatrixTransform : public SoTransformation {

  SO_NODE_HEADER(SoMatrixTransform);

 public:
  // Fields
  /**
   * Transformation matrix.
   * 
   */
  SoSFMatrix          matrix;

  /**
   * Creates a matrix transformation node with default settings.
   */
  SoMatrixTransform();

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
  virtual ~SoMatrixTransform();
};

#endif /* _SO_MATRIX_TRANSFORM_ */

