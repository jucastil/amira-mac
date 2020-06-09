/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Oct 2000)
**=======================================================================*/

#ifndef _SO_EXTTEXTURE_2_
#define _SO_EXTTEXTURE_2_

#include <Inventor/nodes/SoTexture.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoGLTexCacheList.h>

#include <Inventor/image/SbRasterImage.h>
#include <Inventor/sys/SoGLType.h>

class SoSensor;
class SoDither;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoExtTexture2
//
//  Extented 2D Texture node.
//
//////////////////////////////////////////////////////////////////////////////

class SoExtTexture2;
/** 
 * [OIV-WRAPPER NAME{PrequalifyFileCB}] 
 */
typedef SbBool ExtPrequalifyFileCallback(const SbString &, void *, SoExtTexture2 *);

/**
 * @VSGEXT Extended texture mapping node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This property node defines a texture map and parameters for that map. This map
 *   is used to apply texture to subsequent shapes as they are rendered.
 *   
 *   The node is similar to SoTexture2, but differs in the following significant
 *   ways:
 *   
 *   1. It has no @B image @b field.
 *   
 *   2. It doesn't load the texture image into @I system @i memory until the node is
 *   traversed. Depending on the scene graph, this may significantly reduce the use
 *   of system memory, e.g., if the scene has lots of LODs containing textures. On
 *   the other hand, when the scene graph is first traversed there may be a small
 *   delay while the textures are being loaded.
 *   
 *   3. It has additional features (e.g., support for OpenGL paletted textures) for
 *   reducing the use of @I texture @i memory.
 *   
 *   The texture is read from the file specified by the #filename field. There
 *   is no image field created. Data is sent directly to OpenGL. 
 *   
 *   The maximum system memory allowed for all SoExtTexture2 nodes (in total) can be
 *   set using setMemorySpace().
 *   
 *   If the memory allowed for texture images (setMemorySpace()) would be
 *   exceeded by loading a new image, one or more existing images will be deleted
 *   from system memory. In most cases OpenGL texture objects will already have been
 *   created for the deleted images (i.e. OpenGL has a copy of the images), so this
 *   does not affect rendering.
 *   
 *   If it is necessary to recreate an OpenGL texture object and the required texture
 *   image has been deleted from system memory, the node will automatically re-read
 *   the image file. For this reason, applications should be careful not to remove
 *   image files that might be needed during program execution. 
 *   
 *   To reduce the use of texture memory (by approximately a factor of 4), use the
 *   useTexturePalette() method to request the image be converted to a 256-color
 *   paletted image. This feature is available only if the driver supports the
 *   GL_EXT_paletted_texture or GL_EXT_texture_color_table extension.
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
 *   technique is platform dependent, and varies based on the texturing performance.
 *   If mipmap filtering is required, mipmaps are automatically created using a
 *   simple box filter.
 *
 *   @B Performance Note@b: Automatic scaling of texture images
 *   to a power of 2 is
 *   a very convenient feature for prototyping, but it does
 *   take additional time the first time the texture node is
 *   traversed for rendering. For large images, or a large
 *   number of images, this can make the application seem slow
 *   while starting up or loading a new data file. Avoid this
 *   effect by either pre-scaling the image or by storing it
 *   as a sub-image in a "power of 2" image (then provide explicit
 *   texture coordinates such that only the sub-image is used).
 * 
 * @FILE_FORMAT_DEFAULT
 *    ExtTexture2 {
 *    @TABLE_FILE_FORMAT
 *       @TR filename                 @TD ""
 *       @TR enableCompressedTexture  @TD FALSE
 *       @TR wrapS                    @TD REPEAT
 *       @TR wrapT                    @TD REPEAT
 *       @TR model                    @TD MODULATE
 *       @TR blendColor               @TD 0 0 0
 *       @TR loadingStatus            @TD FALSE
 *       @TR syncMode                 @TD SYNCHRONOUS
 *       @TR loadingMode              @TD AUTO
 *       @TR loadingThreadPriorty     @TD 1
 *       @TR enableBorder             @TD FALSE
 *       @TR borderColor              @TD 0 0 0 0
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
 *        Sets: SoTextureImageElement, SoGLExtTextureImageElement, SoGLTextureEnabledElement
 * 
 * @SEE_ALSO
 *    SoTexture2,
 *    SoComplexity,
 *    SoMaterial,
 *    SoTexture2Transform,
 *    SoTextureCoordinate2,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction
 * 
 * 
 */ 

class INVENTOR_API SoExtTexture2 : public SoTexture {
  
  SO_NODE_HEADER(SoExtTexture2);
  
 public:
   /** 
    * [OIV-WRAPPER NAME{Texture2CB}] 
    */
  typedef void SoExtTexture2CB(void *userData, SoExtTexture2 *tex);

  /** Synchrone/asynchrone loading mode */
   enum Sync 
   {
    /**
     * The loading is blocking (no thread launched).
     */
    SYNCHRONOUS = 0,

    /**
     * The loading is non blocking (the loading is done within a thread).
     */
    ASYNCHRONOUS
  };

   /** Loading mode */
  enum Loading {    
    /**
     * The texture is loaded at the node's traversal.
     */
    AUTO = 0,

    /**
     * The texture is loaded by the user using the loadTexture method.
     */
    MANUAL
  };

  /**
   * Names file from which to read texture image. The standard image file formats are
   * supported. See SoRasterImageRW for the list. If the
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
   * Indicates what to do when texture coordinates in the T 
   * (vertical) direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap.  Default is REPEAT.
   */
  SoSFEnum wrapT;

  /**
   * Tells if the texture is loaded or not (not necessarily displayed)
   *
   */
  SoSFBool loadingStatus;

  /**
   * Specifies the synchronous/asynchronous mode.
   * Use enum #Sync. Default is SYNCHRONOUS.
   */
  SoSFEnum syncMode;

  /**
   * Specifies the loading mode.
   * Use enum #Loading. Default is AUTO.
   */
  SoSFEnum loadingMode;

  /**
   * Specifies the priority of the texture loading thread when activated (syncMode = ASYNCHRONOUS).
   * This part uses the SbThread class.
   */
  SoSFInt32 loadingThreadPriority;

  /**
   * Creates a texture node with default settings.
   */
  SoExtTexture2();

  /**
   * This callback is called by SoExtTexture2 nodes just before opening a file
   * with the proposed path. It allows you to modify the path and/or indicate
   * that the texture has already been handled. 
   *
   * You could use the callback, for example, to load an image in a file
   * format that Open Inventor doesn't natively support. The callback could
   * - detect (by examining the path) that the file is of a particular format,
   * - call application-supplied code to read the texture file
   * - set the image into the image field of the texture node
   * - set the flag indicating that the texture has been handled.
   * [OIV-WRAPPER EVENT_NAME{PrequalifyFileCallback}]
   */
  static void setPrequalifyFileCallBack(ExtPrequalifyFileCallback *p_cb, void *u_data);

  /**
   * If TRUE, allows the PrequalifyFile \oivnetdoc delegate \else callback \endoivnetdoc to be called.
   */
  void allowPrequalifyFile(SbBool);
  
  /**
   * Returns the size and the number of components in the image.
   * [OIVJAVA-WRAPPER PACK{ImageSize}]
   */
  void getImageSize(SbVec2s &size, int &nc);
  
  /**
   * Sets the system memory space allowed for the texture images. This value is
   * specified in megabytes (MB). The default is 16 MB.
   */
  static void setMemorySpace(double megaBytes);

  /**
   * Gets the system memory space allowed for the texture images. This value is
   * specified in megabytes (MB).
   */
  static double getMemorySpace();

  /**
   * Return the current system memory used by all texture images.
   */
  static double getGlobalMemoryUsed();
  
  /**
   * 
   * If TRUE, uses a 256-color-indexed palette. You must call this method before
   * the textures are loaded. Default is FALSE. @BR
   * @B NOTE:@b If the field #enableCompressedTexture is set TRUE, its value takes
   * precedence over this request to use a paletted texture. Compressed textures will
   * be used.
   */
  static void useTexturePalette(SbBool value);
  
  // Load callbacks
  
  /**
   * \oivnetdoc Delegate \else Callback \endoivnetdoc invoked when starting loading the texture.
   * [OIV-WRAPPER EVENT_NAME{LoadStart}]
   */
  void addOnLoadStartCB(SoExtTexture2CB* cb, void* userData);
  
  /**
   * Callback invoked when the texture is loaded and ready to use.
   * [OIV-WRAPPER EVENT_NAME{LoadFinish}]
   */
  void addOnLoadFinishCB(SoExtTexture2CB* cb, void* userData);
  
  /**
   * Callback invoked when the texture is unloaded.
   * [OIV-WRAPPER EVENT_NAME{Unload}]
   */
  
  void addOnUnloadCB(SoExtTexture2CB* cb, void* userData);

  // Manual loading
  
  /**
   * Loads the texture if the loading mode is set to MANUAL.
   */
  void loadTexture();

 SoEXTENDER public:
  virtual void doAction(SoAction *action);
  virtual void GLRender(SoGLRenderAction *action);
  virtual void write(SoWriteAction* action);
  
 SoINTERNAL public:
  
  enum textureFormat {   // Image format
    RGB_FORMAT,
    PALETTED,
    COLORTABLE
  };
    
  static void initClass();
  static void exitClass();

  const SbString &getOverrideURL() { return overrideURL; }
  void setOverrideURL(const SbString &path) { overrideURL = path; }
  
  // Loads and process the texture ()
  static void *manageLoading(void *userData, SbBool isCallTouch=TRUE);

  // Loads and process the texture ()
  // Call manageLoading with isCallTouch=TRUE.
  // A new prototype is necessary because SbThread::create() accept only
  // 1 parameter.
  static void *manageLoadingThread(void *userData);
    
  // Get system time at last traversal
  SoSFTime sysTime;
  
  // Returns the next index available for a texture name (multiviewer)
  int getNextTexNameIndex();

  // Manages field dependencies, when one of them change
  virtual void fieldHasChanged( SoField *field ); // override of SoFieldContainer

  // OpenGL Extensions
  static int glLUTExt; 
  
 protected:

  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);
  
  virtual ~SoExtTexture2();
  
  virtual void copyContents(const SoFieldContainer *fromFC, 
                            SbBool copyConnections);
 
 private:
  // Check OpenGL Extensions
  static void checkOGLExtensions() ;

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;
  SbThreadRWMutex* m_mutex;

  // Temporary data 
  //unsigned char *m_bytes;
  unsigned char *m_palette;
  
  // File loading thread
  SbThread *m_loadingThread;
  
  SbString overrideURL;
  
  static ExtPrequalifyFileCallback *prequalifyFileCB;
  static void *prequalifyFileCB_udata;
  SbBool prequalifyFileFlag;
  
  static void readTextureFile(SoExtTexture2 *tex); 
  
  SoDither *m_dither;
  
  // These keep the filename field in sync.
  void filename_HasChanged(void);
  void wrap_HasChanged(void);
  void maxAnisotropy_HasChanged(void);

  // Load callbacks attributes
  SoExtTexture2CB *m_loadStartCB;
  SoExtTexture2CB *m_loadFinishCB;
  SoExtTexture2CB *m_unloadCB;

  void *m_loadStartCBData;
  void *m_loadFinishCBData;
  void *m_unloadCBData;

  static GLint maxTexSize;  // depends on the video board
   
  // Current memory used by all texture objects
  static long m_globalMemoryUsed;
  
  // Memory used by the node
  long m_memoryUsed;
  
  // List of all SoExtTexture2 nodes
  static SbPList m_nodeList;
  
  // Maximum memory space allocated for the texture objects
  static long memorySpace;
  
  static int m_numNodes;
  static int m_numTexObjs;
  static int m_numNodeMax;
  
  // Use of texture lut ?
  static SbBool m_useTextureLUT;
  
  static void manageNodeListAlloc(SoExtTexture2 *node);

  SbRasterImage* m_rasterImage;

  // store a stack of directory to use for finding the file
  SbStringList currentDirStack;

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_EXTTEXTURE_2_ */

