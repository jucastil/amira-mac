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


#ifndef  _SO_LINEAR_PROFILE_
#define  _SO_LINEAR_PROFILE_

#include <Inventor/nodes/SoProfile.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoLinearProfile
//
//  Piecwise linear 2D profile. The profile is defined as line
//  segments between the current profile coordinates.
//
//////////////////////////////////////////////////////////////////////////////

// This value, when used as the last value of the index field, 
// the coordinates, starting from the last index+1 (zero if there is
// only one value in the index field).
#define SO_LINEAR_PROFILE_USE_REST_OF_VERTICES  (-1)

/**
 * Piecewise-linear profile curve.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node specifies a piecewise-linear curve that is used as a profile for
 *   either a trimming patch of a NURBS surface or for the bevel of SoText3. The
 *   @B index @b field indexes into the current profile coordinates (specified in an
 *   SoProfileCoordinate2 or SoProfileCoordinate3 node). If the last value of the
 *   @B index @b field is SO_LINEAR_PROFILE_USE_REST_OF_VERTICES (-1), all remaining
 *   coordinates in the current coordinates will be used, starting with the
 *   coordinate after the previous index (all coordinates will be used if
 *   SO_LINEAR_PROFILE_USE_REST_OF_VERTICES is the only value in the @B index @b
 *   field). For example, if @B index @b contains the values [2,0,-1] and there are
 *   4 profile coordinates (0-3), it is as if the @B index @b field contains
 *   [2,0,1,2,3].
 *
 *   Note: Trimmed NURBS are correctly displayed only if an outer 
 *   boundary is defined (must have counterclockwise orientation).
 * 
 * @FILE_FORMAT_DEFAULT
 *    LinearProfile {
 *    @TABLE_FILE_FORMAT
 *       @TR index     @TD 0
 *       @TR linkage   @TD START_FIRST
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoRayPickAction,  SoCallbackAction @BR
 *        Adds a profile to the current state.
 * 
 * 
 * @SEE_ALSO
 *    SoNurbsProfile,
 *    SoProfileCoordinate2,
 *    SoProfileCoordinate3
 * 
 * 
 */ 

class INVENTOR_API SoLinearProfile : public SoProfile{

  SO_NODE_HEADER(SoLinearProfile);

 public:
  // Inherits all fields from parent class

  /**
   * Creates a linear profile node with default settings.
   */
  SoLinearProfile();

 SoEXTENDER public:
  // Returns a profile as a trim curve.  numKnots will be zero.
  // floatsPerVec will be either 2 or 3 depending on whether the
  // curve is non-rational or rational.
  virtual void        getTrimCurve(SoState *state, int32_t &numPoints,
                                   float *&points, int &floatsPerVec,
                                   int32_t &numKnots, float *&knotVector);

  // Returns vertices defining the profile
  virtual void        getVertices(SoState *state, int32_t &nVertices,
                                  SbVec2f *&vertices);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoLinearProfile();
};

#endif /* _SO_LINEAR_PROFILE_ */

