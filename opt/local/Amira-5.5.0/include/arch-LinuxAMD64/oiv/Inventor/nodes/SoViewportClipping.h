/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Damien Dallarosa (Apr 2011)
** Modified by : Tristan Mehamli (Apr 2011)
**=======================================================================*/


#ifndef  SO_VIEWPORT_CLIPPING
#define  SO_VIEWPORT_CLIPPING

#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SoType.h>

class SoGLRenderAction;

//@TOBEWRAPPED
/**
 * Viewport clipping node.
 * 
 * @ingroup Nodes
 * 
 * @DESCRIPTION
 *   This node specifies a clipping region on the screen defined by a 
 *   position and a size in pixels.  Any portion of a primitive outside
 *   this region will not be rendered.
 *
 *   Note that this clipping is applied in screen space after viewing
 *   and view clipping. (For OpenGL programmers, think of it as a call to glScissor.)
 *
 *   The clipping region also limits the effect of clearing the depth
 *   buffer using an SoDepthBuffer node.
 *
 *   @NODE_SINCE_OIV 8.6
 * 
 * @FILE_FORMAT_DEFAULT
 *    ViewClipping {
 *    @TABLE_FILE_FORMAT
 *       @TR   origin   @TD 0 0
 *       @TR   size     @TD 0 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Sets the clipping region.
 *        Sets: SoGLUpdateAreaElement
 * 
 *    SoCallbackAction,  SoRayPickAction @BR
 * 
 * @SEE_ALSO
 *    SoViewport
 *
 */ 

class INVENTOR_API SoViewportClipping : public SoNode 
{

  SO_NODE_HEADER( SoViewportClipping );

 public:

   /**
    * Specifies the position of the clip region in pixels.
    * (Although this is a float field, the values really
    * are pixels, not normalized units.) Default is 0,0.
    */
   SoSFVec2f origin;

   /**
    * Specifies the size of the clip region in pixels.
    * (Although this is a float field, the values really
    * are pixels, not normalized units.) Default is 0,0.
    */
   SoSFVec2f size;

   /**
    * Constructor.
    */
   SoViewportClipping();

SoEXTENDER public:

  /** default actions behavior */
  virtual void doAction(SoAction *action);

  /** @copydoc SoNode::pick */
  virtual void pick(SoPickAction *action);

  /** @copydoc SoNode::callback */
  virtual void callback(SoCallbackAction* action);

  /** @copydoc SoNode::GLRender */
  virtual void GLRender(SoGLRenderAction * action);

SoINTERNAL public:
  /** @copydoc SoNode::initClass */
  static void initClass();

  /** @copydoc SoNode::exitClass */
  static void exitClass();

protected:
  /** Destructor */
  virtual ~SoViewportClipping();

};

#endif // SO_VIEWPORT_CLIPPING
