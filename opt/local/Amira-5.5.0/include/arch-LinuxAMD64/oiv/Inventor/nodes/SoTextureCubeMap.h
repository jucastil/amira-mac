/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_CUBE_MAP_
#define  _SO_TEXTURE_CUBE_MAP_

#include <Inventor/fields/SoSFColor.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/fields/SoMFFilePathString.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture.h>
#include <Inventor/image/SbRasterImage.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/sys/SoGLType.h>
#include <Inventor/threads/SbThreadStorage.h>

class SoSensor;
class SbThreadRWMutex;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTextureCubeMap
//
//  Texture node.
//
//////////////////////////////////////////////////////////////////////////////

class SoTextureCubeMap;
typedef SbBool CubeMapPrequalifyFileCallback(const SbString &, void *, SoTextureCubeMap *);

/** 
 * @VSGEXT Cube texture mapping node.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 * Cube map textures provide a new texture generation scheme for looking up
 * textures from a set of six two-dimensional images representing the faces of
 * a cube. The (s,t,r) texture coordinates are treated as a direction vector
 * emanating from the center of a cube. At texture generation time, the
 * interpolated per-fragment (s,t,r) selects one cube face two-dimensional image
 * based on the largest magnitude coordinate (the major axis). A new (s,t) is
 * calculated by dividing the two other coordinates (the minor axes values) by
 * the major axis value, and the new (s,t) is used to lookup into the selected
 * two-dimensional texture image face of the cube map.
 *
 * Cube map textures are often used within shader programs to implement effects
 * such as reflection or refraction.
 * 
 * There are three ways to send the texture to Open Inventor:
 * - The textures can be read from six image files specified in the #filenames
 * field.
 * - Textures can be specified in memory by setting the image fields
 * (#imagePosX, ...) to contain the texture data. Doing so resets the #filenames field
 * to the empty string.
 * - Textures can be rendered from a scene graph using the renderToTextureProperty field.
 * 
 * But in all cases, the images must be specified in the following order:
 * - imagePosX (left)
 * - imagePosY (bottom)
 * - imagePosZ (back)
 * - imageNegX (right)
 * - imageNegY (top)
 * - imageNegZ (front)
 *
 * The SoTextureCoordinateReflectionMap node can be used to automatically generate
 * appropriate texture coordinates for cube mapping.
 * 
 * Example:
 * \oivnetdoc
 * \code
 *     SoInput.AddDirectoryFirst("/ImageDirectory");
 *     string[] faceFile = { 
 *       "left.jpg",
 *       "bottom.jpg",
 *       "back.jpg",
 *       "right.jpg",
 *       "top.jpg",
 *       "front.jpg",
 *     };
 *     // Add a sphere with a texture cube map.
 *     SoTextureCubeMap myTexture = new SoTextureCubeMap();
 *     for (int i = 0; i < 6; ++i)
 *       myTexture.filenames.Set1Value(i, faceFile[i]);
 *     root.AddChild(new SoTextureCoordinateReflectionMap());
 *     root.AddChild(myTexture);
 *     root.AddChild(new SoSphere());
 * \endcode
 * \else
 * \code
 *   SoInput.addDirectoryFirst( "/ImageDirectory" );
 *   static char *faceFile[6] = {
 *     "left.jpg",
 *     "bottom.jpg",
 *     "back.jpg",
 *     "right.jpg",
 *     "top.jpg",
 *     "front.jpg",
 *   };
 *   // Add a sphere with a texture cube map.
 *   SoTextureCubeMap *myTexture = new SoTextureCubeMap;
 *   for (int i=0;i<6;i++)
 *     myTexture->filenames.set1Value(i,SbString(faceFile[i]))
 *   root->addChild(new SoTextureCoordinateReflectionMap) ;
 *   root->addChild(myTexture);
 *   root->addChild(new SoSphere);
 * \endcode
 * \endoivnetdoc
 *
 *   If the texture image's width or height is not a power of 2, and the 
 *   Non Power Of Two (NPOT) extension is available on your graphics board, by default Open Inventor
 *   will send the image to OpenGL without modification. See SoTexture2 for a complete
 *   discussion of this feature.
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
 *    TextureCubeMap {
 *    @TABLE_FILE_FORMAT
 *       @TR filenames                @TD ""
 *       @TR imagePosX                @TD 0 0 0
 *       @TR imageNegX                @TD 0 0 0
 *       @TR imagePosY                @TD 0 0 0
 *       @TR imageNegY                @TD 0 0 0
 *       @TR imagePosZ                @TD 0 0 0
 *       @TR imageNegZ                @TD 0 0 0
 *       @TR wrapS                    @TD REPEAT
 *       @TR wrapT                    @TD REPEAT
 *       @TR wrapR                    @TD REPEAT
 *       @TR enableCompressedTexture  @TD FALSE
 *       @TR model                    @TD MODULATE
 *       @TR blendColor               @TD 0 0 0
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
 * 
 * 
 * @SEE_ALSO
 *    SoComplexity,
 *    SoExtTexture2,
 *    SoMaterial,
 *    SoTexture2,
 *    SoTexture2Transform,
 *    SoTextureCoordinate2,
 *    SoTextureCoordinateBinding,
 *    SoTextureCoordinateFunction,
 *    SoTextureCoordinateNormalMap,
 *    SoTextureCoordinateReflectionMap,
 *    SoTextureUnit
 * 
 * 
 */ 

class INVENTOR_API SoTextureCubeMap : public SoTexture {

  SO_NODE_HEADER(SoTextureCubeMap);

 public:
 
  /**
   *
   * Names file(s) from which to read texture image(s). The standard image file formats are
   * supported. See SoRasterImageRW for the list. 
   * If the first file is an HDRI file, only this file is used since it has all 6 faces encoded.
   * If the filename is not an absolute path name, the list of directories maintained by
   * SoInput is searched. If the texture is not found in any of those directories,
   * then the file is searched for relative to the directory from which the
   * SoTextureCubeMap node was read. For example, if an SoTextureCubeMap node with a filename of
   * "../tofu.rgb" is read from /usr/people/bob/models/food.iv, then
   * /usr/people/bob/tofu.rgb will be read (assuming tofu.rgb isn't found in the
   * directories maintained by SoInput).
   * 
   */
  SoMFFilePathString  filenames;

  /**
   * Contains an in-memory representation of the texture map. It is either the
   * contents of the file read from #filenames, an image read directly from an
   * Open Inventor file, or an image set programmatically using the methods provided
   * by SoSFImage.
   * 
   */
  SoSFImage           imagePosX;
  /**
   * See #imagePosX.
   */
  SoSFImage           imagePosY;
  /**
   * See #imagePosX.
   */
  SoSFImage           imagePosZ;
  /**
   * See #imagePosX.
   */
  SoSFImage           imageNegX;
  /**
   * See #imagePosX.
   */
  SoSFImage           imageNegY;
  /**
   * See #imagePosX.
   */
  SoSFImage           imageNegZ;

  /**
   * Indicates what to do when texture coordinates in the T
   * (vertical) direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap. Default is REPEAT.
   */
  SoSFEnum            wrapT;
  /**
   * Indicates what to do when texture coordinates in the R (depth)
   * direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap. Default is REPEAT.
   */
  SoSFEnum            wrapR;

  /**
   * 
   * Specifies an SoRenderToTextureProperty node containing a scene graph that 
   * will be rendered to create the texture image.
   * The scene is rendered into a Pbuffer and then directly bound or copied into
   * texture memory.
   * Null by default.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFNode renderToTextureProperty;


  /**
   * 
   * Specifies an exposure factor when using an HDRI file. 1.0 by default.
   */
  SoSFFloat HDRIExposure;

  /**
   * Creates a texture node with default settings.
   */
  SoTextureCubeMap();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);

  static void setPrequalifyFileCallBack(CubeMapPrequalifyFileCallback *p_cb, void *u_data);
  static CubeMapPrequalifyFileCallback *getPrequalifyFileCallBack( void *&user_data );
  void allowPrequalifyFile(SbBool);
  SbBool isAllowPrequalifyFile() const;


 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  const SbString &getOverrideURL() { return overrideURL; }
  void setOverrideURL(const SbString &path) { overrideURL = path; }

  // Manages field dependencies, when one of them change
  virtual void fieldHasChanged( SoField *field ); // override of SoFieldContainer


 protected:
  // Reads stuff into instance. Returns FALSE on error.
  virtual SbBool readInstance(SoInput *in, unsigned short flags);

  virtual ~SoTextureCubeMap();

  virtual void copyContents(const SoFieldContainer *fromFC, SbBool copyConnections);
  
  /** This function converts the texture in FLOAT to UNSIGNED_BYTE  
    * if the float textures ext is not available 
    */
  void checkTexturesFormat( SoState* state );

 private:


  SbRasterImage* m_rasterHDRIImageRBE[6];

  SbString overrideURL;

  static void reformatImage(unsigned char * &bytes, int w, int h, int nc, int newNC);
  static void fillCubeMapTextures(int i);

  static CubeMapPrequalifyFileCallback *prequalifyFileCB;
  static void *prequalifyFileCB_udata;
  SbBool prequalifyFileFlag;
 
  // Index of filenames, corresponding to the 6 faces
  enum IdxIMAG { IPosX=0, IPosY=1, IPosZ=2, INegX=3, INegY=4, INegZ=5 }; 

  // These methods manage dependencies for field modifications 
  void image_HasChanged( SoSFImage *image, IdxIMAG _idxImag );
  void filenames_HasChanged(void);
  void wrapS_HasChanged(void);
  void maxAnisotropy_HasChanged(void);
  void wrapT_HasChanged(void);
  void wrapR_HasChanged(void);
  void renderToTextureProperty_HasChanged(void);
  void useAutoMipmap_HasChanged(void);
  void internalFormat_HasChanged(void);
  void HDRIExposure_HasChanged(void);

  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;

  SbThreadRWMutex  *m_mutex;

  SbRasterImage* m_compressedImage[6];

  int m_numRenderCaches;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_TEXTURE_CUBE_MAP_ */
