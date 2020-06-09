/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*==============================================================================
*   Classes     : SoTrackFollower
*   Author(s)   : Fabien ARNAUD
*               : Jerome HUMMEL
*   Date        : Jul, 23 2002
*==============================================================================
*
* Description : See below
*
*============================================================================*/

#ifndef _SO_TRACK_FOLLOWER_H_
#define _SO_TRACK_FOLLOWER_H_

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFBool.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/nodes/SoCoordinate3.h>

#define SO_UNDEFINED_TIME_STAMP (-1)



/**
 * @VSGEXT Animates an object or camera along a track
 *
 * @ingroup engines
 *
 * @DESCRIPTION
 *   This engine is designed to add animations to a scene graph. It manages a
 *   track that can be followed either by an object (a sub scene graph) or by 
 *   a camera.
 *   The track is defined by a set of control points. Each control point can be
 *   associated with a time stamp, a turn angle, roll information, and a head
 *   rotation.
 *   Only the #points field is required.  All other data fields are optional.
 *
 *   The input that drives the animation is the #alpha field.  This value should
 *   vary between 0 and 1, assuming 0 as the position and orientation at the 
 *   first control point, and 1 as the position and orientation at the last control
 *   point.  Alpha values are clamped to the interval [0,1].  An SoTimerSensor
 *   or other engines can be used to dynamically modify the alpha value.
 *
 *   The outputs are a #position field and an #orientation field that can be 
 *   connected directly to the corresponding fields of an SoCamera or SoTransform
 *   node (see SoField::connectFrom). The values of these fields are
 *   computed by interpolating the track points with the #alpha field value.
 *
 *   The rollAngle values are only used if the track specified by the points field
 *   is curved.
 *
 *   An example .iv file using SoTrackFollower is provided in the directory
 *   $OIVHOME/data/models/toys/TrackSample.
 *
 * @FILE_FORMAT_DEFAULT
 *    TrackFollower {
 *    @TABLE_FILE_FORMAT
 *       @TR points         @TD 0 0 0
 *       @TR timeStamps     @TD 0
 *       @TR radius         @TD 0
 *       @TR rollAngle      @TD 0
 *       @TR rollSpeed      @TD 0
 *       @TR keepRollAngle  @TD FALSE
 *       @TR headRotation   @TD 0 0 1  0
 *       @TR alpha          @TD 0
 *       @TR loop           @TD TRUE
 *       @TR useHeadRotationOnly   @TD FALSE
 *    @TABLE_END
 *    }
 *
 *
 * @SEE_ALSO
 *    SoVRMLTimeSensor,
 *    SoInterpolate
 *
 *
 */

class INVENTOR_API SoTrackFollower : public SoEngine {

  SO_ENGINE_HEADER (SoTrackFollower);

 public:

  // Input fields
  /**
   * Coordinates of the control points.
   */
  SoMFVec3f    points;

  /**
   * Time stamps associated with the control points. A time stamp represents
   * the time at which a control point must be reached; the "scale" of the time
   * is independent of the animation time. However, it is proportional to
   * it. For example, if point 1 has a time stamp value of 10, point 2 has a time
   * stamp value of 30, and point 3 has a time stamp value of 40, 
   * it means that the interpolation will take twice
   * as long to go from point 1 to point 2 (20 time units) as it will to go 
   * from point 2 to point 3 (10 time units).
   * The actual time to complete an animation, and therefore the
   * overall speed, is determined by the time it takes for the
   * #alpha value to go from 0 to 1.  In other words, the overall
   * speed is controlled by the application or another engine
   * (for example @B SoVRMLTimeSensor@b) which is updating the @B alpha @b input.
   *
   * If a time stamp has a value of @B SO_UNDEFINED_TIME_STAMP@b (default value),
   * then the computed time stamp is proportional to the distance between
   * the previous and the next control point, i.e., speed is constant.
   * If all the time stamps are set to @B SO_UNDEFINED_TIME_STAMP@b or are not
   * set at all, they are
   * all computed to be proportional to the distance between the points, and
   * speed is constant over the entire track.
   *
   * If the time stamp field contains one more value than the points field, the last
   * time stamp is assumed to apply to the first/last control point in 
   * a @B loop@b.
   * If fewer than 3 time stamps are provided, the track is interpolated
   * proportional to the distance between control points.
   */
  SoMFFloat    timeStamps;

  /**
   * Radius of the turn at a control point.
   * If radius is zero for a control point (the default), the orientation
   * changes immediately when the animation reachs that point. For many
   * animations this is an unrealistic or undesirable behavior. Radius
   * values allow the orientation to change smoothly, following a curve.
   *
   * If there are fewer radius values than control points, the value of 
   * the last radius is used for the remaining control points.
   */
  SoMFFloat    radius; 


  /**
   * Roll angle during the turn at a control point. The roll angle 
   * inclines the track inside the turn. If the specified roll angle is
   * negative, the track is inclined outside the turn.
   *
   * If rollAngle is zero for a control point (the default), the animated
   * object will rotate around a vector perpendicular to the plane defined
   * by the preceding and following segments of the track. This is
   * typically the desired behavior, for example, when animating a 
   * vehicle on the ground. However rollAngle allows a more realistic animation of a
   * flying vehicle.
   *
   * If there are fewer rollAngle values than control points, the value
   * of the last rollAngle is used for the remaining control points.
   */
  SoMFFloat    rollAngle;

  /**
   * Speed at which the roll angle is reached during a turn. By default,
   * (value = 0) the roll angle varies from 0 at the beginning of the turn to the
   * specified roll angle value in the middle of the turn and then back to 0
   * at the end of the turn. A value of 1 means the roll angle is immediately
   * reached at the begining of the turn. Intermediate values vary the point at
   * which the full roll angle is reached.
   *
   * If there are fewer rollSpeed values than control points, the value of
   * the last rollSpeed is used for the remaining control points.
   */
  SoMFFloat    rollSpeed;

  /**
   * Indicates if the roll angle should be maintained after the middle of the turn. If
   * this flag is set to TRUE for a control point, the roll speed is assumed to be 1 in the
   * second part of the turn for the current control point and in the first part
   * of the turn for the next control point. This allows the roll angle to be maintained
   * between two adjacent turns.
   *
   * If there are fewer keepRollAngle values than control points, the value of the
   * last keepRollAngle is used for the remaining control points.
   */
  SoMFBool     keepRollAngle;

  /**
   * The final rotation applied at a control point, which allows the camera
   * or the object to be rotated while following the track.
   *
   * If there are fewer headRotation values than control points, the value of the
   * last headRotation is used for the remaining control points.
   */
  SoMFRotation headRotation;

  /**
   * The value on which the interpolation is made. It must between 0.0 and 1.0.
   */
  SoSFFloat    alpha;

  /**
   * If loop is TRUE, the animation will loop. For N control points, there must
   * be N+1 time stamps. The last time stamp is used for interpolating between
   * the last control point and the first control point at the end of the 
   * animation loop. For example, if there are four points (P1, P2, P3, and P4),
   * there must be five time stamps (T1,... T5) as shown below:
   *
   * @IMAGE tracker_loop.gif
   *
   */
  SoSFBool     loop;

  /**
   * If TRUE, the #orientation output field is a direct
   * interpolation of #headRotation values, without taking into consideration
   * the roll angle or the track itself.
   */
  SoSFBool     useHeadRotationOnly;

  // Output fields

  /**
   * (SoSFVec3f) Position interpolated from the #alpha value.
   */
  SoEngineOutput  position;   // (SoSFVec3f) position

  /**
   * (SoSFRotation) Rotation interpolated from the #alpha value. It's a
   * rotation from the @B -Z @b vector to the heading vector, with the initial
   * @B up @b vector along the @B Y @b vector.
   */
  SoEngineOutput  orientation;   // (SoSFRotation) position

  // Constructor

  /**
   * Constructor
   */
  SoTrackFollower();

 SoEXTENDER public:
  // Internal values access

  /**
   * Returns the @B alpha @b value at a control point, depending on the distance between
   * control points and on the @B timeStamps @b values.
   */
  float getAlphaValue (int control_point)
    { return m_01_time [control_point]; }

  /**
   * Returns a set of coordinates that can be used to build a @B TriangleStripSet @b
   * or a @B LineSet @b that materialized the track. The @B width @b value tune the width
   * of the @B TriangleStripSet @b set; if it's set to 0, then the coordinates can be used
   * to build a @B LineSet@b . If the @B flat @b flag is set, the roll angle is not
   * used for this computation. @B Precision @b tune the number of triangles that must
   * be used in a turn.
   */
  void getTrackCoordinate (SoCoordinate3* coords, float width = 1, SbBool flat = FALSE, int precision = 16);

  /**
   * Returns the position and the three rotations used to compute the orientation
   * field for a given @B alpha @b value.
   */
  void computeData (float alpha, SbVec3f& vessel_pos, SbRotation& vessel_rot, SbRotation& roll_rot, SbRotation& head_rot);

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 protected:
  // Destructor
  ~SoTrackFollower();

 private:
  // Inventor's engine private functions
  virtual void evaluate ();
  virtual void inputChanged (SoField* whichField);

  // Time used for interpolation
  void compute01Time();
  float* m_01_time;
  SbBool m_need_01time_computation;

  // Smooth angles
  void computeAngles();
  SbBool m_need_angles_computation;
  float* m_turn_start_time;
  float* m_turn_end_time;
  float* m_turn_gamma;
  SbVec3f* m_turn_center;
  SbVec3f* m_turn_normal;
  SbVec3f* m_turn_start_point;
  SbVec3f* m_turn_end_point;
};

#endif  // _SO_TRACK_FOLLOWER_H_
