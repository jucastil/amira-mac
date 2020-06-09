/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thad Beier (MMM yyyy)
** Modified by : Dave Immel (MMM yyyy)
** Modified by : Paul Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NURBS_PROFILE_
#define  _SO_NURBS_PROFILE_

#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoProfile.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNurbsProfile
//
//
//////////////////////////////////////////////////////////////////////////////
/**
 * NURBS profile curve.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies a NURBS curve that is used as a profile.
 *   
 *   When a NURBS shape is rendered, its NURBS profile is constructed using the NURBS
 *   profile information from this node and the current profile coordinates. (Note:
 *   Here "current" means at the time the NURBS shape is traversed, not when the
 *   SoNurbsProfile is traversed.)
 *   
 *   The curve is defined in the same way as a standard SoNurbsCurve, except that the
 *   control points are constructed from the current set of profile coordinates,
 *   using the @B index @b field. 
 *
 *   When two profiles 
 *   share the same boundary, the corresponding NURBS surfaces will be joined along these
 *   profiles, producing crack-free tessellation. Two profiles share
 *   the same boundary when their #boundary fields contain the same SoNurbsBoundary node.
 *   To be rendered crack free, the surfaces must be part of the same SoNurbsGroup.
 *
 *   Note: Trimmed NURBS are correctly displayed only if an outer boundary is defined
 *   (must have counterclockwise orientation).
 * 
 * @FILE_FORMAT_DEFAULT
 *    NurbsProfile {
 *    @TABLE_FILE_FORMAT
 *       @TR index        @TD 0
 *       @TR linkage      @TD START_FIRST
 *       @TR knotVector   @TD 0
 *       @TR boundary     @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Adds a profile to the current traversal state.
 * 
 * 
 * @SEE_ALSO
 *    SoLinearProfile,
 *    SoNurbsCurve,
 *    SoProfileCoordinate2,
 *    SoProfileCoordinate3,
 *    SoNurbsGroup,
 *    SoNurbsBoundary
 * 
 * 
 */ 

class INVENTOR_API SoNurbsProfile : public SoProfile{

  SO_NODE_HEADER(SoNurbsProfile);

 public:
  /**
   * The knot vector for the NURBS curve. It must be a list of non-decreasing
   * floating point values.
   * 
   */
  SoMFFloat           knotVector;

  /**
   * Associate the profile with the specified boundary using an SoNurbsBoundary node. 
   * All profiles which are associated 
   * with the same boundary are joined together.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFNode           boundary;

  /**
   * Creates a NURBS profile curve node with default settings.
   */
  SoNurbsProfile();

 SoEXTENDER public:
  // Returns a profile as a trim curve. floatsPerVec will be either
  // 2 or 3 depending on whether the curve is non-rational or
  // rational.
  virtual void        getTrimCurve(SoState *state, int32_t &numPoints,
                                   float *&points, int &floatsPerVec,
                                   int32_t &numKnots, float *&knotVector);

  // Returns vertices approximating the profile
  virtual void        getVertices(SoState *state, int32_t &nVertices,
                                  SbVec2f *&vertices);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  int getNurbsBoundaryID() { return m_boundaryId; }
  void setNurbsBoundaryID(int id) { m_boundaryId = id; }

 protected:
  virtual ~SoNurbsProfile();

 private:
  int m_boundaryId;
};

#endif /* _SO_NURBS_PROFILE_ */

