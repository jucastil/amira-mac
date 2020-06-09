/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_NURBS_GROUP_
#define  _SO_NURBS_GROUP_

#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoNurbsProperty.h>
#include <Inventor/elements/SoNurbsPropertyElement.h>
#include <Inventor/STL/vector>

class SoCache;
class SoState;
class SoNurbsBREPAction;
class SoBrep;

#ifndef HIDDEN_FROM_DOC 
namespace A3DPhigsCrackFreeTess
{
  class Pid_polyline_data;
  class Pid_quad_data;
}
class SoTrimList;

#endif
/**
 * @VSGEXT Group that encapsulates NURBS surfaces to be joined
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 * This node allows you to join multiple NURBS surfaces without cracks between them.
 * Surfaces which need to be joined must have profiles (SoNurbsProfile) 
 * that share the same boundary (SoNurbsBoundary).
 *
 * In order to work, profiles must have an equivalent parameterization. 
 * Evaluating two profiles with a shared boundary at the same @I t @i 
 * will give two (u,v)  pairs: (u1,v1) and (u2,v2). Then, evaluating  
 * (u1,v1) on the first NURBS 
 * surface will give a point P1 and (u2,v2) will give a point P2 on the second
 * surface. If P1 and P2 are equal (within a tolerance) then the two profiles 
 * have an equivalent parameterization.
 * 
 * The picture below is a scene graph
 * with joined surfaces: 
 * @IMAGE nurbsgroup.gif
 * 
 * In this scene, the following surfaces will be joined:
 *
 * - NS0 and NS1 with boundary NB0    
 * - NS1 and NS2 with boundary NB1    
 * - NS0 and NS2 with boundary NB2
 * 
 * @FILE_FORMAT_DEFAULT
 *    NurbsGroup {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction, SoCallbackAction, SoRayPickAction @BR
 *        Traverses each child in order.
 *        
 * @SEE_ALSO
 *    SoNurbsSurface,
 *    SoNurbsProfile,
 *    SoNurbsBoundary
 * 
 * 
 */ 
class INVENTOR_API SoNurbsGroup : public SoGroup {
  
  SO_NODE_HEADER(SoNurbsGroup);
  
 public:

  /**
   * Creates an empty NurbsGroup node.
   */
  SoNurbsGroup();
  /**
   * Destructor.
   */
  virtual ~SoNurbsGroup();

  SoEXTENDER public:
    virtual void GLRender(SoGLRenderAction *action);
    virtual void rayPick(SoRayPickAction *action);
    virtual void callback(SoCallbackAction *action);

  SoINTERNAL public:
#ifndef HIDDEN_FROM_DOC 
    static void initClass();
    static void exitClass();

    struct NurbsProperty {
      SoNurbsPropertyElement::DrawStyle style;
      int numSamplePoints;
      SoNurbsProperty::TessellationType tessType;
      float tessAngle;
      float tessDistance;
      int steps;
    };
#endif

 private:
  SoNurbsBREPAction *m_brepAction;

  void deleteBrepStruct(SoBrep *brep);
  void deleteTessData();
  void dispatchData(SbBool doTextures);
  void fillCache(SoAction *action, SbBool renderAction);
  void computeBREP(SoState *state, SoBrep *brep,
                   SoNurbsProperty::TessellationType tessType,
                   float tessAngle, float tessDistance,
                   SbBool doTextures);

  SoCache *cache;
  void createGroupCache(SoState *state);

  size_t m_numPolygons;
  std::vector<SoTrimList*> m_polygons;
  class A3DPhigsCrackFreeTess::Pid_polyline_data *m_loops;
  class A3DPhigsCrackFreeTess::Pid_polyline_data *m_isoParam;
};

#endif /* _SO_NURBS_GROUP_ */

