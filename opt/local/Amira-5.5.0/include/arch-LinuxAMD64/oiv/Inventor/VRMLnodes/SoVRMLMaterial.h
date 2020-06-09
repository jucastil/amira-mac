/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_VRMLMATERIAL_
#define  _SO_VRMLMATERIAL_

#include <Inventor/fields/SoMFColor.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/VRMLnodes/SoVRMLNode.h>

class SoColorPacker;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLMaterial
//
//  Surface material node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Surface material definition node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
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
 *   The SoVRMLMaterial node specifies surface material properties for associated
 *   geometry nodes and are used by the VRML lighting equations during rendering. See
 *   "Concepts - Lighting Model" for a detailed description of the VRML lighting
 *   model equations.
 *   
 *   All of the fields in the SoVRMLMaterial node range from 0.0 to 1.0.
 *   
 *   The fields in the SoVRMLMaterial node determine the way light reflects off an
 *   object to create color: 
 *   
 *   - The #diffuseColor reflects all VRML light sources depending on the angle
 *   of the surface with respect to the light source. The more directly the surface
 *   faces the light, the more diffuse light reflects. 
 *   
 *   - The #ambientIntensity field specifies how much ambient light from light
 *   sources this surface should reflect. Ambient light is omnidirectional and
 *   depends only on the number of light sources, not their positions with respect to
 *   the surface. Ambient color is calculated as #ambientIntensity *
 *   #diffuseColor. 
 *   
 *   - The #specularColor and #shininess determine the specular
 *   highlights--for example, the shiny spots on an apple. When the angle from the
 *   light to the surface is close to the angle from the surface to the viewer, the
 *   #specularColor is added to the diffuse and ambient color calculations.
 *   Lower shininess values produce soft glows, while higher values result in
 *   sharper, smaller highlights. 
 *   
 *   - Emissive color models "glowing" objects. This can be useful for displaying
 *   radiosity-based models (where the light energy of the room is computed
 *   explicitly), or for displaying scientific data. 
 *   
 *   - Transparency is how "clear" the object is, with 1.0 being completely
 *   transparent, and 0.0 completely opaque. 
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLMaterial {
 *    @TABLE_FILE_FORMAT
 *       @TR ambientIntensity   @TD 0.2
 *       @TR diffuseColor       @TD 0.8 0.8 0.8
 *       @TR emissiveColor      @TD 0 0 0
 *       @TR shininess          @TD 0.2
 *       @TR specularColor      @TD 0 0 0
 *       @TR transparency       @TD 0
 *       @TR metadata     @TD NULL
 *       @TR reflectiveColor    @TD 0 0 0
 *       @TR receiveShadow      @TD FALSE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction  @BR
 * 
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFFloat   @TD   set_ambientIntensity      
 *       @TR   SoSFColor   @TD   set_diffuseColor      
 *       @TR   SoSFColor   @TD   set_emissiveColor      
 *       @TR   SoSFFloat   @TD   set_shininess      
 *       @TR   SoSFColor   @TD   set_specularColor      
 *       @TR   SoSFFloat   @TD   set_transparency
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFFloat   @TD   ambientIntensity_changed      
 *       @TR   SoSFColor   @TD   diffuseColor_changed      
 *       @TR   SoSFColor   @TD   emissiveColor_changed      
 *       @TR   SoSFFloat   @TD   shininess_changed      
 *       @TR   SoSFColor   @TD   specularColor_changed      
 *       @TR   SoSFFloat   @TD   transparency_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLMaterial : public SoVRMLNode {

  SO_NODE_HEADER(SoVRMLMaterial);

 public:
  // Fields
  /**
   * Diffuse color of the surface.
   * 
   */
  SoSFColor           diffuseColor;
  /**
   * Specifies how much ambient light from the light sources this surface should
   * reflect.
   * 
   */
  SoSFFloat           ambientIntensity;
  /**
   * Specular color of the surface.
   * 
   */
  SoSFColor           specularColor;
  /**
   * Emissive color of the surface.
   * 
   */
  SoSFColor           emissiveColor;
  /**
   * Shininess coefficient of the surface. Values range from 0.0 for no shininess to
   * 1.0 for maximum shininess.
   * 
   */
  SoSFFloat           shininess;
  /**
   * Transparency value of the surface. Values range from 0.0 for opaque to 1.0 for
   * completely transparent surfaces.
   * 
   */
  SoSFFloat           transparency;

  /** 
   * DirectViz parameter. Reflective color of the shape. 
   * When set to black, the object is not reflective.
   * The reflective component is added to the overall color of the object.
   * This field has no effect when not doing DirectViz rendering.
   * NOTE: This field is not part of the VRML specification.
   *
   * @FIELD_SINCE_OIV 6.1
   */
  SoSFColor           reflectiveColor;
 
 /** 
   * DirectViz parameter. Indicates that all the shapes using this material node will 
   * receive shadows from other shapes when doing DirectViz rendering.
   * This field has no effect when not doing DirectViz rendering.
   * NOTE: This field is not part of the VRML specification.
   *
   * @FIELD_SINCE_OIV 6.1
   */
  SoSFBool              receiveShadow;

  /**
   * Constructor.
   */
  SoVRMLMaterial();

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoVRMLMaterial();
  SoColorPacker *colorPacker;

 private:
  // Temporary storage during traversal
  // (traversal state wants SoMF fields and we only have SoSF fields!)
  static SoMFColor    *m_diffuse;
  static SoMFColor    *m_emissive;
  static SoMFColor    *m_specular;
  static SoMFFloat    *m_transparency;
  static SoMFFloat    *m_shininess;
  static SoMFColor    *m_ambient;

  // Count instances of this type so we can clean up the temporary storage
  static int instanceCounter;
};

#endif /* _SO_VRMLMATERIAL_ */

