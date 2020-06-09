/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (May 1998)
**=======================================================================*/

                                                             /* include files */
#ifndef _SO_MARKER_SET_
#define _SO_MARKER_SET_

#include <Inventor/nodes/SoPointSet.h>
#include <Inventor/fields/SoMFInt32.h>

class SbThreadMutex;
class SoMarker;

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Extension of PointSet that draws a small bitmap (symbol) at each 3D location.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 * 
 *   This class draws a marker (small image) at each of a set of points located at
 *   the coordinates specified by the #vertexProperty field (from SoVertexShape) 
 *   or the current inherited 3D coordinates. For best performance, the 
 *   #vertexProperty field is recommended.  SoMarkerSet uses the coordinates in 
 *   order, starting with the first one. The number of coordinates to use (the
 *   number of markers in the set) is specified by the #numPoints field.  The
 *   default value of this field is -1, which means to use all the coordinates,
 *   so it may not be necessary to explicitly set this field.
 *
 *   You specify the marker to be drawn at each point using the field #markerIndex,
 *   which indexes into the global list of defined markers.  There is a set of
 *   pre-defined markers already in the list.  You can add your own markers to this
 *   list using the #addMarker functions.  Markers in the list can be used by any
 *   SoMarkerSet or SoIndexedMarkerSet node.
 *
 *   A marker is an image defined by a bitmap and optional color values.  If no 
 *   color values are given then image pixels corresponding to "1" bits are drawn 
 *   using the current material color (see SoMaterial) and pixels corresponding 
 *   to "0" bits are not drawn (whatever is behind the marker shows through).  If 
 *   color values are given then each pixel in the image is assigned an RGBA value.
 *
 *   Note that custom markers defined with addMarker are not automatically
 *   saved in the Open Inventor file when an SoWriteAction is applied to the
 *   scene graph (and therefore are not defined if the scene graph is reloaded).
 *   To save marker definitions in an Open Inventor file use the SoMarker node.
 *
 *   Shape Antialiasing type is SoShape::POINTS.
 *   
 *   The following markers are defined by default:
 *   
 *   @IMAGE MARKERS.gif 
 *   
 * 
 * @FILE_FORMAT_DEFAULT
 *    MarkerSet {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexProperty   @TD NULL
 *       @TR startIndex       @TD 0
 *       @TR numPoints        @TD -1
 *       @TR markerIndex      @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws bitmaps based on the current coordinates.
 * 
 *    SoGetPrimitiveCountAction @BR
 *        Increments the image count by 1 for each marker in the marker set.
 * 
 * 
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoFullSceneAntialiasing,
 *    SoIndexedMarkerSet,
 *    SoMarker,
 *    SoPointSet,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoMarkerSet : public SoPointSet {
  SO_NODE_HEADER(SoMarkerSet) ;

 public:
  /**
   * Specifies the marker index (type of marker)
   * 
   */
  SoMFInt32 markerIndex ;

  /**
   * Constructor.
   */
  SoMarkerSet() ;

  /** Marker type */
  enum MarkerType {
    /** Cross 5x5 */
    CROSS_5_5,
    /** Plus 5x5 */
    PLUS_5_5,
    /** Minus 5x5 */
    MINUS_5_5,
    /** Slash 5x5 */
    SLASH_5_5,
    /** Backslash 5x5 */
    BACKSLASH_5_5,
    /** Bar 5x5 */
    BAR_5_5,
    /** Star 5x5 */
    STAR_5_5,
    /** Y 5x5 */
    Y_5_5,
    /** Lightning 5x5 */
    LIGHTNING_5_5,
    /** Well 5x5 */
    WELL_5_5,
    
    /** Circle line 5x5 */
    CIRCLE_LINE_5_5,
    /** Square line 5x5 */
    SQUARE_LINE_5_5,
    /** Diamond line 5x5 */
    DIAMOND_LINE_5_5,
    /** Triangle line 5x5 */
    TRIANGLE_LINE_5_5,
    /** Rhombus line 5x5 */
    RHOMBUS_LINE_5_5,
    /** Hourglass line 5x5 */
    HOURGLASS_LINE_5_5,
    /** Satellite line 5x5 */
    SATELLITE_LINE_5_5,
    /** Pine line 5x5 */
    PINE_TREE_LINE_5_5,
    /** Caution line 5x5 */
    CAUTION_LINE_5_5,
    /** Ship line 5x5 */
    SHIP_LINE_5_5,

    /** Circle filled 5x5 */
    CIRCLE_FILLED_5_5,
    /** Square filled 5x5 */
    SQUARE_FILLED_5_5,
    /** Diamond filled 5x5 */
    DIAMOND_FILLED_5_5,
    /** Triangle filled 5x5 */
    TRIANGLE_FILLED_5_5,
    /** Rhombus filled 5x5 */
    RHOMBUS_FILLED_5_5,
    /** Hourglass filled 5x5 */
    HOURGLASS_FILLED_5_5,
    /** Satellite filled 5x5 */
    SATELLITE_FILLED_5_5,
    /** Pine filled 5x5 */
    PINE_TREE_FILLED_5_5,
    /** Caution filled 5x5 */
    CAUTION_FILLED_5_5,
    /** Ship filled 5x5 */
    SHIP_FILLED_5_5,

    /** Cross 7x7 */
    CROSS_7_7,
    /** Plus 7x7 */
    PLUS_7_7,
    /** Minus 7x7 */
    MINUS_7_7,
    /** Slash 7x7 */
    SLASH_7_7,
    /** Backslash 7x7 */
    BACKSLASH_7_7,
    /** Bar 7x7 */
    BAR_7_7,
    /** Star 7x7 */
    STAR_7_7,
    /** Y 7x7 */
    Y_7_7,
    /** Lightning 7x7 */
    LIGHTNING_7_7,
    /** Well 7x7 */
    WELL_7_7,

    /** Circle line 7x7 */
    CIRCLE_LINE_7_7,
    /** Square line 7x7 */
    SQUARE_LINE_7_7,
    /** Diamond line 7x7 */
    DIAMOND_LINE_7_7,
    /** Triangle line 7x7 */
    TRIANGLE_LINE_7_7,
    /** Rhombus line 7x7 */
    RHOMBUS_LINE_7_7,
    /** Hourglass line 7x7 */
    HOURGLASS_LINE_7_7,
    /** Satellite line 7x7 */
    SATELLITE_LINE_7_7,
    /** Pine line 7x7 */
    PINE_TREE_LINE_7_7,
    /** Caution line 7x7 */
    CAUTION_LINE_7_7,
    /** Ship line 7x7 */
    SHIP_LINE_7_7,
    
    /** Circle  filled 7x7 */
    CIRCLE_FILLED_7_7,
    /** Square filled 7x7 */
    SQUARE_FILLED_7_7,
    /** Diamond filled 7x7 */
    DIAMOND_FILLED_7_7,
    /** Triangle filled 7x7 */
    TRIANGLE_FILLED_7_7,
    /** Rhombus filled 7x7 */
    RHOMBUS_FILLED_7_7,
    /** Hourglass filled 7x7 */
    HOURGLASS_FILLED_7_7,
    /** Satellite filled 7x7 */
    SATELLITE_FILLED_7_7,
    /** Pine filled 7x7 */
    PINE_TREE_FILLED_7_7,
    /** Caution filled 7x7 */
    CAUTION_FILLED_7_7,
    /** Ship filled 7x7 */
    SHIP_FILLED_7_7,

    /** Cross 9x9 */
    CROSS_9_9,
    /** Plus 9x9 */
    PLUS_9_9,
    /** Minus 9x9 */
    MINUS_9_9,
    /** Slash 9x9 */
    SLASH_9_9,
    /** Backslash 9x9 */
    BACKSLASH_9_9,
    /** Bar 9x9 */
    BAR_9_9,
    /** Star 9x9 */
    STAR_9_9,
    /** Y 9x9 */
    Y_9_9,
    /** Lightning 9x9 */
    LIGHTNING_9_9,
    /** Well 9x9 */
    WELL_9_9,
    
    /** Circle line 9x9 */
    CIRCLE_LINE_9_9,
    /** Square line 9x9 */
    SQUARE_LINE_9_9,
    /** Diamond line 9x9 */
    DIAMOND_LINE_9_9,
    /** Triangle line 9x9 */
    TRIANGLE_LINE_9_9,
    /** Rhombus line 9x9 */
    RHOMBUS_LINE_9_9,
    /** Hourglass line 9x9 */
    HOURGLASS_LINE_9_9,
    /** Satellite line 9x9 */
    SATELLITE_LINE_9_9,
    /** Pine line 9x9 */
    PINE_TREE_LINE_9_9,
    /** Caution line 9x9 */
    CAUTION_LINE_9_9,
    /** Ship line 9x9 */
    SHIP_LINE_9_9,

    /** Circle filled 9x9 */
    CIRCLE_FILLED_9_9,
    /** Square filled 9x9 */
    SQUARE_FILLED_9_9,
    /** Diamond filled 9x9 */
    DIAMOND_FILLED_9_9,
    /** Triangle filled 9x9 */
    TRIANGLE_FILLED_9_9,
    /** Rhombus filled 9x9 */
    RHOMBUS_FILLED_9_9,
    /** Hourglass filled 9x9 */
    HOURGLASS_FILLED_9_9,
    /** Satellite filled 9x9 */
    SATELLITE_FILLED_9_9,
    /** Pine filled 9x9 */
    PINE_TREE_FILLED_9_9,
    /** Caution filled 9x9 */
    CAUTION_FILLED_9_9,
    /** Ship filled 9x9 */
    SHIP_FILLED_9_9
  };

  /**
   * Return the number of defined markers
   */
  static int getNumDefinedMarkers();

  /**
   * Add a new marker with index @B markerIndex @b. If the marker exists, it is
   * replaced. @B size @b is the size of the marker in pixels. @B bytes @b is the
   * marker bitmap. The bitmap is arranged row by row from left to right and top
   * to bottom (according to the parameter @B isUpToDown @b). Each byte in the
   * bitmap corresponds to eight pixels.  Open Inventor makes a copy of the bitmap.
   * 
   * @B isLSBFirst @b: If TRUE, bits are ordered within a byte from least significant
   * to most significant; otherwise the first bit in each byte is the most
   * significant one.
   *
   * @B isUpToDown @b: If TRUE, marker bitmap is described from top to bottom
   * (bytes[0] is the left top corner of the bitmap), otherwise from bottom to
   * top (bytes[0] is the bottom left corner).
   */
  static void addMarker(int markerIndex, const SbVec2s &size, const unsigned char *bytes,
                        SbBool isLSBFirst = TRUE, SbBool isUpToDown = TRUE);

  /** 
   * Add a new colored marker with index @B markerIndex @b. If the marker exists, it is
   * replaced. @B size @b is the size of the marker in pixels. @B bytes @b is the
   * marker bitmap. @B orderedRGBA @b is an array of per-pixel color values to apply
   * to the marker.  The bitmap is arranged row by row from left to right and top to
   * bottom (according to the parameter @B isUpToDown @b). Each byte in the bitmap
   * corresponds to eight pixels. Each value in orderedRGBA corresponds to one pixel.
   * Open Inventor makes a copy of the bitmap and color values.
   * 
   * @B isLSBFirst @b: If TRUE, bits are ordered within a byte from least significant
   * to most significant; otherwise the first bit in each byte is the most
   * significant one.
   8
   * @B isUpToDown @b: If TRUE, marker bitmap and color array are described from top
   * to bottom (bytes[0] is the left top corner of the bitmap), otherwise from bottom
   * to top (bytes[0] is the bottom left corner).
   */
  static void addMarker(int markerIndex, const SbVec2s &size,
                        const unsigned char *bytes,
                        const uint32_t *orderedRGBA,
                        SbBool isLSBFirst = TRUE, SbBool isUpToDown = TRUE);

  /** 
   * Add a new marker with index @B markerIndex @b using an existing marker definition.
   * If the marker exists, it is replaced.
   */
  static void addMarker(int markerIndex, SoMarker* marker );

  /**
   * Retrieve the description of the marker with index @B markerIndex @b. Returns
   * TRUE if the marker exists, otherwise returns FALSE and the parameters are
   * not modified.
   * [OIV-WRAPPER-ARG IN,OUT,OUT&ARRAY{size[0] % 8 != 0? ((int)(size[0] / 8) + 1)*size[1]: size[0] / 8 * size[1]},OUT]
   * [OIVJAVA-WRAPPER PACK{MarkerInfo}]
   */
  static SbBool getMarker(int markerIndex,
                          SbVec2s &size,
                          const unsigned char *&bytes,
                          SbBool &isLSBFirst);

  /**
   * Retrieve the description of the colored marker with index @B markerIndex @b.
   * Returns TRUE if the marker exists, otherwise returns FALSE and the
   * parameters are not modified.  If the marker does not have color values, 
   * orderedRGBA will point to a single uint32_t containing the value zero.
   * [OIV-WRAPPER-ARG IN,OUT,OUT&ARRAY{size[0] % 8 != 0? ((int)(size[0] / 8) + 1)*size[1]: size[0] / 8 * size[1]},ARRAY{size[0]*size[1]},OUT]
   * [OIVJAVA-WRAPPER NAME{getColoredMarker},PACK{ColoredMarkerInfo}]
   */
  static SbBool getMarker(int markerIndex,
                          SbVec2s &size,
                          const unsigned char *&bytes,
                          const uint32_t *&orderedRGBA,
                          SbBool &isLSBFirst);

  /**
   * Retrieve the definition of the marker with index @B markerIndex @b. Returns
   * NULL if the marker does not exist.
   */
  static SoMarker* getMarker( int markerIndex );

  /**
   * Remove the marker with index @B markerIndex @b. Returns TRUE if the marker
   * was successfully removed, FALSE otherwise.
   */
  static SbBool removeMarker(int markerIndex);

SoEXTENDER public:
  virtual void  GLRender(SoGLRenderAction *action);
  virtual void  getPrimitiveCount(SoGetPrimitiveCountAction *action);

  static SbBool isMarkerBitSet(int markerIndex, int bitNumber);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual ~SoMarkerSet();

};

#endif // !_SO_MARKER_SET_
