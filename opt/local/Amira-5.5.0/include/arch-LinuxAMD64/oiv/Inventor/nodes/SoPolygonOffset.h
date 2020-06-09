/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Nov 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_POLYGON_OFFSET_
#define  _SO_POLYGON_OFFSET_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBitMask.h>
#include <Inventor/fields/SoSFBool.h>

#include <Inventor/nodes/SoNode.h>

#include <Inventor/elements/SoPolygonOffsetElement.h>

class SoGLRenderAction ;
class SoCallbackAction ;

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Property node that sets the polygon offset.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This class encapsulates the OpenGL 1.1 glPolygonOffset() function. This node can
 *   be used to offset polygons that are at the exact same depth to avoid depth
 *   buffer artifacts, commonly called z-buffer stitching.
 * 
 *   NOTE: SoPolygonOffset, as its name implies, only works with polygonal geometry.
 *
 *   SoPolygonOffset affects filled primitives such as SoFaceSet and SoTriangleStripSet.  
 *   It also affects lines and points in the limited sense that it affects polygonal 
 *   primitives when the draw style is set to LINES or POINTS. However, because 
 *   polygon offset does not affect non-polygonal geometry, primitives such as SoLineSet 
 *   and SoPointSet cannot be offset with SoPolygonOffset(). To avoid depth buffer 
 *   artifacts with mixed polygonal and non-polygonal geometry, you should "push" the 
 *   polygonal geometry away from the camera.
 *   
 *   Note: There is only one offset value (combination of #factor
 *   and #units) in the traversal state at any given time.
 *
 *   The value of the offset is @B factor @b* z + r * @B #units@b, where @BR
 *   - @B z @b is a measurement of the change in depth relative to the
 *   screen area of the polygon (commonly called the depth slope), and
 *   - @B r @b is the smallest value that is guaranteed to produce a resolvable 
 *     offset for a given OpenGL implementation.
 *
 *   So @B units @b produces a constant depth offset and @B factor @b produces
 *   a variable depth offset which is zero when a polygon is perpendicular to
 *   the view vector (parallel to the view plane) and increases as the depth
 *   slope increases.
 *
 *   Both @B factor @b and @B units @b may be either positive or negative. 
 *   A positive offset value pushes primitives away from the camera 
 *   and a negative value pulls them closer. 
 *   Generally a small value, like 1.0, is sufficient for both parameters.
 *   
 * @FILE_FORMAT_DEFAULT
 *    PolygonOffset {
 *    @TABLE_FILE_FORMAT
 *       @TR factor   @TD 1
 *       @TR units    @TD 100
 *       @TR styles   @TD FILLED
 *       @TR on       @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Calls @B glPolygonOffset @b and enables or disables the polygon offset feature
 *        as specified.  Sets: SoPolyonOffsetElement.
 * 
 * @SEE_ALSO
 *    SoDepthOffset, SoDepthBuffer
 * 
 * 
 */ 

class INVENTOR_API SoPolygonOffset : public SoNode {  
  SO_NODE_HEADER(SoPolygonOffset) ;


 public:

   /** Offset style */
  enum Style {
    /** Filled */
    FILLED = SoPolygonOffsetElement::FILLED,
    /** Lines */
    LINES  = SoPolygonOffsetElement::LINES, 
    /** Points */
    POINTS = SoPolygonOffsetElement::POINTS
  } ;

  // Fields
  /**
   * Specifies a scale factor that is used	to create a variable depth 
   * offset	for each polygon. Positive values push polygons away from
   * the camera (opposite of SoDepthOffset). Default = 1.0.
   */
  SoSFFloat   factor ;

  /**
   * Is multiplied by an OpenGL implementation-specific value to
	 * create a constant depth offset. Positive values push polygons
   * away from the camera (oppsite of SoDepthOffset). Default = 100.0.
   */
  SoSFFloat   units ;
 
  /**
   * A bit-wise combination of FILLED, LINES, and POINTS
   * that determines which polygon modes should be offset. Default = FILLED.
   */
  SoSFBitMask styles ;

  /**
   * Enables/disables polygon offset. Default = TRUE.
   */
  SoSFBool    on ;

  /**
   * Constructor.
   */
  SoPolygonOffset() ;

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;

  
  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  SoSFBool override;

 protected:
  // Destructor
  virtual ~SoPolygonOffset() ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_POLYGON_OFFSET_ */

