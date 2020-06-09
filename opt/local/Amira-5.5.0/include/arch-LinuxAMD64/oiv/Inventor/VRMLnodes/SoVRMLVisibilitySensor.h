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



#ifndef  _SO_VRMLVISIBILITYSENSOR_
#define  _SO_VRMLVISIBILITYSENSOR_

#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLVisibilitySensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Detects visibility changes of a rectangular box.\ @NO_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLVisibilitySensor detects visibility changes of a rectangular box as
 *   the user navigates the world. SoVRMLVisibilitySensor is typically used to detect
 *   when the user can see a specific object or region in the scene, and to activate
 *   or deactivate some behavior or animation in order to attract the user or improve
 *   performance.
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
 *   The SoVRMLVisibilitySensor detects visibility changes of a rectangular box as the
 *   user navigates the world. SoVRMLVisibilitySensor is typically used to detect
 *   when the user can see a specific object or region in the scene, and to activate
 *   or deactivate some behavior or animation in order to attract the user or improve
 *   performance.
 *   
 *   The #enabled field enables and disables the SoVRMLVisibilitySensor. If
 *   #enabled is set to FALSE, the SoVRMLVisibilitySensor does not send output
 *   events. If #enabled is TRUE, then the SoVRMLVisibilitySensor detects
 *   changes to the visibility status of the box specified and sends events through
 *   the @B isActive @b eventOut. A TRUE event is output to @B isActive @b when any
 *   portion of the box impacts the rendered view, and a FALSE event is sent when the
 *   box has no effect on the view. Browsers must guarantee that if @B isActive @b
 *   is FALSE that the box has absolutely no effect on the rendered view - browsers
 *   may error liberally when @B isActive @b is TRUE (e.g. maybe it does affect the
 *   rendering).
 *   
 *   The exposed fields #center and #size specify the object space
 *   location of the box center and the extents of the box (i.e., width, height, and
 *   depth). The SoVRMLVisibilitySensor's box is affected by hierarchical
 *   transformations of its parents.
 *   
 *   The @B enterTime @b event is generated whenever the @B isActive @b TRUE event
 *   is generated, and @B exitTime @b events are generated whenever @B isActive @b
 *   FALSE events are generated.
 *   
 *   Each SoVRMLVisibilitySensor behaves independently of all other
 *   SoVRMLVisibilitySensors - every enabled SoVRMLVisibilitySensor that is affected
 *   by the user's movement receives and sends events, possibly resulting in multiple
 *   SoVRMLVisibilitySensors receiving and sending events simultaneously. Unlike
 *   SoVRMLTouchSensors, there is no notion of an SoVRMLVisibilitySensor lower in the
 *   scene graph "grabbing" events. Instanced (DEF/USE) SoVRMLVisibilitySensors use
 *   the union of all the boxes defined by their instances to check for enter and
 *   exit - an instanced SoVRMLVisibilitySensor will detect enter, motion, and exit
 *   for all instances of the box and send output events appropriately.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLVisibilitySensor {
 *    @TABLE_FILE_FORMAT
 *       @TR center    @TD 0 0 0
 *       @TR enabled   @TD TRUE
 *       @TR size      @TD 0 0 0
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFVec3f   @TD   set_center      
 *       @TR   SoSFBool   @TD   set_enabled      
 *       @TR   SoSFVec3f   @TD   set_size
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   enterTime      
 *       @TR   SoSFTime   @TD   exitTime      
 *       @TR   SoSFBool   @TD   isActive      
 *       @TR   SoSFVec3f   @TD   center_changed      
 *       @TR   SoSFBool   @TD   enabled_changed      
 *       @TR   SoSFVec3f   @TD   size_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLVisibilitySensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLVisibilitySensor);

 public:
  // Fields

  /**
   * Object space location of the box center.
   * 
   */
  SoSFVec3f          center; 
  /**
   * Width, height, and depth of the box.
   * 
   */
  SoSFVec3f          size; 
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool           enabled;

  /**
   * Constructor.
   */
  SoVRMLVisibilitySensor();

  /**
   * Enables/disables events for @I all @i SoVRMLVisibilitySensor objects. If you
   * have created several objects of this class, you can disable/enable events for
   * all of them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);
  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoSFTime           enterTime;         // eventOut
  SoSFTime           exitTime;          // eventOut
  SoSFBool           isActive;          // eventOut
  static SbBool      enableEventsFlag;
  virtual ~SoVRMLVisibilitySensor();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLVISIBILITYSENSOR_ */

