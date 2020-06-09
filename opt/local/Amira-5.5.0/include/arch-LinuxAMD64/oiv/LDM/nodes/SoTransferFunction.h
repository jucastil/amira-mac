/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Mar 2000)
**=======================================================================*/
#ifndef  _SO_TRANSFER_FUNCTION_
#define  _SO_TRANSFER_FUNCTION_

#include <LDM/SoLDM.h>
#include <LDM/nodes/SoHardwareQuery.h>
#include <LDM/elements/SoTransferFunctionElement.h>

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFShort.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/sensors/SoNodeSensor.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/cassert>
#include <Inventor/STL/limits>

class SoGLRenderAction;
class SoCallbackAction;
class SoWriteAction;
class SoState;
class SoNodeSensor;
class SoGLTexture;

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
 * @LDMEXT Describes the association between data set values and colors.
 *
 * @ingroup LDMNodes
 *
 * @DESCRIPTION
 *   This node defines a mapping from scalar data set values to color
 *   and transparency (alpha) values.
 *
 *   To use one of the predefined color maps, set the #predefColorMap
 *   to a valid value other than NONE, for example INTENSITY.
 *
 *   To define a custom color map, the #predefColorMap field must be set
 *   to NONE, the #colorMapType field should be set to the appropriate 
 *   type (RGBA is the default) and the color map values loaded into the 
 *   #colorMap field as defined in the description of that field.
 *
 *   If no transfer function has been specified, VolumeViz rendering
 *   nodes automatically use the predefined GRAY color map.
 *
 *   The transfer function is associated with the rendering node(s),
 *   not the volume data node.  So for example it is possible to use
 *   one transfer function for volume rendering (SoVolumeRender) and
 *   a different transfer function for slices (e.g. SoOrthoSlice).
 *
 *   When rendering a single volume, there is only one transfer function
 *   active at a time and each rendering node uses the current (i.e. last
 *   traversed) transfer function in the traversal state, similar to the 
 *   way materials apply to polygonal geometry.
 *
 *   The application may switch from one transfer function to a different
 *   one.  For example, by putting multiple transfer functions under an
 *   SoSwitch node.  The application may also dynamically modify the
 *   contents of a transfer function, even if using a predefined color map.
 *   See the #colorMap and #actualColorMap fields.
 *
 *   When combining multiple volumes using SoMultiDataSeparator and
 *   SoVolumeShader it is possible to specify multiple transfer functions. 
 *   All the transfer functions under the SoMultiDataSeparator will be
 *   available to the shader program based on their #transferFunctionId.
 *   The application should assign a unique id to each transfer function.
 *   See the description of the #transferFunctionId field for more details.
 *
 *   When using volume masks (SoVolumeMask and SoVolumeMaskGroup), the
 *   #transferFunctionId is also very important.  In this case multiple
 *   transfer functions, with different id values, may exist in the
 *   traversal state simultaneously. Each mask region is only visible if
 *   there exists a transfer function with the same id value as that region.
 *   In addition, traversal order of the transfer functions is not important.
 *   Each region, including the original (unmasked) volume, is colored using
 *   the transfer function (if any) that has the same id value.
 *   See SoVolumeMask for more details.
 *
 *   By default, the full range of the volume's data type is mapped into the 
 *   color map.  This is usually appropriate for 8-bit (byte) data, but may
 *   be incorrect for larger data types.  For example, DICOM data is often
 *   12-bit values stored in 16-bit voxels.  To get the correct image in
 *   this case the application should set the data range to 0..4095.
 *   The SoDataRange node is used to specify a range of data values to
 *   be mapped into the color map.
 *
 *   The data values may also be rescaled before mapping onto the color
 *   map, using the #shift and #offset fields as shown below. Note that
 *   this may not be supported on volume rendering hardware.
 *
 *   The color map may also be "remapped", compressing the original list
 *   of color values into the range of entries specified by the #minValue
 *   and #maxValue fields.  Entries outside this range are set to full
 *   transparent black (all components set to zero).  This is convenient
 *   for example, to quickly remove low value voxels that represent
 *   "noise" in the data.  But note that this reduces the resolution of
 *   the color map.  In general it's better to change the range of data
 *   values mapped into the color map (see SoDataRange).
 *
 *   This node also supports a "faux shading" technique that can produce
 *   results somewhat similar to surface shading without the performance
 *   penalty for computing lighting.  Faux shading modifies the lower
 *   portion of the color map so that color and opacity ramp down to zero.
 *   Faux shading is controlled by the #fauxShadingLength, #fauxShadingStrength,
 *   and #fauxShadingDarkenThreshold fields.
 *      @TABLE_1B
 *         @TR No Faux Shading @TD Faux Shading
 *         @TR     @IMAGE volume_noedges.jpg
 *             @TD @IMAGE fauxshading.jpg
 *      @TABLE_END
 *
 *   The #actualColorMap field always contains the actual color values (after
 *   remapping, faux shading, etc have been applied) that will be used for rendering.
 *
 *   This node acts on the rendering shape nodes of VolumeViz (SoVolumeRender, SoOrthoSlice,
 *   SoObliqueSlice, SoVolumeSkin, etc.) and ReservoirViz (SoMeshLogicalSlice, SoMeshSkin  etc.)
 *
 *   Note that modifying the color map when using TEX3D or TEX2D rendering with
 *   RGBA (not paletted) textures will usually force the textures to be recreated,
 *   which may be slow.  See the SoVolumeData::usePalettedTexture field of SoVolumeData.
 *
 *   NOTE: When using an SoVolumeGroup, the SoTransferFunction node must
 *   be inserted after the SoVolumeData, not before.
 *
 * @FILE_FORMAT_DEFAULT
 *    TransferFunction {
 *    @TABLE_FILE_FORMAT
 *       @TR shift            @TD 0
 *       @TR offset           @TD 0
 *       @TR predefColorMap   @TD GREY
 *       @TR colorMapType     @TD RGBA
 *       @TR colorMap         @TD 0
 *       @TR actualColorMap   @TD 0
 *       @TR transferFunctionId   @TD 0
 *       @TR minValue @TD 0
 *       @TR maxValue @TD 255
 *       @TR fauxShadingStrength @TD 1
 *       @TR fauxShadingLength @TD 0
 *       @TR fauxShadingDarkenThreshold @TD 1
 *    @TABLE_END
 *    }
 *
 * @ACTION_BEHAVIOR
 * SoCallbackAction,
 * SoGLRenderAction @BR
 * Sets transfer function parameters in the traversal state.
 *
 * @SEE_ALSO
 *    SoDataRange,
 *    SoVolumeRender,
 *    SoOrthoSlice,
 *    SoObliqueSlice
 */

class LDM_API SoTransferFunction : public SoNode {
  SO_NODE_HEADER( SoTransferFunction );

 public:
  /**
   * This field allows the use of multiple transfer functions. @BR
   * By default all transfer function nodes are initialized to a transfer function id of 0.
   * If you want to use multiple transfer functions, a different id must be assigned to each
   * transfer function.
   * The transfer function id can be used in shader programs (see SoVolumeShader) to access
   * one of multiple transfer funcions and can also be used to associate a transfer function
   * with a volume mask (see SoVolumeMask).
   *
   * All active transfer functions are combined into a single 2D texture by "stacking" them
   * in order according to their ids. By default this texture is bound to OpenGL texture
   * unit 0. It is possible to change the texture unit used for transfer
   * functions by setting the preferences variable IVVR_TF_TEX_UNIT (see SoPreferences).
   *
   * Since OpenInventor 8.1, functions are provided which allow convenient access to a
   * specific transfer function in a GLSL fragment shader.  Although manual access
   * is still valid in this release, we recommend using the convenience functions to ensure
   * compatibility with future rendering features:
   * -vec4 VVizTransferFunction(float pos, int tfId): Returns the color at the normalized
   *  position @I pos @i in the transfer function @I tfId @i.
   * -vec4 VVizTransferFunction(float frontVoxel, float backVoxel, int tfId): Returns the
   *  preintegrated color between @I frontVoxel @i and @I backVoxel @i in the transfer
   *  function @I tfId @i.
   *
   * For manual access, the texture @I S @i coordinate specifies the entry in the color map
   * and the texture @I T @i coordinate specifies which color map to use.
   * If N is the number of color maps used, the rules are:
   *
   *   - Like all texture coordinates, the @I s @i and @I t @i coordinates range from 0 to 1.
   *   - The transferFunctionId ranges from 0 to N-1.
   *   - To access a specific transfer function, the @I t @i value passed must be between
   *     [ transferFunctionId / N, ( transferFunctionId + 1 ) / N ]
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoSFShort transferFunctionId;

  /**
   * Used for rescaling the input data values.
   * Before color association, the data value is re-scaled as follows:
   * <PRE>
   *      newvalue = value << #shift + #offset
   * </PRE>
   * By default, #shift = #offset = 0.
   */
   SoSFInt32 shift;
  /**
   * Used for rescaling the input data values.
   * See #shift.
   */
  SoSFInt32 offset;

  /**
  *
  * Remap the defined color map between @B minValue @b and @B maxValue @b indices. Entries
  * less than @B minValue @b and greater than @B maxValue @b are set to full transparent
  * black (all components set to zero).
  *
  * Setting minValue to 64 and maxValue to 192 while the predefined STANDARD color map is selected
  * makes the color map as shown:
  *
  * @IMAGE standardReMap.jpg
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
  */
  SoSFInt32 minValue;

  /**
   *
   * See #minValue field.
   * The value is automatically set to the number of colors in colorMap
   * minus 1 as long an explicit value is not specified.
   *
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFInt32 maxValue;

  /**
   *
   * Controls how many color values will be affected by faux shading.
   *
   * Valid values are between 0.0 and 1.0 (in other words a percentage of
   * the color map).  0.0 (the default) means no faux shading.
   * Faux shading is applied between minValue and minValue + ( maxValue - minValue ) * fauxShadingLength.
   * Faux shading darkens the color and reduces the opacity of the affected color map entries.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat fauxShadingLength;

  /**
   *
   * Controls how much faux shading will darken
   * the color values of the transfer function.
   *
   * Any value greater than 0.0 is valid.
   * 1.0 (the default) means a linear darkening progression.
   * Values greater than 1.0 darken the color map faster.
   * Values less than 1.0 darken the color map more slowly.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat fauxShadingStrength;

 /**
   *
   * Opacity threshold for darkening edges.
   *
   * Valid values are between 0.0 and 1.0.  The default is 1.0.
   * Only colors with opacity lower than
   * fauxShadingDarkenThreshold will be darkened.
   * Use this to prevent the volume from being globally darkened.
   * @BR @BR
   * @FIELD_SINCE_OIV 7.0
   */
  SoSFFloat fauxShadingDarkenThreshold;

  /**
   * Predefined color map.
   */
  enum PredefColorMap {
    /** No color map */
    NONE,
    /** Grey (Default) */
    GREY,
    /** Gray (Synonym of grey) */
    GRAY = GREY,
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
    BLUE_WHITE_RED,
    /** Intensity */
    INTENSITY
  };

  /**
   * Predefined color map to use.
   * Use enum #PredefColorMap. Default is GRAY.
   * All predefined color maps have 256 entries.
   *
   *    @TABLE_0B
   *       @TR GREY or GRAY   @TD @IMAGE grayColorMap.jpg
   *       @TR TEMPERATURE    @TD @IMAGE temperatureColorMap.jpg
   *       @TR PHYSICS        @TD @IMAGE physicsColorMap.jpg
   *       @TR STANDARD       @TD @IMAGE standardColorMap.jpg
   *       @TR GLOW           @TD @IMAGE glowColorMap.jpg
   *       @TR BLUE_RED       @TD @IMAGE blue_redcolormap.jpg
   *       @TR SEISMIC        @TD @IMAGE seismicColorMap.jpg
   *       @TR BLUE_WHITE_RED @TD @IMAGE blue_white_redcolormap.jpg
   *       @TR INTENSITY      @TD @IMAGE intensityColorMap.jpg
   *    @TABLE_END
   *
   * NOTE: The checkerboard pattern shows through where the color map alpha (opacity)
   * value is less than 1.0.
   *
   *
   * If this field is set to NONE, the #colorMap and #colorMapType fields must be set.
   */
  SoSFEnum predefColorMap;

  /** Available color map type */
  enum ColorMapType {
    /** (1 floats) */
    ALPHA,
    /** (2 floats) */
    LUM_ALPHA,
    /** (4 floats) */
    RGBA
  };

  /**
   * ColorMap type (number of color components).
   * Use enum #ColorMapType. Default is RGBA.
   *
   * ALPHA means one alpha component per color.
   *
   * LUM_ALPHA means two components per color, luminance and alpha. In such a case the
   * colorMap float array contains a list of two floats. Index 0 is luminance, index
   * 1 is alpha, index 2 is luminance, index 3 is alpha and so on.
   *
   * RGBA means four components per color, ordered red, green, blue, then alpha.
   * alpha.
   *
   * An alpha value equal to zero means "fully transparent", an alpha value equal to
   * one means "completely opaque" (exactly the inverse of transparency in SoMaterial).
   */
  SoSFEnum  colorMapType;

  #ifdef OIV_NET_DOC
 /**
   * Array of floats in the range [0,1]. The number of floats depends on #colorMapType.
   * It is equal to the number of colors defined multiplied by the number of components
   * per color. For example, for an RGBA color map of length n, there should 4*n float
   * values in the field.
   *
   * NOTE: Changing a value in the colorMap field automatically updates the #actualColorMap field.
   * Thus it can be very inefficient to set the color map entries one at a time using
   * set1Value(). To avoid a performance decrease we recommend using one of the
   * following techniques, particularly when changing many values:
   *
   * - Use the setValues method instead of set1Value.
   *
   * - Use the startEditing/finishEditing methods. For example,@BR @BR
   *      colorMap.StartEditing(); @BR
   *      <change colorMap field> @BR
   *      colorMap.FinishEditing();@BR
   *
   * - Disable notifications on the field.
   *
   */
 #else
  /**
   * Array of floats in the range [0,1] defining a color map. @BR
   * The number of floats needed depends on #colorMapType.
   * It is equal to the number of colors in the color map multiplied by the number of
   * components in each color. For example, for an RGBA color map of length N,
   * there must be 4*N float values in the field.
   *
   * NOTE: Changing a value in the colorMap field automatically updates the #actualColorMap field.
   * Thus it can be very inefficient to set the color map entries one at a time using
   * #set1Value(). To avoid a performance decrease we recommend using one of the
   * following techniques, particularly when changing many values:
   *
   * - Use the setValues method instead of set1Value.
   *
   * - Use the startEditing/finishEditing methods. For example,@BR @BR
   *      colorMap.startEditing(); @BR
   *      \<change colorMap field\> @BR
   *      colorMap.finishEditing();@BR
   *
   * - Disable notifications on the field. For example,@BR @BR
   *   m_transferFunc->colorMap.enableNotify(false) ;@BR
   *   \<your code\> @BR
   *   m_transferFunc->colorMap.enableNotify(true) ;@BR
   *   m_transferFunc->colorMap.touch() ;@BR
   *
   */
#endif
  SoMFFloat colorMap;

  /**
   * This field contains the actual color map used.
   * It is set automatically according to the value of the other fields.
   * The method reMap() modifies this field as well.
   * You may modify this field, and your changes will be taken into account during rendering.
   * However these changes will be lost as soon as the other fields are changed.
   *
   * @FIELD_SINCE_OIV 6.0
   */
  SoMFFloat actualColorMap;

  /**
   * Constructor
   */
  SoTransferFunction();

  /**
   * Returns TRUE if the current color map contains alpha values less than 1.
   * FALSE means the color map is completely opaque.
   */
  SbBool hasTransparency() const;

  /**
   * Load colormap from a file.
   * Returns true if successful.  The specified file name must have an
   * extension of either ".am" or ".col".
   *
   * Note: This method loads RGBA values into the colorMap field, but
   * the application must still set the predefColorMap field to NONE
   * for the custom colormap values to be used.
   * 
   * Supported formats:
   * - .am  : Avizo Colormap v1.0
   * - .col : Avizo Colormap v2.0
   *
   */
  virtual SbBool loadColormap(const SbString& filename);

  /**
   * @deprecated No longer used. Use the #minValue and #maxValue fields instead.
   * @DEPRECATED_SINCE_OIV 7.0
   */
  SoDEPRECATED void reMap(int min, int max);

  //------------------------------------------------------------------------------

 SoEXTENDER public:
  virtual void doAction( SoAction *action );
  virtual void callback( SoCallbackAction *action );
  virtual void GLRender( SoGLRenderAction *action );
  virtual void pick(SoPickAction *action) ;
  virtual void write(SoWriteAction *action);

  //------------------------------------------------------------------------------
 SoINTERNAL public:
  typedef float OpacityCorrectionFunction(float alpha, void* userData);

  /** Handle field change */
  virtual void notify(SoNotList *list);

  static void initClass();
  static void exitClass();

  int getPackedColorMap(unsigned int * &, int);
  static unsigned int  getDefaultPackedColor(unsigned int);
  enum GLColorMapType {
    NO_COLORMAP = 0,
    TEX_SHARED_PALETTE = 1,
    TEX_FRAGMENT_PROGRAM = 2
  };

  GLColorMapType installColorMap(SoState*, int alphaUse, bool useArbShader);
  /**
   * Apply f on all alpha values before sending the colormap to GL
   */
  GLColorMapType installColorMap(SoState*, int, OpacityCorrectionFunction* f, void* userData, bool useArbShader);
  GLColorMapType getColorMapType();
  int m_colorMapMin;
  int m_colorMapMax;

  /**
   * Do opacity correction on the buffer allRgba of size numRgba
   */
  void applyOpacityCorrection(unsigned int* allRgba, size_t numRgba,
                              OpacityCorrectionFunction* f, void* userData);
  /*
   * Returns TRUE if the colormap is fully transparent between the given min max values.
   */
  SbBool isFullyTransparent(int64_t min, int64_t max, int alphaUse = 0);

  //for cluster command, list of method to sync
  enum Cmd{
    REMAP = 0
  };

  void  getCMBuffer( int alphaUse, int nrgba, unsigned int *rgba );

  /**
   * Return true if all value between min and max are transparent
   */
  inline bool isTransparent(size_t min, size_t max, float materialTransparency);

  /** Return the palette texture */
  SoGLTexture* getTexture() const { return m_texPalette; }

  /** Return the number of color in thetransfer function.
   * A color is a alpha value, a alpha-lum pair or a RGBA quad according to colorMapType
   */
  inline unsigned int getNumColors() const;

  /** True if there is only 0/1 transparency */
  inline bool isBinary() const;

  /** Fill tex with a set of preintegrated tf  on each depth */
  static void createPreIntegratedTexture(SoState *state, SoGLTexture* tex3d);

  /** Return the needed texture height for tf id between minTfId and maxTfId  */
  static int getTextureHeight(int minTfId, int maxTfId);

  /**
   * Return the number of component according to colormapType
   */
  size_t getNumComponents() const;

 protected:
  // Destructor
  virtual ~SoTransferFunction();
 private:
  /** true if tf1->id < tf2->id */
  static bool maxTfId(SoTransferFunction* tf1, SoTransferFunction* tf2);

  /** true if tf1->numColors < tf2->numColors */
  static bool maxNumColor(SoTransferFunction* tf1, SoTransferFunction* tf2);

  /** Compute preintegrated transfer function */
  void getPreintegratedTf(unsigned char *destPtr);

  /** Return the max tf id in the list */
  static int getMaxTransferFunctionId(const SoTransferFunctionElement::TransferFunctionVector& tfList);

  /** Return the min tf id in the list */
  static int getMinTransferFunctionId(const SoTransferFunctionElement::TransferFunctionVector& tfList);

  /** Return the needed texture depth for tf id between minTfId and maxTfId  */
  static int getTextureDepth(int minTfId, int maxTfId);

  /** Return position of the transfer function in the texture
   * Will be a row number for 2D tf, a depth number for 3D
   */
  int getTransferFunctionPosInTexture(int maxTfId);

  int            m_numrgba;
  unsigned int  *m_rgba;
  std::vector<unsigned int> m_allRgba; //used for multiple transfer function.
  unsigned int  *m_rgbau;
  SbBool         m_hasTransparency;

  //true if there is only 0/1 transparency
  bool m_isBinary;

  SoNodeSensor  m_nodeSensor;
  static void nodeSensorCB(void *data, SoSensor *sensor);

  //Really do the remap
  void updateActualCM();
  void reMapInternal(int min, int max);
  void applyFauxShading();

  float m_fauxShadingStrength;
  float m_fauxShadingLength;
  float m_fauxShadingDarkenThreshold;

  /**
   * True as soon user changes min/maxValue.
   * When true, stop to update automatically maxValue
   * each time colorMap size changes
   */
  bool m_userDefinedMinMax;


  /**
   * Fill m_summedOpacity such as:
   * m_summedOpacity[i] = sum(0,i) alpha[j]
   */
  void computeSummedOpacity();

  void           buildActualCM();
  void           buildPackedCM();
  static void    fieldsChangedCB1(void *, SoSensor *);
  static void    fieldsChangedCB2(void *, SoSensor *);

  static void setRGBA(std::vector<unsigned char>& dest, int offset, int r, int g, int b, int a);

  SoGLTexture* m_texPalette;

  std::vector<float> m_summedOpacity;

  /** store cache for preintegrated transferFunction */
  uint64_t m_tfPreintegratedTimeStamp;
  std::vector<unsigned char> m_tfPreintegrated;

  /**
   * Texture unit for the transfer function
   */
  unsigned int m_tfTexUnit;

  int loadAvizoColormap( FILE *file, int &numComps, float *&values );

};

/******************************************************************************/
bool
SoTransferFunction::isTransparent(size_t min, size_t max, float materialTransparency)
{
  // Convert min/max into an index following the OpenGL specs for texture nearest addressing.
  // So we can address transfer function mapping in the same way as OpenGL.
  size_t numEntries = m_summedOpacity.size()-1;
  min = size_t(min/255.*(numEntries-1));
  max = size_t(max/255.*(numEntries-1));

  assert(min<=max);
  assert(min<m_summedOpacity.size());
  assert(max+1<m_summedOpacity.size());
  float summedOpacity = m_summedOpacity[max+1]-m_summedOpacity[min];

  return summedOpacity*materialTransparency <= std::numeric_limits<float>::epsilon();
}

/******************************************************************************/
bool
SoTransferFunction::isBinary() const
{
  return m_isBinary;
}

/******************************************************************************/
unsigned int
SoTransferFunction::getNumColors() const
{
  return actualColorMap.getNum() / 4;
}

#if defined(_WIN32)
#pragma warning( pop )
#pragma warning(disable:4251)
#endif

#endif // _SO_TRANSFER_FUNCTION_
