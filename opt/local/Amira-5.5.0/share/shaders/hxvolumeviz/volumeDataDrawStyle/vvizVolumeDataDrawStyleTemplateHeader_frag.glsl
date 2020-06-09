//VVIZINTERNALSHADER
#define VVIZ_DRAWSTYLE_NONE 0
#define VVIZ_DRAWSTYLE_VR 1
#define VVIZ_DRAWSTYLE_VR_BOUND 3
#define VVIZ_DRAWSTYLE_ISO 4
#define VVIZ_DRAWSTYLE_ISO_VR 5
#define VVIZ_DRAWSTYLE_ISO_BOUND 6
#define VVIZ_DRAWSTYLE_ISO_VR_BOUND 7

void VVizClipVoxel();
vec3 VVizComputeCoordinates(const vec3);
void VVizOutputColor(vec4 color);

vec4 VVizApplyNpr(vec4 fragColor, vec3 viewVec, vec3 grad,
                  float gradNorm, vec3 normal);
vec3 VVizComputeViewVec();
vec3 VVizComputeNormal(vec3 view, vec3 grad);
vec3 VVizComputeGradient(sampler3D tex, vec3 tcoord0);
vec3 VVizComputePreintegratedGradient(sampler3D tex, vec3 tcoord0, vec3 tcoord1);
vec3 VVizComputePreintegratedGradient(vec3 tcoord0, vec3 tcoord1);
vec4 VVizComputePreintegratedLighting(vec4 col, vec3 normal, float gradLength);
vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int mask);
int VVizGetMask(vec3 tcoord);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf, int tfId);
vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int maskId);
VVIZ_DATATYPE VVizGetData(sampler3D tex, vec3 tcoord);
vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord);
vec4 VVizComputeVolumeRenderingLighting(vec4 col, vec3 normal, float gradLength);
vec4 VVizComputeIsoMaterial(sampler3D tex, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int maskId);
vec4 VVizOverOperator(vec4 underCol, vec4 overCol);

#if VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION
vec4 VVizComputeGeobodies(sampler3D tex, int mask, vec3 tCoordFront, vec3 tCoordBack);
#endif //VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION

uniform bool VVizUseVolumeMask;
uniform sampler3D VVizDataMask;
