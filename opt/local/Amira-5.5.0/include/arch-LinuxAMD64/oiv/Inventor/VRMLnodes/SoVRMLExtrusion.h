/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLEXTRUSION_
#define  _SO_VRMLEXTRUSION_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/fields/SoMFRotation.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLGeometry.h>
#include <Inventor/threads/SbThreadRWMutex.h>

class SoNormalBundle;
class SoNormalCache;
class SoState;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLExtrusion
//
//  Node that defines the extrusion parameters 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies geometric shapes based on a 2D cross section along a 3D spine.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLExtrusion node specifies geometric shapes based on a two-dimensional
 *   cross section extruded along a three-dimensional spine. The cross section can be
 *   scaled and rotated at each spine point to produce a wide variety of shapes. 
 * 
 * @VRML2_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *   This section may reference portions of the VRML97 specification that are not
 *   present in this help file. The complete VRML97 spec is available at
 *   @B http://www.web3d.org @b.
 *   
 *   The SoVRMLExtrusion node specifies geometric shapes based on a two-dimensional
 *   cross section extruded along a three-dimensional spine. The cross section can be
 *   scaled and rotated at each spine point to produce a wide variety of shapes. 
 *   
 *   An SoVRMLExtrusion is defined by a 2D #crossSection piecewise linear curve
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
 *   values must equal the number of spine points, or contain one value that is
 *   applied to all points. The #scale values must be > 0.
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
 *   circle and the spine is straight, then the SoVRMLExtrusion is equivalent to a
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
 *   SoVRMLExtrusion has three parts: the @B sides @b, the #beginCap (the
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
 *   SoVRMLExtrusion automatically generates its own normals. Orientation of the
 *   normals is determined by the vertex ordering of the triangles generated by
 *   SoVRMLExtrusion. The vertex ordering is in turn determined by the
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
 *   See "Concepts - Geometry Nodes" for a description of the #ccw,
 *   #solid, #convex, and #creaseAngle fields. 
 *
 *   NOTE: If your extrusion appears to twist unexpectedly,
 *   try setting environment variable OIV_EXTRUSION_EPSILON to a value 
 *   slightly smaller number than the default, which is .998.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLExtrusion {
 *    @TABLE_FILE_FORMAT
 *       @TR beginCap       @TD TRUE
 *       @TR ccw            @TD TRUE
 *       @TR convex         @TD TRUE
 *       @TR creaseAngle    @TD 0
 *       @TR crossSection   @TD [ 1 1, 1 -1, -1 -1, -1 1, 1 1 ]
 *       @TR endCap         @TD TRUE
 *       @TR orientation    @TD 0 0 1 0
 *       @TR scale          @TD 1 1
 *       @TR solid          @TD TRUE
 *       @TR spine          @TD [ 0 0 0, 0 1 0 ]
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoMFVec2f      @TD   set_crossSection      
 *       @TR   SoMFRotation   @TD   set_orientation      
 *       @TR   SoMFVec2f      @TD   set_scale      
 *       @TR   SoMFVec3f      @TD   set_spine
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLExtrusion : public SoVRMLGeometry {

  SO_NODE_HEADER(SoVRMLExtrusion);

 public:
  // Fields
  /**
   * The surface at the initial end of the spine. 
   * If TRUE, the planar cap surface is generated.
   */
  SoSFBool            beginCap; 
  /**
   * Indicates whether the vertices are ordered in a counterclockwise direction when
   * viewed from the outside (TRUE) or in a clockwise direction (FALSE).
   * 
   */
  SoSFBool            ccw;
  /**
   * If you know that the shape encloses a volume, set this value to TRUE. 
   * Then backface culling will be performed. 
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
  SoSFBool            solid;
  /**
   * Indicates whether faces of a shape are convex (TRUE). If nothing is known about
   * the faces, set this value to FALSE.
   * 
   */
  SoSFBool            convex;
  /**
   * Indicates the minimum angle (in radians) between two adjacent face normals
   * required to form a sharp crease at the edge when default normals are computed
   * and used.
   * 
   */
  SoSFFloat           creaseAngle;
  /**
   * A 2D crossSection piecewise linear curve (described as 
   * a series of connected vertices);
   *
   */
  SoMFVec2f           crossSection;    
  /**
   * The surface at the final end of the spine. 
   * If TRUE, the planar cap surface is generated.
   */
  SoSFBool            endCap;    
  /**
   * The orientation of the crossSection at each spine point.
   */
  SoMFRotation        orientation; 
  /**
   * The scale factor of the crossSection at each spine point.
   */
  SoMFVec2f           scale; 
  /**
   * A 3D spine piecewise linear curve (also described as a 
   * series of connected vertices); 
   */
  SoMFVec3f           spine;          

  /**
   * Constructor.
   */
  SoVRMLExtrusion();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        generatePick(SoRayPickAction *action, SoNode *node);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);


  // This handles bounding box computation for all shapes derived
  // from this class. It sets the bounding box to contain all
  // vertices of the shape, assuming that the shape uses the
  // coordinates indexed by all non-negative values in the
  // coordIndex field. It also sets the center to the average of the
  // vertices' coordinates.
  virtual void        computeBBox(SoAction *action, SbBox3f &box,
                                  SbVec3f &center);


 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Returns the current normal cache, or NULL if there is none.
  // This method was protected prior to OIV version 3.0.
  // Normal cache will only exist if the node has been traversed
  // by a render action and Inventor needed to compute normals.
  SoNormalCache       *getNormalCache() const { return normalCache; }

 protected:
  virtual ~SoVRMLExtrusion();
  // Generates triangles representing faces
  virtual void        generatePrimitives(SoAction *action);

  // Sets up a cache to hold normals. This assumes the cache depends
  // on only the current coordinates, shape hints, and crease angle.
  void                setNormalCache(SoState *state,
                                     int numNormals, 
                                     const SbVec3f *normals, 
                                     const SoNormalBindingElement::Binding binding
                                     );

  // Per-instance mutex to protect access to the normalCache
  SbThreadRWMutex *normalCacheMutex;

  // Overrides standard method to create an SoFaceDetail instance
  //virtual SoDetail *  createTriangleDetail(SoRayPickAction *action,
  //const SoPrimitiveVertex *v1,
  //const SoPrimitiveVertex *v2,
  //const SoPrimitiveVertex *v3,
  //SoPickedPoint *pp);
 private:
  // set verts = NULL to force generateVertices to be called if
  // the inputs change 
  virtual void        notify(SoNotList *list);

  // This allows instances to cache normals that have been generated
  SoNormalCache       *normalCache;

  // Constructor for rotation that rotates one direction vector to another
  SbRotation& setRotValue(const SbVec3f &rotateFrom, const SbVec3f &rotateTo);
  virtual SbBool       generateDefaultNormals(SoState *state, int numcols,
                                              int numrows, SbVec3f *verts,
                                              SoNormalBundle *nb );
  SbVec3f *verts;
  int numSpinePts;
  int numCrossSectionPts;
};

#endif /* _SO_VRMLEXTRUSION_ */
