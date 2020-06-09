/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : John Rohlf (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/



#ifndef  _SO_VRMLPIXEL_TEXTURE_
#define  _SO_VRMLPIXEL_TEXTURE_

#include <Inventor/VRMLnodes/SoVRMLTexture.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/nodes/SoNode.h>

class SoSensor;
class SoFieldSensor;
class SoGLDisplayList;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoVRMLPixelTexture
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT Texture node.
 * 
 * @ingroup VRML2
 * 
 * @DESCRIPTION
 *   See the VRML97 Specification, below.
 *   
 *   If the texture image's width or height is not a power of 2, or the image's width
 *   or height is greater than the maximum supported by OpenGL, then the image will
 *   be automatically scaled up or down to the next power of 2 or the maximum texture
 *   size. For maximum speed, point-sampling is used to do the scale; if you want
 *   more accurate resampling, pre-filter images to a power of 2 smaller than the
 *   maximum texture size (use the OpenGL glGetIntegerv(GL_MAX_TEXTURE_SIZE...) call
 *   to determine maximum texture for a specific OpenGL implementation).
 * 
 *   The quality of the texturing is affected by the @B textureQuality @b field of
 *   the SoComplexity node. The @B textureQuality @b field affects what kind of
 *   filtering is done to the texture when it must be minified or magnified. The
 *   mapping of a particular texture quality value to a particular OpenGL filtering
 *   technique is implementation dependent, and varies based on the texturing
 *   performance. If mipmap filtering is required, mipmaps are automatically created
 *   using the simple box filter.
 * 
 *  @B Performance Note@b: Automatic scaling of texture images
 *  to a power of 2 is
 *  a very convenient feature for prototyping, but it does
 *  take additional time the first time the texture node is
 *  traversed for rendering.  For large images, or a large
 *  number of images, this can make the application seem slow
 *  while starting up or loading a new data file.  Avoid this
 *  effect by either pre-scaling the image or by storing it
 *  as a sub-image in a "power of 2" image (then provide explicit
 *  texture coordinates such that only the sub-image is used).
 *   
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
 *   The SoVRMLPixelTexture node defines a 2D image-based texture map as an explicit
 *   array of pixel values and parameters controlling tiling repetition of the
 *   texture onto geometry. 
 *   
 *   Texture maps are defined in a 2D coordinate system, (s,t), that ranges from 0.0
 *   to 1.0 in both directions. The bottom edge of the pixel image corresponds to the
 *   S-axis of the texture map, and left edge of the pixel image corresponds to the
 *   T-axis of the texture map. The lower-left pixel of the pixel image corresponds
 *   to s=0, t=0, and the top-right pixel of the image corresponds to s=1, t=1.
 *   
 *   @IMAGE imagets.gif 
 *   
 *   Images may be one component (grayscale), two component (grayscale plus alpha
 *   opacity), three component (full RGB color), or four-component (full RGB color
 *   plus alpha opacity). An ideal VRML implementation will use the texture image to
 *   modify the diffuse color and transparency ( = 1 - alpha opacity) of an object's
 *   material (specified in an SoVRMLMaterial node), then perform any lighting
 *   calculations using the rest of the object's material properties with the
 *   modified diffuse color to produce the final image. The texture image modifies
 *   the diffuse color and transparency depending on how many components are in the
 *   image, as follows: 
 *   
 *   1. Diffuse color is multiplied by the grayscale values in the texture image. 
 *   
 *   2. Diffuse color is multiplied by the grayscale values in the texture image;
 *   material transparency is multiplied by transparency values in texture image. 
 *   
 *   3. RGB colors in the texture image replace the material's diffuse color. 
 *   
 *   4. RGB colors in the texture image replace the material's diffuse color;
 *   transparency values in the texture image replace the material's transparency. 
 *   
 *   Browsers may approximate this ideal behavior to increase performance. One common
 *   optimization is to calculate lighting only at each vertex and combining the
 *   texture image with the color computed from lighting (performing the texturing
 *   after lighting). Another common optimization is to perform no lighting
 *   calculations at all when texturing is enabled, displaying only the colors of the
 *   texture image. 
 *   
 *   See "Concepts - Lighting Model" for details on the VRML lighting equations.
 *   
 *   See the "Field Reference - SFImage" specification for details on how to specify
 *   an image. 
 *   
 *   The @B repeatS @b and @B repeatT @b fields specify how the texture wraps in the
 *   S and T directions. If @B repeatS @b is TRUE (the default), the texture map is
 *   repeated outside the 0-to-1 texture coordinate range in the S direction so that
 *   it fills the shape. If @B repeatS @b is FALSE, the texture coordinates are
 *   clamped in the S direction to lie within the 0-to-1 range. The @B repeatT @b
 *   field is analogous to the @B repeatS @b field.
 * 
 * @FILE_FORMAT_DEFAULT
 *    VRMLPixelTexture {
 *    @TABLE_FILE_FORMAT
 *       @TR image     @TD 0 0 0
 *       @TR repeatS   @TD TRUE
 *       @TR repeatT   @TD TRUE
 *       @TR metadata     @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *      SoGLRenderAction,  SoCallbackAction  @BR
 *      Sets: SoTextureImageElement
 * 
 * @EVENTS
 * 
 *    @TABLE_EVENT_IN      
 *       @TR   SoSFImage   @TD   set_image
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 * 
 *    @TABLE_EVENT_OUT      
 *       @TR   SoSFImage   @TD   image_changed
 *       @TR   SoSFNode   @TD   metadata_changed

 *    @TABLE_END
 * 
 * 
 * 
 */ 

class INVENTOR_API SoVRMLPixelTexture : public SoVRMLTexture {

  SO_NODE_HEADER(SoVRMLPixelTexture);

 public:

  /**
   * The texture map.
   * 
   */
  SoSFImage           image;

  /**
   * Constructor.
   */
  SoVRMLPixelTexture();
    
 SoEXTENDER public:

  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();


 protected:
  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool      readInstance(SoInput *in, unsigned short flags);

  virtual ~SoVRMLPixelTexture();

  int             getReadStatus()             { return readStatus; }
  void            setReadStatus(int s)        { readStatus = s; }

 private:
  // These keep the image and filename fields in sync.
  SoFieldSensor *     imageSensor;
  static void         imageChangedCB(void *, SoSensor *);
  SoFieldSensor *repeatSSensor;
  static void repeatChangedCB(void *, SoSensor *);
  SoFieldSensor *repeatTSensor;
   
  int                 readStatus;
    
  // Display list info for this texture:
  SoGLDisplayList *renderList;
  float       renderListQuality;
  SoSFEnum model; 
  SoSFColor blendColor;
};

#endif /* _SO_VRMLPIXEL_TEXTURE_ */

