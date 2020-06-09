/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Alan Norton (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_LAZY_ELEMENT
#define _SO_LAZY_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/SbColor.h>
#include <Inventor/elements/SoElement.h>
#include <Inventor/elements/SoSubElement.h>
#include <math.h>

class SoMFFloat;
class SoMFColor;
class SoColorPacker;
class SbThreadMutex;

/**
*  Threshold to ignore changes in shininess:
*/
#define SO_LAZY_SHINY_THRESHOLD 0.005

/**
*  Number of components (subelements) in this element:
*/
#define SO_LAZY_NUM_COMPONENTS 11

/**
*  Manages several properties that need to
*  be lazily tracked for OpenGL.
*
* @ingroup elements
*
*   @DESCRIPTION
*  This element manages several properties such as colors, that need to
*  be lazily tracked for OpenGL. Allows Open Inventor property nodes to
*  set these properties without immediately making any OpenGL calls.
*  Thus we avoid making redundant OpenGL calls to set, for example,
*  the material color. Open Inventor rendering nodes then request that
*  the values of any properties that are relevant to that shape and
*  "out of date" (not current with OpenGL state) be sent to OpenGL.
*
*  Includes: @BR
*  Transparencies @BR
*  GLColorMaterial@BR
*  GLBlendEnablement@BR
*  PolygonStipple@BR
*  Light model@BR
*  Color index@BR
*
*   @SEE_ALSO
*   SoBaseColor, SoMaterial, SoPackedColor, SoTransparencyType, SoVertexProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoLazyElement : public SoElement {

  SO_ELEMENT_HEADER(SoLazyElement);

 public:
 /**
 *  Following masks and cases define the components of the
 *  lazy element. Masks are needed by SoEXTENDER apps that
 *  need to use SoGLLazyElement::reset(bitmask) to invalidate
 *  GL values of particular components.
 *  NOTE: the order of these cases should not be changed without
 *  careful consideration of dependencies in the reallySend method.
 */
   /** Cases */
 enum cases {
   /** Light model case */
   LIGHT_MODEL_CASE = 0,
   /** Color material case */
   COLOR_MATERIAL_CASE = 1,
   /** Diffuse case */
   DIFFUSE_CASE = 2,
   /** Ambient case */
   AMBIENT_CASE = 3,
   /** Emissive case */
   EMISSIVE_CASE = 4,
   /** Specular case */
   SPECULAR_CASE = 5,
   /** Shininess case */
   SHININESS_CASE = 6,
   /** Blending case */
   BLENDING_CASE = 7,
   /** Transparency case */
   TRANSPARENCY_CASE = 8,
   /** Pattern case */
   PATTERN_CASE = 9,
   /** Smoothing case */
   SMOOTHING_CASE = 10
  };

 /** Masks */
 enum masks {
   /** Light model mask */
   LIGHT_MODEL_MASK = 1 << LIGHT_MODEL_CASE,
   /** Color mask */
   COLOR_MATERIAL_MASK = 1 << COLOR_MATERIAL_CASE,
   /** Diffuse mask */
   DIFFUSE_MASK = 1 << DIFFUSE_CASE,
   /** Ambient mask */
   AMBIENT_MASK = 1 << AMBIENT_CASE,
   /** Emissive mask */
   EMISSIVE_MASK = 1 << EMISSIVE_CASE,
   /** Specular mask */
   SPECULAR_MASK = 1 << SPECULAR_CASE,
   /** Shininess mask */
   SHININESS_MASK = 1 << SHININESS_CASE,
   /** Transparency mask */
   TRANSPARENCY_MASK = 1 << TRANSPARENCY_CASE,
   /** Blending mask */
   BLENDING_MASK = 1 << BLENDING_CASE,
   /** Smoothing mask */
   SMOOTHING_MASK = 1 << SMOOTHING_CASE,
   /** All masks */
   ALL_MASK = (1 << SO_LAZY_NUM_COMPONENTS)-1,
   /** Pattern mask */
   PATTERN_MASK = 1 << PATTERN_CASE
 };

  /**
  * Enum values to be used in setting/getting light model.
  */
  enum LightModel {
    /** Base color */
    BASE_COLOR = 0,
    /** Phong */
    PHONG = 1
  };

  /**
  *  Static set method.
  */
  /**
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY,IN]
   */
  static void setDiffuse(SoState *state,
                         SoNode *node,
                         int32_t numColors,
                         const SbColor *colors,
                         SoColorPacker *cPacker);
  /**
  *  Static set method.
  */
  /**
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(transp != NULL? transp->Length: 0)},ARRAY,IN]
   */
  static void setTransparency(SoState *state,
                              SoNode *node,
                              int32_t numTransp,
                              const float *transp,
                              SoColorPacker *cPacker);
  /**
  *  Static set method.
  */
  /**
   * [OIV-WRAPPER-ARG IN,IN,IN,NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY]
   */
  static void setPacked(SoState *state,
                        SoNode *node,
                        SoColorPacker *cPacker,
                        int32_t numColors,
                        const uint32_t *colors);
  /**
  *  Static set method.
  */
  /**
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(indices != NULL? indices->Length: 0)},ARRAY]
   */
  static void setColorIndices(SoState *state,
                              SoNode *node,
                              int32_t numIndices,
                              const int32_t *indices);

  /**
   * [OIV-WRAPPER-ARG IN,IN]
   */
  SoDEPRECATED static void setAmbient(SoState *state, const SbColor *color)
  { setAmbient(state,*color); }
  /**
   * [OIV-WRAPPER-ARG IN,IN]
   */
  SoDEPRECATED static void setEmissive(SoState *state, const SbColor *color)
  { setEmissive(state,*color); }
  /**
   * [OIV-WRAPPER-ARG IN,IN]
   */
  SoDEPRECATED static void setSpecular(SoState *state, const SbColor *color)
  { setSpecular(state,*color); }

  static void setAmbient(SoState *state, const SbColor &color);
  static void setEmissive(SoState *state, const SbColor &color);
  static void setSpecular(SoState *state, const SbColor &color);

  static void setShininess(SoState *state, float value);
  static void setColorMaterial(SoState *state, SbBool value);
  static void setBlending(SoState *state, SbBool value);
  static void setSmoothing(SoState *state, SbBool value);
  static void setLightModel(SoState *state, const int32_t model);

  /**
  *  get() methods get value from Inventor state. The public methods are
  *  static, they get an instance of the element. If there is a cache,
  *  the appropriate virtual registerGetDependence is called.
  */
  static const SbColor &getDiffuse(SoState *state, int index);
  /**
  *  get() methods get value from Inventor state. The public methods are
  *  static, they get an instance of the element. If there is a cache,
  *  the appropriate virtual registerGetDependence is called.
  */
  static float getTransparency(SoState *, int index);
  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetInstance(state)->GetNumDiffuse()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getInstance(state)->getNumDiffuse()}]
   */
  static const uint32_t *getPackedColors(SoState *state);
  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetInstance(state)->GetNumColorIndices()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getInstance(state)->getNumColorIndices()}]
   */
  static const int32_t *getColorIndices(SoState *state);
  static int32_t getColorIndex(SoState *, int num);
  static const SbColor &getAmbient(SoState *);
  static const SbColor &getEmissive(SoState *);
  static const SbColor &getSpecular(SoState *);
  static float getShininess(SoState *);
  static SbBool getColorMaterial(SoState *);
  static SbBool getBlending(SoState *);
  static SbBool getSmoothing(SoState *);
  static int32_t getLightModel(SoState *);

  /**
  *  Method to inquire about current colors.
  */
  int32_t getNumDiffuse() const {
    return ivState.numDiffuseColors;
  }
  /**
  *  Method to inquire about current colors.
  */
  int32_t getNumTransparencies() const {
    return ivState.numTransparencies;
  }
  /**
  *  Method to inquire about current colors.
  */
  int32_t getNumColorIndices() const {
    return (ivState.colorIndices ? ivState.numDiffuseColors : 0);
  }
  /**
  *  Method to inquire about current colors.
  */
  SbBool isPacked() const {
    return ivState.packed;
  }
  /**
  *  Method to inquire about current colors.
  */
  SbBool isTransparent() const;

  /**
  *  Returns the top (current) instance of the element in the state
  *  Note that the cache dependencies associated with this element
  *  are managed differently from other elements:
  *  this replaces the SoElement::getConstElement that is used by
  *  standard elements, but which causes cache dependency. Note
  *  that this element is not const; however modifications to it
  *  can cause problems. SoEXTENDER apps should use only SoEXTENDER
  *  methods on this element.
  */
  static SoLazyElement *getInstance(SoState *state) {
    return (SoLazyElement *)(state->getElementNoPush(SoLazyElement::getClassTypeId(), getClassStackIndex()));
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static float getDefaultAmbientIntensity() {
    return 0.2F;
  }

  /**
  * Specify Open Inventor defaults for colors, etc.
  */
  static SbColor getDefaultDiffuse() {
    return SbColor(0.8F, 0.8F, 0.8F);
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static SbColor getDefaultAmbient() {
    return SbColor(0.2F, 0.2F, 0.2F);
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static SbColor getDefaultSpecular() {
    return SbColor(0.0F, 0.0F, 0.0F);
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static SbColor getDefaultEmissive() {
    return SbColor(0.0F, 0.0F, 0.0F);
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static float getDefaultShininess() {
    return 0.2F;
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static uint32_t getDefaultPackedInternal();
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static uint32_t getDefaultPacked() {
    return (0xccccccff);
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static float getDefaultTransparency() {
    return 0.0F;
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static int32_t getDefaultLightModel() {
    return PHONG;
  }
  /**
  * Specify Open Inventor defaults for colors, etc.
  */
   static int32_t getDefaultColorIndex() {
    return 1;
  }

 SoINTERNAL public:

  // Initializes element
  virtual void init(SoState *state);

  // set method for use in SoMaterial nodes:
  static void setMaterials(SoState *state,
                           SoNode *node,
                           uint32_t bitmask,
                           SoColorPacker *cPacker,
                           const SoMFColor &diffuse,
                           const SoMFFloat &transp,
                           const SoMFColor &ambient,
                           const SoMFColor &emissive,
                           const SoMFColor &specular,
                           const SoMFFloat &shininess);

  // set method for use in SoMaterial nodes:
  static void setMaterials(SoState *state,
                           SoNode *node,
                           uint32_t bitmask,
                           SoColorPacker *cPacker,
                           SoMFColor *diffuse,
                           SoMFFloat *transp,
                           SoMFColor *ambient,
                           SoMFColor *emissive,
                           SoMFColor *specular,
                           SoMFFloat *shininess);

  // push (for non-GL elements)
  virtual void push(SoState *state);

  // note: matches, copyMatchinfo not used by this element.
  // they are replaced by lazyMatches, copyLazyMatchInfo, on
  // SoGLLazyElement.
  virtual SbBool matches(const SoElement *) const;

  virtual SoElement *copyMatchInfo() const;

  //Get a Writable instance, so will force a push if needed:
  static SoLazyElement  *getWInstance(SoState *state) {
    return state->getElement<SoLazyElement>();
  }

  // Prints element (for debugging)
  virtual void print(FILE *fp) const;

  // Initializes the SoLazyElement class
  static void initClass();
  static void exitClass();

  //Following SoINTERNAL get() methods do NOT cause cache dependency, should
  //only be invoked by nodes that use the reallySend method on SoGLLazyElement
  //to establish correct cache dependencies by tracking what was actually
  //sent to GL.
  const uint32_t *getPackedPointer() const {
    return ivState.packedColors;
  }
  const SbColor *getDiffusePointer() const {
    return ivState.diffuseColors;
  }
  const int32_t *getColorIndexPointer() const {
    return ivState.colorIndices;
  }
  const float *getTransparencyPointer() const {
    return ivState.transparencies;
  }

  // set method for transparency type is SoINTERNAL, because it should
  // only be invoked by SoGLRenderAction
  static void setTransparencyType(SoState *state, int32_t type);

  // set method for usePattern is SoINTERNAL, because it should
  // only be invoked by SoPatternElement
  static void setPatternFlag(SoState *state, SbBool flag);

  enum internalMasks {
    OTHER_COLOR_MASK = AMBIENT_MASK|EMISSIVE_MASK|SPECULAR_MASK|SHININESS_MASK,
    ALL_COLOR_MASK = OTHER_COLOR_MASK|DIFFUSE_MASK,
    NO_COLOR_MASK = ALL_MASK & (~ALL_COLOR_MASK),
    ALL_BUT_DIFFUSE_MASK = ALL_MASK &(~ DIFFUSE_MASK),
    DIFFUSE_ONLY_MASK = ALL_MASK &(~ OTHER_COLOR_MASK)
  };

  // method to register dependence due to get().
  // only the GL version does any work
  virtual void registerGetDependence(SoState *, uint32_t);

protected:

  // method to tell the cache that a redundant set was issued.
  // only the GL version does any work.
  virtual void registerRedundantSet(SoState *, uint32_t);



  //Struct to hold the inventor state:
  struct INVENTOR_API  __ivstate {
    // keep nodeID to compare diffuse GL and diffuse inventor state:
    // 0 is initial value, 1 is invalid
    uint64_t diffuseNodeId;

    // for transparency, keep either nodeid, or 0 if opaque. Value of
    // 1 indicates invalid.
    uint64_t transpNodeId;

    // store a value of each color component; ambient, emissive,
    // specular, shininess, or appropriate info to identify state.
    SbColor ambientColor;
    SbColor emissiveColor;
    SbColor specularColor;
    float shininess;
    int32_t colorMaterial;
    int32_t blending;
    int32_t smoothing;
    int32_t lightModel;
    int32_t stippleNum;

    // following are not used for matching GL & IV, but must
    // be copied on push:
    SbBool packed;
    SbBool packedTransparent;
    int32_t numDiffuseColors;
    int32_t numTransparencies;
    const SbColor *diffuseColors;
    const float *transparencies;
    const uint32_t *packedColors;
    const uint32_t *packedColors2;
    const int32_t *colorIndices;
    int32_t transpType;
    uint32_t cacheLevelSetBits;
    uint32_t cacheLevelSendBits;
    int32_t patternStippleNum;
  } ivState;

  virtual ~SoLazyElement();

  // This is more convenient here, but might logically be kept with
  // SoGLLazyElement. This is a bitmask indicating what components
  // have not been sent to GL.
  uint32_t invalidBits;

  // store pointers to the default color, transp so that we can set
  // point to them if no other color or transp has been set.
  static SbColor *defaultDiffuseColor;
  static float *defaultTransparency;
  static int32_t *defaultColorIndices;
  static uint32_t *defaultPackedColor;

  // Returns number of transparency levels supported with stipple
  // patterns. (Add one - solid - that is not included in this number.)
  static int getNumPatterns() {
    return 64;
  }
  // -1 = don't know yet, 0 = no transp, 1 = has transp
  int m_hasTransparency;

 private:
  // Virtual setElt methods, to be overridden by GL versions.
  virtual void setDiffuseElt(SoNode *,
                             int32_t numColors,
                             const SbColor *colors,
                             SoColorPacker *cPacker);
  virtual void setPackedElt(SoNode *,
                            int32_t numColors,
                            const uint32_t *colors,
                            SoColorPacker *cPacker);
  virtual void setColorIndexElt(SoNode *,
                                int32_t numIndices,
                                const int32_t *indices);
  virtual void setTranspElt(SoNode *,
                            int32_t numTrans,
                            const float *trans,
                            SoColorPacker *cPacker);
  virtual void setPatternFlagElt(SbBool flag);
  virtual void setTranspTypeElt(int32_t type);
  virtual void setAmbientElt(const SbColor *color);
  virtual void setEmissiveElt(const SbColor *color);
  virtual void setSpecularElt(const SbColor *color);
  virtual void setShininessElt(float value);
  virtual void setColorMaterialElt(SbBool value);
  virtual void setBlendingElt(SbBool value);
  virtual void setSmoothingElt(SbBool value);
  virtual void setLightModelElt(SoState *state, int32_t model);
  virtual void setMaterialElt(SoNode *,
                              uint32_t bitmask,
                              SoColorPacker *cPacker,
                              const SoMFColor &,
                              const SoMFFloat &,
                              const SoMFColor &,
                              const SoMFColor &,
                              const SoMFColor &,
                              const SoMFFloat &);
  virtual void setMaterialElt(SoNode *,
                              uint32_t bitmask,
                              SoColorPacker *cPacker,
                              SoMFColor *,
                              SoMFFloat *,
                              SoMFColor *,
                              SoMFColor *,
                              SoMFColor *,
                              SoMFFloat *);
};

///////////////////////////////////////////////////////////////////////////
//
// Class: SoColorPacker
// This class is meant to be used by all property nodes that set either
// a diffuse color or transparency in the lazy element. It maintains
// a cache of the current diffuse color and transparency in a packed
// color array.
//////////////////////////////////////////////////////////////////////////

class INVENTOR_API SoColorPacker {

 public:

  //Constructor, makes a colorPacker with NULL packedColor pointer:
  SoColorPacker();

  // destructor, deletes packed color array
  ~SoColorPacker();

  /**
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize()}]
   * [OIVJAVA-WRAPPER-RETURN-TYPE ARRAY{getSize()}]
   */
  uint32_t *getPackedColors() const {
    return packedColors;
  }
  SbBool diffuseMatch(uint64_t nodeId) {
    return (nodeId == diffuseNodeId);
  }
  SbBool transpMatch(uint64_t nodeId) {
    return (nodeId == transpNodeId);
  }
  void setNodeIds(uint64_t diffNodeId, uint64_t tNodeId) {
    diffuseNodeId = diffNodeId;
    transpNodeId = tNodeId;
  }
  int32_t getSize() {
    return packedArraySize;
  }
  void reallocate(int32_t size);

  static void exitClass();

 private:

  // nodeids are used for testing cache validity
  uint64_t transpNodeId;
  uint64_t diffuseNodeId;
  // array of packed colors, or NULL if empty
  uint32_t *packedColors;
  // size of packed color array (not necessarily number of valid colors)
  int32_t packedArraySize;

  static SbThreadMutex *m_mutex;

};

#endif /* _SO_LAZY_ELEMENT */

