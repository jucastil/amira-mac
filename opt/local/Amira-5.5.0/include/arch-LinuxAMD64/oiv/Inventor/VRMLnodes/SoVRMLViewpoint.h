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



#ifndef  _SO_VRMLVIEWPOINT_
#define  _SO_VRMLVIEWPOINT_

#include <Inventor/fields/SoSFTime.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLViewpoint
//
//  Specifies position from which the user might view the scene 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Specifies position from which the user might view the scene.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLViewpoint node defines a specific location in a local coordinate
 *   system from which the user might view the scene.
 *   
 *   Note: The binding behavior and associated eventIns and eventOuts are not
 *   implemented. 
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
 *   The SoVRMLViewpoint node defines a specific location in a local coordinate system
 *   from which the user might view the scene. SoVRMLViewpoints are bindable children
 *   nodes and thus there exists an SoVRMLViewpoint stack in the browser in which the
 *   top-most SoVRMLViewpoint on the stack is the currently active SoVRMLViewpoint.
 *   If a TRUE value is sent to the @B set_bind @b eventIn of an SoVRMLViewpoint, it
 *   is moved to the top of the SoVRMLViewpoint stack and thus activated. When an
 *   SoVRMLViewpoint is at the top of the stack, the user's view is conceptually
 *   reparented as a child of the SoVRMLViewpoint. All subsequent changes to the
 *   SoVRMLViewpoint's coordinate system change the user's view (e.g. changes to any
 *   parent transformation nodes or to the SoVRMLViewpoint's position or orientation
 *   fields). Sending a @B set_bind @b FALSE event removes the SoVRMLViewpoint from
 *   the stack and results in @B isBound @b FALSE and @B bindTime @b events. If the
 *   popped SoVRMLViewpoint is at the top of the viewpoint stack the user's view is
 *   reparented to the next entry in the stack. See "Concepts - Bindable Children
 *   Nodes" for more details on the the binding stacks. When an SoVRMLViewpoint is
 *   moved to the top of the stack, the existing top of stack Viewpoint sends an
 *   @B isBound @b FALSE event and is pushed onto the stack.
 *   
 *   SoVRMLViewpoints have the additional requirement from other binding nodes in that
 *   they store the relative transformation from the user view to the current
 *   SoVRMLViewpoint when they are moved to the top of stack. This is needed by the
 *   #jump field, described below.
 *   
 *   An author can automatically move the user's view through the world by binding the
 *   user to an SoVRMLViewpoint and then animating either the SoVRMLViewpoint or the
 *   transformations above it. Browsers must allow the user view to be navigated
 *   relative to the coordinate system defined by the SoVRMLViewpoint (and the
 *   transformations above it), even if the SoVRMLViewpoint or its parent
 *   transformations are being animated.
 *   
 *   The @B bindTime @b eventOut sends the time at which the SoVRMLViewpoint is bound
 *   or unbound. This can happen during loading, when a @B set_bind @b event is sent
 *   to the SoVRMLViewpoint, or when the browser binds to the SoVRMLViewpoint via its
 *   user interface (see below).
 *   
 *   The #position and #orientation fields of the SoVRMLViewpoint node
 *   specify relative locations in the local coordinate system. @B Position @b is
 *   relative to the coordinate system's origin (0,0,0), while #orientation
 *   specifies a rotation relative to the default orientation; the default
 *   orientation has the user looking down the -Z axis with +X to the right and +Y
 *   straight up. SoVRMLViewpoints are affected by the transformation hierarchy.
 *   
 *   Navigation types (see SoVRMLNavigationInfo) that require a definition of a
 *   @I down @i vector (e.g. terrain following) will use the negative Y-axis of the
 *   coordinate system of the currently bound SoVRMLViewpoint. Likewise navigation
 *   types (see SoVRMLNavigationInfo) that require a definition of an @B up @b
 *   vector will use the positive Y-axis of the coordinate system of the currently
 *   bound SoVRMLViewpoint. Note that the #orientation field of the
 *   SoVRMLViewpoint does not affect the definition of the down or up vectors. This
 *   allows the author to separate the viewing direction from the gravity
 *   direction.
 *   
 *   The #jump field specifies whether the user's view `jumps' (or animates) to
 *   the position and orientation of a bound SoVRMLViewpoint. Regardless of the value
 *   of #jump at bind time, the relative viewing transformation between the
 *   user's view and the current SoVRMLViewpoint will be stored with the current
 *   SoVRMLViewpoint for later use when @I un-jumping @i. The following is a
 *   re-write of the general bind stack rules described in "Concepts - Bindable Child
 *   Nodes, Bind Stack Behavior" with additional rules regarding Viewpoints (in
 *   @B bold @b):
 *   
 *   -# During read: 
 *     - the first encountered  SoVRMLViewpoint is bound by pushing it
 *       to the top of the SoVRMLViewpoint stack, 
 *        - nodes contained within SoVRMLInline are not candidates for the first
 *          encountered SoVRMLViewpoint,
 *        - the first node within a prototype is a valid candidate for the
 *          first encountered  SoVRMLViewpoint
 *     - the first encountered SoVRMLViewpoint sends an @B isBound @b TRUE event. 
 *   -# When a @B @I set_bind @i @b TRUE eventIn is received by an SoVRMLViewpoint:
 *     - if it is not on the top of the stack: 
 *       - the relative transformation from the current top of stack SoVRMLViewpoint to
 *         the user's view is stored with the current top of stack SoVRMLViewpoint, 
 *       - the current top of stack node sends an @B isBound @b eventOut FALSE, 
 *       - the new node is moved to the top of the stack and becomes the currently bound
 *         SoVRMLViewpoint, 
 *       - the new SoVRMLViewpoint (top of stack) sends an @B isBound @b TRUE eventOut,
 *       - if @B @I jump @i @b is TRUE for the new SoVRMLViewpoint, then the
 *         user's view is `jumped' (or animated) to match the values in the
 *         #position and #orientation fields of the new
 *         SoVRMLViewpoint; 
 *     - else if the node is already at the top of the stack, then this event has no
 *       effect. 
 *   -# When a @B set_bind @b FALSE eventIn is received by an SoVRMLViewpoint: 
 *     - it is removed from the stack, 
 *     - if it is on the top of the stack: 
 *       - it sends an @B isBound @b eventOut FALSE, 
 *       - the next node in the stack becomes the currently bound SoVRMLViewpoint (i.e.,
 *         pop) and issues an @B isBound @b TRUE eventOut, 
 *       - if its @B @I jump @i @b is TRUE the user's view is 'jumped' (or
 *         animated) to the  #position and  #orientation
 *         of the next SoVRMLViewpoint in the stack with the stored relative
 *         transformation for with this next SoVRMLViewpoint applied, 
 *   -# If a @B set_bind @b FALSE eventIn is received by a node not in the stack, the
 *      event is ignored and @B isBound @b events are not sent. 
 *   -# When a node replaces another node at the top of the stack, the @B isBound @b
 *      TRUE and FALSE eventOuts from the two nodes are sent simultaneously (i.e.,
 *      identical timestamps). 
 *   -# If a bound node is deleted then it behaves as if it received a @B set_bind
 *      @b FALSE event (see #3). 
 *   
 *   Note that the #jump field may change after an SoVRMLViewpoint is bound -
 *   the rules described above still apply. If #jump was TRUE when the
 *   SoVRMLViewpoint is bound, but changed to FALSE before the @B set_bind @b FALSE
 *   is sent, then the SoVRMLViewpoint does not @I un-jump @i during unbind. If
 *   #jump was FALSE when the SoVRMLViewpoint is bound, but changed to TRUE
 *   before the @B set_bind @b FALSE is sent, then the SoVRMLViewpoint does perform
 *   the @I un-jump @i during unbind.
 *   
 *   The #fieldOfView field specifies a preferred field of view from this
 *   viewpoint, in radians. A small field of view roughly corresponds to a telephoto
 *   lens; a large field of view roughly corresponds to a wide-angle lens. The field
 *   of view should be greater than zero and smaller than pi; the default value
 *   corresponds to a 45 degree field of view. The value of #fieldOfView
 *   represents the maximum viewing angle in any direction axis of the view. For
 *   example, a browser with a rectangular viewing projection will use an angle of
 *   #fieldOfView for the larger direction (depending on aspect ratio) and
 *   #fieldOfView times@I aspect ratio @i in the smaller direction. If the
 *   aspect ratio is 2x1 (i.e., horizontal twice the vertical) and the fieldOfView is
 *   1.0, then the horizontal viewing angle would be 1.0 and the vertical viewing
 *   angle would be 0.5. #fieldOfView is a hint to the browser and may be
 *   ignored.
 *   
 *   The #description field identifies SoVRMLViewpoints that are recommended to
 *   be publicly accessible through the browser's user interface (e.g.
 *   SoVRMLViewpoints menu). The string in the #description field should be
 *   displayed if this functionality is implemented. If #description is empty,
 *   then the SoVRMLViewpoint should not appear in any public user interface. It is
 *   recommended that the browser bind and move to an SoVRMLViewpoint when its
 *   #description is selected, either animating to the new position or jumping
 *   directly there. Once the new position is reached both the @B isBound @b and
 *   @B bindTime @b eventOuts are sent. 
 *   
 *   The URL syntax ".../scene.wrl#ViewpointName" specifies the user's initial view
 *   when entering "scene.wrl" to be the first SoVRMLViewpoint in file "scene.wrl"
 *   that appears as "DEF ViewpointName Viewpoint { ... }" - this overrides the first
 *   SoVRMLViewpoint in the file as the initial user view and receives a
 *   @B set_bind @b TRUE message. If the SoVRMLViewpoint "ViewpointName" is not
 *   found, then assume that no SoVRMLViewpoint was specified and use the first
 *   SoVRMLViewpoint in the file. The URL syntax "#ViewpointName" specifies a view
 *   within the existing file. If this is loaded, then it receives a @B set_bind @b
 *   TRUE message.
 *   
 *   If an SoVRMLViewpoint is bound (@B set_bind @b) and is the child of an
 *   SoVRMLLOD, SoVRMLSwitch, or any node or prototype that disables its children,
 *   then the result is undefined. If an SoVRMLViewpoint is bound that results in
 *   collision with geometry, then the browser performs its self-defined navigation
 *   adjustments as if the user navigated to this point (see SoVRMLCollision).
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    Viewpoint {
 *    @TABLE_FILE_FORMAT
 *       @TR fieldOfView   @TD 0.785398
 *       @TR jump          @TD TRUE
 *       @TR orientation   @TD 0 0 1 0
 *       @TR position      @TD 0 0 10
 *       @TR centerOfRotation @TD 0 0 0
 *       @TR description   @TD ""
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_bind @NI       
 *       @TR   SoSFFloat   @TD   set_fieldOfView      
 *       @TR   SoSFBool   @TD   set_jump  @NI      
 *       @TR   SoSFRotation   @TD   set_orientation      
 *       @TR   SoSFVec3f   @TD   set_position
 *       @TR   SoSFVec3f   @TD   set_centerOfRotation  @NI 
 *       @TR   SoSFString  @TD   set_description
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime   @TD   bindTime @NI       
 *       @TR   SoSFBool   @TD   isBound @NI       
 *       @TR   SoSFFloat   @TD   fieldOfView_changed      
 *       @TR   SoSFBool   @TD   jump_changed @NI       
 *       @TR   SoSFRotation   @TD   orientation_changed      
 *       @TR   SoSFVec3f   @TD   position_changed
 *       @TR   SoSFVec3f   @TD   centerOfRotation_changed @NI  
 *       @TR   SoSFString   @TD   description_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLViewpoint : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLViewpoint);

 public:
  // Fields

  /**
   * Specifies a position relative to the coordinate system's origin (0,0,0).
   * 
   */
  SoSFVec3f           position;

  /**
   * Specifies a rotation relative to the default orientation.
   * 
   */
  SoSFRotation        orientation;

  /**
   * Specifies a preferred field of view from the viewpoint, in radians. A small
   * field of view roughly corresponds to a telephoto lens; a large field of view
   * roughly corresponds to a wide-angle lens. The field of view should be greater
   * than zero and smaller than pi.
   * 
   */
  SoSFFloat           fieldOfView;

  /**
   * Specifies viewpoints that are recommended to be publicly accessible.
   * 
   */
  SoSFString          description;

  /**
   *  @NI Specifies whether the user's view "jumps" to the position and orientation.
   * 
   */
  SoSFBool            jump;

  /**
   *  @NI Specifies a center about which to rotate the users eyepoint
   * when in EXAMINE mode.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when 
   * this node is written to a VRML file, the file will contain
   * this incompatible field and standard VRML97 file readers 
   * will not be able to read it.
   */
   SoSFVec3f          centerOfRotation;

  /**
   * Constructor.
   */
  SoVRMLViewpoint();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoSFBool            set_bind;        // eventIn
  SoSFTime            bindTime;        // eventOut
  SoSFBool            isBound;         // eventOut
  virtual ~SoVRMLViewpoint();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLVIEWPOINT_ */

