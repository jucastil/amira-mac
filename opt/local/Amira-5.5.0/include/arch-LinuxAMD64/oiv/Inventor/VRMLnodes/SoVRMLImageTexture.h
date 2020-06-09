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

#ifndef  _SO_VRMLIMAGE_TEXTURE_
#define  _SO_VRMLIMAGE_TEXTURE_

#include <Inventor/VRMLnodes/SoVRMLTexture.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoMFString.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/image/SbRasterImage.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/threads/SbThreadStorage.h>

class SoSensor;
class SoFieldSensor;
class SbThreadRWMutex;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

class SoVRMLImageTexture;
/** 
 * [OIV-WRAPPER NAME{ImagePrequalifyFileCallback}] 
 */
typedef SbBool VRMLPrequalifyFileCallback(const SbString &, void *, SoVRMLImageTexture *);

/**
 * @VSGEXT Texture map node.
 *
 * @ingroup VRML2
 *
 * @DESCRIPTION
 *   The SoVRMLImageTexture node defines a texture map by specifying an image file
 *   and general parameters for mapping to geometry. Texture maps are defined in a 2D
 *   coordinate system, (s,t), that ranges from 0.0 to 1.0 in both directions. The
 *   bottom edge of the image corresponds to the S-axis of the texture map, and left
 *   edge of the image corresponds to the T-axis of the texture map. The lower-left
 *   pixel of the image corresponds to s=0, t=0, and the top-right pixel of the image
 *   corresponds to s=1, t=1.
 *
 *   Texture images may be one component (grayscale), two component (grayscale plus
 *   transparency), three component (full RGB color), or four-component (full RGB
 *   color plus transparency).
 *
 *   The @B repeatS @b and @B repeatT @b fields specify how the texture wraps in the
 *   S and T directions. If @B repeatS @b is TRUE (the default), the texture map is
 *   repeated outside the 0-to-1 texture coordinate range in the S direction so that
 *   it fills the shape. If @B repeatS @b is FALSE, the texture coordinates are
 *   clamped in the S direction to lie within the 0-to-1 range. The @B repeatT @b
 *   field is analogous to the @B repeatS @b field.
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
 *   Open Inventor can read GIF, JPEG, PNG, RGB (native Silicon Graphics format),
 *   TIFF, and BMP texture files.
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
 *   The SoVRMLImageTexture node defines a texture map by specifying an image file and
 *   general parameters for mapping to geometry. Texture maps are defined in a 2D
 *   coordinate system, (s,t), that ranges from 0.0 to 1.0 in both directions. The
 *   bottom edge of the image corresponds to the S-axis of the texture map, and left
 *   edge of the image corresponds to the T-axis of the texture map. The lower-left
 *   pixel of the image corresponds to s=0, t=0, and the top-right pixel of the image
 *   corresponds to s=1, t=1.
 *
 *   @IMAGE imagets.gif
 *
 *   The texture is read from the URL specified by the #url field. To turn off
 *   texturing, set the #url field to have no values ([]). Browsers are
 *   required to support the JPEG and PNG image file formats, and in addition, may
 *   support any other image formats. Support for the GIF format including
 *   transparent backgrounds is also recommended. See the section "Concepts - URLS
 *   and URNs" for details on the #url field.
 *
 *   Texture images may be one component (grayscale), two component (grayscale plus
 *   transparency), three component (full RGB color), or four-component (full RGB
 *   color plus transparency). An ideal VRML implementation will use the texture
 *   image to modify the diffuse color and transparency of an object's material
 *   (specified in an SoVRMLMaterial node), then perform any lighting calculations
 *   using the rest of the object's material properties with the modified diffuse
 *   color to produce the final image. The texture image modifies the diffuse color
 *   and transparency depending on how many components are in the image, as follows:
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
 *   See "Concepts - Lighting Model" for details on lighting equations and the
 *   interaction between textures, materials, and geometries.
 *
 *   Browsers may approximate this ideal behavior to increase performance. One common
 *   optimization is to calculate lighting only at each vertex and combining the
 *   texture image with the color computed from lighting (performing the texturing
 *   after lighting). Another common optimization is to perform no lighting
 *   calculations at all when texturing is enabled, displaying only the colors of the
 *   texture image.
 *
 *   The @B repeatS @b and @B repeatT @b fields specify how the texture wraps in the
 *   S and T directions. If @B repeatS @b is TRUE (the default), the texture map is
 *   repeated outside the 0-to-1 texture coordinate range in the S direction so that
 *   it fills the shape. If @B repeatS @b is FALSE, the texture coordinates are
 *   clamped in the S direction to lie within the 0-to-1 range. The @B repeatT @b
 *   field is analogous to the @B repeatS @b field.
 *
 *
 * @FILE_FORMAT_DEFAULT
 *    VRMLImageTexture {
 *    @TABLE_FILE_FORMAT
 *       @TR url       @TD []
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
 *       @TR   SoMFString   @TD   set_url
 *       @TR   SoSFNode   @TD   set_metadata
 *    @TABLE_END
 *
 *    @TABLE_EVENT_OUT
 *       @TR   SoMFString   @TD   url_changed
 *       @TR   SoSFNode   @TD   metadata_changed
 *    @TABLE_END
 *
 *
 *
 */

class INVENTOR_API SoVRMLImageTexture : public SoVRMLTexture {

  SO_NODE_HEADER(SoVRMLImageTexture);

 public:
  /**
   * Filename (or URL) from which to read the texture image. Note: Open Inventor only
   * tries to open the first URL in the field.
   *
   */
  SoMFFilePathString url;

  /**
   * Constructor.
   */
  SoVRMLImageTexture();

  /**
   * Specifies the application callback that will be invoked when the ImageTexture
   * node is about to read an image file (if the prequalify flag is TRUE).
   */
  static void setPrequalifyFileCallBack(VRMLPrequalifyFileCallback *, void *);
  /**
   * Sets the prequalify file flag. If FALSE, the prequalification \oivnetdoc delegate \else callback \endoivnetdoc will not
   * be called. Default is TRUE.
   */
  void allowPrequalifyFile(SbBool);

    /** FileType */
  enum FileType {
    /** UNKNOWN */
    UNKNOWN = SoTexture::UNKNOWN,
    /** RGB */
    RGB = SoTexture::RGB,
    /** SGI */
    SGI = SoTexture::SGI,
    /** TIFF */
    TIFF = SoTexture::TIFF,
    /** GIF */
    GIF = SoTexture::GIF,
    /** JPEG */
    JPEG = SoTexture::JPEG,
    /** BMP */
    BMP = SoTexture::BMP,
    /** PNG */
    PNG = SoTexture::PNG,
    /** JPEG2000 */
    JPEG2000 = SoTexture::JPEG2000,
    /** PGX */
    PGX = SoTexture::PGX,
    /** PNM */
    PNM = SoTexture::PNM,
    /** RAS */
    RAS = SoTexture::RAS,
    /** DDS (DirectDraw Surface) */
    DDS = SoTexture::DDS,
    /** HDRi (High Dynamic Range image) */
    HDRI = SoTexture::HDRI,
    /** NUM_FILETYPES */
    NUM_FILETYPES };

  void setBitmapFileType(FileType in_type) { m_filetype = in_type; }
  FileType getBitmapFileType(void) { return (m_filetype); }
  /**
   * Query the image.
   * [OIV-WRAPPER-RETURN-TYPE NAME{buffer},ARRAY{size.Value[0]*size.Value[1]*numcomp}]
   * [OIVJAVA-WRAPPER PACK{TextureImage}]
   */
  const unsigned char *  getImage(SbVec2s &size, int &numcomp);

 SoEXTENDER public:

  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void callback(SoCallbackAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();
  const SbString & getOverrideURL() { return overrideURL; }
  void setOverrideURL(const SbString &path) { overrideURL = path; }

  //If SoPreference OIV_VRML_IMAGETEXTURE_MODEL_SUPPORT environment variable is set (TRUE by default),
  // textureModel will be used as is( GL_MODULATE by default)
  //Otherwise, the VRML2 specs will be respected, and textureModel will be GL_MODULATE for grayscale images, GL_REPLACE for all others.
  //Enum values are : GL_MODULATE, GL_DECAL, GL_BLEND, GL_REPLACE, GL_ADD, GL_COMBINE
  SoSFEnum textureModel;

 protected:
  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  virtual ~SoVRMLImageTexture();

  //Check the textureModel field
  void checkTextureModel( int numComponents );

  int getReadStatus() { return readStatus; }
  void setReadStatus(int s) { readStatus = s; }

  // Read libimage-format file
  virtual void copyContents(const SoFieldContainer *fromFC,
                            SbBool copyConnections);

 private:
  // These keep the image and filename fields in sync.
  SbString overrideURL;
  SoFieldSensor *imageSensor;
  static void imageChangedCB(void *, SoSensor *);
  SoFieldSensor *filenameSensor;
  static void filenameChangedCB(void *, SoSensor *);
  SoFieldSensor *repeatSSensor;
  static void repeatChangedCB(void *, SoSensor *);
  SoFieldSensor *repeatTSensor;

  int readStatus;

  static VRMLPrequalifyFileCallback *prequalifyFileCB;
  static void *prequalifyFileCB_udata;

  SbBool prequalifyFileFlag;

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;

  SbThreadRWMutex  *m_mutex;

  // Hidden fields

  SoMFString model;
  SoSFColor blendColor;
  SoSFImage image;

  FileType m_filetype;

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_VRMLIMAGE_TEXTURE_ */

