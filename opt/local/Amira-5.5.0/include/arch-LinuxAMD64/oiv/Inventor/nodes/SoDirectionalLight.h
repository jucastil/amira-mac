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


#ifndef  _SO_DIRECTIONAL_LIGHT_
#define  _SO_DIRECTIONAL_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoDirectionalLight
//
//  Directional light source node. A directional light illuminates in
//  rays parallel to a given direction vector. It is equivalent to the
//  GL's "infinite" light source, so named because it is like a point
//  source at an infinite distance (which seems to me to be a pretty
//  bizarre way of naming things.)
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a directional light source.
 *
 * @ingroup LightNodes
 *
 * @DESCRIPTION
 *   This node defines a directional light source that illuminates along rays
 *   parallel to a given 3-dimensional vector.
 *
 * @FILE_FORMAT_DEFAULT
 *    DirectionalLight {
 *    @TABLE_FILE_FORMAT
 *       @TR on          @TD TRUE
 *       @TR intensity   @TD 1
 *       @TR color       @TD 1 1 1
 *       @TR direction   @TD 0 0 -1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Activates this light (if so specified) during traversal. All shape nodes that
 *        come after this light in the scene graph are illuminated by this light. The
 *        light's direction is affected by the current transformation.
 *        Sets: SoLightElement, SoGLLightIdElement
 *
 * @SEE_ALSO
 *    SoPointLight,
 *    SoSpotLight
 *
 *
 */

class INVENTOR_API SoDirectionalLight : public SoLight {

  SO_NODE_HEADER(SoDirectionalLight);

 public:
  /**
   * Illumination direction vector.
   *
   */
  SoSFVec3f           direction;

  /**
   * Creates a directional light source node with default settings.
   */
  SoDirectionalLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  /** Return a camera associated to the light */
  virtual SoCamera* getCamera(SoState* state, SoPath* scene,
                              float visibilityLength);

 protected:
  virtual ~SoDirectionalLight();
};

#endif /* _SO_DIRECTIONAL_LIGHT_ */

