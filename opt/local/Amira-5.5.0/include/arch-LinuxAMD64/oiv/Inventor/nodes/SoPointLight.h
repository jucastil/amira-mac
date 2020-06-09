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


#ifndef  _SO_POINT_LIGHT_
#define  _SO_POINT_LIGHT_

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/nodes/SoLight.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoPointLight
//
//  Point light source node. A point light illuminates in all
//  directions from a given point in space.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node representing a point light source.
 * 
 * @ingroup LightNodes
 * 
 * @DESCRIPTION
 *   This node defines a point light source at a fixed 3D location. A point source
 *   illuminates equally in all directions; that is, it is omnidirectional.
 * 
 * @FILE_FORMAT_DEFAULT
 *    PointLight {
 *    @TABLE_FILE_FORMAT
 *       @TR on          @TD TRUE
 *       @TR intensity   @TD 1
 *       @TR color       @TD 1 1 1
 *       @TR location    @TD 0 0 1
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
 *    SoSpotLight
 * 
 * 
 */ 

class INVENTOR_API SoPointLight : public SoLight {

  SO_NODE_HEADER(SoPointLight);

 public:
  /**
   * Location of the source.
   * 
   */
  SoSFVec3f           location;

  /**
   * Creates a point light source node with default settings.
   */
  SoPointLight();

 SoEXTENDER public:
  // Creates a light source during rendering
  virtual void        GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoPointLight();
};

#endif /* _SO_POINT_LIGHT_ */

