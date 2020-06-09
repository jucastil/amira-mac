/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_COORDINATE_DEFAULT_
#define  _SO_TEXTURE_COORDINATE_DEFAULT_

#include <Inventor/nodes/SoTextureCoordinateFunction.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCoordinateDefault
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that removes texture coordinates from state.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This node changes the current traversal state to indicate that there are no
 *   currently defined texture coordinates or texture coordinate function. This
 *   forces subsequent shapes to use their own default texture coordinates. The net
 *   result is that this node turns off any previous texture coordinate
 *   specification.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TextureCoordinateDefault {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Removes any texture coordinates or function.
 * 
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinateEnvironment,
 *    SoTextureCoordinatePlane
 * 
 * 
 */ 

class INVENTOR_API SoTextureCoordinateDefault : public SoTextureCoordinateFunction {

  SO_NODE_HEADER(SoTextureCoordinateDefault);

 public:
  // No fields.

  /**
   * Creates a node with default settings.
   */
  SoTextureCoordinateDefault();

 SoEXTENDER public:
  // These action methods all just call doAction.
  void                GLRender(SoGLRenderAction *action);
  void                pick(SoPickAction *action);
  void                callback(SoCallbackAction *action);
    
  // Updates the state for any action.
  void                doAction(SoAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTextureCoordinateDefault();
};

#endif /* _SO_TEXTURE_COORDINATE_DEFAULT_ */

