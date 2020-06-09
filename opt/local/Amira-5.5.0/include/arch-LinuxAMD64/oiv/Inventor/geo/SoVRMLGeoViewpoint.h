/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : SGI (MMM YYYY)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : Julien SALLANNE (Jun 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOVIEWPOINT_
#define  _SO_VRMLGEOVIEWPOINT_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLViewpoint.h>


/** 
 * @VSGEXT Specifies position from which the user might view the scene.\ @NO_ACTION
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *   The SoVRMLGeoViewpoint node defines a specific location in a local geospatial
 *   coordinate system from which the user might view the scene.
 * 
 * @VRMLX3D_SPECIFICATION
 *    This section describes the expected behavior of the node in a conforming X3D / VRML97
 *   browser application. In some cases, the application is responsible for
 *   implementing portions of the expected behavior. Open Inventor viewer classes and
 *   IVF classes implement some of the application behaviors.
 *   
 *    This section may reference portions of the X3D specification that are not
 *   present in this help file. The complete X3D spec is available at
 *   @B http://www.web3d.org @b.
 *
 *    The SoVRMLGeoViewpoint node allows the specification of a viewpoint in terms of
 *   a geospatial coordinate. This node can be used wherever a Viewpoint node can
 *   be used and can be combined with Viewpoint nodes in the same scene.
 *   The #fieldOfView, #jump, #description, #set_bind, #bindTime, and #isBound fields
 *   and events have the same behavior as the standard Viewpoint node. When a
 *   SoVRMLGeoViewpoint node is bound, it overrides the currently bound Viewpoint and
 *   NavigationInfo nodes in the scene.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The #position is used to define the actual coordinate at which the viewpoint
 *   is to be located. It should be provided in a format consistent with that
 *   specified by geoSystem. There is also a #set_position field which can be
 *   routed from the #geovalue_changed field of a GeoPositionInterpolator node in
 *   order to animate the position of the SoVRMLGeoViewpoint.
 *   The #orientation string defines a relative orientation from the local
 *   orientation frame that is defined by the #position field. By default, the
 *   orientation of the viewpoint will always be aligned such that the +Y axis
 *   is the up vector for the local area (the normal to the tangent plane on the
 *   ellipsoid), -Z points towards the north pole, and +X is east. Therefore, if
 *   a SoVRMLGeoViewpoint is created that always looked straight down, no matter where
 *   on the planetary body is being observed, an orientation value of
 *   [ 1 0 0 -1.57 ] is used. The #set_orientation field can be routed to the
 *   #value_changed field of an OrientationInterpolator in order to animate the
 *   orientation of the SoVRMLGeoViewpoint.
 *   The #navType field is used to specify the navigation type that is to be bound
 *   when this SoVRMLGeoViewpoint node is bound. The acceptable values for this field
 *   are the same as those for the type field of the NavigationInfo node.
 *   The #headlight field is used to specify the whether the viewer shall turn on
 *   a headlight when this viewpoint is bound. A headlight is a directional light
 *   that always points in the direction that the user is looking.
 *   The SoVRMLGeoViewpoint node may be implemented as if there is an embedded
 *   NavigationInfo node that is bound and unbound with the SoVRMLGeoViewpoint node.
 *   The #speedFactor field of the SoVRMLGeoViewpoint node is used as a multiplier to
 *   the elevation-based velocity that the node sets internally; i.e., this is a
 *   relative value and not an absolute speed as is the case for the
 *   NavigationInfo node.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoViewpoint {
 *    @TABLE_FILE_FORMAT
 *       @TR description   @TD ""
 *       @TR fieldOfView   @TD 0.785398
 *       @TR headlight     @TD TRUE
 *       @TR jump          @TD TRUE
 *       @TR metadata      @TD NULL
 *       @TR navType  	   @TD ["WALK","ANY"]
 *       @TR geoOrigin     @TD NULL
 *       @TR geoSystem     @TD ["GD","WE"]
 *       @TR orientation   @TD 0 0 1 0
 *       @TR position      @TD 0 0 100000
 *       @TR speedFactor   @TD 1.0
 *    @TABLE_END
 *    }
 * 
 * 
 * @EVENTS 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFBool      @TD   set_bind @NI
 *       @TR   SoSFFloat     @TD   set_fieldOfView @NI
 *       @TR   SoSFBool      @TD   set_headlight @NI
 *       @TR   SoSFBool      @TD   set_jump  @NI
 *       @TR   SoSFRotation  @TD   set_orientation @NI
 *       @TR   SoSFVec3f     @TD   set_position @NI
 *       @TR   SoSFString    @TD   set_description @NI
 *       @TR   SoMFString    @TD   set_navType @NI
 *       @TR   SoSFNode      @TD   set_metadata @NI
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFTime      @TD   bindTime @NI
 *       @TR   SoSFBool      @TD   isBound @NI
 *       @TR   SoSFFloat     @TD   fieldOfView_changed @NI
 *       @TR   SoSFString    @TD   description_changed @NI
 *       @TR   SoSFBool      @TD   headlight_changed @NI
 *       @TR   SoSFBool      @TD   jump_changed @NI
 *       @TR   SoMFString    @TD   navType_changed @NI
 *       @TR   SoSFNode      @TD   metadata_changed @NI
 *    @TABLE_END
 * 
 */
class INVENTOR_API SoVRMLGeoViewpoint : public SoVRMLViewpoint {

  SO_NODE_HEADER(SoVRMLGeoViewpoint);

  public:
  // Fields
  /**
   * An SoVRMLGeoOrigin node specifying the origin of the local coordinate system.
   */
  SoSFNode           geoOrigin;

  /**
   * Defines the spatial reference frame. @BR
   * Valid values are:
   * - GC: Earth-fixed Geocentric with respect to the WGS84 ellipsoid.
   * - GD: Geodetic spatial reference frame. @BR
   *   An optional second string may be used to specify the ellipsoid using
   *   one of the ellipsoid codes that are defined in X3D. If no ellipsoid is 
   *   specified, then "WE" is assumed (the WGS84 ellipsoid).
   * - UTM: Universal Transverse Mercator @BR
   *   One further required argument must be supplied for UTM in order to
   *   specify the zone number (1..60). This is given in the form "Z<n>", where
   *   <n> is the zone number. An optional argument of "S" may be supplied in 
   *   order to specify that the coordinates are in the southern hemisphere
   *  (otherwise, northern hemisphere will be assumed).
   */
  SoMFString         geoSystem;

  /**
   * @NI Specifies whether the headlight should be turned on (TRUE).
   * This field can be used to set the headlight on or off in IVF.
   */
  SoSFBool           headlight;

  /**
   * @NI Specifies a navigation paradigm to use. You may specify "ANY".
   * If this field is set to anything but "ANY", the type is used
   * to set the viewer type in IVF.
   */
  SoMFString        navType;

  /**
   *  @NI A multiplier
   * 
   */
  SoSFFloat         speedFactor;

  /**
   * Constructor.
   */
  SoVRMLGeoViewpoint();


 SoEXTENDER public:
  // Implements actions
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLGeoViewpoint();

  // NOTE: This node has not been fully implemented.
};

#endif /* _SO_VRMLGEOVIEWPOINT_ */
