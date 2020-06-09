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


#ifndef  _SO_VRMLPOINT_LIGHT_
#define  _SO_VRMLPOINT_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPointLight
//
//  Point light source node. A point light illuminates in all
//  directions from a given point in space.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Node representing a point light source.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   The SoVRMLPointLight node specifies a point light source at a 3D location in the
 *   local coordinate system. A point source emits light equally in all directions;
 *   that is, it is omnidirectional. SoVRMLPointLights are specified in their local
 *   coordinate system and are affected by parent transformations.
 *   
 *   Note: SoVRMLPointLights only illuminate objects in their enclosing parent group
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
 *   The SoVRMLPointLight node specifies a point light source at a 3D location in the
 *   local coordinate system. A point source emits light equally in all directions;
 *   that is, it is omnidirectional. SoVRMLPointLights are specified in their local
 *   coordinate system and are affected by parent transformations.
 *   
 *   See "Concepts - Light Sources" for a detailed description of the
 *   @B ambientIntensity @b, @B color @b, and @B intensity @b fields.
 *   
 *   A SoVRMLPointLight may illuminate geometry within #radius (>= 0.0) meters
 *   of its #location. Both radius and location are affected by parent
 *   transformations (scale #radius and transform #location).
 *   
 *   A SoVRMLPointLight's illumination falls off with distance as specified by three
 *   #attenuation coefficients. The attenuation factor is
 *   @I 1/( @i@B @I attenuation @i @b@I [0] +
 *    @i@B @I attenuation @i @b@I [1]*r +
 *    @i@B @I attenuation @i @b@I [2]*r^2) @i, where @I r @i is the distance of
 *   the light to the surface being illuminated. The default is no attenuation. An
 *   #attenuation value of @B 0 @b @B 0 @b @B 0 @b is identical to @B 1 @b
 *   @B 0 @b @B 0 @b. Attenuation values must be >= 0.0. Renderers that do not
 *   support a full attenuation model may approximate as necessary. See "Concepts -
 *   Lighting Model" for a detailed description of VRML's lighting equations. 
 * 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPointLight {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientIntensity   @TD 0
 *       @TR attenuation        @TD 1 0 0
 *       @TR color              @TD 1 1 1
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
 *       @TR   SoSFColor   @TD   set_color      
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
 *       @TR   SoSFColor   @TD   color_changed      
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

class INVENTOR_API SoVRMLPointLight : public SoVRMLLight {

  SO_NODE_HEADER(SoVRMLPointLight);

 public:
  /**
   * Location of the source.
   * 
   */
  SoSFVec3f           location;
  /**
   * @NI Meters from the location the light can illuminate.
   * 
   */
  SoSFFloat           radius;
  /**
   * Attenuation coefficients.
   * 
   */
  SoSFVec3f           attenuation;

  /**
   * Constructor.
   */
  SoVRMLPointLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoVRMLPointLight();
};

#endif /* _SO_VRMLPOINT_LIGHT_ */

