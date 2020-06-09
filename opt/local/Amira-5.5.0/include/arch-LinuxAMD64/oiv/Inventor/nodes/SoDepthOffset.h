/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Dec 2008)
**=======================================================================*/


#ifndef SO_DEPTH_OFFSET_H
#define SO_DEPTH_OFFSET_H

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>

/**
 * @VSGEXT Property node that applies a depth offset.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *
 * This node can be used to offset shapes that are co-planar, in
 * order to resolve depth buffer artifacts, commonly called z-buffer "stitching".
 *
 * The effect is similar to SoPolygonOffset but this node uses a different 
 * algorithm (based on Lengyel's method from Game Programming Gems and improved by VSG) in which 
 * the projection matrix is modified to offset subsequent geometry. As a result 
 * it has advantages over SoPolygonOffset in some cases. Specifically, 
 * SoDepthOffset applies its offset value to all types of geometry, not just 
 * polygons, and does not require any additional per-vertex calculations on the GPU.
 *
 * The #offset value is accumulated in the traversal state. For example:
 *   @IMAGE depthOffsetState.png
 *
 * SoDepthOffset has two limitations.  First, since it modifies the projection matrix 
 * during traversal, it may prevent building a render cache for part of the scene graph. 
 * Second, the offset does not take into account the depth slope of the geometry (as
 * SoPolygonOffset does), so a larger offset may be required for geometry that is not
 * perpendicular to the view vector (facing the camera).
 *
 * The render caching issue is easily handled, by adjusting your scene graph structure, 
 * just as you would for any non-cacheable node, to ensure that the actual shape nodes 
 * are cached even if the parent group node cannot cache: @BR
 *   For example, using this scene graph structure: @BR
 *   @IMAGE depthOffsetCache.png
 *
 *   instead of this one: @BR
 *   @IMAGE depthOffsetNoCache.png
 *
 *   
 * @FILE_FORMAT_DEFAULT
 *    DepthOffset {
 *    @TABLE_FILE_FORMAT
 *       @TR offset   @TD 0.001
 *       @TR on       @TD TRUE
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *        Sets: SoProjectionMatrixElement
 * 
 * @SEE_ALSO
 *    SoPolygonOffset, SoDepthBuffer
 *
 * 
 */

class INVENTOR_API SoDepthOffset : public SoNode
{
  SO_NODE_HEADER(SoDepthOffset);

public:
  /**
   * Constructor.
   */
  SoDepthOffset();

  /** @TOBEREVIEWED
   * Offset to apply to the projection matrix. @BR
   * Positive values move geometry toward the camera (the opposite of SoPolygonOffset).
   * Offset value must be in the range [-0.5 .. 0.5] (offset is expressed in a constant value in the normalized device coordinates depth).
   * Default is 0.001
   */
  SoSFFloat offset;

  /**
   * Enables depth offset.
   * @FIELD_SINCE_OIV 8.1
   */
  SoSFBool on;


SoINTERNAL public:
  static void initClass();
  static void exitClass();

  virtual void GLRender(SoGLRenderAction* action);
  virtual void search( SoSearchAction* action );

protected:
  /** Destructor. */
  virtual ~SoDepthOffset();

private:
  static SbBool s_compat80;
  static uint32_t instanceCount;
};

#endif //SO_DEPTH_OFFSET_H

/**/
