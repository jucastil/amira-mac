/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jan 2005)
**=======================================================================*/

#ifndef  _SO_COLOR_MAP_
#define  _SO_COLOR_MAP_

#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFEnum.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/sensors/SoFieldSensor.h>
#include <Inventor/threads/SbThreadStorage.h>
#include <Inventor/caches/SoGLObjectCache.h>


class SoGLRenderAction ;
class SoCallbackAction ;
class SbThreadRWMutex;
class SoCache;  
class SoState;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/*----------------------------------------------------------------------------*/

/**
 * @VSGEXT Class for indexed texture color map
 * 
 * @ingroup TextureNodes
 * 
 * @DESCRIPTION
 *   This class describes the association between values of the SoIndexedTexture2 node and colors.
 *   
 *   The data value coming from the SoIndexedTexture2 node is used as an index into 
 *   the color map defined by the #colorMap field or the #predefinedColorMap field.
 *   
 *   The #predefinedColorMap field allows you to specify a predefined color map
 *   or using value NONE, that the color map is contained in the #colorMap field.
 *
 *   The #min and #max fields define the range of the data values that will actually
 *   be used.
 *   The color map is modified such that only data values ranging from #min to #max will 
 *   be mapped to the color map.
 *   The figure below illustrates the effects of these fields:
 *   @IMAGE colormapremap.jpg     
 *
 *   The SoColorMap node acts like an SoShaderProgram with an SoFragmentShader. 
 *   Standard Open Inventor operations on textures will be disabled on all subsequent nodes, thus
 *   using an SoTexture2 node or multitexturing after this node will not give the expected result.
 *
 *   @B NOTE: @b @UL
 *         @LI The SoColorMap node must be inserted before the SoIndexedTexture2.
 *         @LI This node puts the color map in the next available texture unit, so this 
 *             unit must not be used for any other purpose in your application. 
 *             On hardware which doesn't support @I ARB_fragment_program @i but supports @I EXT_paletted_texture @i,
 *             the next available texture unit is not used and thus remains available for use by the application.
 *         @LI If your graphics hardware does not support the ARB_fragment_program or the
 *              EXT_paletted_texture OpenGL extension, this node has no effect.
 *         @LI SoColorMap is only used to color SoIndexedTexture2 nodes.
 *             To specify a color map for volume rendering, see SoTransferFunction.
 *         @ul
 *
 *@EXAMPLE
 *  The following example shows how to apply an indexed texture on a geometry node:
 *  \oivnetdoc
 *    \code
 *    SoColorMap colorMap = new SoColorMap();
 *    colorMap.predefinedColorMap.SetValue( (int)SoColorMap.PredefinedColorMaps.TEMPERATURE );
 *    colorMap.min.SetValue( -1000 );        
 *    colorMap.max.SetValue( 20000 );        
 *    SoIndexedTexture2 indexedTexture = new SoIndexedTexture2();
 *    indexedTexture.imageIndex.SetValue(size, (int)SoSFArray.DataTypes.SIGNED_SHORT, data); 
 *    root.AddChild( colorMap );
 *    root.AddChild( indexedTexture );
 *    root.AddChild( geometry ); 
 *    \endcode
 *  \else
 *    \code
 *    SoColorMap *colorMap = new SoColorMap;
 *    colorMap->predefinedColorMap = SoColorMap::TEMPERATURE;  
 *    colorMap->min.setValue( -1000 );        
 *    colorMap->max.setValue( 20000 );        
 *    SoIndexedTexture2 *indexedTexture = new SoIndexedTexture2 ;
 *    indexedTexture->imageIndex.setValue(size, SoSFArray2D::SIGNED_SHORT, data); 
 *    root->addChild( colorMap );
 *    root->addChild( indexedTexture );
 *    root->addChild( geometry );
 *    \endcode
 *  \endoivnetdoc
 * 
 *
 * @FILE_FORMAT_DEFAULT
 *    ColorMap {
 *      @TABLE_FILE_FORMAT
 *       @TR min                  @TD 0
 *       @TR max                  @TD 0
 *       @TR predefinedColorMap   @TD TEMPERATURE
 *       @TR colorMapFormat       @TD RGB_ALPHA
 *       @TR colorMap             @TD 0
 *      @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction, SoCallbackAction @BR
 *    Sets: SoColorMapElement
 * 
 * @SEE_ALSO
 *       SoIndexedTexture2
 *
 * 
 */ 

class INVENTOR_API SoColorMap : public SoNode {  
  SO_NODE_HEADER(SoColorMap) ;

 public:
   /** Color map format */
   enum ColorMapFormat {
    /** (1 float) */
    LUMINANCE,
    /** (1 float) */
    ALPHA,

    /** (2 floats) */
    LUMINANCE_ALPHA,

    /** (3 floats) */
    RGB,

    /** (4 floats) */
    RGB_ALPHA
   } ;

   /** Predefined color map */
   enum PredefinedColorMap {
     /** None */
     NONE,
     /** Gray (Default) */
     GRAY,
     /** Temperature */
     TEMPERATURE,
     /** Physics */
     PHYSICS,
     /** Standard */
     STANDARD,
     /** Glow */
     GLOW,
     /** Blue red */
     BLUE_RED,
     /** Seismic */
     SEISMIC,
     /** Blue white red */
     BLUE_WHITE_RED
   } ;

 /**
  * This field allow to remap the color map such that only data values ranging from 
  * @B min @b to @B max @b will be mapped to the color map. @B min @b and  @B max @b must
  * be between @B minValue @b and @B maxValue @b of the corresponding SoIndexedTexture2
  * node.
  *
  * Values less than @B min @b and greater than @B max @b will be set to colorMap[0] and
  * colorMap[colorMap.getNum()-1] respectively. If @B min @b is less than the minimum of the 
  * indexed texture @B minValue @b, it will be clamped to this minimum.
  * If @B max @b is greater than the maximum of the indexed texture @B maxValue @b, 
  * it will be clamped to this maximum.
  * When #min and #max are equal to 0 (the default), the entire range of data values is used.
  *
  * Setting @B (min,max) @b to (64,192) while the predefined STANDARD color map is selected
  * and in the case of a UNSIGNED_BYTE indexed texture will  make the color map as shown:
  * 
  * @IMAGE standardReMap.jpg
  */
  SoSFFloat   min ;

 /**
  * See #min
  */
  SoSFFloat   max ;

  /**
  * Use this field to load predefined color maps. 
  * See enum #PredefinedColorMap. Default is TEMPERATURE.
  * All predefined color maps have 256 entries.
  * 
  *    @TABLE_0B
  *       @TR GRAY           @TD @IMAGE grayColorMap.jpg
  *       @TR TEMPERATURE    @TD @IMAGE temperatureColorMap.jpg
  *       @TR PHYSICS        @TD @IMAGE physicsColorMap.jpg
  *       @TR STANDARD       @TD @IMAGE standardColorMap.jpg
  *       @TR GLOW           @TD @IMAGE glowColorMap.jpg
  *       @TR BLUE_RED       @TD @IMAGE blue_redcolormap.jpg
  *       @TR SEISMIC        @TD @IMAGE seismicColorMap.jpg
  *       @TR BLUE_WHITE_RED @TD @IMAGE blue_white_redcolormap.jpg
  *    @TABLE_END 
  * 
  * NOTE: In the images above the checkerboard pattern shows through where the color map alpha (opacity)
  * value is less than 1.0.   
  * 
  * If it is set to NONE, the fields below must be set.
  */
  SoSFEnum   predefinedColorMap ;
   
 /**
  * Indicates the format of the color map (number of color components).
  * See enum #ColorMapFormat. Default is RGB_ALPHA.
  *
  * LUMINANCE means one component per color for a grayscale color map.
  * 
  * ALPHA means one alpha component per color.
  * 
  * LUMINANCE_ALPHA means two components per color, luminance and alpha. In such a case the
  * colorMap float array contains a list of two floats. Index 0 is luminance, index
  * 1 is alpha, index 2 is luminance, index 3 is alpha and so on.
  * 
  * RGB means three components per color, ordered red first, then green and blue.
  *
  * RGB_ALPHA means four components per color, ordered red first, then green, blue, and
  * alpha.
  * 
  * An alpha value equal to zero means "fully transparent", an alpha value equal to
  * one means "opaque".
  */
  SoSFEnum   colorMapFormat ;

  /**
  * Array of floats in range [0,1]. The number of floats depends on #colorMapFormat.
  * It is equal to the number of colors defined multiplied by the number of components
  * per color. For example, for an RGBA color map of length n, there should be 4*n float
  * values in the field. If a predefined color map is specified, the values of this
  * field are not used.
  */
  SoMFFloat  colorMap ;

  /**
   * Constructor.
   */
  SoColorMap() ;
   
  /**
   * This convenience method returns the number of colors in the color map 
   * (ie: colorMap.getNum()/Number of components or 256 if a predefined color map is used)
   */
  unsigned int getNumColor() const;

  /**
   * Returns TRUE if the current color map contains alpha values less than 1. 
   * FALSE means the color map is completely opaque. 
   */
  SbBool hasTransparency() const;

 SoEXTENDER public:
  virtual void  doAction(SoAction *action);
  virtual void  GLRender(SoGLRenderAction *action) ;
  virtual void callback( SoCallbackAction* action );

 /*----------------------------------------------------------------------------*/
  
 SoINTERNAL public:
  static void initClass() ;
  static void exitClass() ;

  //bind fragment and texture object
  void enableFragment(SoState *state, SbBool enable);
  //do the teximage or colortable for the palette
  void installGLColorMap(SoState* state, int indexTexPrec) ;

  //Remap the defined color map between min and max indices
  //minType and maxType are respectively the minimum value and 
  //the maximum value of the datatype  
   void reMap(float minType, float maxType, SbBool forceUpdate = FALSE);

   // Returns the packed color map
   unsigned int* getPackedColorMap() const { return m_packColorMap; };

  enum GLColorMapType {
    NO_COLORMAP = 0,
    TEX_SHARED_PALETTE = 1,
    TEX_FRAGMENT_PROGRAM = 2
  };
  GLColorMapType getColorMapType();

 protected:
  // Destructor
  virtual ~SoColorMap() ;

 private:
   int m_packColorMapSize ;
   unsigned int* m_packColorMap ;   
   int m_colorMapUnit;
   int m_prevColorMapUnit;
   int m_colorMapSize;
   
   SbBool         m_useFragment;
   SbBool         m_usePalettedTex;
   SbBool         m_cmInstalled;
   //Check and Initialize needed opengl extensions
   void checkGLExtensions(SoState*state);

   // Display list info for color map's texture:
   SoGLObjectCache* m_texList;  

   // Display list info for fragment program:
   SoGLObjectCache* m_progList;  

   //Construct the packed color version of the colormap
   void buildColorMap() ;
   
   //Replace the first string texName by n in shader
   void setTextureUnitInFragment(char *shader, char *texName, int n);
   
   SoFieldSensor *m_colorMapSensor;
   SoFieldSensor *m_predefColorMapSensor;
   static void fieldsChangedCB(void *data, SoSensor *);
   static void minMaxChangedCB(void *data, SoSensor *);
   
   SoFieldSensor *m_minSensor;
   SoFieldSensor *m_maxSensor;

   struct Handle
   {
     void* handle;
     void unref(){}
   };

   SbThreadStorage< bool > m_needUpdate;
   SbThreadStorage< Handle* > m_shaderHandle;

   SbBool m_hasTransparency;
} ;
/*----------------------------------------------------------------------------*/

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif /* _SO_COLOR_MAP_ */
