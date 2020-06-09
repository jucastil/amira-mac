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


#ifndef  _SO_TEXTURE_2_
#define  _SO_TEXTURE_2_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/image/SbRasterImage.h>

#include <Inventor/sys/SoGLType.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoGLTexCacheList.h>

class SoSensor;
class SbThreadRWMutex;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTexture2
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

class SoTexture2;
typedef SbBool PrequalifyFileCallback(const SbString &, void *, SoTexture2 *);

/** 
 * 2D texture mapping node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This property node defines a texture map and parameters for that map. 
 *   This map applies to the current texture unit (see SoTextureUnit) and
 *   is used to apply texture to subsequent shapes as they are rendered.
 *   
 *   The texture can be read from the file specified by the #filename field.
 *   
 *   If you want to postpone the texture loading, set the #loadingMode field to #MANUAL 
 *   before setting the #filename field.
 *   In this case, you must call #loadTexture() to load and display the texture.
 * 
 *   Once the texture has been read, the #image field contains the texture
 *   data. However, this field is marked so the image is not written out when the
 *   texture node is written to a file. To turn off texturing, set the
 *   #filename field to an empty string ("").
 *   
 *   DDS format files load faster because the compressed image 
 *   can be sent directly to the graphics hardware. 
 *   This format can also embed mipmaps (levels of resolution).
 *   Note that the #image field is not filled with the image data when using DDS files.
 *   DDS format is not supported on all hardware. The GL_EXT_texture_compression_s3tc
 *   extension is required. If it is not available, the DDS texture is not loaded.
 *
 *   Textures can also be specified in memory by setting the #image field to
 *   contain the texture data. Doing so resets the #filename to the empty
 *   string.
 *
 *   Textures can also be rendered from a scene graph using the #renderToTextureProperty field.
 *   If a value is specified for this field, the #image and #filename fields are
 *   ignored. 
 *
 *   You can modify a subset of the image without causing the OpenGL texture to be
 *   recreated. Open Inventor will automatically use @B glTexSubImage2D @b if the
 *   image is modified using the SoSFImage::setSubValue() method. This is much
 *   more efficient than using the @B startEditing @b and @B finishEditing @b
 *   methods because when these methods are used Open Inventor must assume that the
 *   entire image has been modified.
 *
 *   If the texture image's width or height is not a power of 2, and the 
 *   Non Power Of Two (NPOT) extension is available on your graphics board, by default Open Inventor
 *   will send the image to OpenGL without modification. However,
 *   if the texture image's width or height is not a power of 2 (and 
 *   the Non Power Of Two (NPOT) extension is not available on your graphics board),
 *   or the image's width
 *   or height is greater than the maximum supported by OpenGL, then the image will
 *   be automatically scaled up or down to the nearest power of 2 or the maximum texture
 *   size. 
 *   For maximum speed, point-sampling is used to do the scaling. If you want
 *   higher quality scaling, pre-filter your images to a power of 2 smaller than the
 *   maximum texture size. Use the OpenGL glGetIntegerv(GL_MAX_TEXTURE_SIZE...) call
 *   to determine the maximum texture dimension for a specific OpenGL implementation.
 *   Setting the environment variable OIV_USE_NPOT to 0 will force the image to 
 *   be rescaled (when necessary) even if the NPOT extension is available.
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
 *  traversed for rendering. For large images, or a large
 *  number of images, this can make the application seem slow
 *  while starting up or loading a new data file. Avoid this
 *  effect by either pre-scaling the image or by storing it
 *  as a sub-image in a "power of 2" image (then provide explicit
 *  texture coordinates such that only the sub-image is used).
 *  
 *  @B Performance Note@b: The performance advantage of modifying
 *  a sub-image is significantly less when the texture image
 *  needs to be automatically scaled to a power of 2. 
 *  This is because each
 *  sub-image must be scaled before sending it to OpenGL.
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
 * @FILE_FORMAT_DEFAULT
 *    Texture2 {
 *    @TABLE_FILE_FORMAT
 *       @TR filename                 @TD ""
 *       @TR image                    @TD 0 0 0
 *       @TR wrapS                    @TD REPEAT
 *       @TR wrapT                    @TD REPEAT
 *       @TR model                    @TD MODULATE
 *       @TR enableCompressedTexture  @TD FALSE
 *       @TR blendColor               @TD 0 0 0
 *       @TR enableBorder             @TD FALSE
 *       @TR borderColor              @TD 0 0 0 1
 *       @TR maxAnisotropy            @TD 1.0
 *       @TR minFilter                @TD AUTO
 *       @TR magFilter                @TD AUTO
 *       @TR loadingMode              @TD AUTO
 *       @TR useAutoMipmap            @TD FALSE
 *       @TR internalFormat           @TD AUTO_INTERNAL_FORMAT
 *       @TR renderToTextureProperty  @TD NULL
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction @BR
 *        Sets current texture in state.
 *        Sets: SoTextureImageElement, SoGLTextureEnabledElement
 * 
 * @SEE_ALSO
 *    SoComplexity,
 *    SoExtTexture2,
 *    SoMaterial,
 *    SoTexture,
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

class INVENTOR_API SoTexture2 : public SoTexture {

  SO_NODE_HEADER(SoTexture2);

 public:

   /** 
    * [OIV-WRAPPER NAME{LoadingCallback}] 
    */
  typedef void SoTexture2CB(void *userData, SoTexture2 *tex);

  /** Loading mode */
  enum Loading {
    /**
    * The texture is loaded when #filename field is set.
    */
    AUTO = 0,

    /**
    * The texture is loaded when the #loadTexture method is called.
    */
    MANUAL
  };
 
  /**
   * Name of the file from which to read texture image. @BR The standard image file formats 
   * are supported. See SoRasterImageRW for the list. If the
   * filename is not an absolute path name, the list of directories maintained by
   * SoInput is searched. If the texture is not found in any of those directories,
   * then the file is searched for relative to the directory from which the
   * SoTexture2 node was read. For example, if an SoTexture2 node with a filename of
   * "../tofu.rgb" is read from /usr/people/bob/models/food.iv, then
   * /usr/people/bob/tofu.rgb will be read (assuming tofu.rgb isn't found in the
   * directories maintained by SoInput).
   * 
   */
  SoSFFilePathString filename;

  /**
   * Contains an in-memory representation of the texture map. It is either the
   * contents of the file read from #filename, an image read directly from an
   * Open Inventor file, or an image set programmatically using the methods provided
   * by SoSFImage.
   * 
   */
  SoSFImage image;

  /**
   * Indicates what to do when texture coordinates in the T
   * (vertical) direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap. Default is REPEAT.
   */
  SoSFEnum wrapT;

  /** 
   * Specifies the loading mode. 
   * Use enum #Loading. Default is AUTO.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFEnum loadingMode;


  /**
   * Specifies an SoRenderToTextureProperty node containing a scene graph that 
   * will be rendered to create the texture image.
   * Null by default.
   *
   * NOTE: The #image field is not updated when the scene graph is rendered.
   * That would require reading back the frame buffer from the graphics
   * board, which can be time consuming and would reduce performance. 
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFNode renderToTextureProperty;

  /**
   * 
   * Callback invoked when starting to load the texture.
   */
  void setStartLoadingCallback(SoTexture2CB* cb, void* userData);
  
  /**
   * 
   * Callback invoked when the texture is loaded and ready to use.
   */
  void setFinishLoadingCallback(SoTexture2CB* cb, void* userData);

  // Manual loading
  
  #ifdef OIV_NET_DOC
/**
   * 
   * Loads the texture if the #loadingMode field is set to MANUAL.
   */
 #else
  /**
   * 
   * Loads the texture if the #loadingMode field is set to MANUAL.
   * A typical use is:
   * <PRE> 
   *   texture = new SoTexture2();
   *   texture->loadingMode.setValue(SoTexture2::MANUAL);
   *   texture->filename = "texture.png";
   *   root->addChild(texture);
   *
   * ,..
   *
   *   static void* 
   *   threadRoutine( void* userData ) 
   *   {
   *     SbThread::setPriorityLevel(1);
   *     SoDB::threadInit();
   *     texture->loadTexture();
   *     return 0;
   *   }
   *
   * ,..
   *
   *   SbThread::create(threadRoutine, NULL);
   * </PRE>
   */
#endif
  void loadTexture();

  /**
   * Creates a texture node with default settings.
   */
  SoTexture2();
  
 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        doActionOnRTT(SoAction *action);

  static void setPrequalifyFileCallBack(PrequalifyFileCallback *p_cb, void *u_data);
  static PrequalifyFileCallback *getPrequalifyFileCallBack( void *&user_data );
  void allowPrequalifyFile(SbBool);
  SbBool isAllowPrequalifyFile() const;


 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  const SbString &getOverrideURL() { return overrideURL; }
  void setOverrideURL(const SbString &path) { overrideURL = path; }
  
  // provided only to manage SoRenderToTexture node changes !! 
  virtual void notify(SoNotList *list); // override

  // Manages field dependencies, when one of them change
  virtual void fieldHasChanged( SoField *field ); // override of SoFieldContainer
   
  // Read libimage-format file
  SbBool readImage(SoTexture2* tex);

  void setIsTextureLoaded(SbBool isTextureLoaded) { m_isTextureLoaded = isTextureLoaded; }

  SoGLDisplayList* getDisplayList(SoState* state, float quality);

 protected:
  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  virtual ~SoTexture2();

  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);

  /** This function converts the texture in FLOAT to UNSIGNED_BYTE  
    * if the float textures ext is not available 
    */
  void checkTexturesFormat( SoState* state );

 private:
  SbString overrideURL;

  static PrequalifyFileCallback *prequalifyFileCB;
  static void *prequalifyFileCB_udata;
  SbBool prequalifyFileFlag;

  // These keep the image and filename fields in sync.  
  void image_HasChanged(void);  
  void filename_HasChanged(void);
  void wrapS_HasChanged(void);  
  void wrapT_HasChanged(void);
  void renderToTextureProperty_HasChanged(void);
  void maxAnisotropy_HasChanged(void);
  void useAutoMipmap_HasChanged(void);
  void internalFormat_HasChanged(void);

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;

  SbThreadRWMutex  *m_mutex;



  void setTrueInternalFormat();
  InternalFormat m_trueInternalFormat;

  SbRasterImage* m_compressedImage;

  // Load callbacks attributes
  SoTexture2CB *m_loadStartCB;
  SoTexture2CB *m_loadFinishCB;

  void *m_loadStartCBData;
  void *m_loadFinishCBData;

  // Tells if the texture is loaded or not (not necessarily displayed)
  SbBool m_isTextureLoaded;
  SbBool m_isTextureRGBE;

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_TEXTURE_2_ */
