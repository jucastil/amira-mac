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


#ifndef  _SO_SPOT_LIGHT_
#define  _SO_SPOT_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSpotLight
//
//  Spot light source node. A spot light illuminates from a point in
//  space along a primary direction. The illumination is within a cone
//  whose angle is given by the cutOffAngle field. The intensity of
//  the source may vary as the illumination direction diverges from
//  the primary direction, as specified in the dropOffRate field.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a spotlight source.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node defines a spotlight style light source. A spotlight is placed at a
 *   fixed location in 3-space and illuminates in a cone along a particular
 *   direction. The intensity of the illumination drops off exponentially as a ray of
 *   light diverges from this direction toward the edges of the cone. The rate of
 *   drop-off and the angle of the cone are controlled by the #dropOffRate and
 *   #cutOffAngle fields.
 * 
 * @FILE_FORMAT_DEFAULT
 *    SpotLight {
 *    @TABLE_FILE_FORMAT
 *       @TR on            @TD TRUE
 *       @TR intensity     @TD 1
 *       @TR color         @TD 1 1 1
 *       @TR location      @TD 0 0 1
 *       @TR direction     @TD 0 0 -1
 *       @TR dropOffRate   @TD 0
 *       @TR cutOffAngle   @TD 0.785398
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Activates this light (if so specified) during traversal. All shape nodes that
 *        come after this light in the scene graph are illuminated by this light. The
 *        light's location is affected by the current transformation.
 *        Sets: SoLightElement, SoGLLightIdElement
 * 
 * @SEE_ALSO
 *    SoDirectionalLight,
 *    SoPointLight
 * 
 * 
 */ 

class INVENTOR_API SoSpotLight : public SoLight {

  SO_NODE_HEADER(SoSpotLight);

 public:
  /**
   * Location of the source.
   * 
   */
  SoSFVec3f   location;
  /**
   * Principal direction of illumination (center axis of cone).
   * 
   */
  SoSFVec3f   direction;
  /**
   * Rate of intensity drop-off per change in angle from primary direction: 0 =
   * constant intensity, 1 = very sharp drop-off
   * 
   */
  SoSFFloat   dropOffRate;
  /**
   * Angle (in radians) outside of which intensity is zero, measured from the center
   * axis of the cone to an edge.
   * 
   */
  SoSFFloat   cutOffAngle;

  /**
   * Creates a spotlight source node with default settings.
   */
  SoSpotLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoSpotLight();
};

#endif /* _SO_SPOT_LIGHT_ */

