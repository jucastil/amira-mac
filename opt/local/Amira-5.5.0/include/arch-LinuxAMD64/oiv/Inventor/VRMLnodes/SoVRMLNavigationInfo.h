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



#ifndef  _SO_VRMLNAVIGATIONINFO_
#define  _SO_VRMLNAVIGATIONINFO_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLNavigationInfo
//
//  Node that holds viewer-specific information 
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Describes physical characteristics of viewer and viewing model.\ @PARTIAL_ACTION
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLNavigationInfo node contains information describing the physical
 *   characteristics of the viewer and viewing model. 
 *   
 *   Note: The binding behavior, the @B set_bind @b eventIn and the @B isBound @b
 *   eventOut are not implemented.
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
 *   The SoVRMLNavigationInfo node contains information describing the physical
 *   characteristics of the viewer and viewing model. SoVRMLNavigationInfo is a
 *   bindable node (see "Concepts - Bindable Children Nodes") and thus there exists
 *   an SoVRMLNavigationInfo stack in the browser in which the top-most
 *   SoVRMLNavigationInfo on the stack is the currently active SoVRMLNavigationInfo.
 *   The current SoVRMLNavigationInfo is considered to be a child of the current
 *   SoVRMLViewpoint - regardless of where it is initially located in the file.
 *   Whenever the current SoVRMLViewpoint changes, the current SoVRMLNavigationInfo
 *   must be reparented to it. Whenever the current SoVRMLNavigationInfo changes, the
 *   new SoVRMLNavigationInfo must be reparented to the current SoVRMLViewpoint.
 *   
 *   If a TRUE value is sent to the @B set_bind @b eventIn of an
 *   SoVRMLNavigationInfo, it is pushed onto the SoVRMLNavigationInfo stack and
 *   activated. When an SoVRMLNavigationInfo is bound, the browser uses the fields of
 *   the SoVRMLNavigationInfo to set the navigation controls of its user interface
 *   and the SoVRMLNavigationInfo is conceptually re-parented under the currently
 *   bound SoVRMLViewpoint. All subsequent scaling changes to the current
 *   SoVRMLViewpoint's coordinate system automatically change aspects (see below) of
 *   the SoVRMLNavigationInfo values used in the browser (e.g. scale changes to any
 *   parent transformation). A FALSE value of @B set_bind @b pops the
 *   SoVRMLNavigationInfo from the stack, results in an @B isBound @b FALSE event,
 *   and pops to the next entry in the stack which must be reparented to the current
 *   SoVRMLViewpoint. See "Concepts - Bindable Children Nodes" for more details on
 *   the binding stacks. 
 *   
 *   The #type field specifies a navigation paradigm to use. Minimally, browsers
 *   must support the following navigation types: "WALK", "EXAMINE", "FLY", and
 *   "NONE". Walk navigation is used for exploring a virtual world. It is recommended
 *   that the browser should support a notion of gravity in walk mode. Fly navigation
 *   is similar to walk except that no notion of gravity should be enforced. There
 *   should still be some notion of "up" however. Examine navigation is typically
 *   used to view individual objects and often includes (but does not require) the
 *   ability to spin the object and move it closer or further away. The "none" choice
 *   removes all navigation controls - the user navigates using only controls
 *   provided in the scene, such as guided tours. Also allowed are browser specific
 *   navigation types. These should include a unique suffix (e.g. _sgi.com) to
 *   prevent conflicts. The #type field is multi-valued so that authors can
 *   specify fallbacks in case a browser does not understand a given type. If none of
 *   the types are recognized by the browser, then the default ["WALK", "ANY"] is
 *   used. These strings values are case sensitive ("walk" is not equal to "WALK").
 *   
 *   The #speed is the rate at which the viewer travels through a scene in
 *   meters per second. Since viewers may provide mechanisms to travel faster or
 *   slower, this should be the default or average speed of the viewer. If the
 *   SoVRMLNavigationInfo #type is EXAMINE, #speed should affect panning
 *   and dollying--it should have no effect on the rotation speed. The transformation
 *   hierarchy of the currently bound SoVRMLViewpoint (see above) scales the
 *   #speed - translations and rotations have no effect on #speed. Speed
 *   must be >= 0.0 - where 0.0 specifies a stationary avatar.
 *   
 *   The #avatarSize field specifies the user's physical dimensions in the world
 *   for the purpose of collision detection and terrain following. It is a
 *   multi-value field to allow several dimensions to be specified. The first value
 *   should be the allowable distance between the user's position and any collision
 *   geometry (as specified by SoVRMLCollision) before a collision is detected. The
 *   second should be the height above the terrain the viewer should be maintained.
 *   The third should be the height of the tallest object over which the viewer can
 *   "step". This allows staircases to be built with dimensions that can be ascended
 *   by all browsers. Additional values are browser dependent and all values may be
 *   ignored, but if a browser interprets these values the first 3 should be
 *   interpreted as described above. The transformation hierarchy of the currently
 *   bound SoVRMLViewpoint scales the #avatarSize - translations and rotations
 *   have no effect on #avatarSize.
 *   
 *   For purposes of terrain following the browser needs a notion of the @B down @b
 *   direction (down vector), since gravity is applied in the direction of the down
 *   vector. This down vector should be along the negative Y-axis in the local
 *   coordinate system of the currently bound SoVRMLViewpoint (i.e., the accumulation
 *   of the SoVRMLViewpoint's parent transformations, not including the
 *   SoVRMLViewpoint's orientation field).
 *   
 *   The #visibilityLimit field sets the furthest distance the user is able to
 *   see. The browser may clip all objects beyond this limit, fade them into the
 *   background or ignore this field. A value of 0.0 (the default) indicates an
 *   infinite visibility limit. @B VisibilityLimit @b is restricted to be >= 0.0.
 *   
 *   The #speed, #avatarSize and #visibilityLimit values are all
 *   scaled by the transformation being applied to currently bound SoVRMLViewpoint.
 *   If there is no currently bound SoVRMLViewpoint, they are interpreted in the
 *   world coordinate system. This allows these values to be automatically adjusted
 *   when binding to an SoVRMLViewpoint that has a scaling transformation applied to
 *   it without requiring a new SoVRMLNavigationInfo node to be bound as well. If the
 *   scale applied to the SoVRMLViewpoint is non-uniform, the behavior is undefined.
 *   
 *   The #headlight field specifies whether a browser should turn a headlight
 *   on. A headlight is a directional light that always points in the direction the
 *   user is looking. Setting this field to TRUE allows the browser to provide a
 *   headlight, possibly with user interface controls to turn it on and off. Scenes
 *   that enlist precomputed lighting (e.g. radiosity solutions) can turn the
 *   headlight off. The headlight will have @B intensity @b = 1, @B color @b = 1 1
 *   1, @B ambientIntensity @b = 0.0, and @B direction @b = 0 0 -1.
 *   
 *   It is recommended that the near clipping plane should be set to one-half of the
 *   collision radius as specified in the #avatarSize field. This
 *   recommendation may be ignored by the browser, but setting the near plane to this
 *   value prevents excessive clipping of objects just above the collision volume and
 *   provides a region inside the collision volume for content authors to include
 *   geometry that should remain fixed relative to the viewer, such as icons or a
 *   heads-up display, but that should not be occluded by geometry outside of the
 *   collision volume.
 *   
 *   The first SoVRMLNavigationInfo node found during reading of the world is
 *   automatically bound (receives a @B set_bind @b TRUE event) and supplies the
 *   initial navigation parameters. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLNavigationInfo {
 *    @TABLE_FILE_FORMAT
 *       @TR avatarSize        @TD [ 0.25, 1.6, 0.75 ]
 *       @TR headlight         @TD TRUE
 *       @TR speed             @TD 1.0
 *       @TR type              @TD ["WALK", "ANY"]
 *       @TR visibilityLimit   @TD 0.0
 *       @TR transitionType    @TD ["TELEPORT","LINEAR","ANIMATE"]
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool   @TD   set_bind @NI 
 *       @TR   SoMFFloat   @TD   set_avatarSize      
 *       @TR   SoSFBool   @TD   set_headlight      
 *       @TR   SoSFFloat   @TD   set_speed  @NI      
 *       @TR   SoMFString   @TD   set_type      
 *       @TR   SoSFFloat   @TD   set_visibilityLimit @NI  
 *       @TR   SoMFString   @TD   set_transitionType @NI 
 *       @TR   SoSFNode   @TD   set_metadata  
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFBool   @TD   isBound  @NI      
 *       @TR   SoMFFloat   @TD   avatarSize_changed      
 *       @TR   SoSFBool   @TD   headlight_changed      
 *       @TR   SoSFFloat   @TD   speed_changed  @NI      
 *       @TR   SoMFString   @TD   type_changed      
 *       @TR   SoSFFloat   @TD   visibilityLimit_changed @NI 
 *       @TR   SoMFString   @TD   transitionType_changed  @NI  
 *       @TR   SoSFTime    @TD   bindTime @NI 
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLNavigationInfo : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLNavigationInfo);

 public:
  // Fields

  /**
   * Specifies a navigation paradigm to use. You may specify "ANY".
   * If this field is set to anything but "ANY", the type is used
   * to set the viewer type in IVF.
   * 
   */
  SoMFString          type;
  /**
   *  @NI The rate at which the viewer travels through a scene.
   * 
   */
  SoSFFloat           speed;
  /**
   * The user's physical dimensions in the world for the purpose of collision
   * detection and terrain following. This is used by the
   * QtLargeModelViewer to set the collision distance and the
   * gravity offset.
   * 
   */
  SoMFFloat           avatarSize;
  /**
   *  @NI Sets the furthest distance the user is able to see.
   * 
   */
  SoSFFloat           visibilityLimit;
  /**
   * Specifies whether the headlight should be turned on (TRUE).
   * This field can be used to set the headlight on or off in IVF.
   * 
   */
  SoSFBool            headlight;
  /**
   * @NI The transitionType field specifies an ordered list of paradigms 
   * that determine the manner in which the browser moves the viewer 
   * when a new Viewpoint node is bound.
   *
   * @FIELD_SINCE_OIV 5.0
   *
   * @B NOTE 2:@b This field is not compatible with VRML97.
   * If you specify a non-default value for this field, when this node
   * is written to a VRML file, the file will contain this incompatible
   * field and standard VRML97 file readers will not be able to read it.
   */
  SoMFString            transitionType;
  /**
   * Constructor.
   */
  SoVRMLNavigationInfo();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  SoSFBool            set_bind;          // eventIn
  SoSFBool            isBound;           // eventOut
  SoSFTime            bindTime;          // eventOut
  virtual ~SoVRMLNavigationInfo();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLNAVIGATIONINFO_ */

