/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef MC_VIEW_VOLUME_H
#define MC_VIEW_VOLUME_H

#include "Vs.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>
#include <mclib/McMat4f.h>
#include <mclib/McBox3f.h>
#include <mclib/McPlane.h>
#include <mclib/McLine.h>

/** 3D viewing volume class. This class is used to represent a 3D viewing
    volume. This class is used to represent viewing frusta and picking
    volumes. For perspective projection, the view volume is a frustum. For
    orthographic (parallel) projection, the view volume is a rectangular
    prism.
  
    \sa McVec3f, McVec2f, McBox3f, McMat4f, McRotation
 */ 

class VSVOLREN_API McViewVolume
{
 public:
  /// Indicates projection information
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

  ///
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
  };

  /**
   * Constructor.
   */
  McViewVolume();
  /**
   * Destructor.
   */
  ~McViewVolume()     {}

  /**
   * Returns two matrices corresponding to the view volume. The first is a viewing
   * matrix, which is guaranteed to be an affine transformation. The second is
   * suitable for use as a projection matrix in OpenGL. The return value is the
   * stereo offset for a camera.
   * 
   * Prior to release 2.6, the return value was a @B void@b, not a @B float@b.
   */
  float getMatrices(McMat4f &affine, McMat4f &proj) const;

  /**
   * Like the method above, but returns the affine and projection parts together in
   * one matrix (i.e., @B affine.multRight(proj) @b ).
   */
  McMat4f    getMatrix() const;

  /**
   * Returns a matrix that transforms the view volume into camera space: it
   * translates the view volume so the viewpoint is at the origin, and rotates it so
   * the view direction is along the negative z axis.
   */
  McMat4f    getCameraSpaceMatrix() const;

  /**
   * Maps a 2D point (in 0 <= x,y <= 1) to a 3D line.
   */
  void projectPointToLine(const McVec2f &pt, McLine &line) const;
  /**
   * Maps a 2D point (in 0 <= x,y <= 1) to a 3D line.
   */
  void projectPointToLine(const McVec2f &pt,
                          McVec3f &line0, 
                          McVec3f &line1) const;

  /**
   * Maps the 3D point in world coordinates to a 2D point in normalized screen
   * coordinates (0 <= x,y,z <= 1). The z-screen coordinate represents the
   * homogeneous z coordinate which goes (nonlinearly) from 0 at the near clipping
   * plane to 1 at the far clipping plane.
   */
  void projectToScreen(const McVec3f &src, McVec3f &dst) const;

  /**
   * Returns a plane parallel to the near (or far) plane of the view volume at a
   * given distance from the projection point (eye).
   */
  McPlane getPlane(float distFromEye) const;

  /**
   * Returns the point along the line of sight at the given distance from the
   * projection point (eye).
   */
  McVec3f    getSightPoint(float distFromEye) const;

  /**
   * Returns the projection of a given point in normalized screen coordinates (see
   * projectToScreen()) onto the plane parallel to the near plane that is at
   * @B distFromEye @b units from the eye.
   */
  McVec3f    getPlanePoint(float distFromEye,
                           const McVec2f &normPoint) const;

  /**
   * Returns a rotation that would align a viewed object so that its positive x-axis
   * (of its object space) is to the right in the view and its positive y-axis is up.
   * If @B rightAngleOnly @b is TRUE, it will come as close as it can to this goal
   * by using only 90 degree rotations.
   */
  McRotation    getAlignRotation(bool rightAngleOnly = false) const;

  /**
   * Returns a scale factor that would scale a unit sphere centered at
   * @B worldCenter @b so that it would appear to have the given radius in
   * normalized screen coordinates when projected onto the near plane.
   */
  float    getWorldToScreenScale(const McVec3f &worldCenter,
                                 float normRadius) const;

  /**
   * Projects the given 3D bounding box onto the near plane and returns the size (in
   * normalized screen coordinates) of the rectangular region that encloses it.
   */
  McVec2f    projectBox(const McBox3f &box) const;

  /**
   * Given a view volume, narrows the view to the given sub-rectangle of the near
   * plane. The coordinates of the rectangle are between 0 and 1, where (0,0) is the
   * lower-left corner of the near plane and (1,1) is the upper-right corner.
   */
  McViewVolume  narrow(float left,  float bottom,
                       float right, float top) const;

  /**
   * Narrows a view volume by the given box. The box must lie inside the unit cube,
   * and the view will be shrunk according to the size of the box.
   */
  McViewVolume  narrow(const McBox3f &box) const;

  /**
   * Sets up an orthographic view volume with the given sides. The parameters are the
   * same as for the OpenGL glOrtho() routine.
   */
  void    ortho(float left,   float right,
                float bottom, float top,
                float nearPlane,   float farPlane);

  /**
   * Sets up a perspective view volume with the given field of view and aspect ratio.
   * The parameters are the same as for the OpenGLgluPerspective() routine,
   * except that the field of view angle is specified in radians.
   */
  void    perspective(float fovy, float aspect,
                      float nearPlane, float farPlane);

  /**
   * Rotate the camera view direction. Note that this accomplishes the reverse of
   * doing an OpenGL glRotate() command after defining a camera, which rotates
   * the scene viewed by the camera.
   */
  void    rotateCamera(const McRotation &q);

  /**
   * Translate the camera viewpoint. Note that this accomplishes the reverse of doing
   * an OpenGL glTranslate() command after defining a camera, which translates
   * the scene viewed by the camera.
   */
  void    translateCamera(const McVec3f &v);

  /**
   * Returns the positive z axis in eye space. In this coordinate system, the z value
   * of the near plane should be greater than the z value of the far plane.
   */
  McVec3f    zVector() const;

  /**
   * Returns a narrowed view volume which contains as tightly as possible the given
   * interval on the z axis (in eye space). The returned view volume will never be
   * larger than the current volume, however. @B near @b and @B far @b are given in
   * terms of zVector(): this means that @B near @b > @B far @b must hold.
   */
  McViewVolume  zNarrow(float nearPlane, float farPlane) const;

  /**
   * Scales width and height of view volume by given factor.
   */
  void    scale(float factor);

  /**
   * Scales view volume to be the given ratio of its current width, leaving
   * the resulting view volume centered about the same point (in the near plane) as
   * the current one.
   */
  void    scaleWidth(float ratio);
  /**
   * Scales view volume to be the given ratio of its current height, leaving
   * the resulting view volume centered about the same point (in the near plane) as
   * the current one.
   */
  void    scaleHeight(float ratio);

  /**
   * Returns projection type.
   */
  ProjectionType  getProjectionType() const  { return type; }

  /**
   * Returns projection point.
   */
  const McVec3f &getProjectionPoint() const { return projPoint; }

  /**
   * Returns projection direction.
   */
  const McVec3f &getProjectionDirection() const   { return projDir; }

  /**
   * Returns distance from projection point to near plane.
   */
  float    getNearDist() const { return nearDist; }

  /**
   * Returns width of viewing frustum.
   */
  float               getWidth() const      { return (lrfO-llfO).length(); }
  /**
   * Returns height of viewing frustum.
   */
  float               getHeight() const     { return (ulfO-llfO).length(); }
  /**
   * Returns depth of viewing frustum.
   */
  float               getDepth() const      { return nearToFar; }

  /**
   * Sets the stereo offset.
   */
  void  setStereoAdjustment(float adjustment) { stereoAdjustment = adjustment ; }
  /**
   * Queries the stereo offset.
   */
  float getStereoAdjustment() const           { return stereoAdjustment ; }
  /**
   * Sets the parallax balance.
   */
  void  setBalanceAdjustment(float adjustment){ balanceAdjustment = adjustment ; }
  /**
   * Queries the parallax balance.
   */
  float getBalanceAdjustment() const    { return balanceAdjustment ; }
  //    float getStereoCameraOffset() const  { return stereoCameraOffset ; }
  
  /**
   * Sets the stereo mode.
   */
  void  setStereoMode(StereoMode mode)  { stereoMode = mode ; }
  /**
   * Queries the stereo mode.
   */
  StereoMode getStereoMode() const    { return stereoMode ; }

 public:
  ProjectionType type;

  // Note that there is redundant info in this data structure and its
  // elements should not be changed by hand.  
  McVec3f  projPoint;    // must be (0,0,0) for ortho
  McVec3f  projDir;
  float  nearDist;    // distance to near plane
  float  nearToFar;    // distance between z clips
  McVec3f  llf;
  McVec3f  lrf;
  McVec3f  ulf;

  // Alternate way to set up a perspective view volume.
  // Parameters are the same as for glFrustum.
  void frustum( float left, float right, float bottom,
                float top, float near_plane, float far_plane );

  // Transforms the view volume by the given matrix. NOTE: if the
  // matrix performs a scale and a rotation, angles between the
  // transformed projection direction and the sides of the view
  // volume may not be preserved.
  void  transform(const McMat4f &matrix);

  // Returns TRUE if view volume contains point
  bool  intersect(const McVec3f &point) const;

  // Returns TRUE if line segment between 2 points may intersect
  // volume. Returns closest point on line to center ray of volume
  // if intersection is found.
  bool intersect(const McVec3f &p0, const McVec3f &p1,
                   McVec3f &closestPoint) const;

  // Returns TRUE if bounding box may intersect volume
  bool  intersect(const McBox3f &box) const;

  // Returns TRUE if the bounding box defined by min,max is totally
  // outside plane p.
  bool  outsideTest(const McPlane &p,
                      const McVec3f &min, const McVec3f &max) const;

  void setCameraOffset(float);
  float getCameraOffset(void) const;
  void unsetCameraOffset(void);
  int isCameraOffsetSet(void) const;

 private:
  // Points on the near clipping plane.  Add in the projPoint to
  // figure out where they are in world space:
  McVec3f  llfO;  // x = -w, y = -w, z = -w
  McVec3f  lrfO;  // x =  w, y = -w, z = -w
  McVec3f  ulfO;  // x = -w, y =  w, z = -w
  float stereoAdjustment, balanceAdjustment;
  StereoMode stereoMode;

  float mPStereoCameraOffset;
  int mPStereoOffsetSet;
};

#endif


/// @}
