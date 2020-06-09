/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Nov 2002)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_BUMP_MAPPING_PROPERTY_
#define  _SO_BUMP_MAPPING_PROPERTY_


#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFEnum.h>

#include <Inventor/nodes/SoNode.h>

#include <Inventor/elements/SoBumpMappingPropertyElement.h>


class SoGLRenderAction ;
class SoCallbackAction ;

/*----------------------------------------------------------------------------*/
/**
 * 
 * @FXEXT Bump mapping property node.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   This node defines the current bump mapping properties for all subsequent shapes.
 *   However,
 *   currently, only SoFaceSet, SoQuadMesh, and SoTriangleStripSet support bump mapping.
 *   Two categories of properties can be defined:
 *      - Texture properties
 *      - Appearance properties
 *   
 *   @B Texture Properties: @b  
 *   The format of the bump map texture stored within the SoTexture2 is given by the 
 *   #textureFormat field. The SoTextureUnit::mappingMethod field 
 *   indicates if the texture stored within SoTexture2 node is a bump map texture or not.
 *   This texture can be a "height map", which is a grayscale texture of height 
 *   (TextureFormat::HEIGHT_MAP), or a "normal map", which is a 3-component texture of 
 *   normals (TextureFormat::NORMAL_MAP) with x, y, and z  
 *   corresponding to the red, green, and blue components respectively.
 *
 *   If the current SoTexture2 node does not contain a 3-component texture,
 *   specifying normal map format will have no bump mapping effect.
 *
 *   For a height map format, only the first component of each pixel is used.
 *   A height map texture is converted internally to a normal map.
 *
 *   Each normal in the normal map texture can be expressed either in the space of the 
 *   object called "modeling space" or in the space of the face called "tangent space".
 *   The #normalMapSpace field allows you to specify the desired coordinate system.
 *   The tangent space coordinate system is convenient for applying repetitive 
 *   wrinkle patterns. 
 *   
 *   @B Appearance Properties: @b
 *   OpenGL Gouraud lighting is deactivated when a shape is rendered using
 *   the bump mapping technique. A pixel shader and a vertex shader are used instead for
 *   computing the lighting contribution per pixel according to the normals stored in the
 *   normal map.
 *
 *   Depending on the hardware capabilities, the number of passes (maximum 3)
 *   necessary to render a shape also depends on the number of lights, brightness of 
 *   the shape, and texturing (or not) of the shape.
 *   In order to select a compromise between rendering quality and rendering performance, several
 *   fields are available:
 *      - #isOnlyClosestLightUsed:      Indicates if only the closest light to the shape is used 
 *                                    for the lighting computation. TRUE (default) improves 
 *                                    performance by decreasing the number of rendering passes.
 *                                    
 * 
 *      - #isEyeDistanceAttenuation:    Prevents a bumped face from smoothing with camera distance.
 *                                    Setting TRUE reduces performance.
 *
 *      - #isShadowed:                  Activate/deactivate the self-shadow based on the geometric
 *                                    normal. Setting TRUE reduces performance.
 *                                    
 *                                    
 *   
 *
 * 
 * @FILE_FORMAT_DEFAULT
 *    BumpMappingProperty {
 *      @TABLE_FILE_FORMAT
 *        @TR normalMapSpace            @TD MODEL_SPACE
 *        @TR isShadowed                @TD FALSE
 *        @TR isEyeDistanceAttenuation  @TD FALSE
 *        @TR isOnlyClosestLightUsed    @TD TRUE
 *        @TR textureFormat             @TD NORMAL_MAP
 *      @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction, SoCallbackAction @BR
 *    Sets the current properties linked to the bump mapping.
 *    Sets: SoBumpMappingPropertyElement
 * 
 * @SEE_ALSO
 *    SoTextureUnit, SoTexture2, SoAppearancePreserver.
 * 
 * 
 */ 

class FXVIZ_API SoBumpMappingProperty : public SoNode {  
  SO_NODE_HEADER(SoBumpMappingProperty) ;


 public:
  enum NormalMapSpace {
    /**
     * Normals are expressed in the space of faces.
     */
    TANGENT_SPACE = SoBumpMappingPropertyElement::TANGENT_SPACE,

    /**
     * Normals are expressed in the space of the model (i.e., modeling
     * coordinates).
     */
    MODEL_SPACE  = SoBumpMappingPropertyElement::MODEL_SPACE
  } ;

  enum TextureFormat {
    /**
     * Grayscale height texture.
     */
    HEIGHT_MAP,

    /**
     * 3-component normal texture.
     */
    NORMAL_MAP
  } ;

  //Fields

  /**
   * Specifies in which space normals in the normal map are expressed.
   */
  SoSFEnum normalMapSpace ;

  /**
   * Indicates if the specified bump map texture in SoTexture2 is a
   * height map or a normal map.
   */
  SoSFEnum   textureFormat ;

  /**
   * Activates/deactivates the lighting of unlit areas.
   */
  SoSFBool isShadowed ;

  /**
   * Eye distance attenuation.
   */
  SoSFBool isEyeDistanceAttenuation ;

  /**
   * Indicates if only the closest light (relative to the shape) is used  
   * or if all lights are used. 
   */
  SoSFBool isOnlyClosestLightUsed ;

  /**
   * Constructor.
   */
  SoBumpMappingProperty() ;

  /**
   * Indicates if bump mapping is supported by your graphics board.
   *
   */
  static SbBool isSupported() ;

   
 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  callback(SoCallbackAction *action) ;
  virtual void  GLRender(SoGLRenderAction *action) ;
  
  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;
  
 protected:
  // Destructor
  virtual ~SoBumpMappingProperty() ;
} ;
/*----------------------------------------------------------------------------*/

#endif /* _SO_BUMP_MAPPING_PROPERTY_ */

