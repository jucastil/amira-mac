/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ANTI_SQUISH_
#define  _SO_ANTI_SQUISH_

#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAntiSquish
//
//  undoes any uneven scales in the current transformation matrix.
//  during traversal
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Transformation node that undoes non-uniform 3D scales.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node removes nonuniform 3D scaling from the current transformation matrix
 *   when traversed by an action. It is used by draggers such as the
 *   SoTrackballDragger that need to stay uniformly scaled no matter where they are
 *   located in the scene graph.
 *   
 *   The magnitude of the new scale is determined by the current transformation matrix
 *   and the sizing field. This node does not change the translation or rotation in
 *   the matrix.
 * 
 * @FILE_FORMAT_DEFAULT
 *    AntiSquish {
 *    @TABLE_FILE_FORMAT
 *       @TR sizing         @TD AVERAGE_DIMENSION
 *       @TR recalcAlways   @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoRayPickAction @BR
 *        Appends the current transformation with a new matrix to create an unsquished
 *        result.
 * 
 * 
 * @SEE_ALSO
 *    SoCenterballDragger,
 *    SoJackDragger,
 *    SoTrackballDragger,
 *    SoTransformerDragger,
 *    SoTransformation,
 *    SoTransformBoxDragger
 * 
 * 
 */ 

class INVENTOR_API SoAntiSquish : public SoTransformation {

  SO_NODE_HEADER(SoAntiSquish);

 public:

  /**
   * Creates an anti-squish node with default settings.
   */
  SoAntiSquish();

  /** Sizing */
  enum Sizing {
    /**
     *  Fits the other two axes to match the X axis, whose size is unchanged 
     */
    X,
    /**
     *  Fits the other two axes to match the Y axis, whose size is unchanged 
     */
    Y,
    /**
     *  Fits the other two axes to match the Z axis, whose size is unchanged 
     */
    Z,
    /**
     *  Uses average of 3 scales in the matrix 
     */
    AVERAGE_DIMENSION,
    /**
     *  Uses biggest of 3 scales in the matrix 
     */
    BIGGEST_DIMENSION,
    /**
     *  Uses smallest of 3 scales in the matrix 
     */
    SMALLEST_DIMENSION,
    /**
     *  Accounts for shearing; transforms a cube by the matrix and then uses length of
     * longest diagonal 
     */
    LONGEST_DIAGONAL
  };

  // Fields
  /**
   * Determines which of the algorithms enumerated by the type Sizing will be used to
   * select the new scale when the x,y, and z scales are not equal.
   * Use enum #Sizing.  Default is AVERAGE_DIMENSION.
   */
  SoSFEnum                sizing;
  /**
   * If recalcAlways is TRUE, this node calculates its unsquishing matrix every time
   * it is traversed. If FALSE, then this only occurs during the first traversal
   * folllowing a call to recalc().  Default is TRUE.
   * 
   */
  SoSFBool                recalcAlways;

  /**
   * Sets a flag so that the next time the node is traversed, it will recalculate its
   * unsquishing matrix.
   */
  void recalc();

 SoEXTENDER public:
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        pick(SoPickAction *action);
  
  // Called by actions that need to change the state with a new matrix.
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoAntiSquish();

  SbMatrix getUnsquishingMatrix( SbMatrix squishedMatrix, SbBool doInverse,
                                 SbMatrix &inverseAnswer );

 private:
  SbMatrix savedAnswer, savedInverseAnswer;

  SbBool recalcNextTime;
};

#endif /* _SO_ANTI_SQUISH_ */

