/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_EXTRUSION_
#define  _SO_EXTRUSION_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec3f.h>

#include <Inventor/nodes/SoBaseExtrusion.h>

class SoNormalBundle;
class SoState;
class SoExtrusionImpl;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoExtrusion
//
//  Node that defines the extrusion parameters 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Geometric shape formed by extruding a 2D cross section along a 3D spine.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   The SoExtrusion node specifies geometric shapes based on a two-dimensional
 *   cross section extruded along a three-dimensional spine. The cross section can be
 *   scaled and rotated at each spine point to produce a wide variety of shapes. 
 *       
 *   An SoExtrusion is defined by a 2D #crossSection piecewise linear curve
 *   (described as a series of connected vertices), a 3D #spine piecewise
 *   linear curve (also described as a series of connected vertices), a list of 2D
 *   #scale parameters, and a list of 3D #orientation parameters. Shapes
 *   are constructed as follows: The cross-section curve, which starts as a curve in
 *   the XZ plane, is first scaled about the origin by the first #scale
 *   parameter (first value scales in X, second value scales in Z). It is then
 *   rotated about the origin by the first #orientation parameter, and
 *   translated by the vector given as the first vertex of the #spine curve. It
 *   is then extruded through space along the first segment of the #spine
 *   curve. Next, it is scaled and rotated by the second #scale and
 *   #orientation parameters and extruded by the second segment of the
 *   #spine, and so on. The number of #scale and #orientation
 *   values will equal the number of spine points, or contain one value that is
 *   applied to all points. The #scale values must be > 0.
 *
 *   The #scaleMode field is used to select the points that will be scaled by the current
 *   transformation (for example SoTransform), if any.  Translation and rotation
 *   are applied in all cases.  The options are:
 *   - DEFAULT    : Every point in the generated geometry is scaled.
 *   - SPINE_ONLY : Only the spine points are scaled.
 *                  The cross section points are not scaled, so the cross 
 *                  section shape is undistorted even is scaling is non-uniform.
 *   - SECTION_ONLY : Only the cross section points are scaled. Not currently implemented.
 *   - NONE         : SoExtrusion ignores the scaling state. Not currently implemented.
 *   
 *   A transformed cross section is found for each joint (that is, at each vertex of
 *   the #spine curve, where segments of the extrusion connect), and the joints
 *   and segments are connected to form the surface. No check is made for
 *   self-penetration. Each transformed cross section is determined as follows: 
 *   
 *   1. Start with the cross section as specified, in the XZ plane. 
 *   
 *   2. Scale it about (0, 0, 0) by the value for #scale given for the current
 *   joint. 
 *   
 *   3. Apply a rotation so that when the cross section is placed at its proper
 *   location on the spine it will be oriented properly. Essentially, this means that
 *   the cross section's Y axis (@I up @i vector coming out of the cross section) is
 *   rotated to align with an approximate tangent to the spine curve. 
 *   
 *   @I For all points other than the first or last: @i The tangent for
 *   #spine[@I i @i] is found by normalizing the vector defined by
 *   (#spine[@I i @i+1] - #spine[@I i @i-1]). 
 *   
 *   @I If the spine curve is closed: @i The first and last points need to have the
 *   same tangent. This tangent is found as above, but using the points
 *   #spine[0] for #spine[@I i @i], #spine[1] for
 *   #spine[@I i @i+1] and #spine[@I n @i-2] for
 *   #spine[@I i @i-1], where #spine[@I n @i-2] is the next to last
 *   point on the curve. The last point in the curve, #spine[@I n @i-1], is
 *   the same as the first, #spine[0]. 
 *   
 *   @I If the spine curve is not closed: @i The tangent used for the first point is
 *   just the direction from #spine[0] to #spine[1], and the tangent used
 *   for the last is the direction from #spine[@I n @i-2] to
 *   #spine[@I n @i-1]. 
 *   
 *   In the simple case where the spine curve is flat in the XY plane, these rotations
 *   are all just rotations about the Z axis. In the more general case where the
 *   spine curve is any 3D curve, you need to find the destinations for all 3 of the
 *   local X, Y, and Z axes so you can completely specify the rotation. The Z axis is
 *   found by taking the cross product of: 
 *   
 *   (#spine[@I i @i-1] - #spine[@I i @i]) and (#spine[@I i @i+1] - #spine[@I i @i]). 
 *   
 *   If the three points are collinear then this value is zero, so take the value from
 *   the previous point. Once you have the Z axis (from the cross product) and the Y
 *   axis (from the approximate tangent), calculate the X axis as the cross product
 *   of the Y and Z axes. 
 *   
 *   4. Given the plane computed in step 3, apply the #orientation to the
 *   cross-section relative to this new plane. Rotate it counterclockwise about the
 *   axis and by the angle specified in the #orientation field at that joint.
 *   
 *   5. Finally, the cross section is translated to the location of the #spine
 *   point. @BR
 *    
 *   
 *   @I Surfaces of revolution: @i If the cross section is an approximation of a
 *   circle and the spine is straight, then the SoExtrusion is equivalent to a
 *   surface of revolution, where the #scale parameters define the size of the
 *   cross section along the spine. 
 *   
 *   @I Cookie-cutter extrusions: @i If the scale is 1, 1 and the spine is straight,
 *   then the cross section acts like a cookie cutter, with the thickness of the
 *   cookie equal to the length of the spine. 
 *   
 *   @I Bend/twist/taper objects: @i These shapes are the result of using all fields.
 *   The spine curve bends the extruded shape defined by the cross section, the
 *   orientation parameters twist it around the spine, and the scale parameters taper
 *   it (by scaling about the spine). 
 *   
 *   SoExtrusion has three parts: the @B sides@b, the #beginCap (the
 *   surface at the initial end of the spine) and the #endCap (the surface at
 *   the final end of the spine). The caps have an associated SFBool field that
 *   indicates whether it exists (TRUE) or doesn't exist (FALSE). 
 *   
 *   When the #beginCap or #endCap fields are specified as TRUE, planar
 *   cap surfaces will be generated regardless of whether the #crossSection is
 *   a closed curve. (If #crossSection isn't a closed curve, the caps are
 *   generated as if it were -- equivalent to adding a final point to
 *   #crossSection that's equal to the initial point. Note that an open surface
 *   can still have a cap, resulting (for a simple case) in a shape something like a
 *   soda can sliced in half vertically.) These surfaces are generated even if
 *   #spine is also a closed curve. If a field value is FALSE, the
 *   corresponding cap is not generated. 
 *   
 *   SoExtrusion automatically generates its own normals. Orientation of the
 *   normals is determined by the vertex ordering of the quads generated by
 *   SoExtrusion. The vertex ordering is in turn determined by the
 *   #crossSection curve. If the #crossSection is counterclockwise when
 *   viewed from the +Y axis, then the polygons will have counterclockwise ordering
 *   when viewed from 'outside' of the shape (and @I vice versa @i for clockwise
 *   ordered #crossSection curves).
 *   
 *   Texture coordinates are automatically generated by extrusions. Textures are
 *   mapped so that the coordinates range in the U direction from 0 to 1 along the
 *   #crossSection curve (with 0 corresponding to the first point in
 *   #crossSection and 1 to the last) and in the V direction from 0 to 1 along
 *   the #spine curve (again with 0 corresponding to the first listed
 *   #spine point and 1 to the last). When #crossSection is closed, the
 *   texture has a seam that follows the line traced by the #crossSection's
 *   start/end point as it travels along the #spine. If the #endCap
 *   and/or #beginCap exist, the #crossSection curve is uniformly scaled
 *   and translated so that the largest dimension of the cross-section (X or Z)
 *   produces texture coordinates that range from 0.0 to 1.0. The #beginCap and
 *   #endCap textures' S and T directions correspond to the X and Z directions
 *   in which the #crossSection coordinates are defined. 
 *
 *   Also 3D texture coordinates are automatically generated, in a similar way to 
 *   2D textures.
 *
 *   NOTE: If your extrusion appears to twist unexpectedly,
 *   try setting environment variable OIV_EXTRUSION_EPSILON to a value 
 *   slightly smaller number than the default, which is .998.
 *
 *   NOTE: If your #crossSection is not convex, you must use a SoShapeHints and set the
 *   faceType field to UNKNOWN_FACE_TYPE.
 *   
 * @FILE_FORMAT_DEFAULT
 *    Extrusion {
 *    @TABLE_FILE_FORMAT
 *       @TR beginCap       @TD TRUE
 *       @TR endCap         @TD TRUE
 *       @TR spine          @TD [ 0 0 0, 0 1 0 ]
 *       @TR scaleMode      @TD DEFAULT
 *       @TR crossSection   @TD [ 1 1, 1 -1, -1 -1, -1 1, 1 1 ]
 *       @TR orientation    @TD 0 0 1 0
 *       @TR scale          @TD 1 1
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *   SoBaseExtrusion
 * 
 */ 

class INVENTOR_API SoExtrusion : public SoBaseExtrusion  {

  SO_NODE_HEADER(SoExtrusion);

 public:
  // Fields


  /**
   * Piecewise linear curve.
   * Default is [ 1 1, 1 -1, -1 -1, -1 1, 1 1 ].
   */
  SoMFVec2f           crossSection;

  /**
   * Cross section transformation.
   * Default is no rotation.
   */
  SoMFRotation        orientation;

  /**
   * Joint scale amounts.
   * Default is (1,1) meaning no scaling.
   */
  SoMFVec2f           scale;

  /**
   * Constructor.
   */
  SoExtrusion();


 SoEXTENDER public:
  // Implements actions

  /** @copydoc SoShape::doAction */
  virtual void doAction( SoAction *action );

  /** @copydoc SoShape::callback */
  virtual void callback( SoCallbackAction *action );

  /** @copydoc SoShape::rayPick */
  virtual void rayPick( SoRayPickAction *action );

  /** @copydoc SoShape::getPrimitiveCount */
  virtual void getPrimitiveCount( SoGetPrimitiveCountAction *action );

  /** @copydoc SoShape::computeBBox */
  virtual void computeBBox( SoAction *action, SbBox3f &box, SbVec3f &center );

  /** @copydoc SoShape::computeBBox */
  virtual void computeBBox( SoAction *action, SbXfBox3d &box, SbVec3d &center );

 SoINTERNAL public:

  /** @copydoc SoShape::notify */
  virtual void notify( SoNotList *list );

  /** @copydoc SoNode::initClass */
  static void initClass();

  /** @copydoc SoNode::exitClass */
  static void exitClass();

 protected:

  /** @copydoc SoShape::generatePrimitives */
  virtual void generatePrimitives( SoAction *action );

  /** Destructor */
  virtual ~SoExtrusion();

 private:

  // Generates default normals for the generated extrusion.
  SbBool generateDefaultNormals( SoState *state, int numcols,
                                 int numrows, SbVec3f *verts,
                                 SoNormalBundle *nb );
  // Implementation class.
  SoExtrusionImpl* m_impl;

};

#endif /* _SO_EXTRUSION_ */

