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


#ifndef  _SO_JACK_MANIP_
#define  _SO_JACK_MANIP_

#include <Inventor/manips/SoTransformManip.h>

/**
 * Transform node with 3D interface for rotating, scaling, and translating.
 * 
 * @ingroup manips
 * 
 * @DESCRIPTION
 *   SoJackManip is derived from SoTransform (by way of SoTransformManip). When its
 *   fields change, nodes following it in the scene graph rotate, scale, and/or
 *   translate.
 *   
 *   As a subclass of SoTransformManip, this manip also has a 3D interface to edit
 *   some of its fields. In this case, the interface edits the @B scaleFactor @b,
 *   @B rotation @b and @B translation @b fields.
 *   
 *   A manipulator differs from a dragger. When you move a dragger, no other nodes are
 *   affected. When you move an SoTransformManip, other nodes move along with it.
 *   (See the reference page for SoTransformManip).
 *   
 *   The interface for an SoJackManip is exactly the same as that of the
 *   SoJackDragger. To find out more about the interface, see the reference page for
 *   SoJackDragger. To find out how the manipulator uses a dragger to provide its
 *   interface, see the reference page for SoTransformManip.
 *   
 *   On screen, this manip will surround the objects influenced by its motion. This is
 *   because it turns on the @B surroundScale @b part of the dragger (See the
 *   reference page for SoSurroundScale)
 * 
 * @FILE_FORMAT_DEFAULT
 *    JackManip {
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
 *    SoJackDragger,
 *    SoTabBoxManip,
 *    SoTrackballManip,
 *    SoTransformBoxManip,
 *    SoTransformerManip,
 *    SoTransform,
 *    SoTransformManip
 * 
 * 
 */ 

class INVENTOR_API SoJackManip : public SoTransformManip
{
  SO_NODE_HEADER(SoJackManip);

 public:
  
  /**
   * Constructor.
   */
  SoJackManip();

 SoINTERNAL public:
  static void initClass();  // initialize the class
  static void exitClass();

 protected:
  virtual ~SoJackManip();
};    

#endif  /* _SO_JACK_MANIP_ */

