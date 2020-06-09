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


#ifndef  _SO_PROFILE_
#define  _SO_PROFILE_

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoProfile
//
//  Abstract base class of 2D profiles.  These profiles are used as trim
//  curves for nurbs and bevels for 3D text.  The two (so far) subclasses
//  are SoLinearProfile and SoNurbsProfile
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Abstract base class for all profile nodes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node is the abstract base class for all profile nodes, which define 2D
 *   curves. A profile is not itself geometry, but is used to change or delimit the
 *   geometry of something else. For an SoText3 node, the profile determines the
 *   cross-section of the side of each text character. For an SoNurbsSurface node,
 *   the profile is used to specify trim curves for the surface.
 *   
 *   The current profile state can consist of one or more profiles, each of which can
 *   be made up of one or more instances of SoProfile subclass nodes. Each profile
 *   node specifies (in the #index field) a set of indices that refer to the
 *   current set of profile coordinates, specified using either an
 *   SoProfileCoordinate2 or an SoProfileCoordinate3 node. No profile curve should
 *   intersect itself or another profile curve.
 *   
 *   Profiles are part of the state, just like all other properties. The state
 *   contains a current list of profiles. Depending on the #linkage field, a
 *   profile can clear the list and begin a new profile, begin a new profile at the
 *   end of those already in the list, or append to the last profile in the current
 *   list. Note that when appending profile B to the end of profile A, B must begin
 *   at the same 2D point at which A ends.
 * 
 * @FILE_FORMAT_DEFAULT
 *    This is an abstract class. See the reference page of a derived class for the
 *   format and default values.
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Adds profile to current traversal state. Sets: SoProfileElement
 * 
 * 
 * @SEE_ALSO
 *    SoLinearProfile,
 *    SoNurbsProfile,
 *    SoNurbsSurface,
 *    SoProfileCoordinate2,
 *    SoProfileCoordinate3,
 *    SoText3
 * 
 * 
 */ 

class INVENTOR_API SoProfile : public SoNode{

  SO_NODE_ABSTRACT_HEADER(SoProfile);

 public:
   /** Profile */
  enum Profile {
    /**
     *  Start a new profile and remove any existing profiles from the current list 
     */
    START_FIRST    = SoProfileElement::START_FIRST,
    /**
     *  Start a new profile and add it to the current list 
     */
    START_NEW      = SoProfileElement::START_NEW,
    /**
     *  Add to end of the last profile in the current list 
     */
    ADD_TO_CURRENT = SoProfileElement::ADD_TO_CURRENT
  };

  // Fields
  /**
   * Indices into profile coordinates.
   * 
   */
  SoMFInt32           index;
  /**
   * Specifies connectivity of profile curve with respect to profiles in current list
   * in state. Use enum #Profile. Default is START_FIRST.
   * 
   */
  SoSFEnum            linkage;

 SoEXTENDER public:
  // These action methods are implemented for profiles. Each of them
  // just adds the profile to the current state.
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

  // Returns a profile as a trim curve.  numKnots is zero if the
  // curve is linear. floatsPerVec will be either 2 or 3 depending
  // on whether the curve is non-rational or rational.
  virtual void        getTrimCurve(SoState *state, int32_t &numPoints,
                                   float *&points, int &floatsPerVec,
                                   int32_t &numKnots, float *&knotVector) = 0;

  // Returns vertices approximating the profile
  virtual void        getVertices(SoState *state, int32_t &nVertices,
                                  SbVec2f *&vertices) = 0;

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoProfile();

  virtual ~SoProfile();
};

#endif /* _SO_PROFILE_ */

