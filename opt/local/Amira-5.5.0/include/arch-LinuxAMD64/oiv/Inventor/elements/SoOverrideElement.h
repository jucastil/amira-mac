/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Roger Chickering (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_OVERRIDE_ELEMENT
#define  _SO_OVERRIDE_ELEMENT

#include <Inventor/elements/SoSubElement.h>

//
// Macro to implement get*Override inline methods.  There are a lot of
// these methods, each of which has an identical implementation and
// which needs to be inline to keep traversal fast.
#define SO_GET_OVERRIDE(flag)     \
  const SoOverrideElement *elt;                                       \
  elt = SoElement::getConstElement<SoOverrideElement>(state); \
  return (elt->flags & flag)!=0;

//
// Implement set*Override methods.
//
#define SO_SET_OVERRIDE(flag)                                       \
  SoOverrideElement   *elt;                                         \
  elt = SoElement::getElement<SoOverrideElement>(state); \
  if (override)                                                     \
    elt->flags |= flag;                                             \
  else                                                              \
    elt->flags &= ~flag;

/**
*   Stores a flag for each type of element which can be
*   overridden.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores a flag for each type of element which can be
*   overridden. Nodes implement override by setting the appropriate
*   bit if their override flag is on, and ignoring overridden elements
*   if the corresponding bit in the state's SoOverrideElement is set.
*
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoOverrideElement : public SoElement {

  SO_ELEMENT_HEADER(SoOverrideElement);

  enum {
    AMBIENT_COLOR    = 0x1,
    COLOR_INDEX      = 0x2,
    COMPLEXITY       = 0x4,
    COMPLEXITY_TYPE  = 0x8,
    CREASE_ANGLE     = 0x10,
    DIFFUSE_COLOR    = 0x20,
 /**
 *  TRANSPARENCY is same as diffuse color: overriding one will override both.
 */
    TRANSPARENCY     = 0x20,
    DRAW_STYLE       = 0x40,
    EMISSIVE_COLOR   = 0x80,
    FONT_NAME        = 0x100,
    FONT_SIZE        = 0x200,
    LIGHT_MODEL      = 0x400,
    LINE_PATTERN     = 0x800,
    LINE_WIDTH       = 0x1000,
    MATERIAL_BINDING = 0x2000,
    POINT_SIZE       = 0x4000,
    PICK_STYLE       = 0x8000,
    SHAPE_HINTS      = 0x10000,
    SHININESS        = 0x20000,
    SPECULAR_COLOR   = 0x40000,
    POLYGON_OFFSET   = 0x80000,
    PATTERN_OFFSET   = 0x100000,
    FONT_RENDERSTYLE = 0x200000,
    FULL_SCENE_ANTIALIASING = 0x400000,
    TRANSPARENCY_TYPE = 0x800000,
    ENVIRONMENT       = 0x1000000,
    DEPTH_BUFFER_RANGE = 0x2000000,
    DEPTH_BUFFER_FUNCTION = 0x4000000,
    BBOX_TYPE         = 0x8000000,
    NEIGHBOR_TOLERANCE = 0x10000000
  };

 public:
  /**
  *  Comparison based on value of int32_ts.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Overrides push() method to copy values from next instance in
  *  the stack, and set up cache dependencies correctly.
  */
  virtual void push(SoState *state);

  //
  // "get" methods for each element which can be overridden.
  //

  /**
  *  Returns TRUE if SoAmbientColorElement is overridden.
  */
  static SbBool getAmbientColorOverride(SoState *state)
    { SO_GET_OVERRIDE(AMBIENT_COLOR); }

  /**
  *  Returns TRUE if SoColorIndexElement is overridden.
  */
  static SbBool getColorIndexOverride(SoState *state)
    { SO_GET_OVERRIDE(COLOR_INDEX); }

  /**
  *  Returns TRUE if SoComplexityElement is overridden.
  */
  static SbBool getComplexityOverride(SoState *state)
    { SO_GET_OVERRIDE(COMPLEXITY); }

  /**
  *  Returns TRUE if SoComplexityTypeElement is overridden.
  */
  static SbBool getComplexityTypeOverride(SoState *state)
    { SO_GET_OVERRIDE(COMPLEXITY_TYPE); }

  /**
  *  Returns TRUE if SoCreaseAngleElement is overridden.
  */
  static SbBool getCreaseAngleOverride(SoState *state)
    { SO_GET_OVERRIDE(CREASE_ANGLE); }

  /**
  *  Returns TRUE if SoNeighborToleranceElement is overridden.
  */
  static SbBool getNeighborToleranceOverride(SoState *state)
    { SO_GET_OVERRIDE(NEIGHBOR_TOLERANCE); }

  /**
  *  Returns TRUE if SoDiffuseColorElement is overridden.
  */
  static SbBool getDiffuseColorOverride(SoState *state)
    { SO_GET_OVERRIDE(DIFFUSE_COLOR); }

  /**
  *  Returns TRUE if SoDrawStyleElement is overridden.
  */
  static SbBool getDrawStyleOverride(SoState *state)
    { SO_GET_OVERRIDE(DRAW_STYLE); }

  /**
  *  Returns TRUE if SoEmissiveColorElement is overridden.
  */
  static SbBool getEmissiveColorOverride(SoState *state)
    { SO_GET_OVERRIDE(EMISSIVE_COLOR); }

  /**
  *  Returns TRUE if SoFontNameElement is overridden.
  */
  static SbBool getFontNameOverride(SoState *state)
    { SO_GET_OVERRIDE(FONT_NAME); }

  /**
  *  Returns TRUE if SoFontSizeElement is overridden.
  */
  static SbBool getFontSizeOverride(SoState *state)
    { SO_GET_OVERRIDE(FONT_SIZE); }

  /**
  *  Returns TRUE if SoFontRenderStyleElement is overridden.
  */
  static SbBool getFontRenderStyleOverride(SoState *state)
    { SO_GET_OVERRIDE(FONT_RENDERSTYLE); }

  /**
  *  Returns TRUE if SoLightModelElement is overridden.
  */
  static SbBool getLightModelOverride(SoState *state)
    { SO_GET_OVERRIDE(LIGHT_MODEL); }

  /**
  *  Returns TRUE if SoLinePatternElement is overridden.
  */
  static SbBool getLinePatternOverride(SoState *state)
    { SO_GET_OVERRIDE(LINE_PATTERN); }

  /**
  *  Returns TRUE if SoLineWidthElement is overridden.
  */
  static SbBool getLineWidthOverride(SoState *state)
    { SO_GET_OVERRIDE(LINE_WIDTH); }

  /**
  *  Returns TRUE if SoMaterialBindingElement is overridden.
  */
  static SbBool getMaterialBindingOverride(SoState *state)
    { SO_GET_OVERRIDE(MATERIAL_BINDING); }

  /**
  *  Returns TRUE if SoPointSizeElement is overridden.
  */
  static SbBool getPointSizeOverride(SoState *state)
    { SO_GET_OVERRIDE(POINT_SIZE); }

  /**
  *  Returns TRUE if SoPickStyleElement is overridden.
  */
  static SbBool getPickStyleOverride(SoState *state)
    { SO_GET_OVERRIDE(PICK_STYLE); }

  /**
  *  Returns TRUE if SoShapeHintsElement is overridden.
  */
  static SbBool getShapeHintsOverride(SoState *state)
    { SO_GET_OVERRIDE(SHAPE_HINTS); }

  /**
  *  Returns TRUE if SoShininessElement is overridden.
  */
  static SbBool getShininessOverride(SoState *state)
    { SO_GET_OVERRIDE(SHININESS); }

  /**
  *  Returns TRUE if SoSpecularColorElement is overridden.
  */
  static SbBool getSpecularColorOverride(SoState *state)
    { SO_GET_OVERRIDE(SPECULAR_COLOR); }

  /**
  *  Returns TRUE if SoTransparencyElement is overridden.
  */
  static SbBool getTransparencyOverride(SoState *state)
    { SO_GET_OVERRIDE(TRANSPARENCY); }

  /**
  *  Returns TRUE if SoTransparencyTypeElement is overridden.
  */
  static SbBool getTransparencyTypeOverride(SoState *state)
    { SO_GET_OVERRIDE(TRANSPARENCY_TYPE); }

  /**
  *  Returns TRUE if SoEnvironmentElement is overridden.
  */
  static SbBool getEnvironmentOverride(SoState *state)
    { SO_GET_OVERRIDE(ENVIRONMENT); }

  /**
  *  Returns TRUE if SoPolygonOffsetElement is overridden.
  */
  static SbBool getPolygonOffsetOverride(SoState *state)
    { SO_GET_OVERRIDE(POLYGON_OFFSET); }

  /**
  *  Returns TRUE if SoPatternElement is overriden.
  */
  static SbBool getPatternOverride(SoState* state)
    { SO_GET_OVERRIDE(PATTERN_OFFSET); }

  /**
  *  Returns TRUE if SoFullSceneAntialiasingElement is overridden.
  */
  static SbBool getFullSceneAntialiasingOverride(SoState *state)
    { SO_GET_OVERRIDE(FULL_SCENE_ANTIALIASING); }

  /**
  *  Returns TRUE if SoDepthBuffer::range  is overridden.
  */
  static SbBool getDepthBufferRangeOverride(SoState *state)
    { SO_GET_OVERRIDE(DEPTH_BUFFER_RANGE); }

  /**
  *  Returns TRUE if SoDepthBuffer::function is overridden.
  */
  static SbBool getDepthBufferFunctionOverride(SoState *state)
    { SO_GET_OVERRIDE(DEPTH_BUFFER_FUNCTION); }

  /**
  *  Returns TRUE if SoComplexityType::bboxType is overridden.
  */
  static SbBool getBBoxTypeOverride(SoState *state)
    { SO_GET_OVERRIDE(BBOX_TYPE); }

  //
  // "set" methods for each element which can be overridden.
  //

  /**
  *  Set override flag for SoAmbientColorElement.
  */
  static void setAmbientColorOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(AMBIENT_COLOR); }

  /**
  *  Set override flag for SoColorIndexElement.
  */
  static void setColorIndexOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(COLOR_INDEX); }

  /**
  *  Set override flag for SoComplexityElement.
  */
  static void setComplexityOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(COMPLEXITY); }

  /**
  *  Set override flag for SoComplexityTypeElement.
  */
  static void setComplexityTypeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(COMPLEXITY_TYPE); }

  /**
  *  Set override flag for SoCreaseAngleElement.
  */
  static void setCreaseAngleOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(CREASE_ANGLE); }

  /**
  *  Set override flag for SoNeighborToleranceElement.
  */
  static void setNeighborToleranceOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(NEIGHBOR_TOLERANCE); }

  /**
  *  Set override flag for SoDiffuseColorElement.
  */
  static void setDiffuseColorOverride(SoState *state, SoNode *, SbBool override);

  /**
  *  Set override flag for SoDrawStyleElement.
  */
  static void setDrawStyleOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(DRAW_STYLE); }

  /**
  *  Set override flag for SoEmissiveColorElement.
  */
  static void setEmissiveColorOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(EMISSIVE_COLOR); }

  /**
  *  Set override flag for SoFontNameElement.
  */
  static void setFontNameOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(FONT_NAME); }

  /**
  *  Set override flag for SoFontSizeElement.
  */
  static void setFontSizeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(FONT_SIZE); }

  /**
  *  Set override flag for SoFontRenderStyleElement.
  */
  static void setFontRenderStyleOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(FONT_RENDERSTYLE); }

  /**
  *  Set override flag for SoLightModelElement.
  */
  static void setLightModelOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(LIGHT_MODEL); }

  /**
  *  Set override flag for SoLinePatternElement.
  */
  static void setLinePatternOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(LINE_PATTERN); }

  /**
  *  Set override flag for SoLineWidthElement.
  */
  static void setLineWidthOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(LINE_WIDTH); }

  /**
  *  Set override flag for SoMaterialBindingElement.
  */
  static void setMaterialBindingOverride(SoState *state, SoNode *, SbBool override);

  /**
  *  Set override flag for SoPickStyleElement.
  */
  static void setPickStyleOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(PICK_STYLE); }

  /**
  *  Set override flag for SoPointSizeElement.
  */
  static void setPointSizeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(POINT_SIZE); }

  /**
  *  Set override flag for SoShapeHintsElement.
  */
  static void setShapeHintsOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(SHAPE_HINTS); }

  /**
  *  Set override flag for SoShininessElement.
  */
  static void setShininessOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(SHININESS); }

  /**
  *  Set override flag for SoSpecularColorElement.
  */
  static void setSpecularColorOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(SPECULAR_COLOR); }

  /**
  *  Set override flag for SoTransparencyElement.
  */
  static void setTransparencyOverride(SoState *state, SoNode *, SbBool override);

  /**
  *  Set override flag for SoTransparencyTypeElement.
  */
  static void setTransparencyTypeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(TRANSPARENCY_TYPE); }

  /**
  *  Set override flag for SoEnvironmentElement.
  */
  static void setEnvironmentOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(ENVIRONMENT); }

  /**
  *  Set override flag for SoPolygonOffsetElement.
  */
  static void setPolygonOffsetOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(POLYGON_OFFSET); }

  /**
  *  Set override flag for SoPatternElement.
  */
  static void setPatternOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(PATTERN_OFFSET); }

  /**
  *  Set override flag for SoFullSceneAntialiasingElement.
  */
  static void setFullSceneAntialiasingOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(FULL_SCENE_ANTIALIASING); }

  /**
  *  Set override flag for SoDepthBuffer::range.
  */
  static void setDepthBufferRangeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(DEPTH_BUFFER_RANGE); }

  /**
  *  Set override flag for SoDepthBuffer::function.
  */
  static void setDepthBufferFunctionOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(DEPTH_BUFFER_FUNCTION); }

  /**
  *  Set override flag for SoComplexity::bboxType.
  */
  static void setBBoxTypeOverride(SoState *state, SoNode *, SbBool override)
    { SO_SET_OVERRIDE(BBOX_TYPE); }

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoOverrideElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

  // Copy method, copies flags
  virtual SoElement *copyMatchInfo() const;

 private:
  // Used by ::print method
  void pFlag(FILE *, const char *, int) const;

  uint32_t flags;
};

#endif /* _SO_OVERRIDE_ELEMENT */

