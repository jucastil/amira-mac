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


#ifndef  _SO_RESET_TRANSFORM_
#define  _SO_RESET_TRANSFORM_

#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoResetTransform
//
//  This node resets the current transformation to be identity. It can
//  be used to achieve the effect of an absolute transformation, such
//  as translating to a specific point. It also allows the bounding
//  box computed by an SoGetBoundingBoxAction to be reset to empty
//  during traversal.
//
//  This node is dangerous and should be used with caution.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that resets the current transformation to identity.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node resets the current transformation to identity. It can be used to apply
 *   an absolute world space transformation afterwards, such as translating to a
 *   specific point from within a hierarchy. An SoResetTransform node should probably
 *   be used under an SoSeparator or SoTransformSeparator so it won't change
 *   transformations for the rest of the scene graph. An SoResetTransform node can
 *   also be used to reset the current bounding box to empty during traversal of an
 *   SoGetBoundingBoxAction, if the #whatToReset field has the @B BBOX @b bit
 *   set.
 * 
 *   CAUTION: Picking on a shape below an SoResetTransform may fail
 *   if bounding box caching is enabled (default). Bounding box caching 
 *   is set using SoSeparator.
 *
 *   Clipping and culling anomalies may also occur.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ResetTransform {
 *    @TABLE_FILE_FORMAT
 *       @TR whatToReset   @TD TRANSFORM
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        If specified, resets current transformation matrix to identity.
 *        Sets: SoModelMatrixElement, SoUnitsElement
 * 
 *    SoGetBoundingBoxAction @BR
 *        If specified, resets current transformation matrix to identity and current
 *        computed bounding box to be empty. Sets: SoBBoxModelMatrixElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns identity matrix.
 * 
 * 
 * @SEE_ALSO
 *    SoTransform
 * 
 * 
 */ 

class INVENTOR_API SoResetTransform : public SoTransformation {

  SO_NODE_HEADER(SoResetTransform);

 public:

  /** Reset Type enumeration values; defines which things get reset. */
  enum ResetType {
    /**
     *  Reset the current transformation to identity 
     */
    TRANSFORM       = 0x01,
    /**
     *  Reset the bounding box to empty 
     */
    BBOX            = 0x02
  };

  // Fields
  /**
   * Specifies which items to reset when the node is traversed.
   * 
   */
  SoSFBitMask         whatToReset;

  /**
   * Creates a reset transformation node with default settings.
   */
  SoResetTransform();

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
  virtual ~SoResetTransform();
};

#endif /* _SO_RESET_TRANSFORM_ */

