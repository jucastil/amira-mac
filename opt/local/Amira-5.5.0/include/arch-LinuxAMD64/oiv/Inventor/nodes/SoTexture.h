/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_
#define  _SO_TEXTURE_

#include <Inventor/fields/SoSFVec4f.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFColor.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/sys/SoGLType.h>

class SoFieldSensor;
class SoNodeSensor;
class SbRasterImage;

#ifndef GL_COMBINE
#define GL_COMBINE 0x8570
#endif
#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812D
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#ifndef GL_MIRRORED_REPEAT
#define GL_MIRRORED_REPEAT 0x8370
#endif


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

/** 
* Abstract base class for texture mapping nodes.
* 
* @ingroup TextureNodes
* 
* @DESCRIPTION
* This is the abstract base class for all texture image nodes.
* It defines the common methods and fields that all texture
* image nodes have. When a texture image node is encountered
* during traversal, the associated image and parameters are applied 
* to the current texture unit (see SoTextureUnit) and used to apply
* texture to subsequent shapes.
* 
* @FILE_FORMAT_DEFAULT
*   This is an abstract class. See the reference page of a derived class
*   for the format and default values.
*
* 
* @SEE_ALSO
*    SoComplexity,
*    SoExtTexture2,
*    SoMaterial,
*    SoTexture2,
*    SoTexture2Transform,
*    SoTexture3,
*    SoTextureCombiner,
*    SoTextureCoordinate2,
*    SoTextureCoordinateBinding,
*    SoTextureCoordinateFunction,
*    SoTextureCubeMap,
*    SoTextureUnit
* 
* 
*/ 
  
class INVENTOR_API SoTexture : public SoNode {

  SO_NODE_ABSTRACT_HEADER(SoTexture);

public:
  /**
   * Texture internal storage format. AUTO_INTERNAL_FORMAT (equivalent to RGB_FORMAT) by default.   
   */
  enum InternalFormat {
   /** Default. */
    AUTO_INTERNAL_FORMAT,
    /** ALPHA_FORMAT */
    ALPHA_FORMAT,
    /** ALPHA_FORMAT */
    ALPHA4, 
    /** ALPHA4 */
    ALPHA8,  
    /** ALPHA12 */
    ALPHA12,  
    /** ALPHA16 */
    ALPHA16,  
    /** LUMINANCE_FORMAT */
    LUMINANCE_FORMAT,  
    /** LUMINANCE4 */
    LUMINANCE4,  
    /** LUMINANCE8 */
    LUMINANCE8,  
    /** LUMINANCE12 */
    LUMINANCE12,  
    /** LUMINANCE16 */
    LUMINANCE16,  
    /** LUMINANCE_ALPHA */
    LUMINANCE_ALPHA, 
    /** LUMINANCE4_ALPHA4 */
    LUMINANCE4_ALPHA4,  
    /** LUMINANCE6_ALPHA2 */
    LUMINANCE6_ALPHA2,  
    /** LUMINANCE8_ALPHA8 */
    LUMINANCE8_ALPHA8,  
    /** LUMINANCE12_ALPHA4 */
    LUMINANCE12_ALPHA4, 
    /** LUMINANCE12_ALPHA12 */
    LUMINANCE12_ALPHA12, 
    /** LUMINANCE16_ALPHA16 */
    LUMINANCE16_ALPHA16, 
    /** INTENSITY_FORMAT */
    INTENSITY_FORMAT,  
    /** INTENSITY4 */
    INTENSITY4, 
    /** INTENSITY8 */
    INTENSITY8, 
    /** INTENSITY12 */
    INTENSITY12, 
    /** INTENSITY16 */
    INTENSITY16,  
    /** R3_G3_B2 */
    R3_G3_B2,  
    /** RGB_FORMAT */
    RGB_FORMAT,  
    /** RGB4 */
    RGB4,  
    /** RGB5 */
    RGB5,  
    /** RGB8 */
    RGB8,  
    /** RGB10 */
    RGB10,  
    /** RGB12 */
    RGB12,  
    /** RGB16 */
    RGB16,  
    /** RGBA_FORMAT */
    RGBA_FORMAT,  
    /** RGBA2 */
    RGBA2,  
    /** RGBA4 */
    RGBA4,  
    /** RGB5_ALPHA1 */
    RGB5_ALPHA1,  
    /** RGBA8 */
    RGBA8,  
    /** RGB10_ALPHA2 */
    RGB10_ALPHA2,  
    /** RGBA12 */
    RGBA12,  
    /** RGBA16 */
    RGBA16, 
    /** RGBA_FLOAT32 */
    RGBA_FLOAT32, 
    /** RGB_FLOAT32 */
    RGB_FLOAT32, 
    /** ALPHA_FLOAT32 */
    ALPHA_FLOAT32, 
    /** INTENSITY_FLOAT32 */
    INTENSITY_FLOAT32, 
    /** LUMINANCE_FLOAT32 */
    LUMINANCE_FLOAT32, 
    /** LUMINANCE_ALPHA_FLOAT32 */
    LUMINANCE_ALPHA_FLOAT32, 
    /** RGBA_FLOAT16 */
    RGBA_FLOAT16, 
    /** RGB_FLOAT16 */
    RGB_FLOAT16, 
    /** ALPHA_FLOAT16 */
    ALPHA_FLOAT16, 
    /** INTENSITY_FLOAT16 */
    INTENSITY_FLOAT16, 
    /** LUMINANCE_FLOAT16 */
    LUMINANCE_FLOAT16, 
    /** LUMINANCE_ALPHA_FLOAT16 */
    LUMINANCE_ALPHA_FLOAT16, 
    /** COMPRESSED_ALPHA */
    COMPRESSED_ALPHA, 
    /** COMPRESSED_LUMINANCE */
    COMPRESSED_LUMINANCE,    
    /** COMPRESSED_LUMINANCE_ALPHA */ 
    COMPRESSED_LUMINANCE_ALPHA, 
    /** COMPRESSED_INTENSITY */
    COMPRESSED_INTENSITY, 
    /** COMPRESSED_RGB */
    COMPRESSED_RGB, 
    /** COMPRESSED_RGBA */
    COMPRESSED_RGBA,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_LUMINANCE_LATC1,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_SIGNED_LUMINANCE_LATC1,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_LUMINANCE_ALPHA_LATC2,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_SIGNED_LUMINANCE_ALPHA_LATC2,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_RED_RGTC1,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_SIGNED_RED_RGTC1,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_RED_GREEN_RGTC2,
   /**
    * @ENUM_SINCE_OIV 7.0
    */
    COMPRESSED_SIGNED_RED_GREEN_RGTC2,
   /**
    * @ENUM_SINCE_OIV 9.0
    */
    DEPTH_COMPONENT16,
   /**
    * @ENUM_SINCE_OIV 9.0
    */
    DEPTH_COMPONENT24,
   /**
    * @ENUM_SINCE_OIV 9.0
    */
    DEPTH24_STENCIL8
  };

  /** Texture model */
  enum Model {
   /**
    *  The texture color is multiplied by the surface color. 
    */
    MODULATE = GL_MODULATE,

   /**
    * In this mode, OpenGL requires that the specified texture image have 
    * either 3 or 4 components. 
    * For a 3-component texture, the texture color replaces the surface color.
    * For a 4-component texture, the texture color is blended with the 
    * surface color using the texture alpha value.
    * See OpenGL documentation on glTexEnv for details. 
    * 
    */
    DECAL = GL_DECAL,

   /**
    *  Blends between the surface color and a specified blend color. 
    */
    BLEND = GL_BLEND,

   /**
    *  The texture color replaces the surface color.
    *
    * @ENUM_SINCE_OIV 4.0
    */
    REPLACE = GL_REPLACE,

   /**
    * Adds incoming fragment and texture source colors.
    * 
    * To use this option, you must be using OpenGL 1.3 or higher, or your board must
    * support the OpenGL GL_ARB_texture_env_add extension. Otherwise, GL_MODULATE
    * is used.
    * 
    * @ENUM_SINCE_OIV 5.0
    */
    ADD = GL_ADD,

   /**
    * Provides a wide range of programmable combiner functions using the incoming
    * fragment color, texture source color, texture constant color, and the
    * result of the previous texture environment stage as possible parameters.
    * 
    * To use this option, you must be using OpenGL 1.3 or higher, or your board must
    * support the OpenGL GL_ARB_texture_env_combine extension.
    * 
    * @ENUM_SINCE_OIV 5.0
    */
    COMBINE = GL_COMBINE

  };

  /** Texture wrap type */
  enum Wrap {
   /**
    *  Repeats texture outside 0-1 texture coordinate range. 
    */
    REPEAT = GL_REPEAT,

   /**
    *  Clamps texture coordinates to lie within 0-1 range.
    */
    CLAMP = GL_CLAMP,

   /**
    * Clamps texture coordinates to a range coinciding with the
    * centers of the border texels of a texture map at each mipmap level. @BR
    * 
    * To use this option, you must be using OpenGL 1.3 or higher, or your board must
    * support the OpenGL GL_ARB_texture_border_clamp extension. Otherwise, GL_CLAMP
    * is used.
    * 
    * @ENUM_SINCE_OIV 5.0
    */
    CLAMP_TO_BORDER         = GL_CLAMP_TO_BORDER,

   /**
    * Clamps texture coordinates to a range coinciding with the
    * centers of the edge texels of a texture map at each mipmap level. @BR
    * 
    * To use this option, you must be using OpenGL 1.2 or higher, or your board must
    * support the OpenGL GL_EXT_texture_edge_clamp or GL_SGIS_texture_edge_clamp extension.
    * Otherwise, GL_CLAMP is used.
    * 
    * @ENUM_SINCE_OIV 5.0
    */
    CLAMP_TO_EDGE         = GL_CLAMP_TO_EDGE,

   /**
    * The texture image is repeated in such a way that every odd repetition is a mirror
    * image. @BR
    * 
    * To use this option, you must be using OpenGL 1.4 or higher, or your board must
    * support the OpenGL GL_EXT_texture_mirrored_repeat extension. Otherwise, GL_CLAMP
    * is used.
    * 
    * @ENUM_SINCE_OIV 5.0
    */
    MIRRORED_REPEAT         = GL_MIRRORED_REPEAT

  };

 /**
  * Specifies the OpenGL filtering method for minification and magnification.
  * AUTO is the default value. In this case Open Inventor automatically
  * selects the filtering method depending on SoComplexity::textureQuality.
  */
  enum Filter
  {
    /** AUTO */
    AUTO  = 0,
    /** NEAREST */
    NEAREST = GL_NEAREST,
    /** LINEAR */
    LINEAR = GL_LINEAR,
    /** NEAREST_MIPMAP_NEAREST */
    NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
    /** NEAREST_MIPMAP_LINEAR */
    NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
    /** LINEAR_MIPMAP_NEAREST */
    LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
    /** LINEAR_MIPMAP_LINEAR */
    LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
  } ;
  
 /**
  * 
  */
  enum HW_Feature {  
 /**
   * Check support for non-power-of-2 textures      
   */  
    HW_NPOT = 0,

  /**
   * Check support for floating point texture format
   */  
    HW_FLOATFORMAT,

  /**
   * Check support for depth textures
   */  
    HW_DEPTHFORMAT,

  /**
   * Check support for automatic mipmap generation
   */  
    HW_AUTOMIPMAP,

  /**
   * Check support for texture coordinates border clamp
   */  
    HW_BORDER_CLAMP,

  /**
   * Check support for texture coordinates edge clamp
   */  
    HW_EDGE_CLAMP,

  /**
   * Check support for texture coordinates mirrored repeat
   */  
    HW_MIRRORED_REPEAT,

  /**
   * Check support for DDS support (S3TC)
   */  
    HW_COMPRESSION_S3TC,

  /**
    * Check support for texture_compression_latc
    */
    HW_COMPRESSION_LATC,

  /**
   * Check support for texture_compression_rgtc
   */
   HW_COMPRESSION_RGTC,

#ifndef HIDDEN_FROM_DOC 
    HW_LAST
#endif
  };

  /**
   * Sets OpenGL auto-mipmap generation (if supported).
   * FALSE by default.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFBool useAutoMipmap;

  /**
   * Internal format for texture storage.
   * If not available on the graphics device, internalFormat is set back to AUTO_INTERNAL_FORMAT.
   * Use enum #InternalFormat. Default is AUTO_INTERNAL_FORMAT.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFEnum internalFormat;

 /**
  * 
  * Enables storage of textures on the graphics board in compressed form.
  * The application supplies textures as usual, then OpenGL compresses the
  * textures. 
  * This can reduce usage of texture memory significantly, depending on 
  * the texture image.@BR
  * 
  * To use this option, you must be using OpenGL 1.3 or higher, or your
  * board must support the OpenGL GL_ARB_texture_compression extension.
  *
  * @FIELD_SINCE_OIV 4.0
  */
  SoSFBool enableCompressedTexture;

 /**
  * Indicates what to do when texture coordinates in the S (horizontal) 
  * direction lie outside the range 0-1.
  * Use enum #Wrap. Default is REPEAT.
  */
  SoSFEnum wrapS;

 /**
  * Specifies how to map texture onto surface.
  * Use enum #Model. Default is MODULATE.
  */
  SoSFEnum model;

 /**
  * Color used for BLEND model.
  */
  SoSFColor blendColor;

 /**
  * Enables borders for textures. This means that the 
  * border is already in the texture.
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFBool enableBorder;

 /**
  * Defines border color used for border texture filtering. This
  * value is only used if #enableBorder is FALSE. 
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFVec4f borderColor;

 /**
  * Specifies on a per-texture object basis, the maximum degree of anisotropy
  * to account for in texture filtering. If the specified value is greater than
  * the maximum supported by the graphics board, the value is clamped to
  * GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT.@BR
  * 
  * To use this option, you must be using OpenGL 1.1 or higher, or your
  * board must support the OpenGL GL_EXT_filter_anisotropic extension.
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFFloat maxAnisotropy;

 /**
  * Specifies the OpenGL minFilter.
  * Use enum #Filter. Default is AUTO.
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFEnum minFilter;

 /**
  * Specifies the OpenGL magFilter. 
  * Use enum #Filter. Default is AUTO. Only the following
  * Filter values are valid: AUTO, NEAREST, and LINEAR. 
  *
  * @FIELD_SINCE_OIV 5.0
  */
  SoSFEnum magFilter;

  /** File Type possible values. */
  // Adding entry to this struct also means that we update 
  // SoImage and SoVrmlImageTexture.
  enum FileType
  {
    /** Unknown file */
    UNKNOWN,
    /** RGB */
    RGB,
    /** SGI */
    SGI,
    /** TIFF */
    TIFF,
    /** GIF */
    GIF,
    /** JPEG */
    JPEG,
    /** BMP */
    BMP,
    /** PNG */
    PNG,
    /** JPEG2000 */ 
    JPEG2000,
    /** PGX */
    PGX,
    /** PNM */
    PNM,
    /** RAS */
    RAS,
    /** DDS */
    DDS,
    /** HDRI */
    HDRI,
    /** NUM_FILETYPES */
    NUM_FILETYPES
  };

 /**
  * Sets the texture file format. Default is UNKNOWN. If file type is set to
  * UNKNOWN, Open Inventor tries to determine the file type from the file name
  * extension (e.g., @B foo@b.@B gif @b implies a GIF file). If the set or
  * determined file type is not UNKNOWN, Open Inventor attempts to read the file as
  * that format. If this fails, Open Inventor will try reading the file as each
  * possible format in turn. It is not necessary to set the file type if the image
  * file has the standard file name extension.
  */
  void setBitmapFileType(FileType in_type);

 /**
  * Gets the texture file format.
  */
  FileType getBitmapFileType(void) { return (m_filetype); }

 /**
  * Returns information about hardware support for various texture
  * features.
  */
  static SbBool isSupported(HW_Feature feature);

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
  virtual void        doAction(SoAction *action)=0;
  virtual void        GLRender(SoGLRenderAction *action)=0;
  virtual void        callback(SoCallbackAction *action);

SoINTERNAL public:
  static void initClass();
  static void exitClass();

  SoSFBool override;

  static SoTexture::InternalFormat getInternalFormatFromDataType(SoState* state, SoSFImage::DataType dataType, int nc, float quality = 1.0, SbBool enableCompressedTexture = FALSE);

  // This funtion describe the specified internal format.
  // If nc is not NULL it will receive the number of components for the returned format
  // If dataType is not NULL it will receive the type of the compenents for the returned format
  static GLenum describeInternalFormat(SoState*state, SoTexture::InternalFormat texInternalFormat, int* nc = NULL, SbDataType* componentType = NULL);

  static bool isClampToEdgeAvailable(SoState* state);

    /**
   * Check the file file type and returns its type from the FilType enum.
   * If it is not able to figure out the format it returns UNKNOWN.
   */
  static FileType checkFileType( const SbString& filename );

  /** 
   * This function reads a texture file to a SbRasterImage.
   */
  static SbRasterImage* readTexture( const SbString& filename, FileType filetype = UNKNOWN );

  /** 
   * This function reads one or more texture files to one or more SbRasterImage.
   * If the splitCubeMaps parameter is set to true and a cubemap is detected then
   * the function will return 6 rasters for this file.
   */
  static std::vector< SbRasterImage* > readTextures( const std::vector< SbString >& filenames, bool splitCubeMaps, FileType filetype = UNKNOWN );

  /**
   * Returns TRUE if texture object is supported.
   */
  static bool isTextureObjectSupported( SoState* state );

  /**
   * Returns TRUE if float texture format is supported.
   */
  static bool isTextureFloatSupported( SoState* state );

  /**
   * Returns TRUE if compressed texture format is supported.
   */
  static bool isTextureCompressionSupported( SoState* state);

  /**
   * Returns TRUE if depth texture format are supported.
   */
  static bool isTextureDepthSupported( SoState* state);

  /**
   * Returns TRUE if paletted texture is supported.
   */
  static bool isPalettedTextureSupported( SoState* state);

  /**
   * Returns TRUE if shared texture palette is supported.
   */
  static bool isSharedTexturePaletteSupported( SoState* state);



protected:

  SoTexture();

  virtual ~SoTexture();

  int getReadStatus() { return m_readStatus; }
  void setReadStatus(int s) { m_readStatus = s; }

  SoFieldSensor *wrapSSensor;
  SoFieldSensor *maxAnisotropySensor;

  bool bFieldChanging;  // to protect from fieldHasChanged rentrance


  /**
  * [OIV-WRAPPER-ARG POINTER_VALUE,IN]
  */

  /**
   * Returns the suffix for the specified FileType.
   */
  static SbString getFileTypeSuffix( FileType type );

  FileType m_filetype;
  SbBool m_userfileType;

  GLenum getGLInternalFormat(SoSFImage& image, float quality = 1.0);
  

  static SbVec4i32 selectGCParams(InternalFormat intFmt);  

  static void convertHDRI_RGBE_TO_FLOAT32(SbRasterImage* rasterIn, float* floatOut, float exposureFactor);
  static void convertHDRI_FLOAT32_TO_UCHAR(float* fcol, unsigned char* outBuff, int width, int height);
  static void convertHDRI_FLOAT32_TO_UCHAR( SoSFImage* );

private:

  static SbRasterImage* readTextureDataFromFile( const SbString& filename, FileType filetype );

  static std::vector< SbRasterImage* > splitRasterImage( SbRasterImage* sourceImage );

  static void readImageSection( unsigned char* input, int inputWidth, 
                      int xOffset, int yOffset, int width, int height, 
                      int elementSize, unsigned char* output, bool invertAndMirror);

  int m_readStatus;

  static SbBool m_featuresInitialized;
  static SbBool m_features[HW_LAST];
  static bool s_ivNoTextureObject;
  static int s_texture_object_extensionID;
  static int s_clamp_to_edge_EXT_extensionID;
  static int s_clamp_to_edge_SGIS_extensionID;
  static int s_texture_float_extensionID;
  static int s_texture_compression_extensionID;
  static int s_detph_texture_ARB_extensionID;
  static int s_paletted_texture_extensionID;
  static int s_shared_texture_palette_extensionID;

};

#endif /* _SO_TEXTURE_ */

