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


#ifndef  _SO_VRMLSPOT_LIGHT_
#define  _SO_VRMLSPOT_LIGHT_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/VRMLnodes/SoVRMLLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLSpotLight
//
//  Spot light source node. A spot light illuminates from a point in
//  space along a primary direction. The illumination is within a cone
//  whose angle is given by the cutOffAngle field. The intensity of
//  the source may vary as the illumination direction diverges from
//  the primary direction, as specified in the dropOffRate field.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node representing a spotlight source.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLSpotLight node defines a light source that emits light from a specific
 *   point along a specific direction vector and constrained within a solid angle.
 *   SoVRMLSpotlights may illuminate geometry nodes that respond to light sources and
 *   intersect the solid angle. SoVRMLSpotlights are specified in their local
 *   coordinate system and are affected by parent transformations.
 *   
 *   Note: SoVRMLSpotLights only illuminate objects in their enclosing parent group
 *   (similar to Directional lights). This is a slight deviation from the behavior
 *   described by the VRML97 specification.
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
 *   The SoVRMLSpotLight node defines a light source that emits light from a specific
 *   point along a specific direction vector and constrained within a solid angle.
 *   SoVRMLSpotlights may illuminate geometry nodes that respond to light sources and
 *   intersect the solid angle. SoVRMLSpotlights are specified in their local
 *   coordinate system and are affected by parent transformations.
 *   
 *   See "Concepts - Light Sources" for a detailed description of
 *   @B ambientIntensity @b, @B color @b, @B intensity @b, and VRML's lighting
 *   equations. See "Concepts - Lighting Model" for a detailed description of the
 *   VRML lighting equations.
 *   
 *   The #location field specifies a translation offset of the center point of
 *   the light source from the light's local coordinate system origin. This point is
 *   the apex of the solid angle which bounds light emission from the given light
 *   source. The #direction field specifies the direction vector of the light's
 *   central axis defined in its own local coordinate system. The @B on @b field
 *   specifies whether the light source emits light--if TRUE, then the light source
 *   is emitting light and may illuminate geometry in the scene, if FALSE it does not
 *   emit light and does not illuminate any geometry. The #radius field
 *   specifies the radial extent of the solid angle and the maximum distance from
 *   #location than may be illuminated by the light source - the light source
 *   does not emit light outside this radius. The #radius must be >= 0.0.
 *   
 *   The #cutOffAngle field specifies the outer bound of the solid angle. The
 *   light source does not emit light outside of this solid angle. The
 *   #beamWidth field specifies an inner solid angle in which the light source
 *   emits light at uniform full intensity. The light source's emission intensity
 *   drops off from the inner solid angle (#beamWidth) to the outer solid angle
 *   (#cutOffAngle). The drop off function from the inner angle to the outer
 *   angle is a cosine raised to a power function:
 *   
 *   <PRE>
 *    intensity(angle) = intensity * (cosine(angle) ** exponent) 
 *    
 *    where exponent = 0.5*log(0.5)/log(cos(beamWidth)), 
 *    intensity is the SpotLight's field value, 
 *    intensity(angle) is the light intensity at an arbitrary 
 *    angle from the direction vector, 
 *    and angle ranges from 0.0 at central axis to cutOffAngle. 
 *    </PRE>
 *    If #beamWidth > #cutOffAngle, then #beamWidth is
 *   assumed to be equal to #cutOffAngle and the light source emits full
 *   intensity within the entire solid angle defined by #cutOffAngle. Both
 *   #beamWidth and #cutOffAngle must be greater than 0.0 and less than
 *   or equal to pi/2. See the figure below for an illustration of the
 *   SoVRMLSpotLight's field semantics (note: this example uses the default
 *   attenuation).
 *   
 *   The light's illumination falls off with distance as specified by three
 *   #attenuation coefficients. The attenuation factor is
 *   @I 1/( @i@B @I attenuation @i @b@I [0] +
 *    @i@B @I attenuation @i @b@I [1]*r +
 *    @i@B @I attenuation @i @b@I [2]*r^2) @i, where @I r @i is the distance of
 *   the light to the surface being illuminated. The default is no attenuation. An
 *   #attenuation value of @B 0 @b @B 0 @b @B 0 @b is identical to @B 1 @b
 *   @B 0 @b @B 0 @b. Attenuation values must be >= 0.0.
 *   
 *   @IMAGE spotlight.gif 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLSpotLight {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientIntensity   @TD 0
 *       @TR attenuation        @TD 1 0 0
 *       @TR beamWidth          @TD 1.570796
 *       @TR color              @TD 1 1 1
 *       @TR cutOffAngle        @TD 0.785398
 *       @TR direction          @TD 0 0 -1
 *       @TR intensity          @TD 1
 *       @TR location           @TD 0 0 0
 *       @TR on                 @TD TRUE
 *       @TR radius             @TD 100
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction  @BR
 *        Sets: SoGLLightIdElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_ambientIntensity      
 *       @TR   SoSFVec3f   @TD   set_attenuation      
 *       @TR   SoSFFloat   @TD   set_beamWidth      
 *       @TR   SoSFColor   @TD   set_color      
 *       @TR   SoSFFloat   @TD   set_cutOffAngle      
 *       @TR   SoSFVec3f   @TD   set_direction      
 *       @TR   SoSFFloat   @TD   set_intensity      
 *       @TR   SoSFVec3f   @TD   set_location      
 *       @TR   SoSFBool   @TD   set_on      
 *       @TR   SoSFFloat   @TD   set_radius @NI 
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFFloat   @TD   ambientIntensity_changed      
 *       @TR   SoSFVec3f   @TD   attenuation_changed      
 *       @TR   SoSFFloat   @TD   beamWidth_changed      
 *       @TR   SoSFColor   @TD   color_changed      
 *       @TR   SoSFFloat   @TD   cutOffAngle_changed      
 *       @TR   SoSFVec3f   @TD   direction_changed      
 *       @TR   SoSFFloat   @TD   intensity_changed      
 *       @TR   SoSFVec3f   @TD   location_changed      
 *       @TR   SoSFBool   @TD   on_changed      
 *       @TR   SoSFFloat   @TD   radius_changed @NI 
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLSpotLight : public SoVRMLLight {

  SO_NODE_HEADER(SoVRMLSpotLight);

 public:
  /**
   * Specifies a translation offset of the centerpoint of the light source from the
   * light's local coordinate system origin.
   * 
   */
  SoSFVec3f   location;
  /**
   * Direction vector of the light's central axis.
   * 
   */
  SoSFVec3f   direction;
  /**
   * Inner solid angle of illumination.
   * 
   */
  SoSFFloat   beamWidth;
  /**
   * Outer solid angle of illumination.
   * 
   */
  SoSFFloat   cutOffAngle;
  /**
   * @NI  Specifies the radial extent of the solid angle and the
   * maximum distances from #location that may be illuminated by the light
   * source.
   * 
   */
  SoSFFloat   radius;
  /**
   * Attenuation coefficients.
   * 
   */
  SoSFVec3f   attenuation;

  /**
   * Constructor.
   */
  SoVRMLSpotLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLSpotLight();
};

#endif /* _SO_VRMLSPOT_LIGHT_ */

