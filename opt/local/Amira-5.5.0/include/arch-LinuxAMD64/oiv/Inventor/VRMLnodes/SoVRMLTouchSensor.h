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


#ifndef  _SO_VRMLTOUCHSENSOR_
#define  _SO_VRMLTOUCHSENSOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoHandleEventAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLTouchSensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Detects when the user has pointed at a specific piece of geometry.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   A SoVRMLTouchSensor tracks the location and state of the pointing device and
 *   detects when the user points at geometry contained by the SoVRMLTouchSensor's
 *   parent group. This sensor can be enabled or disabled by sending it an
 *   #enabled event with a value of TRUE or FALSE. If the SoVRMLTouchSensor is
 *   disabled, it does not track user input or send output events.
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
 *   A SoVRMLTouchSensor tracks the location and state of the pointing device and
 *   detects when the user points at geometry contained by the SoVRMLTouchSensor's
 *   parent group. This sensor can be enabled or disabled by sending it an
 *   #enabled event with a value of TRUE or FALSE. If the SoVRMLTouchSensor is
 *   disabled, it does not track user input or send output events.
 *   
 *   The SoVRMLTouchSensor generates events as the pointing device "passes over" any
 *   geometry nodes that are descendants of the SoVRMLTouchSensor's parent group.
 *   Typically, the pointing device is a 2D device such as a mouse. In this case, the
 *   pointing device is considered to be moving within a plane a fixed distance from
 *   the viewer and perpendicular to the line of sight; this establishes a set of 3D
 *   coordinates for the pointer. If a 3D pointer is in use, then the
 *   SoVRMLTouchSensor generates events only when the pointer is within the user's
 *   field of view. In either case, the pointing device is considered to "pass over"
 *   geometry when that geometry is intersected by a line extending from the viewer
 *   and passing through the pointer's 3D coordinates. If multiple surfaces intersect
 *   this line (hereafter called the bearing), only the nearest will be eligible to
 *   generate events. 
 *   
 *   The #isOver eventOut reflects the state of the pointing device with regard
 *   to whether it is over the SoVRMLTouchSensor's geometry or not. When the pointing
 *   device changes state from a position such that its bearing does not intersect
 *   any of the SoVRMLTouchSensor's geometry to one in which it does intersect
 *   geometry, an #isOver TRUE event is generated. When the pointing device
 *   moves from a position such that its bearing intersects geometry to one in which
 *   it no longer intersects the geometry, or some other geometry is obstructing the
 *   SoVRMLTouchSensor's geometry, an #isOver FALSE event is generated. These
 *   events are generated only when the pointing device has moved and changed `over
 *   state; events are not generated if the geometry itself is animating and moving
 *   underneath the pointing device.
 *   
 *   As the user moves the bearing over the SoVRMLTouchSensor's geometry, the point of
 *   intersection (if any) between the bearing and the geometry is determined. Each
 *   movement of the pointing device, while #isOver is TRUE, generates
 *   #hitPoint_changed, #hitNormal_changed, and
 *   #hitTexCoord_changed events. #hitPoint_changed events contain the 3D
 *   point on the surface of the underlying geometry, given in the
 *   SoVRMLTouchSensor's coordinate system. #hitNormal_changed events contain
 *   the surface normal vector at the hitPoint. #hitTexCoord_changed events
 *   contain the texture coordinates of that surface at the hitPoint, which can be
 *   used to support the 3D equivalent of an image map.
 *   
 *   If #isOver is TRUE, the user may activate the pointing device to cause the
 *   SoVRMLTouchSensor to generate #isActive events (e.g. press the primary
 *   mouse button). When the SoVRMLTouchSensor generates an #isActive TRUE
 *   event, it grabs all further motion events from the pointing device until it
 *   releases and generates an #isActive FALSE event (other pointing device
 *   sensors will not generate events during this time). Motion of the pointing
 *   device while #isActive is TRUE is referred to as a "drag". If a 2D
 *   pointing device is in use, #isActive events will typically reflect the
 *   state of the primary button associated with the device (i.e., #isActive is
 *   TRUE when the primary button is pressed, and FALSE when not released). If a 3D
 *   pointing device is in use, #isActive events will typically reflect whether
 *   the pointer is within or in contact with the SoVRMLTouchSensor's geometry. 
 *   
 *   The eventOut field #touchTime is generated when all three of the following
 *   conditions are true: 
 *   
 *   - the pointing device was over the geometry when it was initially activated
 *   (#isActive is TRUE), 
 *   
 *   - the pointing device is currently over the geometry (#isOver is TRUE), 
 *   
 *   - and, the pointing device is deactivated (#isActive FALSE event is also
 *   generated). 
 *   
 *   See "Concepts - Pointing Device Sensors" for more details.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLTouchSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR enabled       @TD TRUE
 *       @TR description   @TD ""
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_enabled
 *       @TR   SoSFBool   @TD   set_description
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT 
 *       @TR   SoSFString  @TD  description_changed
 *       @TR   SoSFBool    @TD  enabled_changed      
 *       @TR   SoSFVec3f   @TD  hitNormal_changed      
 *       @TR   SoSFVec3f   @TD  hitPoint_changed      
 *       @TR   SoSFVec2f   @TD  hitTexCoord_changed      
 *       @TR   SoSFBool    @TD  isActive      
 *       @TR   SoSFBool    @TD  isOver  @NI      
 *       @TR   SoSFTime    @TD  touchTime
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLTouchSensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLTouchSensor);

 public:
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * String that describes the sensor.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoSFString          description;
    
  /**
   * Constructor.
   */
  SoVRMLTouchSensor();
   
  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;
  
  /**
   * Enables/disables events for @I all @i SoVRMLTouchSensor objects. If you have
   * created several objects of this class, you can disable/enable events for all of
   * them with a single call to this method. 
   */
  static void enableEvents(SbBool OnOffFlag);
  /**
   * Queries if events are enabled for all objects of this class.
   */
  static SbBool isEventsEnabled();

 SoEXTENDER public:
  // Implement actions:
  // Override handleEvent to look for left-mouse clicks, to do a pick:
  virtual void        handleEvent(SoHandleEventAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // EventOuts
  SoSFVec3f           hitNormal_changed;   // Sent when cursor on shape
  SoSFVec3f           hitPoint_changed;    // Sent when cursor on shape
  SoSFVec2f           hitTexCoord_changed; // Sent when cursor on shape
  SoSFBool            isActive;            // Sent on button press/release
  SoSFBool            isOver;              // Sent when cursor on shape
  SoSFTime            touchTime;           // Sent on button release
 protected:
  virtual ~SoVRMLTouchSensor();
   
  // Override to detect changes to fields
  virtual void notify(SoNotList *list);
   
  // Test if geometry has been picked *and* it's geometry that belongs to us
  SbBool pickedOurGeometry(SoHandleEventAction *action);
   
  // Internal instance specific data
  SbBool     m_isEnabled;     // Currently enabled?
  SbBool     m_isActive;      // Is mouse button down?
  SbBool     m_isOver;        // Is cursor on geometry we own?
   
  static SbBool enableEventsFlag;
   
 private:
  // Save ptr to HandleEventAction while we are "grabbing" events
  SoHandleEventAction *m_action;
};

#endif /* _SO_VRMLTOUCHSENSOR_ */

