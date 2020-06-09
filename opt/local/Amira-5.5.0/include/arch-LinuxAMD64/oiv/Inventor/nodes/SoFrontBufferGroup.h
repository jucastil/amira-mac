/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Mike Heck (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_FRONTBUFFERGROUP_
#define  _SO_FRONTBUFFERGROUP_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/fields/SoSFBool.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoFrontBufferGroup
//
//  Grouping node that delays rendering its children until all other nodes
//  have been traversed *and* the buffer swap has occured (if the drawable
//  is double buffered).  The result is that shapes under this node are
//  drawn in the OpenGL "front buffer" after the buffer swap.
//
//  This is useful if part of the scene (for example a very large volume for
//  volume rendering) takes a long time to render.  Most of the scene is
//  drawn normally (double buffered), then the slow part of the scene renders
//  as you watch.  Typically the application will check for input events and
//  abort the front buffer rendering if the user starts another interaction.
//
//  The enable field can be used to select delayed or normal rendering.  For
//  example the application might use normal (double buffered) rendering for
//  small volumes and front buffer rendering for large volumes.
//
//  All non-rendering actions are inherited as is from SoSeparator.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Delayed rendering group node.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node delays rendering its children until all other nodes have been
 *   rendered and (for a double buffered drawable) the OpenGL buffer swap has
 *   occurred. The result is that the shapes under this node are always rendered in
 *   the OpenGL front buffer.
 *   
 *   This node is derived from SoSeparator, so it saves and restores traversal state
 *   for all actions. The behavior is similar to SoAnnotation, but that node only
 *   delays until the end of traversal (before the buffer swap) and also disables the
 *   OpenGL depth buffer test. This node delays until after the buffer swap and
 *   renders with normal depth buffer testing.
 *   
 *   If more than one FrontBufferGroup node is present in a graph, the order in which
 *   they are traversed determines the stacking order - later nodes are rendered on
 *   top of earlier ones. 
 *   
 *   Objects under this node are subject to the current settings for transparency type
 *   and antialiasing/smoothing, but they will not be rendered in stereo. Since
 *   SoFrontBufferGroup is intended for rendering very large/slow objects that cannot
 *   be moved interactively, it would not be desirable to draw them twice (i.e. left
 *   and right images).
 *   
 *   The FrontBufferGroup node does nothing special when picking along a ray. That is,
 *   it does not modify the sorting order of intersected objects based on which ones
 *   are under this node. If your application uses this node and you want to ensure
 *   that objects under it are picked "in front of" other objects, you can tell the
 *   pick action that you want to pick all objects along the ray and then scan
 *   through the paths in the resulting picked point instances to see if any of them
 *   passes through a FrontBufferGroup node. Your program can then decide what to do
 *   in such a case.
 * 
 * @FILE_FORMAT_DEFAULT
 *    FrontBufferGroup {
 *    @TABLE_FILE_FORMAT
 *       @TR enable               @TD TRUE
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR fastEditing          @TD DISABLE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Delays rendering its children until all other nodes have been traversed and the
 *        buffer swap has occurred, then renders in the front buffer.
 * 
 *    SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoRayPickAction,  SoSearchAction @BR
 *        Same as SoSeparator
 * 
 * 
 * 
 */ 

class INVENTOR_API SoFrontBufferGroup : public SoSeparator {

  SO_NODE_HEADER(SoFrontBufferGroup);

 public:

  // Fields
  /**
   * Controls whether children are delayed.
   * 
   */
  SoSFBool            enable;

  /**
   * Creates a FrontBufferGroup node with default settings.
   */
  SoFrontBufferGroup();

 SoEXTENDER public:
  // Implement actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        GLRenderBelowPath(SoGLRenderAction *action);
  virtual void        GLRenderInPath(SoGLRenderAction *action);
  virtual void        GLRenderOffPath(SoGLRenderAction *action);
  virtual int32_t     getRenderUnitID() const;

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  static void     setNoDelay(SbBool flag);
  static SbBool   getNoDelay();

 protected:
  // Destructor
  virtual ~SoFrontBufferGroup();

 private:
  static SbBool noDelay;  // global override for enable field
};

#endif /* _SO_FRONTBUFFERGROUP_ */


