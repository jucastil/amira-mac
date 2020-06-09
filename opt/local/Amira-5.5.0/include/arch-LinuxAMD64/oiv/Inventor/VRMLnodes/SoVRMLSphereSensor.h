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



#ifndef  _SO_VRMLSPHERESENSOR_
#define  _SO_VRMLSPHERESENSOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLSphereSensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Maps pointing device motion onto a sphere.\ @NO_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLSphereSensor maps pointing device (e.g. mouse or wand) motion into
 *   spherical rotation about the center of its local space. 
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
 *   The SoVRMLSphereSensor maps pointing device (e.g. mouse or wand) motion into
 *   spherical rotation about the center of its local space. SoVRMLSphereSensor uses
 *   the descendant geometry of its parent node to determine if a hit occurs. The
 *   feel of the rotation is as if you were rolling a ball.
 *   
 *   The #enabled exposed field enables and disables the SoVRMLSphereSensor - if
 *   TRUE, the sensor reacts appropriately to user events, if FALSE, the sensor does
 *   not track user input or send output events. If #enabled receives a FALSE
 *   event and @B isActive @b is TRUE, the sensor becomes disabled and deactivated,
 *   and outputs an @B isActive @b FALSE event. If #enabled receives a TRUE
 *   event the sensor is enabled and ready for user activation.
 *   
 *   The SoVRMLSphereSensor generates events if the pointing device is activated while
 *   over any descendant geometry nodes of its parent group and then moved while
 *   activated. Typically, the pointing device is a 2D device such as a mouse. The
 *   pointing device is considered to be moving within a plane at a fixed distance
 *   from the viewer and perpendicular to the line of sight; this establishes a set
 *   of 3D coordinates for the pointer. If a 3D pointer is in use, then the sensor
 *   generates events only when the pointer is within the user's field of view. In
 *   either case, the pointing device is considered to "pass over" geometry when that
 *   geometry is intersected by a line extending from the viewer and passing through
 *   the pointer's 3D coordinates. If multiple sensors' geometries intersect this
 *   line (hereafter called the bearing), only the nearest will be eligible to
 *   generate events. 
 *   
 *   Upon activation of the pointing device (e.g. mouse button down) over the sensor's
 *   geometry an @B isActive @b TRUE event is sent. The vector defined by the
 *   initial point of intersection on the SoVRMLSphereSensor's geometry and the local
 *   origin determines the radius of the sphere used to map subsequent pointing
 *   device motion while dragging. The virtual sphere defined by this radius and the
 *   local origin at the time of activation are used to interpret subsequent pointing
 *   device motion and is not affected by any changes to the sensor's coordinate
 *   system while the sensor is active. For each position of the bearing, a
 *   @B rotation_changed @b event is output which corresponds to a relative rotation
 *   from the original intersection, plus the #offset value. The sign of the
 *   rotation is defined by the local coordinate system of the sensor.
 *   @B trackPoint_changed @b events reflect the unclamped drag position on the
 *   surface of this sphere. When the pointing device is deactivated and
 *   #autoOffset is TRUE, #offset is set to the last rotation value and
 *   an @B offset_changed @b event is generated. See "Concepts - Drag Sensors" for
 *   more details.
 *   
 *   When the sensor generates an @B isActive @b TRUE event, it grabs all further
 *   motion events from the pointing device until it releases and generates an
 *   @B isActive @b FALSE event (other pointing device sensors cannot generate
 *   events during this time). Motion of the pointing device while @B isActive @b is
 *   TRUE is referred to as a "drag". If a 2D pointing device is in use,
 *   @B isActive @b events will typically reflect the state of the primary button
 *   associated with the device (i.e., @B isActive @b is TRUE when the primary button
 *   is pressed and FALSE when released). If a 3D pointing device (e.g. wand) is in
 *   use, @B isActive @b events will typically reflect whether the pointer is within
 *   or in contact with the sensor's geometry. 
 *   
 *   While the pointing device is activated, @B trackPoint_changed @b and
 *   @B rotation_changed @b events are output. @B trackPoint_changed @b events
 *   represent the unclamped intersection points on the surface of the invisible
 *   sphere. If the pointing device is dragged off the sphere while activated,
 *   browsers may interpret this in several ways (e.g. clamp all values to the
 *   sphere, continue to rotate as the point is dragged away from the sphere, etc.).
 *   Each movement of the pointing device, while @B isActive @b is TRUE, generates
 *   @B trackPoint_changed @b and @B rotation_changed @b events.
 *   
 *   See "Concepts - Pointing Device Sensors and Drag Sensors" for more details.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLSphereSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR autoOffset   @TD TRUE
 *       @TR enabled      @TD TRUE
 *       @TR offset       @TD 0 1 0 0
 *       @TR description  @TD ""
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_autoOffset      
 *       @TR   SoSFBool   @TD   set_enabled      
 *       @TR   SoSFRotation   @TD   set_offset
 *       @TR   SoSFString  @TD   set_description
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isActive 
 *       @TR   SoSFBool   @TD   isOver      
 *       @TR   SoSFRotation   @TD   rotation_changed      
 *       @TR   SoSFVec3f   @TD   trackPoint_changed      
 *       @TR   SoSFBool   @TD   autoOffset_changed      
 *       @TR   SoSFBool   @TD   enabled_changed      
 *       @TR   SoSFRotation   @TD   offset_changed
 *       @TR   SoSFString  @TD   description_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLSphereSensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLSphereSensor);

 public:
  // Fields

  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * Amount to add to the rotation value.
   * 
   */
  SoSFRotation        offset;
  /**
   * Specifies whether to set #offset to the last rotation value (TRUE).
   * 
   */
  SoSFBool            autoOffset;
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
  SoSFString            description;
  /**
   * Constructor.
   */
  SoVRMLSphereSensor();

  /**
   * Enables/disables events for @I all @i SoVRMLSphereSensor objects. If you have
   * created several objects of this class, you can disable/enable events for all of
   * them with a single call to this method. 
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

  SoSFBool            isActive;            // eventOut
  SoSFBool            isOver;              // eventOut
  SoSFRotation        rotation_changed;    // eventOut
  SoSFVec3f           trackPoint_changed;  // eventOut
 protected:

  static SbBool       enableEventsFlag;
  virtual ~SoVRMLSphereSensor();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLSPHERESENSOR_ */

