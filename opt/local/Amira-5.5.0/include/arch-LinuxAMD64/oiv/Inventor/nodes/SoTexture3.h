/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_TEXTURE_3_
#define  _SO_TEXTURE_3_

#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage3.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/image/SbRasterImage.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/sys/SoGLType.h>
#include <Inventor/threads/SbThreadStorage.h>

class SoSensor;
class SbThreadRWMutex;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture3
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * @VSGEXT 3D texture mapping node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This property node defines a 3D texture map and parameters for that map. This
 *   map is used to apply a 3D texture to subsequent shapes as they are rendered.
 *   
 *   The texture can be read from the file(s) specified by the #filenames field.
 *   Once the texture has been read, the #images field contains the texture
 *   data. However, this field is marked so the image is not written out when the
 *   texture node is written to a file. To turn off texturing, set the first value of
 *   the #filenames field to an empty string ("").
 *   
 *   Textures can also be specified in memory by setting the #images field to
 *   contain the texture data. Doing so resets the #filenames field to the
 *   empty string.
 *   
 *   Simply put, a 3D texture is a set of well-arranged 2D textures. Typically, 3D
 *   textures represent a set of image-slices of a given volume of data, and are used
 *   for mapping onto pieces of geometry. Note that this is different from direct
 *   volume rendering in that 3D textures need to be mapped onto a piece of
 *   geometry.
 *   
 *   OpenGL requires all images in a 3D texture to have the same dimensions, and each
 *   dimension (X, Y, and Z) needs to be a power of 2. Also, images must have the
 *   same number of components (grayscale, grayscale with transparency, RGB, or RGB
 *   with transparency).
 *   
 *   - Images that do not have the same number of components as the first image are
 *   recomputed to have the same number of components. At best, there is no loss of
 *   quality. At worst, the recomputed images may lose colors and/or transparency. 
 *   
 *   - If the 2D texture image's width or height is greater than the maximum supported
 *   by OpenGL, then the image will be clipped at the maximum texture size. 
 *   
 *   - If one or more of the dimensions is not a power of 2, the texture is enlarged
 *   (it is never shrunk) to fit the power-of-2 requirement. Note that, unlike 2D
 *   textures where a resized texture is actually rescaled, the 3D image is @I not
 *   rescaled@i. Instead, black pixels are added to the edge of the image.
 *   @P
 *   You should take this into account when setting texture coordinates. If your 3D
 *   image is not correctly dimensioned, you may want to consider either applying a
 *   ratio to your coordinates or adding an SoTexture3Transform node with the field
 *   scaleFactor set to compensate.
 *   
 *   - Images that have a different size from the first image are resized (clipped or
 *   augmented) to match the size of the first image (which itself may have been
 *   resized to satisfy the size requirements of OpenGL).
 *   
 *   - If the number of images (the depth of the 3D texture) is not a power of 2, an
 *   error is issued and the nearest power of 2 is chosen. If it is lower, some
 *   images are discarded; if it is higher, new images are created and filled with
 *   zeros.
 *   
 *   The quality of the texturing is affected by the @B textureQuality @b field of
 *   the SoComplexity node. The @B textureQuality @b field affects what kind of
 *   filtering is done to the texture when it must be minified or magnified. The
 *   mapping of a particular texture quality value to a particular OpenGL filtering
 *   technique is implementation dependent, and varies based on the texturing
 *   performance. If mipmap filtering is required, mipmaps are automatically created
 *   using the simple box filter.
 *
 *   Transparency
 *   Texture images can contain transparency (alpha values less than 1) and
 *   modify the transparency of geometry in the scene.  But transparent geometry 
 *   will not render correctly in the default transparency mode (SCREEN_DOOR).
 *   Set the transparency mode to a non-default value, for example DELAYED_BLEND,
 *   using the setTransparencyType method in the Viewer class or using an
 *   SoTransparencyType node.  Also note that some image file formats, for
 *   example JPEG, do not support transparency information (alpha channel).
 *
 * @B LIMITATIONS @b
 *
 *   3D textures are only supported by the following shapes:
 *     - SoIndexedFaceSet
 *     - SoIndexedQuadMesh
 *     - SoIndexedTriangleStripSet
 *     - SoFaceSet
 *     - SoQuadMesh
 *     - SoTriangleStripSet
 *    
 *   Only SoIndexedFaceSet shapes automatically compute texture coordinates if they are 
 *   not specified either by a texture coordinate function (see SoTextureCoordinateFunction)
 *   or by explicit texture coordinates (see SoTextureCoordinate3).
 *  
 * @FILE_FORMAT_DEFAULT
 *    Texture3 {
 *    @TABLE_FILE_FORMAT
 *       @TR filenames                @TD ""
 *       @TR enableCompressedTexture  @TD FALSE
 *       @TR images                   @TD 0 0 0 0
 *       @TR wrapS                    @TD REPEAT
 *       @TR wrapT                    @TD REPEAT
 *       @TR wrapR                    @TD REPEAT
 *       @TR model                    @TD MODULATE
 *       @TR blendColor               @TD 0 0 0
 *       @TR enableBorder             @TD FALSE
 *       @TR borderColor              @TD 0 0 0 1
 *       @TR maxAnisotropy            @TD 1.0
 *       @TR minFilter                @TD AUTO
 *       @TR magFilter                @TD AUTO
 *       @TR useAutoMipmap            @TD FALSE
 *       @TR internalFormat           @TD AUTO_INTERNAL_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets current texture in state.
 *        Sets: SoTextureImage3Element, SoGLTexture3EnabledElement
 * 
 * @SEE_ALSO
 *    SoComplexity,
 *    SoMaterial,
 *    SoTextureCoordinate3,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction
 * 
 * 
 */ 

class INVENTOR_API SoTexture3 : public SoTexture {

  SO_NODE_HEADER(SoTexture3);

public:

  /**
   * Names of file(s) from which to read texture image(s).  @BR
   * The standard image file formats are
   * supported. See SoRasterImageRW for the list. If the
   * filename is not an absolute path name, the list of directories maintained by
   * SoInput is searched. If the texture is not found in any of those directories,
   * then the file is searched for relative to the directory from which the
   * SoTexture3 node was read. For example, if an SoTexture3 node with a filename of
   * "../tofu.rgb" is read from /usr/people/bob/models/food.iv, then
   * /usr/people/bob/tofu.rgb will be read (assuming tofu.rgb isn't found in the
   * directories maintained by SoInput).
   * 
   * All images must have the same dimensions and number of components. Depth (number
   * of slices) is determined by the number of file names.
   * 
   * Note that only 2D image file formats are currently supported. A 3D texture image
   * can be read as a series of 2D image files.
   * 
   */
  SoMFFilePathString  filenames;

  /**
   * Contains an in-memory representation of the texture map. It is either the
   * contents of the file(s) read from #filenames, an image read directly from
   * an Open Inventor file, or an image set programmatically using the methods
   * provided by SoSFImage3.
   * 
   */
  SoSFImage3          images;

  /**
   * Indicates what to do when texture coordinates in the
   * T (vertical) direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap. Default is REPEAT.
   */
  SoSFEnum            wrapT;
  /**
   * Indicates what to do when texture coordinates in the R (depth)
   * direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap.  Default is REPEAT.
   */
  SoSFEnum            wrapR;

  /**
   * Creates a texture node with default settings.
   */
  SoTexture3();

 SoEXTENDER public:
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Manages field dependencies, when one of them change
  virtual void fieldHasChanged( SoField *field ); // override of SoFieldContainer

protected:
  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  virtual ~SoTexture3();

private:
  static void reformatImage(unsigned char * &bytes, int w, int h, int nc, int newNC);

  // These keep the image and filename fields in sync.
  void image_HasChanged(void);
  void filenames_HasChanged(void);
  void wrapS_HasChanged(void);
  void wrapT_HasChanged(void);
  void wrapR_HasChanged(void);
  void maxAnisotropy_HasChanged(void);

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;

  int m_numRenderCaches;

  // A mutex to protect the accesses to the renderList :
  // a problem occured when a system can't share display lists.
  SbThreadRWMutex* m_mutex;

};

#endif /* _SO_TEXTURE_3_ */

