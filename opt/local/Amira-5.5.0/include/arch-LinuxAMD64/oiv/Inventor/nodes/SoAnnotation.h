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


#ifndef  _SO_ANNOTATION_
#define  _SO_ANNOTATION_

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/SoType.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoAnnotation
//
//  Annotation group node: delays rendering its children until all
//  other nodes have been traversed, turning off depth buffer
//  comparisons first. The result is that the shapes under the
//  annotation node are rendered on top of the rest of the scene.
//
//  Note that if more than one annotation node is present in a graph,
//  the order in which they are traversed determines the stacking
//  order - later nodes are rendered on top of earlier ones. Also note
//  that since depth buffer comparisons are disabled, complex 3D
//  objects may not be rendered correctly when used under annotation
//  nodes.
//
//  All non-rendering actions are inherited as is from SoSeparator.
//
//////////////////////////////////////////////////////////////////////////////
/**
 * Annotation group node.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node delays rendering its children until all other nodes have been
 *   traversed, turning off depth buffer comparisons first. The result is that the
 *   shapes under the annotation node are rendered on top of the rest of the scene.
 *   This node is derived from SoSeparator, so it saves and restores traversal state
 *   for all actions.
 *   
 *   Rendering order: @BR
 *   Objects under an SoAnnotation node are rendered after "delayed" transparent
 *   objects.  See SoGLRenderAction for more information about rendering order.
 *   Note that if more than one annotation node is present in a graph, the order in
 *   which they are traversed determines the stacking order - later nodes are
 *   rendered on top of earlier ones.
 *
 *   Note: Because depth buffer comparisons are disabled, complex 3D objects may not
 *   be rendered correctly when used under annotation nodes. 
 *   
 *   Picking: @BR
 *   Also note that the annotation node does nothing special when picking along a ray.
 *   That is, it does not modify the sorting order of intersected objects based on
 *   which ones are under annotation nodes. If your application uses annotation nodes
 *   and you want to ensure that objects under them are picked "in front of" other
 *   objects, you can tell the pick action that you want to pick all objects along
 *   the ray and then scan through the paths in the resulting picked point instances
 *   to see if any of them passes through an annotation node. Your program can then
 *   decide what to do in such a case.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Annotation {
 *    @TABLE_FILE_FORMAT
 *       @TR renderCaching        @TD AUTO
 *       @TR boundingBoxCaching   @TD AUTO
 *       @TR renderCulling        @TD AUTO
 *       @TR pickCulling          @TD AUTO
 *       @TR fastEditing          @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Delays rendering its children until all other nodes have been traversed,
 *        turning off depth buffer comparisons first.
 * 
 *    SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoRayPickAction,  SoSearchAction @BR
 *        Same as SoSeparator
 * 
 * 
 * 
 */ 

class INVENTOR_API SoAnnotation : public SoSeparator {

  SO_NODE_HEADER(SoAnnotation);

 public:

  // No fields

  /**
   * Creates an annotation node with default settings.
   */
  SoAnnotation();

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
  static void         setNoDelay(SbBool flag);
  static SbBool       getNoDelay();

 protected:
  // Destructor
  virtual ~SoAnnotation();

 private:
#ifdef _WIN32
  static SbBool noDelay;
#else
  static SbBool noDelay;
#endif
};

#endif /* _SO_ANNOTATION_ */

