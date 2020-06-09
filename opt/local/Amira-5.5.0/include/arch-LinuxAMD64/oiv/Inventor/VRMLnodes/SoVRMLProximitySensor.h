/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Mike Heck (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLPROXSENSOR_
#define  _SO_VRMLPROXSENSOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbBox.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLProximitySensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Generates events when the user moves into, out of, or within a specified region
 * of space.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLProximitySensor generates events when the user enters, exits, and
 *   moves within a region in space (defined by a box).
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
 *   The SoVRMLProximitySensor generates events when the user enters, exits, and moves
 *   within a region in space (defined by a box). A proximity sensor can be enabled
 *   or disabled by sending it an #enabled event with a value of TRUE or FALSE
 *   - a disabled sensor does not send output events.
 *   
 *   An SoVRMLProximitySensor generates #isActive TRUE/FALSE events as the
 *   viewer enters and exits the rectangular box defined by its #center and
 *   #size fields. Browsers must interpolate user positions and timestamp the
 *   #isActive events with the exact time the user first intersected the
 *   proximity region. The #center field defines the center point of the
 *   proximity region in object space, and the #size field specifies a vector
 *   which defines the width (x), height (y), and depth (z) of the box bounding the
 *   region. SoVRMLProximitySensor nodes are affected by the hierarchical
 *   transformations of its parents.
 *   
 *   The #enterTime event is generated whenever the #isActive TRUE event
 *   is generated (user enters the box), and #exitTime events are generated
 *   whenever #isActive FALSE event is generated (user exits the box). 
 *   
 *   The #position_changed and #orientation_changed events send events
 *   whenever the position and orientation of the viewer changes with respect to the
 *   SoVRMLProximitySensor's coordinate system - this includes enter and exit times.
 *   Note that the user movement may be as a result of a variety of circumstances
 *   (e.g. browser navigation, proximity sensor's coordinate system changes, bound
 *   Viewpoint's position or orientation changes, or the SoVRMLProximitySensor's
 *   coordinate system changes).
 *   
 *   Each SoVRMLProximitySensor behaves independently of all other
 *   SoVRMLProximitySensors - every enabled SoVRMLProximitySensor that is affected by
 *   the user's movement receives and sends events, possibly resulting in multiple
 *   SoVRMLProximitySensors receiving and sending events simultaneously. Unlike
 *   SoVRMLTouchSensors, there is no notion of an SoVRMLProximitySensor lower in the
 *   scene graph "grabbing" events.
 *   
 *   Instanced (DEF/USE) SoVRMLProximitySensors use the union of all the boxes to
 *   check for enter and exit - an instanced SoVRMLProximitySensor will detect enter
 *   and exit for all instances of the box and send output events appropriately.
 *   
 *   An SoVRMLProximitySensor that surrounds the entire world will have an enterTime
 *   equal to the time that the world was entered and can be used to start up
 *   animations or behaviors as soon as a world is loaded. A SoVRMLProximitySensor
 *   with a (0 0 0) #size field cannot generate events - this is equivalent to
 *   setting the #enabled field to FALSE.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLProximitySensor {
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
 *       @TR   SoSFBool   @TD   isActive      
 *       @TR   SoSFVec3f   @TD   position_changed      
 *       @TR   SoSFRotation   @TD   orientation_changed 
 *       @TR   SoSFVec3f   @TD   centerOfRotation_changed @NI 
 *       @TR   SoSFTime   @TD   enterTime      
 *       @TR   SoSFTime   @TD   exitTime      
 *       @TR   SoSFVec3f   @TD   center_changed      
 *       @TR   SoSFBool   @TD   enabled_changed      
 *       @TR   SoSFVec3f   @TD   size_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLProximitySensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLProximitySensor);

 public:
  // ExposedFields
  SoSFVec3f           center;  // Center for computation
  /**
   * Define the rectangular box within which isActive event is generated.
   * 
   */
  SoSFVec3f           size;
  /**
   * Enable (TRUE) or disable (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;

  /**
   * Constructor.
   */
  SoVRMLProximitySensor();

  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

  /**
   * Enables/disables events for @I all @i SoVRMLProximitySensor objects. If you
   * have created several objects of this class, you can disable/enable events for
   * all of them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);
  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:
  // Implement actions:
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        rayPick(SoRayPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

 SoINTERNAL public:
  // EventOuts
  SoSFBool            isActive;                    // Sent when viewer enters/leaves
  SoSFVec3f           position_changed;            // Sent when viewer moves
  SoSFRotation        orientation_changed;         // Sent when viewer turns
  SoSFVec3f           centerOfRotation_changed;    // Sent when centerOfRotation changes
  SoSFTime            enterTime;                   // Sent when viewer enters
  SoSFTime            exitTime;                    // Sent when viewer leaves

  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLProximitySensor();

  // Override to detect changes to fields
  virtual void notify(SoNotList *list);

  // Internal utility function
  virtual void updateState(SbVec3f &viewerPos, 
                           SbRotation &viewerOri, 
                           SbBool isInside);

  static SbBool enableEventsFlag;

  // Internal instance specific data
  SbBox3f        m_BBox;          // Bounding box
  SbBool         m_isEnabled;     // Currently enabled?
  SbBool         m_isActive;      // Is viewer currently inside box?
  SbVec3f        m_viewerPos;     // Last viewer position
  SbRotation     m_viewerOri;     // Last viewer orientation
  SbMatrix       m_modelMtx;      // Last model matrix
  SbMatrix       m_invMtx;        // Last model matrix inverse
};

#endif /* _SO_VRMLPROXSENSOR_ */

