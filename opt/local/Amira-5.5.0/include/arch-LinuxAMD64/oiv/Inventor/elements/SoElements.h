/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_ELEMENTS_
#define  _SO_ELEMENTS_

#include <Inventor/elements/SoAnnoText3CharOrientElement.h>
#include <Inventor/elements/SoAnnoText3FontSizeHintElement.h>
#include <Inventor/elements/SoAnnoText3RenderPrintElement.h>
#include <Inventor/elements/SoBBoxModelMatrixElement.h>
#include <Inventor/elements/SoBBoxTypeElement.h>
#include <Inventor/elements/SoBumpMappingPropertyElement.h>
#include <Inventor/elements/SoCacheElement.h>
#include <Inventor/elements/SoClipPlaneElement.h>
#include <Inventor/elements/SoColorMapElement.h>
#include <Inventor/elements/SoComplexityElement.h>
#include <Inventor/elements/SoComplexityTypeElement.h>
#include <Inventor/elements/SoCoordinateElement.h>
#include <Inventor/elements/SoCreaseAngleElement.h>
#include <Inventor/elements/SoDecimationPercentageElement.h>
#include <Inventor/elements/SoDecimationTypeElement.h>
#include <Inventor/elements/SoDepthBufferElement.h>
#include <Inventor/elements/SoDepthOffsetElement.h>
#include <Inventor/elements/SoDrawStyleElement.h>
#include <Inventor/elements/SoEnvironmentElement.h>
#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/elements/SoFocalDistanceElement.h>
#include <Inventor/elements/SoFontNameElement.h>
#include <Inventor/elements/SoFontRenderStyleElement.h>
#include <Inventor/elements/SoFontSizeElement.h>
#include <Inventor/elements/SoFullSceneAntialiasingElement.h>
#include <Inventor/elements/SoGLCacheContextElement.h>
#include <Inventor/elements/SoGLClipPlaneElement.h>
#include <Inventor/elements/SoGLColorMapElement.h>
#include <Inventor/elements/SoGLCoordinateElement.h>
#include <Inventor/elements/SoGLDepthBufferElement.h>
#include <Inventor/elements/SoGLDrawStyleElement.h>
#include <Inventor/elements/SoGLEnvironmentElement.h>
#include <Inventor/elements/SoGLExtTextureImageElement.h>
#include <Inventor/elements/SoGLFullSceneAntialiasingElement.h>
#include <Inventor/elements/SoGLLazyElement.h>
#include <Inventor/elements/SoGLLightIdElement.h>
#include <Inventor/elements/SoGLLinePatternElement.h>
#include <Inventor/elements/SoGLLineWidthElement.h>
#include <Inventor/elements/SoGLModelMatrixElement.h>
#include <Inventor/elements/SoGLNormalElement.h>
#include <Inventor/elements/SoGLPatternElement.h>
#include <Inventor/elements/SoGLPointSizeElement.h>
#include <Inventor/elements/SoGLPolygonOffsetElement.h>
#include <Inventor/elements/SoGLProjectionMatrixElement.h>
#include <Inventor/elements/SoGLRenderPassElement.h>
#include <Inventor/elements/SoGLShaderProgramElement.h>
#include <Inventor/elements/SoGLShadowStyleElement.h>
#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/elements/SoGLTexture3EnabledElement.h>
#include <Inventor/elements/SoGLTextureCombinerElement.h>
#include <Inventor/elements/SoGLTextureCoordinate3Element.h>
#include <Inventor/elements/SoGLTextureCoordinateElement.h>
#include <Inventor/elements/SoGLTextureCubeMapEnabledElement.h>
#include <Inventor/elements/SoGLTextureEnabledElement.h>
#include <Inventor/elements/SoGLTextureImage3Element.h>
#include <Inventor/elements/SoGLTextureImageElement.h>
#include <Inventor/elements/SoGLTextureMatrixElement.h>
#include <Inventor/elements/SoGLTextureUnitElement.h>
#include <Inventor/elements/SoGLTransparencyTypeElement.h>
#include <Inventor/elements/SoGLUniformShaderParameterElement.h>
#include <Inventor/elements/SoGLUpdateAreaElement.h>
#include <Inventor/elements/SoGLViewingMatrixElement.h>
#include <Inventor/elements/SoGLViewportRegionElement.h>
#include <Inventor/elements/SoInt32Element.h>
#include <Inventor/elements/SoInteractiveComplexityElement.h>
#include <Inventor/elements/SoLightAttenuationElement.h>
#include <Inventor/elements/SoLightElement.h>
#include <Inventor/elements/SoLinePatternElement.h>
#include <Inventor/elements/SoLineWidthElement.h>
#include <Inventor/elements/SoLocalBBoxMatrixElement.h>
#include <Inventor/elements/SoMaterialBindingElement.h>
#include <Inventor/elements/SoMaterialElement.h>
#include <Inventor/elements/SoModelMatrixElement.h>
#include <Inventor/elements/SoNeighborToleranceElement.h>
#include <Inventor/elements/SoNormalBindingElement.h>
#include <Inventor/elements/SoNormalElement.h>
#include <Inventor/elements/SoNurbsPropertyElement.h>
#include <Inventor/elements/SoOverrideElement.h>
#include <Inventor/elements/SoPatternElement.h>
#include <Inventor/elements/SoPickRayElement.h>
#include <Inventor/elements/SoPickStyleElement.h>
#include <Inventor/elements/SoPointSizeElement.h>
#include <Inventor/elements/SoPolygonOffsetElement.h>
#include <Inventor/elements/SoProfileCoordinateElement.h>
#include <Inventor/elements/SoProfileElement.h>
#include <Inventor/elements/SoProjectionMatrixElement.h>
#include <Inventor/elements/SoRenderObjectListElement.h>
#include <Inventor/elements/SoShaderProgramElement.h>
#include <Inventor/elements/SoShapeHintsElement.h>
#include <Inventor/elements/SoShapeStyleElement.h>
#include <Inventor/elements/SoSwitchElement.h>
#include <Inventor/elements/SoTextAliasingFactorElement.h>
#include <Inventor/elements/SoTextAlignmentHElement.h>
#include <Inventor/elements/SoTextAlignmentVElement.h>
#include <Inventor/elements/SoTextStyleElement.h>
#include <Inventor/elements/SoTextStyleColorsElement.h>
#include <Inventor/elements/SoTextKerningElement.h>
#include <Inventor/elements/SoTextMarginElement.h>
#include <Inventor/elements/SoTextOrientationElement.h>
#include <Inventor/elements/SoTextOutlineEnabledElement.h>
#include <Inventor/elements/SoTextureCoordinate3Element.h>
#include <Inventor/elements/SoTextTextureQualityRangeElement.h>
#include <Inventor/elements/SoTextureCoordinateBindingElement.h>
#include <Inventor/elements/SoTextureCoordinateElement.h>
#include <Inventor/elements/SoTextureImage3Element.h>
#include <Inventor/elements/SoTextureImageElement.h>
#include <Inventor/elements/SoTextureMatrixElement.h>
#include <Inventor/elements/SoTextureNameElement.h>
#include <Inventor/elements/SoTextureQualityElement.h>
#include <Inventor/elements/SoTextureSendingEnabledElement.h>
#include <Inventor/elements/SoTextureTransformElement.h>
#include <Inventor/elements/SoTextureUnitElement.h>
#include <Inventor/elements/SoTransparencyTypeElement.h>
#include <Inventor/elements/SoUniformShaderParameterElement.h>
#include <Inventor/elements/SoUnitsElement.h>
#include <Inventor/elements/SoVertexShaderParameterElement.h>
#include <Inventor/elements/SoViewVolumeElement.h>
#include <Inventor/elements/SoViewingMatrixElement.h>
#include <Inventor/elements/SoViewportRegionElement.h>
#include <Inventor/elements/SoWindowElement.h>

// New nodes for beveling
#include <Inventor/elements/SoEdgeFlagElement.h>
#include <Inventor/elements/SoVertexFlagElement.h>
#include <Inventor/elements/SoBevelPropertyElement.h>

// Elements for tiled rendering
#include <Inventor/elements/SoLogicalViewportElement.h>
#include <Inventor/elements/SoModifyLogicalViewportElement.h>
#include <Inventor/elements/SoModifyViewVolumeElement.h>

// Element for stereo for MP
#include <Inventor/elements/SoStereoElement.h>

// Elements for DirectViz rendering
#include <Inventor/elements/SoDirectVizEnvironmentShaderElement.h>
#include <Inventor/elements/SoDirectVizCameraShaderElement.h>
#include <Inventor/elements/SoDirectVizShaderElement.h>
#include <Inventor/elements/SoDirectVizLightShaderElement.h>

#include <Inventor/elements/SoProjectionElement.h>

// Elements for Georeferencing
#include <Inventor/elements/SoGeoRenderElement.h>
#include <Inventor/elements/SoGeoOriginElement.h>
#endif /* _SO_ELEMENTS_ */
