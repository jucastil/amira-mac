/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Patrick Vigneras (Nov 1999)
**=======================================================================*/

#ifndef  _SO_TEXTURE_IMAGE3_ELEMENT
#define  _SO_TEXTURE_IMAGE3_ELEMENT

#include <Inventor/SbColor.h>
#include <Inventor/elements/SoReplacedTextureElement.h>
#include <Inventor/sys/SoGLType.h>

class SoBufferObject;

/**
*  @VSGEXT Stores the current 3D texture image.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current 3D texture image.
* 
*   @SEE_ALSO
*   SoTexture3
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureImage3Element : public SoReplacedTextureElement {

  SO_ELEMENT_HEADER(SoTextureImage3Element);

public:
  /** Sets the current image, wrap, and model.
   * [OIV-WRAPPER-ARG IN,IN,IN,IN,IN,IN,WRAP_AS{int},IN,IN,IN,IN,IN,IN,IN,IN]
   */
  static void         set(SoState *state, SoNode *node,
                          const SbVec3s &size, int numComponents,
                          const unsigned char *bytes,
                          SoBufferObject* bufferObject,
                          GLint GLInternalFormat,
                          int wrapS, int wrapT, int wrapR, int model,
                          const SbColor &blendColor,float maxAnisotropy,
                          SbBool enableBorder, const SbVec4f &borderColor);

  /** 
   * Gets the current image, wrap, and model.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{size.Value[0]*size.Value[1]*size.Value[2]*numComponents}]
   */
  static const unsigned char *get(SoState *state, SbVec3s &size,
                                  int &numComponents, int &wrapS,
                                  int &wrapT, int &wrapR, int &model, 
                                  SbColor &blendColor, int unit=0);

  /**
  *  Pass texname = -1 to deactivate subtexturing. subtexturing not active
  *  by default. In any case, the regular set method must be called.
  */
  static void             set(SoState *state, SoNode *node,
                              const SbVec3s &subSize, int xoffset, int yoffset, int zoffset,
                              const unsigned char *bytes, int texname) ;

  /**
  *  Returns TRUE if the texture contains transparency info.
  */
  static SbBool       containsTransparency(SoState *state, int unit=0);

  /**
  *  Returns the default texture image.
  * [OIV-WRAPPER-RETURN-TYPE ARRAY{s.Value[0]*s.Value[1]*s.Value[2]*nc}]
  */
  static const unsigned char *getDefault(SbVec3s &s, int &nc);

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

protected:
  virtual void        setElt(const SbVec3s &s, int nc,
                             const unsigned char *bytes,
                             SoBufferObject* bufferObject,
                             GLint GLInternalFormat,
                             int wrapS, int wrapT, int wrapR, int model,
                             const SbColor &blendColor, float _maxAnisotropy,
                             SbBool _enableBorder, const SbVec4f &_borderColor,
                             int unit=0);
        
  virtual void        setSubElt(const SbVec3s &subSize,
                                int xoffset, int yoffset, int zoffset,
                                const unsigned char *bytes, int texname,
                                int unit=0);

  virtual void        setFilterElt(int _minFilter, int _magFilter, int unit);

  struct SoTexImage3Data {
    SbVec3s               size;
    int                   numComponents;
    const unsigned char*  bytes;
    SoBufferObject*       bufferObject;
    GLint                 GLInternalFormat;
    int                   wrapS, wrapT, wrapR, model;
    SbColor               blendColor;
    float                 maxAnisotropy;
    SbBool                enableBorder;
    SbVec4f               borderColor;
    int                   minFilter;
    int                   magFilter;

    int                   textureName; // used for subtexturing
    SbVec3s               subSize;
    int                   xoffset, yoffset, zoffset;
    const unsigned char*  subBytes ;

	// Constructor
    SoTexImage3Data();

	// copy constructor.
    SoTexImage3Data& operator=(const SoTexImage3Data &data);
  } ;

  virtual ~SoTextureImage3Element();

  // return texture Image element data for the given texture unit
  SoTexImage3Data& getTexImageData(const int unit) const;

private:
  // This stores the list of node id's as pointers associated to
  // each texture unit.
  typedef std::vector<SoTexImage3Data> SoTexImage3DataList;
  mutable SoTexImage3DataList m_texImageDataList;
};

#endif /* _SO_TEXTURE_IMAGE3_ELEMENT */
