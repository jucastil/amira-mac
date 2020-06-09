uniform int VVizGlobalDataDrawStyleId;
vec4 VVizComputeVolumeRendering(float sf);
vec4 VVizComputeVolumeRenderingLighting(vec4 col, vec3 normal, float gradLength);
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
vec3 VVizComputeCoordinates(const vec3);
vec3 VVizComputeCoordinatesGradient(vec3 v);
void VVizOutputColor(vec4 color);
vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, vec3 viewVec, vec3 grad, vec3 normal, float gradLength, vec3 tcoord0, vec3 tcoord1);

vec4 VVizApplyNpr(vec4 fragColor, vec3 viewVec, vec3 grad,
                  float gradNorm, vec3 normal);
vec3 VVizComputeGradient(vec3 tcoord);

vec3 VVizComputeViewVec();
vec3 VVizComputeNormal(vec3 view, vec3 grad);
vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf, int tfId);
int VVizGetMask(vec3 tcoord);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizOverOperator(vec4 underCol, vec4 overCol);

void main()
{
  VVizClipVoxel();

  vec3 tcoordGradient = VVizComputeCoordinatesGradient(gl_TexCoord[0].xyz);
  vec3 tcoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tcoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);
  vec3 viewVec = VVizComputeViewVec();
  vec3 grad = VVizComputeGradient(tcoordGradient);
  float gradLength = length(grad);
  vec3 normal = VVizComputeNormal(viewVec, grad);

  int mask = VVizGetMask(tcoord0);

  VVIZ_DATATYPE sf = VVizCombineData(tcoord0);

  vec4 fragColor = VVizComputeVolumeRendering(sf, mask);
  fragColor = VVizComputeVolumeRenderingLighting(fragColor, normal, gradLength);
  fragColor = VVizApplyNpr(fragColor, viewVec, grad, gradLength, normal);
  fragColor = VVizApplyBoundary(fragColor, mask, tcoord0, tcoord1);
  fragColor = VVizComputeMaskGlobalStyle(fragColor, sf , viewVec, grad, normal, gradLength, tcoord0, tcoord1);

  VVizOutputColor(fragColor);
}

vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, vec3 viewVec, vec3 grad, vec3 normal,
                                float gradLength, vec3 tcoord0, vec3 tcoord1)
{
#if VVIZ_MASK_USES_GLOBAL_DRAW_STYLE
  vec4 globalColor = VVizComputeVolumeRendering(sf, VVizGlobalDataDrawStyleId);
  globalColor = VVizComputeVolumeRenderingLighting(globalColor, normal, gradLength);
  globalColor = VVizApplyBoundary(globalColor, VVizGlobalDataDrawStyleId, VVizGlobalDataDrawStyleId, tcoord0, tcoord1);
  return VVizOverOperator(globalColor, fragColor);
#else
  return fragColor;
#endif
}
