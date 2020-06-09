/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_VIEWVOLUME_
#define _SB_VIEWVOLUME_

#include <Inventor/SbBase.h>
#include <Inventor/SbVec.h>
#include <Inventor/SbBox.h>
#include <Inventor/SbPlane.h>
#include <Inventor/SbRotation.h>

class SbLine;
class SbMatrix;
class SbPlane;
class SbRotation;
class SbVec2f;
class SbVec3f;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbViewVolume
//
//  Defines a 3D view volume. For perspective projection, the view
//  volume is a frustum. For orthographic (parallel) projection, the
//  view volume is a rectangular prism.
//
//////////////////////////////////////////////////////////////////////////////


/**
* 3D viewing volume class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   Class used to represent a 3D viewing volume. This class is used to represent
*   viewing frusta and picking volumes. For perspective projection, the view volume
*   is a frustum. For orthographic (parallel) projection, the view volume is a
*   rectangular prism.
*
*   The view volume used for rendering can be queried from an SoCamera node using
*   its getViewVolume() method.
*
* @SEE_ALSO
*    SbVec3f,
*    SbVec2f,
*    SbBox3f,
*    SbMatrix,
*    SbRotation
*
*
*/

class INVENTORBASE_API SbViewVolume {
public:

  /**
  * Default constructor.  The view volume is not initialized.
  */
  SbViewVolume();
  /**
  * Destructor.
  */
  ~SbViewVolume()     {}

  /**
  * Returns two matrices corresponding to the view volume. The first is a viewing
  * matrix, which is guaranteed to be an affine transformation. The second is
  * suitable for use as a projection matrix in OpenGL. The return value is the
  * stereo offset for a camera.
  *
  * Prior to release 2.6, the return value was a @B void@b, not a @B float@b.
  * [OIVJAVA-WRAPPER PACK{Matrices}]
  * [OIVJAVA-WRAPPER-RETURN-TYPE NAME{stereoOffset}]
  */
  float getMatrices(SbMatrix &affine, SbMatrix &proj) const;

  /**
  * Like the method above, but returns the affine and projection parts together in
  * one matrix (i.e., @B affine.multRight(proj) @b ).
  */
  SbMatrix getMatrix() const;

  /**
  * Returns a matrix that transforms the view volume into camera space: it
  * translates the view volume so the viewpoint is at the origin, and rotates it so
  * the view direction is along the negative z axis.
  */
  SbMatrix getCameraSpaceMatrix() const;

  /**
  * Maps a 2D point (in 0 <= x,y <= 1) to a 3D line.
  */
  void projectPointToLine(const SbVec2f &pt, SbLine &line) const;

  /**
  * Maps a 2D point (in 0 <= x,y <= 1) to a 3D line.
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  void projectPointToLine(const SbVec2f &pt,
    SbVec3f &line0,
    SbVec3f &line1) const;

  /**
  * Maps the 3D point in world coordinates to a 2D point in normalized screen
  * coordinates (0 <= x,y,z <= 1). The z-screen coordinate represents the
  * homogeneous z coordinate which goes (nonlinearly) from 0 at the near clipping
  * plane to 1 at the far clipping plane.
  *
  * Note: This is a convenience function that calls the getMatrix() method,
  * then transforms the point.  The getMatrix() call is somewhat expensive, so
  * if you need to project a large number of points you should call the getMatrix()
  * method just once and apply the matrix to each point using SbMatrix::multVecMatrix().
  */
  void projectToScreen(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Returns a plane parallel to the near (or far) plane of the view volume at a
  * given distance from the projection point (eye).
  */
  SbPlane getPlane(float distFromEye) const;

  /**
  * Returns the point along the line of sight at the given distance from the
  * projection point (eye).
  */
  SbVec3f getSightPoint(float distFromEye) const;

  /**
  * Returns the projection of a given point in normalized screen coordinates (see
  * projectToScreen()) onto the plane parallel to the near plane that is at
  * @B distFromEye @b units from the eye.
  */
  SbVec3f getPlanePoint(float distFromEye,
    const SbVec2f &normPoint) const;

  /**
  * Returns a rotation that would align a viewed object so that its positive x-axis
  * (of its object space) is to the right in the view and its positive y-axis is up.
  * If @B rightAngleOnly @b is TRUE, it will come as close as it can to this goal
  * by using only 90 degree rotations.
  */
  SbRotation getAlignRotation(SbBool rightAngleOnly = FALSE) const;

  /**
  * Returns a scale factor that would scale a unit sphere centered at
  * @B worldCenter @b so that it would appear to have the given radius in
  * normalized screen coordinates when projected onto the near plane.
  */
  float getWorldToScreenScale(const SbVec3f &worldCenter,
    float normRadius) const;

  /**
  * Projects the given 3D bounding box onto the near plane and returns the size (in
  * normalized screen coordinates) of the rectangular region that encloses it.
  */
  SbVec2f projectBox(const SbBox3f &box) const;

  /**
   * Projects the given 3D bounding box onto the near plane and returns it (in
   * normalized screen coordinates).
   */
  SbBox3f getProjectedBbox(const SbBox3f &box) const;

  /**
   * Same as getProjectedBbox but takes a matrix (containing affine and
   * projection parts) to use instead of the one returned by getMatrix.
   */
  SbBox3f getProjectedBbox(const SbMatrix& affineProj, const SbBox3f &box) const;

  /**
  * Given a view volume, narrows the view to the given sub-rectangle of the near
  * plane. The coordinates of the rectangle are between 0 and 1, where (0,0) is the
  * lower-left corner of the near plane and (1,1) is the upper-right corner.
  */
  SbViewVolume narrow(float left,  float bottom,
    float right, float top) const;

  /**
  * Narrows a view volume by the given box. The box must lie inside the unit cube,
  * and the view will be shrunk according to the size of the box.
  */
  SbViewVolume narrow(const SbBox3f &box) const;

  /**
  * Sets up an orthographic view volume with the given sides. The parameters are the
  * same as for the OpenGL glOrtho() routine.
  */
  void ortho(float left,   float right,
    float bottom, float top,
    float nearPlane,   float farPlane);

  /**
  * Sets up a perspective view volume with the given field of view and aspect ratio.
  * The parameters are the same as for the OpenGLgluPerspective() routine,
  * except that the field of view angle is specified in radians.
  */
  void perspective(float fovy, float aspect,
    float nearPlane, float farPlane);

  /**
  * Rotate the camera view direction. Note that this accomplishes the reverse of
  * doing an OpenGL glRotate() command after defining a camera, which rotates
  * the scene viewed by the camera.
  */
  void rotateCamera(const SbRotation &q);

  /**
  * Translate the camera viewpoint. Note that this accomplishes the reverse of doing
  * an OpenGL glTranslate() command after defining a camera, which translates
  * the scene viewed by the camera.
  */
  void translateCamera(const SbVec3f &v);

  /**
  * Returns the positive z axis in eye space. In this coordinate system, the z value
  * of the near plane should be greater than the z value of the far plane.
  */
  SbVec3f zVector() const;

  /**
  * Returns a narrowed view volume which contains as tightly as possible the given
  * interval on the z axis (in eye space). The returned view volume will never be
  * larger than the current volume, however. @B near @b and @B far @b are given in
  * terms of zVector(): this means that @B near @b > @B far @b must hold.
  */
  SbViewVolume zNarrow(float nearPlane, float farPlane) const;

  /**
  * Scales width and height of view volume by given factor.
  */
  void scale(float factor);

  /**
  * Scales view volume to be the given ratio of its current width, leaving
  * the resulting view volume centered about the same point (in the near plane) as
  * the current one.
  */
  void scaleWidth(float ratio);

  /**
  * Scales view volume to be the given ratio of its current height, leaving
  * the resulting view volume centered about the same point (in the near plane) as
  * the current one.
  */
  void scaleHeight(float ratio);

  /**
   * Projection type.
   */
  enum ProjectionType  {
    /**
    *  Orthographic projection
    */
    ORTHOGRAPHIC,
    /**
    *  Perspective projection
    */
    PERSPECTIVE
  };

  /**
  * Returns projection type.
  */
  ProjectionType getProjectionType() const  { return type; }

  /**
  * Returns projection point.
  */
  const SbVec3f &getProjectionPoint() const { return projPoint; }

  /**
  * Returns projection direction.
  */
  const SbVec3f &getProjectionDirection() const   { return projDir; }

  /**
  * Returns distance from projection point to near plane.
  */
  float getNearDist() const { return nearDist; }

  /**
  * Returns width of viewing frustum.
  */
  float getWidth() const      { return (lrfO-llfO).length(); }

  /**
  * Returns height of viewing frustum.
  */
  float getHeight() const     { return (ulfO-llfO).length(); }

  /**
  * Returns depth of viewing frustum.
  */
  float getDepth() const      { return nearToFar; }

  /**
  * Specifies if stereo adjustments are absolute. FALSE by default.
  *
  * The default non-absolute mode allows the stereo settings to be valid over a range
  * of different view volume settings. If you chose absolute mode, you are responsible
  * for modifying the stereo settings (if necessary) when the view volume changes.
  *
  * When absolute mode is TRUE, stereo offset and balance are used as follows
  * for the right eye view:
  * <PRE>
  * StereoCameraOffset = getStereoAdjustment();
  * FrustumAsymmetry   = getBalanceAdjustment();
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  *
  * The left eye view is symmetric.
  *
  * When absolute mode is FALSE, stereo offset and balance are used as follows for the
  * right eye view:
  *
  * Xrange is right minus left (i.e., first two arguments of glFrustum) and
  * multiply that difference by the ratio of the distance to the desired plane
  * of zero parallax to the near clipping plane distance.
  * <PRE>
  * StereoCameraOffset   = Xrange * 0.035 * getStereoAdjustment();
  * FrustumAsymmetry     = -StereoCameraOffset * getBalanceAdjustment();
  * ZeroParallaxDistance = (NearClipDistance + FarClipDistance)/0.5;
  *
  * FrustumAsymmetry *= NearClipDistance / ZeroParallaxDistance;
  *
  * glTranslated (-StereoCameraOffset, 0, 0);
  * glFrustum (FrustumLeft + FrustumAsymmetry, FrustumRight + FrustumAsymmetry,
  *            FrustumBottom, FrustumTop, NearClipDistance, FarClipDistance);</PRE>
  * The left eye view is symmetric.
  */
  void setStereoAbsoluteAdjustments(SbBool absolute);

  /**
  * Returns TRUE if the stereo adjustments are absolute.
  */
  SbBool isStereoAbsoluteAdjustments() const;

  /**
   * Sets the stereo offset (the distance of each eye from the camera position).
   * The right eye is moved plus offset and the left eye is moved minus offset.
   * Default is 0.7. The default can be set using OIV_STEREO_OFFSET environment variable.
  */
  void  setStereoAdjustment(float adjustment);

  /**
  * Queries the stereo offset.
  */
  float getStereoAdjustment() const;

  /**
   * Sets the stereo balance (the position of the zero parallax plane) and specifies whether
   * the balance value is defined as a fraction of the camera near distance.
   *
   * Note: Since the projection matrix always depends on the camera's near plane, in
   * some cases it may be necessary to detect changes to the camera near plane and
   * adjust by setting a new stereo balance value.  Open Inventor will make these
   * adjustments automatically if the @B nearFrac @b parameter is set to TRUE.
   * In this case the stereo balance value is defined as a fraction of the camera
   * near distance.
   *
   * Default balance is 1.0. The default can be set using the OIV_STEREO_BALANCE environment variable.
   * Default nearFrac is FALSE. The default can be set using the OIV_STEREO_BALANCE_NEAR_FRAC environment variable.
   */
  void  setBalanceAdjustment(float adjustment, SbBool nearFrac = false);

  /**
   * Queries the parallax balance.
   */
  float getBalanceAdjustment() const;

  /**
   * Returns TRUE if the stereo balance adjustement is defined as a fraction
   * of the camera near distance.
   */
  SbBool isBalanceNearFraction() const;

  /**
   * Stereo Modes.
   */
  enum StereoMode {
    /**
    *  Monoscopic (i.e., non-stereo) viewing
    */
    MONOSCOPIC,
    /**
    *  Left eye view
    */
    LEFT_VIEW,
    /**
    *  Right eye view
    */
    RIGHT_VIEW
  } ;

  /**
  * Sets the stereo mode.
  */
  void setStereoMode(StereoMode mode)  { stereoMode = mode ; }

  /**
  * Queries the stereo mode.
  */
  StereoMode getStereoMode() const    { return stereoMode ; }

  /**
  * Equality comparison within given tolerance.
  */
  SbBool equals(const SbViewVolume &v, float tolerance);

  SoINTERNAL public:
  ProjectionType type;

  // Note that there is redundant info in this data structure and its
  // elements should not be changed by hand.
  SbVec3f  projPoint;    // must be (0,0,0) for ortho
  SbVec3f  projDir;
  float  nearDist;    // distance to near plane
  float  nearToFar;    // distance between z clips
  SbVec3f  llf;
  SbVec3f  lrf;
  SbVec3f  ulf;
  // Points on the near clipping plane.  Add in the projPoint to
  // figure out where they are in world space:
  SbVec3f  llfO;  // x = -w, y = -w, z = -w
  SbVec3f  lrfO;  // x =  w, y = -w, z = -w
  SbVec3f  ulfO;  // x = -w, y =  w, z = -w

  // Alternate way to set up a perspective view volume.
  // Parameters are the same as for glFrustum.
  void frustum( float left, float right, float bottom,
                float top, float near_plane, float far_plane );

  void frustumWorldCoords( const SbVec3f &projPt, const SbVec3f &projDire, 
                           float radius, float near_plane, float far_plane, bool forceNearPlane = false );

  // Transforms the view volume by the given matrix. NOTE: if the
  // matrix performs a scale and a rotation, angles between the
  // transformed projection direction and the sides of the view
  // volume may not be preserved.
  void  transform( const SbMatrix &matrix);

  // Returns TRUE if view volume contains point
  SbBool  intersect( const SbVec3f &point) const;

  // Returns TRUE if line segment between 2 points may intersect
  // volume. Returns closest point on line to center ray of volume
  // if intersection is found.
  SbBool intersect( const SbVec3f &p0, const SbVec3f &p1,
                    SbVec3f &closestPoint) const;

  // Returns TRUE if triangle, made by three points, intersects
  // volume. Returns closest point in the triangle to center ray of volume
  // if intersection is found.
  SbBool intersect( const SbVec3f &v0, const SbVec3f &v1, const SbVec3f &v2,
		                SbVec3f &intersection,
		                SbVec3f &barycentric, SbBool &front) const;

  // Returns TRUE if bounding box may intersect volume
  inline SbBool intersect( const SbBox3f &box) const
  {
    SbXfBox3f xbox(box);
    return intersect(xbox);
  }

  // Returns TRUE if bounding box may intersect volume
  SbBool  intersect( const SbXfBox3f &box) const;


  // Returns TRUE if the bounding box defined by min,max is totally
  // outside plane p.
  SbBool  outsideTest( const SbPlane &p,
                       const SbVec3f &min, const SbVec3f &max) const;

  void setCameraOffset(float);
  float getCameraOffset(void) const;
  void unsetCameraOffset(void);
  int isCameraOffsetSet(void) const;

  void setClipToFar(SbBool clipToFar);
  void setClipToNear(SbBool clipToNear);

  inline const SbBox3f& getFrustumBbox() const;

  /** Return frustum's bbox with a restricted fardist of : farDist*visibilityLength */
  SbBox3f getRestrictedBbox(float visibilityLength) const ;

  SbVec3f getllf() const { return llf; }

  SbBool checkRadialDistance( const SbVec3f & pt, float radius ) const;

private:
  SbBox3f m_frustumBbox;

  SbBool stereoAbsoluteAdjustments;
  float  stereoAdjustment, balanceAdjustment;
  StereoMode stereoMode;
  bool stereoNearFrac;

  float mPStereoCameraOffset;
  int mPStereoOffsetSet;

  SbBool m_bClipToNear, m_bClipToFar;

  // Use double precision math internally?
  static SbBool m_doublePrecision;
};

// INLINE METHODS
inline void
SbViewVolume::setClipToFar(SbBool clipToFar)
{
  m_bClipToFar = clipToFar;
}

inline void
SbViewVolume::setClipToNear(SbBool  clipToNear)
{
  m_bClipToNear = clipToNear;
}

inline SbBool
SbViewVolume::isStereoAbsoluteAdjustments() const
{
  return stereoAbsoluteAdjustments;
}

inline void
SbViewVolume::setStereoAdjustment(float adjustment)
{
  stereoAdjustment = adjustment;
}

inline float
SbViewVolume::getStereoAdjustment() const
{
  return stereoAdjustment;
}

inline void
SbViewVolume::setBalanceAdjustment(float adjustment, SbBool nearFrac)
{
  balanceAdjustment = adjustment;
  stereoNearFrac = (nearFrac!=FALSE);
}

inline float
SbViewVolume::getBalanceAdjustment() const
{
  return balanceAdjustment;
}

inline SbBool
SbViewVolume::isBalanceNearFraction() const
{
  return stereoNearFrac;
}

inline void
SbViewVolume::setStereoAbsoluteAdjustments(SbBool absolute)
{
  stereoAbsoluteAdjustments = absolute;
}

const SbBox3f&
SbViewVolume::getFrustumBbox() const
{
  return m_frustumBbox;
}

#endif /* _SB_VIEWVOLUME_ */
