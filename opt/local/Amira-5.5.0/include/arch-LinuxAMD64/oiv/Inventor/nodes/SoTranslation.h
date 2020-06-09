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


#ifndef  _SO_TRANSLATION_
#define  _SO_TRANSLATION_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoTransformation.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTranslation
//
//  Node that translates by a 3D vector.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a 3D translation.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   This node defines a translation by a 3D vector.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Translation {
 *    @TABLE_FILE_FORMAT
 *       @TR translation   @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates translation into the current transformation.
 *        Sets: SoModelMatrixElement
 * 
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the translation.
 * 
 * 
 * @SEE_ALSO
 *    SoTransform
 * 
 * 
 */ 

class INVENTOR_API SoTranslation : public SoTransformation {

  SO_NODE_HEADER(SoTranslation);

 public:
  // Fields
  /**
   * Translation vector.
   * 
   */
  SoSFVec3f           translation;

  /**
   * Creates a translation node with default settings.
   */
  SoTranslation();

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
  virtual ~SoTranslation();
};

#endif /* _SO_TRANSLATION_ */

