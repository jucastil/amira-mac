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
** Modified by : Julien SALLANNE (Jul 2009)
**=======================================================================*/

#ifndef  _SO_VRMLGEOTOUCHSENSOR_
#define  _SO_VRMLGEOTOUCHSENSOR_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLTouchSensor.h>


/** 
 * @VSGEXT Detects when the user has pointed at a specific piece of geometry.
 * 
 * @ingroup GeoVRML
 * 
 * @DESCRIPTION
 *   The SoVRMLGeoTouchSensor node tracks the location and state of a pointing
 *   device and detects when the user points at geometry contained by the parent
 *   group of the GeoTouchSensor. This node provides the same functionality as a
 *   TouchSensor but also provides the ability to return the geographic coordinate
 *   under the pointing device.
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
 *    The SoVRMLGeoTouchSensor node tracks the location and state of a pointing
 *   device and detects when the user points at geometry contained by the parent
 *   group of the GeoTouchSensor. This node provides the same functionality as a
 *   TouchSensor but also provides the ability to return the geographic coordinate
 *   under the pointing device.
 *   The #description field in the GeoTouchSensor node specifies a textual
 *   description of the GeoTouchSensor node. This may be used by browser-specific
 *   user interfaces that wish to present users with more detailed information
 *   about the GeoTouchSensor.
 *   A SoVRMLGeoTouchSensor can be enabled or disabled by sending an event of
 *   value TRUE or FALSE to the #enabled field. A disabled GeoTouchSensor does not
 *   track user input or send events.
 *   The #geoOrigin field is used to specify a local coordinate frame for extended
 *   precision as described in 25.2.5 Dealing with high-precision coordinates.
 *   The #geoSystem field is used to define the spatial reference frame and is
 *   described in 25.2.3 Specifying a spatial reference frame.
 *   The fields #hitNormal_changed, #hitPoint_changed, #hitTexCoord_changed, #isActive,
 *   #isOver, and #touchTime all have the same meaning as in the TouchSensor node.
 *   The #hitGeoCoord_changed field is generated while the pointing device is
 *   pointing towards the SoVRMLGeoTouchSensor's geometry (i.e., when isOver is TRUE).
 *   It is a field containing the geospatial coordinate for the point of
 *   intersection between the pointing device's location and the underlying geometry.
 *   The value of the geoSystem string defines the spatial reference frame of
 *   the geospatial coordinate. For example, given the default geoSystem value
 *   of "GD", the #hitGeoCoord_changed field will be in the format
 *   (<latitude> <longitude> <elevation>)
 *   (see 25.2.4 Specifying geospatial coordinates).
 *   The #hitGeoCoordString_changed is the MFString equivalent of #hitGeoCoord_changed.
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLGeoTouchSensor {
 *    @TABLE_FILE_FORMAT
 *       @TR enabled       @TD TRUE
 *       @TR description   @TD ""
 *       @TR metadata      @TD NULL
 *       @TR geoOrigin     @TD NULL
 *       @TR geoSystem     @TD ["GD","WE"]
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
 *       @TR   SoSFVec2f   @TD  hitGeoCoord_changed
 *       @TR   SoMFString  @TD  hitGeoCoordString_changed
 *       @TR   SoSFBool    @TD  isActive
 *       @TR   SoSFBool    @TD  isOver @NI
 *       @TR   SoSFTime    @TD  touchTime
 *       @TR   SoSFNode    @TD  metadata_changed
 *    @TABLE_END
 * 
 */ 
class INVENTOR_API SoVRMLGeoTouchSensor : public SoVRMLTouchSensor {

  SO_NODE_HEADER(SoVRMLGeoTouchSensor);

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
   * Constructor.
   */
  SoVRMLGeoTouchSensor();


 SoEXTENDER public:
  // Implement actions:
  // Override handleEvent to look for left-mouse clicks, to do a pick:
  virtual void        handleEvent(SoHandleEventAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFVec3f           hitGeoCoord_changed;   // Sent when cursor on shape
  SoMFString          hitGeoCoordString_changed;   // Sent when cursor on shape

 protected:
  virtual ~SoVRMLGeoTouchSensor();
};

#endif /* _SO_VRMLGEOTOUCHSENSOR_ */
