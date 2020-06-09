/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORMER_MANIP_
#define  _SO_TRANSFORMER_MANIP_

#include <Inventor/manips/SoTransformManip.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransformerManip
//
//  - allows user to transform objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Transform node with 3D interface for changing scaling, rotation, and
 * translation.
 * 
 * @ingroup manips
 * 
 * @DESCRIPTION
 *   This is a new manipulator with some improvements over the older Inventor manips.
 *   It has the following features: [1] full interface for rotate, translate, and
 *   scale, [2] better feedback, [3] locate highlighting. 
 *   
 *   SoTransformerManip is derived from SoTransform (by way of SoTransformManip). When
 *   its fields change, nodes following it in the scene graph rotate, scale, and/or
 *   translate.
 *   
 *   As a subclass of SoTransformManip, this manipulator also has a 3D interface to
 *   edit some of its fields. In this case, the interface edits the
 *   @B scaleFactor @b, @B rotation @b and @B translation @b fields.
 *   
 *   A manipulator differs from a dragger. When you move a dragger, no other nodes are
 *   affected. When you move an SoTransformManip, other nodes move along with it.
 *   (See the reference page for SoTransformManip).
 *   
 *   The interface for an SoTransformerManip is exactly the same as that of the
 *   SoTransformerDragger. To find out more about the interface, see the reference
 *   page for SoTransformerDragger. To find out how the manipulator uses a dragger to
 *   provide its interface, see the reference page for SoTransformManip.
 *   
 *   On screen, this manipulator will surround the objects influenced by its motion.
 *   This is because it turns on the @B surroundScale @b part of the dragger (See
 *   the reference page for SoSurroundScale)
 * 
 * @FILE_FORMAT_DEFAULT
 *    TransformerManip {
 *    @TABLE_FILE_FORMAT
 *       @TR translation        @TD 0 0 0
 *       @TR rotation           @TD 0 0 1 0
 *       @TR scaleFactor        @TD 1 1 1
 *       @TR scaleOrientation   @TD 0 0 1 0
 *       @TR center             @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoTransformerDragger,
 *    SoTransform,
 *    SoCenterballManip,
 *    SoHandleBoxManip,
 *    SoJackManip,
 *    SoTabBoxManip,
 *    SoTrackballManip,
 *    SoTransformBoxManip,
 *    SoTransformManip
 * 
 * 
 */ 

class INVENTOR_API SoTransformerManip : public SoTransformManip {

  SO_NODE_HEADER(SoTransformerManip);

 public:
  /**
   * Constructor.
   */
  SoTransformerManip();

  /**
   * Tells the dragger inside this manip to unsquish its rotation and scale knobs
   * during the next traversal. Ordinarily, the knobs are only unsquished upon readin
   * from file and when the mouse button is released at the end of a drag. If you
   * want this to happen more often, then you should call this method.
   */
  void unsquishKnobs();

  /**
   * Returns whether or not the dragger inside this manip will perform locate
   * highlighting.
   */
  SbBool isLocateHighlighting();
  /**
   * Sets whether or not the dragger inside this manip will perform locate
   * highlighting. Default is TRUE.
   */
  void setLocateHighlighting( SbBool onOff );

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void exitClass();

 protected:
  virtual ~SoTransformerManip();

};

#endif /* _SO_TRANSFORMER_MANIP_ */

