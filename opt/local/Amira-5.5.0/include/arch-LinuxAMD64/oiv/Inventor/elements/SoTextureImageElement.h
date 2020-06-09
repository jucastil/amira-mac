/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TEXTURE_IMAGE_ELEMENT
#define  _SO_TEXTURE_IMAGE_ELEMENT

#define MAX_TEXTURE_NBR 6
// Texture1D, texture2D and texture3D use one texturename
// But we need 6 for textureCubeMap

#include <Inventor/SbColor.h>
#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/fields/SoSFImage.h>
#include <Inventor/nodes/SoTexture2.h>

#ifndef GL_TEXTURE_CUBE_MAP
#define GL_TEXTURE_CUBE_MAP 0x8513
#endif
#ifndef GL_TEXTURE_2D
#define GL_TEXTURE_2D 0x0DE1
#endif


class SoRenderToTextureProperty;
class SoBufferObject;

/**
*  Stores the current texture image.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture image.
* 
*   @SEE_ALSO
*   SoTexture2, SoExtTexture2, SoIndexedTexture2, SoTextureCubeMap,
*   SoVRMLImageTexture, SoVRMLPixelTexture
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureImageElement : public SoReplacedTextureElement {
  
  SO_ELEMENT_HEADER(SoTextureImageElement);
  
 public:
 
    /** Target */
   enum Target { 
    /** TEXTURE2D */
     TEXTURE2D = GL_TEXTURE_2D, 
    /** TEXTURECUBEMAP */
     TEXTURECUBEMAP = GL_TEXTURE_CUBE_MAP
   };

  /** Sets the current image, wrap, and model.
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,ARRAY,IN,IN,WRAP_AS{int},IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN]
   */
  static void         set(SoState *state, SoNode *node,
                          const SbVec2s &size, int numComponents,
                          const void *buffer, SoBufferObject* bufferObject, SoSFImage::DataType dataType,
                          GLint GLInternalFormat, SoRenderToTextureProperty* renderToTexProp,
                          int wrapS, int wrapT, int wrapR, int model,
                          const SbColor &blendColor, float maxAnisotropy,
                          SbBool enableBorder, const SbVec4f &borderColor,
                          SbBool isCompressed, int numCompressedMipmaps, int hasTransparency = -1, int currentTexture=-1);
  
  /** 
  * Sets the current image, wrap, and model plus minFilter and magFilter
  * [OIV-WRAPPER-ARG IN,IN,IN,IN,ARRAY,IN,IN,WRAP_AS{int},IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN,IN]
  */
  static void         set(SoState *state, SoNode *node,
    const SbVec2s &size, int numComponents,
    const void *buffer, SoBufferObject* bufferObject, SoSFImage::DataType dataType,
    GLint GLInternalFormat, SoRenderToTextureProperty* renderToTexProp,
    int wrapS, int wrapT, int wrapR, int model,
    const SbColor &blendColor, float maxAnisotropy,
    const int &minFilter, const int &magFilter, 
    SbBool enableBorder, const SbVec4f &borderColor,
    SbBool isCompressed, int numCompressedMipmaps, int hasTransparency = -1, int currentTexture=-1);

  /**
   * Gets the current image, wrap, and model.
   * [OIV-WRAPPER-ARG IN,OUT,OUT,OUT,WRAP_AS{int},OUT,OUT,OUT,OUT,IN]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*numComponents}]
   */
  static const void *get(SoState *state, SbVec2s &size, int &numComponents, 
                         SoSFImage::DataType &dataType, 
                         GLint &GLInternalFormat,
                         int &wrapS, int &wrapT, int &model, 
                         SbColor &blendColor, int unit=0);
  /**
  * Gets the current image minFilter, magFilter and maxAnisotropy
  */
  static void get(SoState *state, int &_minFilter,int &_magFilter, float &_maxAnisotropy, int unit=0);

  /** Pass texname = -1 to deactivate subtexturing. Subtexturing not active
   * by default. In any case, the regular set method must be called.
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,IN,ARRAY,IN]
   */
  static void         set(SoState *state, SoNode *node,
                          const SbVec2s &subSize, int xoffset, int yoffset,
                          const void *buffer, int texname) ;
    
    
  /**
  *  Returns TRUE if the texture contains transparency info.
  */
  static SbBool       containsTransparency(SoState *state, int unit=0);
    
  /** Returns the default texture image.
   * [OIV-WRAPPER-ARG OUT,OUT,OUT,WRAP_AS{int}]
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{s.Value[0]*s.Value[1]*nc}]
   */
  static const void *getDefault(SbVec2s &s, int &nc, SoSFImage::DataType &dataType,
                                GLint &GLInternalFormat);
    
  /**
  *  Print info about image for debugging.
  */
  virtual void        print(FILE *fp) const;

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void push(SoState *state) ;
    
 SoINTERNAL public:
  // Initializes the class
  static void         initClass();
  static void         exitClass();

  // Initializes element.
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;
    
  SoTextureImageElement::Target getTargetTexture(){return m_target;} 

 protected:

  SoTextureImageElement::Target m_target;

  virtual void        setElt(const SbVec2s &s, int nc,
                             const void *buffer, SoBufferObject* bufferObject, SoSFImage::DataType dataType,
                             GLint GLInternalFormat, SoRenderToTextureProperty* renderToTex,
                             int wrapS, int wrapT, int wrapR, int model,
                             const SbColor &blendColor, float _maxAnisotropy,
                             SbBool _enableBorder, const SbVec4f &_borderColor, 
                             SbBool isCompressed, int numCompressedMipmaps,
                             int hasTransparency = -1 /* default unknown */, 
                             int unit=0, int currentTexture=-1);
    
  virtual void        setSubElt(const SbVec2s &subSize,
                                int xoffset, int yoffset,
                                const void *buffer, int texname,
                                int unit=0);

  virtual void        setFilterElt(int _minFilter, int _magFilter, int currUnit);


  virtual ~SoTextureImageElement();

  // store information about the texture Image element data
  struct SoTexImageData {
    SbVec2s               size;
    int                   numComponents;
    const void*           buffer[MAX_TEXTURE_NBR];
    SoBufferObject*       bufferObjects[MAX_TEXTURE_NBR];
    int                   wrapS, wrapT,wrapR, model;
    SbColor               blendColor;
    int                   currentTexture; // for CubeMap(0->5), =-1 for texture2D
    bool                  fistPassForCubeMap;
    float                 maxAnisotropy;
    bool                  enableBorder;
    SbVec4f               borderColor;
    int                   minFilter;
    int                   magFilter;
    int                   textureName; // used for subtexturing
    SbVec2s               subSize;
    int                   xoffset, yoffset;
    const void*           subBuffer ;
    SoSFImage::DataType   dataType;
    GLint                 GLInternalFormat;
    SoRenderToTextureProperty* renderToTextureProperty;
    bool                  renderToTexturePropertyFirstPass;
    // Does texture image contain any alpha values less than one?
    // -1 = unknown, 0 = no, 1 = yes
    int                   hasTransparency;
    bool                  isCompressed;
    int                   numCompressedMipmaps;

    // Constructor
    SoTexImageData();

    // copy constructor.
    SoTexImageData& operator=(const SoTexImageData &data);    
  };

  // return texture Image element data for the given texture unit
  SoTexImageData& getTexImageData(const int unit) const;

private:
  // This stores the list of node id's as pointers associated to
  // each texture unit.
  typedef std::vector<SoTexImageData> SoTexImageDataList;
  mutable SoTexImageDataList m_texImageDataList;
};

#endif /* _SO_TEXTURE_IMAGE_ELEMENT */
