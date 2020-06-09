/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SO_VERTEX_FLAG
#define _SO_VERTEX_FLAG

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFInt32.h>

class SoBevelAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVertexFlag
//
//  Node used to mark or unmark vertices in the different shapes.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Class to mark/unmark vertices for beveling.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies the current marked/unmarked vertices for all subsequent
 *   shapes. Marked vertices will be beveled by SoBevelAction; unmarked vertices will
 *   not. It is defined using @B int_32t @b arrays.
 *   
 *   For vertex-based shapes, the array elements are simply indices of the selected
 *   vertices in the coordinate array.
 *   
 *   For SoCube and SoVRMLBox, the following vertices can be marked/unmarked:
 *   
 *   @IMAGE VERTFLG2.gif 
 *   
 *   For SoCone and SoVRMLCone, at least one value greater than or equal to 0 in the
 *   array marks/unmarks the top of the cone (which is the only vertex that can be
 *   marked).
 *   
 *   For SoCylinder and SoVRMLCylinder, no vertex can be marked/unmarked.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VertexFlag {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexMarked     @TD -1
 *       @TR vertexUnmarked   @TD -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    Sets: SoVertexFlagElement
 * 
 * @SEE_ALSO
 *    SoBevelAction,
 *    SoBevelProperty,
 *    SoEdgeFlag
 * 
 * 
 */ 

class INVENTOR_API SoVertexFlag : public SoNode
{
  SO_NODE_HEADER(SoVertexFlag);

 public:
  // Fields
  // Vertices can be marked using an int array. The values of the array determinate the vertices to mark.
  // These values are interpreted differently by the different shapes.
  SoMFInt32 vertexMarked;

  /**
   * These are the fields for marked/unmarked vertices. If a vertex appears in both
   * arrays, it is unmarked.
   * 
   */
  SoMFInt32 vertexUnmarked;

  /**
   * Constructor.
   */
  SoVertexFlag();

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
#ifdef NEEDS_MARKS_FOR_GL
  virtual void  GLRender(SoGLRenderAction *action);
#endif /* NEEDS_MARKS_FOR_GL */
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void  callback(SoCallbackAction *action);
  virtual void  pick(SoPickAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);
  virtual void  bevel(SoBevelAction *action);

 SoINTERNAL public:
  static void           initClass();
  static void           exitClass();

 protected:
  virtual ~SoVertexFlag();
};

#endif

