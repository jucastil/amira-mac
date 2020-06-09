/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_PATH_SWITCH_
#define  _SO_PATH_SWITCH_

#include <Inventor/fields/SoSFPath.h>
#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPathSwitch
//
//  PathSwitch group node: traverses all children only if the path
//  traversed so far matches the one stored in the "path" field. A
//  successful match means that the N nodes in the stored path chain
//  are the same as the last N nodes in the current path, not
//  including the path switch node itself. A NULL path (the default)
//  means don't traverse the children.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Group node that traverses only when traversed along a given path.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   SoPathSwitch is a group node that traverses its children only if the current
 *   traversal path matches the SoPath in the #path field. This can be used,
 *   for example, to affect only one instance of a subgraph. The #path field
 *   contains the path up to (but not including) the SoPathSwitch. The path need not
 *   go all the way back to the root; if it does not, then only the number of
 *   ancestors that are in the path are compared to see if the children should be
 *   traversed. A NULL path means that the children are never traversed.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PathSwitch {
 *    @TABLE_FILE_FORMAT
 *       @TR path   @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction,  SoHandleEventAction @BR
 *        Traverses the children if the paths match.
 * 
 * 
 * @SEE_ALSO
 *    SoPath,
 *    SoSwitch
 * 
 * 
 */ 

class INVENTOR_API SoPathSwitch : public SoGroup {

  SO_NODE_HEADER(SoPathSwitch);

 public:
  // Fields
  /**
   * The path that must match the current traversal path.
   * 
   */
  SoSFPath            path;

  /**
   * Creates a path switch node with default settings.
   */
  SoPathSwitch();

  /**
   * Constructor that takes approximate number of children.
   */
  SoPathSwitch(int nChildren);

 SoEXTENDER public:
  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        handleEvent(SoHandleEventAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        search(SoSearchAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoPathSwitch();

 private:

  // Checks for match of path with current path
  SbBool              matchesPath(const SoPath *switchPath,
                                  const SoPath *currentPath) const;
};

#endif /* _SO_PATH_SWITCH_ */

