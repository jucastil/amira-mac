uniform int VVizGlobalDataDrawStyleId;
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
vec3 VVizComputeCoordinates(const vec3);
void VVizOutputColor(vec4 color);

vec4 VVizApplyNpr(vec4 fragColor, vec3 viewVec, vec3 grad,
                  float gradNorm, vec3 normal);
vec3 VVizComputeViewVec();
vec3 VVizComputeNormal(vec3 view, vec3 grad);
vec3 VVizComputePreintegratedGradient(vec3 tcoord0, vec3 tcoord1);
vec4 VVizComputePreintegratedLighting(vec4 col, vec3 normal, float gradLength);
vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int mask);
int VVizGetMask(vec3 tcoord);
vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, vec3 viewVec, vec3 grad, vec3 normal, float gradLength, vec3 tcoord0, vec3 tcoord1);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizOverOperator(vec4 underCol, vec4 overCol);

void main()
{
  VVizClipVoxel();

  vec3 tcoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tcoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);

  VVIZ_DATATYPE sf = VVizCombineData(tcoord0);
  VVIZ_DATATYPE sb = VVizCombineData(tcoord1);

  vec3 viewVec = VVizComputeViewVec();
  vec3 grad = VVizComputePreintegratedGradient(tcoord0, tcoord1);
  float gradLength = length(grad);
  vec3 normal = VVizComputeNormal(viewVec, grad);

  int mask = VVizGetMask(tcoord0);

  vec4 fragColor = VVizComputePreIntegrated(sf, sb, mask);
  fragColor = VVizComputePreintegratedLighting(fragColor, normal, gradLength);
  fragColor = VVizApplyNpr(fragColor, viewVec, grad, gradLength, normal);
  fragColor = VVizApplyBoundary(fragColor, mask, tcoord0, tcoord1);
  fragColor = VVizComputeMaskGlobalStyle(fragColor, sf , sb, viewVec, grad, normal, gradLength, tcoord0, tcoord1);

  VVizOutputColor(fragColor);
}

vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, vec3 viewVec, vec3 grad, vec3 normal,
                                float gradLength, vec3 tcoord0, vec3 tcoord1)
{
#if VVIZ_MASK_USES_GLOBAL_DRAW_STYLE
  vec4 globalColor = VVizComputePreIntegrated(sf, sb, VVizGlobalDataDrawStyleId);
  globalColor = VVizComputePreintegratedLighting(globalColor, normal, gradLength);
  globalColor = VVizApplyNpr(globalColor, viewVec, grad, gradLength, normal);
  globalColor = VVizApplyBoundary(globalColor, VVizGlobalDataDrawStyleId, VVizGlobalDataDrawStyleId, tcoord0, tcoord1);
  return VVizOverOperator(globalColor, fragColor);
#else
  return fragColor;
#endif
}
