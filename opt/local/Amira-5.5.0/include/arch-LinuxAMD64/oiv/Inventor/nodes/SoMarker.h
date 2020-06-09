/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Feb 2008)
**=======================================================================*/


#ifndef  _SO_MARKER_H_
#define  _SO_MARKER_H_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFUInt32.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFUByte.h>
#include <Inventor/fields/SoSFVec2s.h>
#include <Inventor/fields/SoSFInt32.h>

class SoState;
class SoGLObjectCache;

#define MARKER_HASH_TAB_SIZE 151

/** 
 * @VSGEXT Defines a custom bitmap for SoMarkerSet and SoIndexedMarkerSet.
 * 
 * @ingroup nodes
 * 
 * @DESCRIPTION
 * 
 *   This class defines a Marker.  A marker is an image defined by a bitmap
 *   and optional color values.  If no color values are given then image pixels
 *   corresponding to "1" bits are drawn using the current material color (see 
 *   SoMaterial) and pixels corresponding to "0" bits are not drawn (whatever
 *   is behind the marker shows through).  If color values are given then each
 *   pixel in the image can be assigned an RGBA value.
 *
 *   @B size @b is the dimensions of the marker image in pixels. @B bitmap @b is the
 *   marker bitmap. The bitmap is arranged row by row, from left to right and down
 *   to up (or up to down according to the parameter @B isUpToDown @b). Each byte
 *   specifies eight pixels. If @B isLSBFirst @b is TRUE, bits are ordered within
 *   a byte from Least Significant to Most Significant; otherwise the first bit in each
 *   byte is the most significant one. If @B isUpToDown @b is TRUE, the marker bitmap is
 *   described from up to down (first byte is the top left corner of the bitmap),
 *   otherwise from down to up (first byte is the bottom left corner).
 *   @B orderedRGBA @b is an optional color mask to apply to the marker. The color mask
 *   is arranged the same as bitmap, but each value (unsigned integer) specifies
 *   the color of one pixel. Each color is an ordered RGBA value.  A value of 0xFF for
 *   Alpha makes the color mask be ignored for this pixel, and the color is
 *   inherited from the state depending on the bitmap value (as if no color values
 *   were given).
 *
 *   Note:
 *     - If only orderedRGBA values are set, the bitmap is assumed to be
 *       a fully defined set of "1" bits.
 *     - Marker size must be greater than 1x1.
 *
 *   Marker definitions are used by the SoMarkerSet and SoIndexedMarkerSet nodes.
 *   To make a custom marker available to these nodes, use one of the addMarker 
 *   methods defined in those classes.
 *   
 *   An SoMarker node can be added to the scene graph, but it is not a geometry node
 *   or an attribute node (does not render anything and does not affect the
 *   traversal state list).  However SoMarker nodes are written out to an Inventor
 *   file if an SoWriteAction is applied to the scene graph.  So adding SoMarker
 *   nodes to the scene graph allows custom marker definitions to be saved and restored.
 *   For example:
 *   <PRE>
 *   // Add markers to scene graph in order to export them in IV file.
 *   root->addChild( SoMarkerSet::getMarker(90) );
 *   root->addChild( SoMarkerSet::getMarker(91) );
 *   root->addChild( SoMarkerSet::getMarker(92) );
 *   </PRE>
 * 
 * @FILE_FORMAT_DEFAULT
 *    Marker {
 *    @TABLE_FILE_FORMAT
 *       @TR bitmap       @TD 0
 *       @TR orderedRGBA  @TD 0
 *       @TR upToDown     @TD TRUE
 *       @TR LSBFirst     @TD TRUE
 *       @TR size         @TD (0, 0)
 *       @TR index        @TD -1
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoMarkerSet,
 *    SoIndexedMarkerSet
 * 
 * 
 */ 

class INVENTOR_API SoMarker : public SoNode
{
  SO_NODE_HEADER(SoMarker);

public:

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
   * Marker constructor.
   */
  SoMarker();

  /**
   * Defines the current marker data buffer
   */
  SoMFUByte bitmap;

  /**
   * Defines the marker coloration mask.
   */
  SoMFUInt32 orderedRGBA;

  /**
   * if TRUE, marker bitmap is described from up to down (that is bytes[0] is
   * the left top corner of the bitmap), otherwise from down to up (that is
   * bytes[0] is the bottom left corner).
   */
  SoSFBool upToDown;

  /**
   * if TRUE, bits are ordered within a byte from Least Significant to most
   * significant; otherwise the first bit in each byte is the most significant one.
   */
  SoSFBool isLSBFirst;

  /**
   * Defines the size (in pixels) of the marker. Must be greater than 1x1
   */
  SoSFVec2s size;

  /**
   * Defines the marker index.
   */
  SoSFInt32 index;

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  void render( SoState* state, int index = 0);
  virtual void notify( SoNotList* list );
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  /**
   * Sets marker index
   */
  int getMarkerIndex() 
  { return m_markerIndex; }

  /**
   * Gets marker index
   */
  void setMarkerIndex( const int tindex ) 
  { m_markerIndex = tindex; }

  /**
   * Get num of defined markers.
   */
  static int getNumDefinedMarkers();

  /**
   * Add a new marker.
   */
  static void addMarker(int markerIndex,
                        const SbVec2s &size,
                        const unsigned char *bytes,
                        const uint32_t *orderedRGBA,
                        SbBool isLSBFirst = TRUE,
                        SbBool isUpToDown = TRUE);
  /**
   * Add a new marker.
   */  
  static void addMarker(int markerIndex, SoMarker* marker );

  /**
   * Remove a previously added marker.
   */  
  static SbBool removeMarker(int markerIndex);
  
  static SoMarker* getMarkerDesc( int markerInd );

  static SbBool isMarkerBitSet(int markerIndex, int bitNumber) ;

  // Update the list of all instancied SoMarkerSet
  static void updateListInstanciedMarkerSet();
  static void addMarkerSetDependency(SoNode* );
  static void removeMarkerSetDependency(SoNode* );

protected:
  /**
   * Virtual destructor.
   */
  virtual ~SoMarker();

  SbBool useDL;

private:

  // Index of the marker
  int m_markerIndex;

  // Marker associated displayList
  SoGLObjectCache* m_objCache;

  // Marker hash table
  static SbPList m_markerHashTab[MARKER_HASH_TAB_SIZE];

  // Create/Destroy the list of predefined markers
  static void createListOfPreDefinedMarkers();
  static void destroyListOfPreDefinedMarkers();
  static bool m_isBuildingPredefinedMarkers;

  // Return the marker hash table index from a marker index
  static inline int getMarkerHashTabIndex(int markerIndex);

  // List of instancied SoMarkerSet
  static SbPList m_listInstanciedMarkerSet;

  void setPredefined(bool b);

  bool m_predefined;
  bool m_prevUpToDown;
};

#endif // !_SO_MARKER_H_
