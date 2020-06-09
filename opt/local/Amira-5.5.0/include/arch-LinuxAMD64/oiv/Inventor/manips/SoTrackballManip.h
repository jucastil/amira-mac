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


#ifndef  _SO_TRACKBALL_MANIP_
#define  _SO_TRACKBALL_MANIP_

#include <Inventor/manips/SoTransformManip.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTrackballManip
//
//  Trackball manipulator - allows user to rotate objects.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Transform node with 3D interface for changing rotation and scaling.
 * 
 * @ingroup manips
 * 
 * @DESCRIPTION
 *   SoTrackballManip is derived from SoTransform (by way of SoTransformManip). When
 *   its fields change, nodes following it in the scene graph rotate, scale, and/or
 *   translate.
 *   
 *   As a subclass of SoTransformManip, this manipulator also has a 3D interface to
 *   edit some of its fields. In this case, the interface edits the @B rotation @b
 *   and @B scaleFactor @b fields.
 *   
 *   A manipulator differs from a dragger. When you move a dragger, no other nodes are
 *   affected. When you move an SoTransformManip, other nodes move along with it.
 *   (See the reference page for SoTransformManip).
 *   
 *   The interface for an SoTrackballManip is exactly the same as that of the
 *   SoTrackballDragger. To find out more about the interface, see the reference page
 *   for SoTrackballDragger. To find out how the manipulator uses a dragger to
 *   provide its interface, see the reference page for SoTransformManip.
 *   
 *   On screen, this manipulator will surround the objects influenced by its motion.
 *   This is because it turns on the @B surroundScale @b part of the dragger (See
 *   the reference page for SoSurroundScale)
 * 
 * @FILE_FORMAT_DEFAULT
 *    TrackballManip {
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
 *    SoCenterballManip,
 *    SoHandleBoxManip,
 *    SoJackManip,
 *    SoTabBoxManip,
 *    SoTrackballDragger,
 *    SoTransformBoxManip,
 *    SoTransformerManip,
 *    SoTransform,
 *    SoTransformManip
 * 
 * 
 */ 

class INVENTOR_API SoTrackballManip : public SoTransformManip {

  SO_NODE_HEADER(SoTrackballManip);

 public:
  /**
   * Constructor.
   */
  SoTrackballManip();

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void exitClass();

 protected:
  virtual ~SoTrackballManip();
};

#endif /* _SO_TRACKBALL_MANIP_ */

