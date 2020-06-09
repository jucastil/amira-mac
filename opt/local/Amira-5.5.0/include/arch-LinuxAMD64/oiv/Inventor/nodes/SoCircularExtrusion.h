#if !defined _SO_CIRCEXTRSHAPE_H_
#define _SO_CIRCEXTRSHAPE_H_

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      :  Roberto Calabrese (Feb 2011)
**=======================================================================*/

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/nodes/SoBaseExtrusion.h>

class SoState;
class SoAction;
class SoCircularExtrusionImpl;

//@TOBEWRAPPED
/**
 * @VSGEXT Geometric shape formed by extruding a circle along a 3D spine.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   The SoCircularExtrusion node is a geometric shape based on a constant radius circle 
 *   cross section extruded along a three-dimensional polyline (spine).
 *   The circle center lies on the polyline and the circle lies on the plane
 *   normal to the polyline at each point.
 *
 *   The application can specify which caps are created using the fields #beginCap and #endCap.
 *   By default both caps are visible.
 *
 *   The application can specify the visible portion of the shape along the spine 
 *   using normalized curvilinear coordinates (activeSection). By default the entire spine
 *   is visible.
 *
 *   The SoCircularExtrusion representation is dependent on SoComplexity::value.
 *   The shape is always simplified when the SoComplexity value is less than 1.
 *   Both the cross section (number of segments used for the circle) and the spine
 *   (number of points used for the spine) are affected by the simplification.
 *   The simplification algorithm approximates the spine by taking into account its curvature.
 *   The cross section circle is approximated by at least 10 points.
 *   With a SoComplexity value of 0 the extruded shape has the roughest representation.
 *
 *   Approximately the same geometry could be defined using an SoExtrusion node, but that
 *   node does not currently respond the SoComplexity value.  Likewise the clipping
 *   behavior could be obtained using two SoClipPlane nodes, but SoCircularExtrusion uses
 *   less memory when the activeSection is a subset of the full spine.  These two features
 *   make SoCircularExtrusion valuable when a large number of cylindrical objects must be
 *   displayed.
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
 *   @NODE_SINCE_OIV 8.6
 *   
 * @FILE_FORMAT_DEFAULT
 *    CircularExtrusion {
 *    @TABLE_FILE_FORMAT
 *      @TR beginCap        @TD TRUE
 *      @TR endCap          @TD TRUE
 *      @TR spine           @TD [ 0 0 0, 0 1 0 ]
 *      @TR scaleMode       @TD DEFAULT
 *      @TR radius          @TD [ 1 ]
 *      @TR activeSection   @TD [ 0, 1 ]
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *   SoExtrusion, SoComplexity, SoBaseExtrusion
 * 
 */ 

class INVENTOR_API SoCircularExtrusion : public SoBaseExtrusion
{
  SO_NODE_HEADER( SoCircularExtrusion );

public:
  // Fields
  /** Radius of the circular cross-section.
    * The default value is 1.
    */
  SoSFFloat radius;

  /** Defines the visible section of the spine in normalized coordinates.
   *  The default is (0,1) meaning that the entire spine is rendered.
   */
  SoSFVec2f activeSection;

  /** Constructor */
  SoCircularExtrusion();

SoEXTENDER public:

  // Implement actions

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

  /** register in database */
  static void initClass();

  /** unregister from database */
  static void exitClass();

  /** catch some fields changes */
  virtual void notify( SoNotList *list );

protected:
  /** Destructor */
  virtual ~SoCircularExtrusion();

  /** Generates quads representing shape */
  virtual void generatePrimitives( SoAction *action );

private:
  SoCircularExtrusionImpl* m_impl;
};

#endif /* _SO_CIRCEXTRSHAPE_H_ */


