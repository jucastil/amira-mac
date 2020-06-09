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



#ifndef  _SO_VRMLPLANESENSOR_
#define  _SO_VRMLPLANESENSOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFVec2f.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/SbViewportRegion.h> 
#include <Inventor/fields/SoSFString.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>
class SbPlaneProjector;
class SoGetMatrixAction;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPlaneSensor
//
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Maps pointing device motion onto a plane.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLPlaneSensor maps pointing device (e.g. mouse or wand) motion into
 *   translation in two dimensions, in the XY plane of its local space.
 *   SoVRMLPlaneSensor uses the descendant geometry of its parent node to determine
 *   if a hit occurs.
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
 *   The SoVRMLPlaneSensor maps pointing device (e.g. mouse or wand) motion into
 *   translation in two dimensions, in the XY plane of its local space.
 *   SoVRMLPlaneSensor uses the descendant geometry of its parent node to determine
 *   if a hit occurs.
 *   
 *   The #enabled exposed field enables and disables the SoVRMLPlaneSensor - if
 *   TRUE, the sensor reacts appropriately to user events, if FALSE, the sensor does
 *   not track user input or send output events. If #enabled receives a FALSE
 *   event and #isActive is TRUE, the sensor becomes disabled and deactivated,
 *   and outputs an #isActive FALSE event. If #enabled receives a TRUE,
 *   event the sensor is enabled and ready for user activation.
 *   
 *   The SoVRMLPlaneSensor generates events if the pointing device is activated while
 *   over any descendant geometry nodes of its parent group and then moved while
 *   activated. Typically, the pointing device is a 2D device such as a mouse. The
 *   pointing device is considered to be moving within a plane at a fixed distance
 *   from the viewer and perpendicular to the line of sight; this establishes a set
 *   of 3D coordinates for the pointer. If a 3D pointer is in use, then the sensor
 *   generates events only when the pointer is within the user's field of view. In
 *   either case, the pointing device is considered to "pass over" geometry when that
 *   geometry is intersected by a line extending from the viewer and passing through
 *   the pointer's 3D coordinates. If multiple sensors' geometry intersect this line
 *   (hereafter called the bearing), only the nearest will be eligible to generate
 *   events.
 *   
 *   Upon activation of the pointing device (e.g. mouse button down) over the sensor's
 *   geometry, an #isActive TRUE event is sent. Dragging motion is mapped into
 *   a relative translation in the XY plane of the sensor's local coordinate system
 *   as it was defined at the time of activation. For each subsequent position of the
 *   bearing, a #translation_changed event is output which corresponds to a
 *   relative translation from the original intersection point projected onto the XY
 *   plane, plus the #offset value. The sign of the translation is defined by
 *   the XY plane of the sensor's coordinate system. #trackPoint_changed events
 *   reflect the unclamped drag position on the surface of this plane. When the
 *   pointing device is deactivated and #autoOffset is TRUE, #offset is
 *   set to the last translation value and an @B offset_changed @b event is
 *   generated. See "Concepts - Drag Sensors" for more details.
 *   
 *   When the sensor generates an #isActive TRUE event, it grabs all further
 *   motion events from the pointing device until it releases and generates an
 *   #isActive FALSE event (other pointing device sensors cannot generate
 *   events during this time). Motion of the pointing device while #isActive is
 *   TRUE is referred to as a "drag". If a 2D pointing device is in use,
 *   #isActive events will typically reflect the state of the primary button
 *   associated with the device (i.e., #isActive is TRUE when the primary button
 *   is pressed, and FALSE when not released). If a 3D pointing device (e.g. wand) is
 *   in use, #isActive events will typically reflect whether the pointer is
 *   within or in contact with the sensor's geometry. 
 *   
 *   #minPosition and #maxPosition may be set to clamp @B translation @b
 *   events to a range of values as measured from the origin of the XY plane. If the
 *   X or Y component of #minPosition is greater than the corresponding
 *   component of #maxPosition, #translation_changed events are not
 *   clamped in that dimension. If the X or Y component of #minPosition is
 *   equal to the corresponding component of #maxPosition, that component is
 *   constrained to the given value; this technique provides a way to implement a
 *   line sensor that maps dragging motion into a translation in one dimension. 
 *   
 *   While the pointing device is activated, #trackPoint_changed and
 *   #translation_changed events are output. #trackPoint_changed events
 *   represent the unclamped intersection points on the surface of the local XY
 *   plane. If the pointing device is dragged off of the XY plane while activated
 *   (e.g. above horizon line), browsers may interpret this in several ways (e.g.
 *   clamp all values to the horizon). Each movement of the pointing device, while
 *   #isActive is TRUE, generates #trackPoint_changed and
 *   #translation_changed events.
 *   
 *   See "Concepts - Pointing Device Sensors and Drag Sensors" for more details.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPlaneSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR autoOffset    @TD TRUE
 *       @TR enabled       @TD TRUE
 *       @TR maxPosition   @TD -1 -1
 *       @TR minPosition   @TD 0 0
 *       @TR offset        @TD 0 0 0
 *       @TR description   @TD ""
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_autoOffset      
 *       @TR   SoSFBool   @TD   set_enabled      
 *       @TR   SoSFVec2f   @TD   set_maxPosition      
 *       @TR   SoSFVec2f   @TD   set_minPosition      
 *       @TR   SoSFVec3f   @TD   set_offset
 *       @TR   SoSFString  @TD   set_description
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isActive  
 *       @TR   SoSFBool   @TD   isOver @NI      
 *       @TR   SoSFVec3f   @TD   trackPoint_changed      
 *       @TR   SoSFVec3f   @TD   translation_changed      
 *       @TR   SoSFBool   @TD   autoOffset_changed      
 *       @TR   SoSFBool   @TD   enabled_changed      
 *       @TR   SoSFVec2f   @TD   maxPosition_changed      
 *       @TR   SoSFVec2f   @TD   minPosition_changed      
 *       @TR   SoSFVec3f   @TD   offset_changed
 *       @TR   SoSFString  @TD   description_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLPlaneSensor : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLPlaneSensor);

 public:
  // Fields

  /**
   * Used to clamp translation events to a range of values as measured from the
   * origin of the XY plane.
   * 
   */
  SoSFVec2f           minPosition;
    /**
   * Used to clamp translation events to a range of values as measured from the
   * origin of the XY plane.
   * 
   */
  SoSFVec2f           maxPosition;
  /**
   * Enables (TRUE) or disables (FALSE) the sensor.
   * 
   */
  SoSFBool            enabled;
  /**
   * Amount to add to the translation event value.
   * 
   */
  SoSFVec3f           offset;
  /**
   * Specifies whether to set #offset to the last rotation angle (TRUE).
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
  SoSFString          description;
  /**
   * Constructor.
   */
  SoVRMLPlaneSensor();

  // Overrides default method on SoNode
  virtual SbBool      affectsState() const;

  /**
   * Enables/disables events for @I all @i SoVRMLPlaneSensor objects. If you have
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

  SB_THREAD_TLS_HEADER();
  
  SoSFBool            isActive;             // eventOut
  SoSFBool            isOver;               // eventOut
  SoSFVec3f           trackPoint_changed;   // eventOut
  SoSFVec3f           translation_changed;  // eventOut

 protected:
  virtual ~SoVRMLPlaneSensor();
 
  SbPlaneProjector *planeProj; // projector for planar scaling

  // Override to detect changes to fields
  virtual void notify(SoNotList *list);

  // Test if geometry has been picked *and* it's geometry that belongs to us
  SbBool pickedOurGeometry(SoHandleEventAction *action);

  // Internal instance specific data
  SbBool     m_isEnabled;     // Currently enabled?
  SbBool     m_isActive;      // Is mouse button down?
  SbVec3f    m_hitPoint;

  static SbBool enableEventsFlag;

 private:
  // Save ptr to HandleEventAction while we are "grabbing" events
  SoHandleEventAction *m_action;
  float m_hitz;
  float m_minx, m_miny, m_maxx, m_maxy;
  float m_tranx, m_trany;
  SbMatrix worldToLocal, localToWorld;
  SbVec3f newWorldPt, m_localHitPt;
  SbViewportRegion  viewport;

  struct MTstruct {
    SoGetMatrixAction *matrixAction;
  };
};

#endif /* _SO_VRMLPLANESENSOR_ */

