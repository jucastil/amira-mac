#if !defined(_SO_BASE_EXTRUSION_)
#define  _SO_BASE_EXTRUSION_

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFEnum.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoBaseExtrusion
//
//  Node that defines the extrusion parameters 
//
//////////////////////////////////////////////////////////////////////////////

/**
* Abstract base class for all extrusion-based shape nodes.
* 
* @ingroup ShapeNodes
* 
* @DESCRIPTION
*   This node is the abstract base class for all extrusion-based shape (geometry)
*   nodes. It is used as a repository for convenience functions for subclasses and
*   to provide a type identifier to make it easy to determine whether a shape is
*   extrusion-based.
*   
*   All extrusion-based shapes are created by extruding a 2D shape along a 3D #spine.
*   The user can determine which caps are created using the fields #beginCap and #endCap.
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
*   #extrusionMode is used to select the version of the extrusion algorithm to use 
*
*   The options are:
*   SMOOTH        - the algorithm uses constant section parts cut at spine points 
*                   in a way similar to what a framer would do to build a frame
*                   this provides a better continuity of the shape and avoids cracks
*   BASIC         - the original algorithm, it does not grant that extrusion portions have
*                   constant section, shapes could be more twisted
* 
* @FILE_FORMAT_DEFAULT
*   This is an abstract class. See the reference page of a derived class for the
*   format and default values.
* 
* @SEE_ALSO
*    SoExtrusion,
*    SoCircularExtrusion
* 
* 
*/ 

class INVENTOR_API SoBaseExtrusion : public SoShape  {

  SO_NODE_ABSTRACT_HEADER(SoBaseExtrusion);

  friend class SoExtrusionImpl;

 public:

   enum ScaleMode
   {
     /** Default scaling */
     DEFAULT,
     /** Spine only scaling */
     SPINE_ONLY,
     /** Cross section only scaling - Not currently implemented */
     SECTION_ONLY,
     /** No scaling - Not currently implemented*/
     NONE
   };

   enum ExtrusionMode
   {
     /** Default new extrusion algorithm mode with constant section parts cut at spine joints */
     SMOOTH,
     /** Old extrusion algorithm  */
     BASIC
   };

  // Fields
  /**
   * If TRUE, begin planar cap surfaces generated. Default is TRUE.
   */
  SoSFBool            beginCap;
  
  /**
   * If TRUE, end planar cap surfaces generated. Default is TRUE.
   */
  SoSFBool            endCap;

  /**
   *  Spine points. Default is [0 0 0, 0 1 0].
   */
  SoMFVec3f           spine;

  /**
  *  Scaling behavior of the extrusion.
  *  Use enum #ScaleMode. Default is DEFAULT.
  */
  SoSFEnum            scaleMode;

  /**
  *  Construction behavior of the extrusion.
  *  Use enum #ConstructionMode.  Default is CONSTR_DEFAULT.
  */
  SoSFEnum            extrusionMode;

 protected:
  /** Constructor. */
  SoBaseExtrusion();

  /** Destructor. */
  virtual ~SoBaseExtrusion();


 SoEXTENDER public:

  /** Creates extrusion vertices in 8.5 fully compatible mode */
  static SbVec3f   *generateExtrusionVertices( SoAction *action, const SbVec3f * spine,
                                               int numSpinePts, const SbVec2f *crossSection,
                                               int numCrossSectionPts, const SbRotation *orientPts,
                                               int numOrientPts, const SbVec2f *scalePts,
                                               int numScalePts );

  static SbVec3f   findZaxis( const SbVec3f * spine, const int numspine,
                              const int i, const SbBool closed );
  static SbVec3f   findYaxis( const SbVec3f * spine, const int numspine,
                              const int i, const SbBool closed );

 SoINTERNAL public:

  static void initClass();
  static void exitClass();

  static void updateTols();

 protected:

  static float    s_dot_epsilon;
  static float    s_epsilon;

 };

#endif /* _SO_BASE_EXTRUSION_ */

