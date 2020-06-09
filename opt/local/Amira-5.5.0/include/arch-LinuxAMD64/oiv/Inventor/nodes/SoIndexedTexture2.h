/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 2005)
**=======================================================================*/

#ifndef  _SO_INDEXED_TEXTURE2_
#define  _SO_INDEXED_TEXTURE2_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFArray2D.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoGLTexCacheList.h>
#include <Inventor/caches/SoCache.h>

#include <Inventor/sensors/SoFieldSensor.h>

class SoGLRenderAction ;
class SoCallbackAction ;
class SoColorMap;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Class for 2D indexed textures nodes.
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This property node defines a color index texture map and parameters for that map. 
 *   This map applies to the current texture unit (see SoTextureUnit) and
 *   is used to apply texture to subsequent shapes as they are rendered.
 *   
 * The image data is stored in an SoSFArray2D.
 * This array can contain different types of data (UNSIGNED_BYTE, UNSIGNED_SHORT, UNSIGNED_INT32, 
 * SIGNED_BYTE, SIGNED_SHORT, SIGNED_INT32, FLOAT). 
 *
 *  Each data value coming from the SoSFArray2D is used as an index into 
 *  the color map defined by the current SoColorMap node.
 * 
 *  When Open Inventor creates the OpenGL texture image from the data
 *  array, the data values must be scaled into the range of values of the
 *  texture (0-255 for an 8-bit indexed texture). The #minValue and #maxValue fields
 *  specify the range of data values that will be scaled into the range
 *  of texture values. 
 *  For example, if 
 *  #minValue is set to 10000 and #maxValue to 38000, all values 
 *  less than or equal to 10000 will be mapped to 
 *  the entry 0 of the color map and all values greater than or equal 
 *  to 38000 to the last entry.
 *  The image below illustrates the process of mapping and shows 
 *  how it can be used to map only the used data range to the color map:
 *  @IMAGE dataremap.jpg     
 *
 *  If #minValue or #maxValue change, then the OpenGL texture
 *  must be recreated. If the texture is large, this may be time consuming.
 *  Generally it's more efficient to modify the SoColorMap node because
 *  the OpenGL texture corresponding to the data does not need to be recreated --
 *  only the texture containing the colormap, which is normally quite small.
 *
 *  @B NOTE: @b Texture data values are stored with 12 bits of precision instead of the usual 8 bits, when:
 *  @UL
 *  @LI @I ARB_fragment_program @i is supported by the graphics card.
 *  @LI The number of color map entries is greater than 256.
 *  @LI The texture data type has more than 8 bits of precision (i.e., not UNSIGNED_BYTE or SIGNED_BYTE).
 *  @ul
 *
 *  On graphics cards supporting @I ARB_fragment_program @i, the #model field will 
 *  be ignored and multitexturing 
 *  will not work. It is possible to circumvent this limitation by using a custom shader. The following
 *  GLSL code shows how to do multitexturing between two indexed textures sharing the same color map:
 *
 *\code
 * uniform sampler2D colormap;
 * uniform sampler2D indexedTex; 
 * uniform sampler2D indexedTex2;  
 *
 * void main()
 * {
 *  // Fetch the indexed texture
 *  float x = texture2D(indexedTex, gl_TexCoord[0].xy).x;
 *  // Fetch the color map
 *  vec4 indColor = texture2D(colormap, vec2(x, 0));
 *  // Fetch the second indexed texture
 *  x = texture2D(indexedTex2, gl_TexCoord[0].xy).x;
 *  // Fetch the color map
 *  vec4 indColor2 = texture2D(colormap, vec2(x, 0)); 
 *  // Modulate the two textures
 *  gl_FragColor = indColor*indColor2*gl_Color;
 * }\endcode
 *
 *
 * The scene graph would be initialized like this:
 *
 * \code
 * paramIndexedTex->value = 0; 
 * paramColorMap->value = 1;
 * paramIndexedTex2->value = 2;
 * textureUnit->unit = 2;         //Texture unit for the second indexed texture
 * ... Set fragment shader's parameters and attach it to the shader program...  
 * root->addChild(colorMap);      //Color map will be in texture unit 1
 * root->addChild(indexedTex);    //First indexed texture is in texture unit 0
 * root->addChild(textureUnit); 
 * root->addChild(indexedTex2);   //Second texture is in unit 2
 * root->addChild(shaderProgram);
 * root->addChild(sphere);
 * \endcode
 *
 *  
 * @FILE_FORMAT_DEFAULT
 *    IndexedTexture2 {
 *    @TABLE_FILE_FORMAT
 *       @TR minValue                 @TD 0
 *       @TR maxValue                 @TD 0
 *       @TR imageIndex               @TD 0 0
 *       @TR wrapS                    @TD REPEAT
 *       @TR wrapT                    @TD REPEAT
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
 *    SoGLRenderAction, SoCallbackAction @BR
 *    Sets: SoTextureImageElement
 * 
 * @SEE_ALSO
 *    SoTexture2Transform, SoTextureCoordinate2,  
 *    SoTextureCoordinateFunction, SoColorMap, SoSFArray2D.
 *
 * 
 */ 

class INVENTOR_API SoIndexedTexture2 : public SoTexture {  
  SO_NODE_HEADER(SoIndexedTexture2) ;

 public:
  /**
  * Specifies the range of values which is mapped onto the color map (see SoColorMap). 
  * When #minValue and #maxValue are equal to 0 (the default), the entire range of the data type is 
  * mapped onto the color map, except in the case of float data. For example, for a color map
  * of size N:
  * @UL
  * @LI With unsigned byte values, [0-255] is mapped onto the color map [0 - N-1]
  * @LI With unsigned short values, [0-65535] is mapped onto the color map [0 - N-1]
  * @LI With signed short values, [-32768 - 32767] is mapped onto the color map [0 - N-1].
  * @LI With float data type, [0-1] is mapped onto the color map [0 - N-1]
  * @ul
  * All values less than or equal to #minValue will be mapped to the first entry of the color map.
  * Likewise, all values greater than or equal to #maxValue will be mapped to the last entry of 
  * the color map.
  */
  SoSFFloat   minValue ;

  /**
   * See #minValue
   */
  SoSFFloat   maxValue ;

  /**
   * This field contains the in-memory representation of the indexed texture image.
   * Each value of this array is a color index. In the case of float values, data must 
   * be between 0 and 1.
   */
  SoSFArray2D imageIndex ;

  /**
  * This field controls the way an image with non-power-of-two dimension is handled:
  * @UL
  * @LI If the graphics card supports @I GL_ARB_texture_non_power_of_two @i, this field will be ignored.
  * The image is sent directly to OpenGL.
  * @LI If #rescaleTexCoord is FALSE (the default), the image is rescaled to the next lower
  *     power-of-two dimensions. The scaling is done with a box filter.
  * @LI If #rescaleTexCoord is TRUE, the image is not rescaled but is only copied into a
  * texture with the next higher power-of-two dimension, and its texture coordinates 
  * are scaled by applying a texture transform in order to only display the actual image.
  * 
  * In this mode, if other texture transforms are applied to the texture coordinates 
  * (especially if the texture is repeated), the unused part of the larger texture 
  * could be displayed. 
  * Furthermore, in this mode, if non-power-of-two textures occur one after another 
  * in the scene graph, an incorrect image may result because texture transforms are
  * cumulative. For example, the following code would give incorrect results: 
  *
  * \oivnetdoc
  * \code
  * root.AddChild(colorMap);
  * root.AddChild(nonPowerOfTwoIndexedTexture1);
  * root.AddChild(nonPowerOfTwoIndexedTexture2);
  * root.AddChild(nonPowerOfTwoIndexedTexture3);
  * \endcode
  * \else
  * \code
  * root->addChild(colorMap);
  * root->addChild(nonPowerOfTwoIndexedTexture1);
  * root->addChild(nonPowerOfTwoIndexedTexture2);
  * root->addChild(nonPowerOfTwoIndexedTexture3);
  * \endcode
  * \endoivnetdoc
  *
  * The correct way is to use a separator above each texture, as shown:
  *
  * \oivnetdoc
  * \code
  * root.AddChild(colorMap);
  * root.AddChild(separator1);
  * separator1.AddChild(nonPowerOfTwoIndexedTexture1);
  * root.AddChild(separator2);
  * separator2.AddChild(nonPowerOfTwoIndexedTexture2);
  * root.AddChild(separator3);
  * separator3.AddChild(nonPowerOfTwoIndexedTexture3);
  * \endcode
  * \else
  * \code
  * root->addChild(colorMap);
  * root->addChild(separator1);
  * separator1->addChild(nonPowerOfTwoIndexedTexture1);
  * root->addChild(separator2);
  * separator2->addChild(nonPowerOfTwoIndexedTexture2);
  * root->addChild(separator3);
  * separator3->addChild(nonPowerOfTwoIndexedTexture3);
  * \endcode
  * \endoivnetdoc
  * 
  * @ul
  */
  SoSFBool  rescaleTexCoord;

  /**
   * Indicates what to do when texture coordinates in the T
   * (vertical) direction lie outside the range 0-1.
   * Use enum SoTexture::Wrap. Default is REPEAT.
   */
  SoSFEnum   wrapT ;

  /**
   * Compute the min and max value of the indexed image and put the result in #minValue and #maxValue.
   *
   */
  void computeDataRange();

  /**
   * Constructor.
   */
  SoIndexedTexture2() ;

 SoEXTENDER public:
  virtual void doAction( SoAction* action );
  virtual void GLRender( SoGLRenderAction* action );

  /** 
   * This method returns the alternate represention (currently only for PDF and U3D exports).
   * The node returned is an SoTexture2.
   */
  virtual SoNode* getAlternateRep( SoAction* action );

  /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  SbVec2s getTexSize() const { return m_size; }

  /**
   * Create a subgraph for the alternateRep field that gives approximately
   * the same appearance, but using only core Open Inventor nodes.
   * Might be useful in other cases.
   */
  virtual SoNode* createAlternateRep( SoAction *action );

  // Manage field dependencies  when one of them change   AJO eBug #1972
  virtual void fieldHasChanged( SoField *field ); // override of SoFieldContainer


 protected:
  // Destructor
  virtual ~SoIndexedTexture2() ;


 private:
  // Display list info for this texture:
  SbThreadStorage< SoGLTexCacheList* > m_texList;
  SbThreadRWMutex* m_mutex;

  GLenum getGLInternalFormat(SoSFArray2D::DataType dataType, SoColorMap *cm) const;

  //Map data on the color map
  void mapData(SoColorMap *cm);
  
  //Reconstruct m_indexedImageData if imageIndex, max or min change
  SbThreadStorage< bool > m_needUpdate;
  
  //Allow to choose the correct delete[] on m_indexedImageData
  SoSFArray2D::DataType m_previousType;
  void deleteIndexedData(SoSFArray2D::DataType datatype);

  SoSFImage::DataType getDataType(SoSFArray2D::DataType dataType, SoColorMap *cm);

  //Final indexed data which are sent to OpenGL
  void *m_indexedImageData;

  // Tesxture size
  SbVec2s m_size;

  //Check colormap modifications
  SbThreadStorage< SoCache* > m_cache;  

  //Contains the rescaled image
  SoSFArray2D m_rescaledImageIndex ;
  void scaleTexCoord();
  SbBool m_hasNPOT;
  SbBool m_forceScaleImage; //True if texture size > GL_MAX_TEXTURE_SIZE

  //Scale the texture but not the image data
  void scaleTexture(unsigned char *dest, const unsigned char *src, SbVec2s newSize, SbVec2s size,
                    SoSFArray2D::DataType dataType);
} ;
/*----------------------------------------------------------------------------*/

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_INDEXED_TEXTURE2_ */
