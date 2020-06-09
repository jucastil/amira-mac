/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SB_EXTRUSION_GENERATOR_H_
#define _SB_EXTRUSION_GENERATOR_H_

#include <Inventor/SbBox.h>
#include <Inventor/SbMatrix.h>
#include <Inventor/nodes/SoCoordinate3.h>

class SoShape;
class SoCallbackAction;
class SoPrimitiveVertex;

//@TOBEWRAPPED
/**
 * Factory that generates an extruded mesh from a polyline.
 *
 * @DESCRIPTION
 *   This class generates an extruded shape from a simple or a complex polyline. 
 *   The line is extruded between the 2 planes parallel that can be specified 
 *   with a boundingBox or directly in camera space (see createFrom2DPoints() methods)
 *   The generated shape is closed and contains only triangles in CCW order.
 *
 * @B LIMITATIONS @b
 *   - Only vertices are handled in the generated shape, none of the normal, color or
 *     texCoord properties are taken into account.
 *
 * @B NOTES @b
 *   - In an orthographic view, the polyline is extruded along the view vector
 *     (normal to the camera plane),
 *     but in a perspective view the generated shape is a truncated cone with a 
 *     larger base farther from the camera, due to the perspective transform.
 *   - @B Local space @b refers to the space in which the shape will be expressed.
 */
class INVENTOR_API SbExtrusionGenerator
{

public:

  /**
   * Create an extruded shape from points in world space.
   *
   * @param pointsInWorld Polyline in world space.
   * @param nodePath Path from root to the node space in which the generated shape
   * will be expressed. Generally, the separator which will contain the shape.
   * If NULL, the shape will be expressed in world space.
   * @param volume View volume corresponding to the camera in which the points were taken.
   * @param bboxInLocal Bounding box that specifies limits of extruded shape, expressed in local 
   * space. If not specified, the shape will be extruded between the camera near and far 
   * planes.
   *
   * @warning Return NULL if error occurred.
   */
  static SoShape* createFrom3DPoints ( const std::vector<SbVec3f>& pointsInWorld, 
    SoPath* nodePath, 
    const SbViewVolume& volume, 
    const SbBox3f& bboxInLocal = SbBox3f() );

  /**
   * Create an extruded shape from points in camera space.
   *
   * @param pointsInCam Polyline in normalized screen space ([-1, 1]x[-1, 1]).
   * @param nodePath Path from root to the node space in which the generated shape
   * will be expressed. Generally, the separator which will contain the shape.
   * If NULL, the shape will be expressed in world space.
   * @param volume View volume corresponding to the camera in which the points were taken.
   * @param bboxInLocal Bounding box that specifies limits of extruded shape, expressed in local 
   * space. If not specified, the shape will be extruded between the camera near and far 
   * planes.
   *
   * @warning Return NULL if error occurred.
   */
  static SoShape* createFrom2DPoints ( const std::vector<SbVec2f>& pointsInCam, 
    SoPath* nodePath, 
    const SbViewVolume& volume, 
    const SbBox3f& bboxInLocal = SbBox3f() );

  /**
   * Create an extruded shape from points in camera space.
   *
   * @param pointsInCam Polyline in normalized screen space ([-1, 1]x[-1, 1]).
   * @param localToCam Transform matrix from local space to camera space
   * (modelViewProj matrix)
   * @param bboxInLocal Bounding box that specifies limits of extruded shape, expressed in local 
   * space. If not specified, the shape will be extruded between the camera near and far 
   * planes.
   *
   * @warning Return NULL if error occurred.
   */
  static SoShape* createFrom2DPoints ( const std::vector<SbVec2f>& pointsInCam, 
    const SbMatrix& localToCam, 
    const SbBox3f& bboxInLocal  = SbBox3f() );

  /**
  * Create an extruded shape from points in camera space.
  *
  * @param pointsInCam Polyline in normalized screen space ([-1, 1]x[-1, 1]).
  * @param camToLocal Transform matrix from camera space to local space
  * (modelViewProjInv matrix)
  * @param zMin Min extrusion plane, in camera space. By default, it's the 
  * camera's near clip plane.
  * @param zMax Max extrusion plane, in camera space. By default, it's the 
  * camera's far clip plane.
  *
  * @warning Return NULL if error occurred.
  */
  static SoShape* createFrom2DPoints ( const std::vector<SbVec2f>& pointsInCam, 
    const SbMatrix& camToLocal, 
    float zMin = -1.0f,
    float zMax = 1.0f);

private:

  /** Constructor. As all method are static, this class should not be instantiated. */
  SbExtrusionGenerator();

  /** Destructor */
  virtual ~SbExtrusionGenerator();

  /** 
   * Remove duplicated points, add point where line is self intersect and find
   * CW-ness of each segments to make polyline ready to the extrusion process. 
   * isCCW is a vector of bool indicating if specified segment should be considered
   * as CW or CCW: 
   * isCCW[i] => [polyline[i], polyline[i+1]] is CCW.
   * @note This imply that, when this function return, polyline.size() == isCCW.size().
   */
  static void prepareLine( std::vector<SbVec2f>& polyline, std::vector<bool>& isCCW );

  /** Remove contiguous duplicated points. */
  static void removeContiguousDuplicated( std::vector<SbVec2f>& polyline );

  /** 
   * Insert point each time line is self-intersecting:
   * If segments of polyline intersect other polyline segment, points are inserted
   * at right place.
   */
  static void insertIntersectingPoints( std::vector<SbVec2f>& polyline );

  /**
   * Find points that correspond to a self-intersection.
   * intersect is a vector of bool indicating if specified point is a self-intersection
   * intersect[i] == true => polyline[i] is a self intersection point.
   * @note This imply that, when this function return, polyline.size() == intersect.size().
   * This method should be called just after insertIntersectingPoints() to be sure that
   * their is not self-intersecting segments in polyline.
   */
  static void findSelfIntersection( const std::vector<SbVec2f>& polyline, std::vector<bool>& intersect );

  /** 
   * return intersection point between ]A, B[ and ]A1, B1[. 
   * @warning segments are opened, so if segments are connected, equal or tangent, it 
    * will returned false.
   */
  static bool getIntersection( const SbVec2f& A, const SbVec2f& B, const SbVec2f& A1, const SbVec2f& B1, SbVec2f& intersection );

  /**
   * Return true if 1st segment of polyline can be considered as CCW: if true, 
   * normal toward @B inside @b of segment is direct orthogonal of segment:
   * segment = polyline[1] - polyline[0];
   * normal(-segment.y, segment.x);
   */
  static bool isStartCCW( const std::vector<SbVec2f>& polyline );


  /** 
   * Compute distance from bbox to camera in camera space 
   * @param bboxInSomeSpace BoundingBox in arbitrary space
   * @param someSpaceToCam transform matrix from arbitrary space (space in which 
   * is expressed the bbox) to camera space.
   * @param zMin the nearest distance from camera to bbox in camera space.
   * @param zMax the farthest distance from camera to bbox in camera space.
   *
   * @note zMin and zMax are in [-1, 1] if bbox is in between camera near and 
   * far clip plane. If bbox has no volume, [zMin, zMax] are set to [-1, 1].
   */
  static void distanceFromCam(  const SbBox3f& bboxInSomeSpace, 
                                const SbMatrix& someSpaceToCam, 
                                float& zMin, float& zMax );

  /** 
   * Convenient method to convert a vector of point in some space to a vector 
   * of point in other space 
   */
  static void spaceChangeVector( const std::vector<SbVec3f>& lineInSpace1, 
                              const SbMatrix& space1ToSpace2, 
                              std::vector<SbVec3f>& lineInSpace2);

  /** 
   * Generate some king of extrusion between the 2 specified lines so that 
   * nearLine[i] will be connected to farLine[i]. Of course, the 2 lines must 
   * have the same size. 
   * isCCW specified if corresponding segment has to be considered in CCW order:
   * In case of self-intersecting polyline, we cannot decide the cw-ness of the 
   * whole line. Some parts are CCW, other parts are CW. For example, an "8"
   * has half of its shape CCW and the other half CW.
   */
  static SoShape* generateCylinder( const std::vector<SbVec3f>& nearLine, 
                                        const std::vector<SbVec3f>& farLine,
                                        const std::vector<bool>& isCCW);

  /** 
   * Generate cone between specified origin using specified line as base. 
   * isCCW specified if corresponding segment has to be considered in CCW order
   * if we sse cone from origin.
   * In case of self-intersecting polyline, we cannot decide the cw-ness of the 
   * whole line. Some parts are CCW, other parts are CW. For example, an "8"
   * has half of its shape CCW and the other half CW.
   * The specified CW-ness use cone origin as point of view. The generated shape
   * must use the opposite CW-ness, because we want the base to be CCW as seen
   * from the base, and not from the top.
   */
  static SoShape* generateCone( const SbVec3f& origin, 
                                const std::vector<SbVec3f>& baseLine,
                                const std::vector<bool>& isCCW);

  /**
  * Generate an SoShape from a list of triangles. triangles.size() must be a multiple of 3.
  * Return NULL if triangle.size() = 0 is not a multiple of 3.
  */
  static SoShape* generateShape( const std::vector<SbVec3f>& triangles);

  /** 
   * Tessellate the specified polygon and return corresponding triangles.
   * The returned point represent triangles. So, triangles.size() is a multiple 
   * of 3. 
   */
  static void tesselate( const std::vector<SbVec3f>& polygon, 
                          std::vector<SbVec3f>& triangles );

  /**
   * Make specified list of triangles CCW according to viewVector.
   * triangles.size must be a multiple of 3. If triangle.size < 3, nothing is done.
   */
  static void makeTrianglesCCW( std::vector<SbVec3f>& triangles, const SbVec3f& viewVector );

  /** 
   * Callback used by tesselate method callbackAction. userData must be an 
   * std::vector<SbVec3f>*. This callback just push the 3 specified vertices to 
   * the userData vector. 
   */
  static void pushTriangleCallback( void* userData, SoCallbackAction*, 
                                    const SoPrimitiveVertex* v1, 
                                    const SoPrimitiveVertex* v2, 
                                    const SoPrimitiveVertex* v3);

};


#endif // _SB_EXTRUSION_GENERATOR_H_
