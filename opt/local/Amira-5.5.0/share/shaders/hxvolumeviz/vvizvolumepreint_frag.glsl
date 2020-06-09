uniform int VVizGlobalDataDrawStyleId;
vec4 VVizComputePreIntegrated(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, int mask);
vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord);
void VVizOutputColor(vec4 color);

VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
vec3 VVizComputeCoordinates(const vec3);
int VVizGetMask(vec3 tcoord);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, vec3 tcoord0, vec3 tcoord1);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizOverOperator(vec4 underCol, vec4 overCol);

void main()
{
  VVizClipVoxel();

  vec3 tCoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tCoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);

  VVIZ_DATATYPE sf = VVizCombineData(tCoord0);
  VVIZ_DATATYPE sb = VVizCombineData(tCoord1);

  int mask = VVizGetMask(tCoord0);

  vec4 res = VVizComputePreIntegrated(sf, sb, mask);
  res = VVizApplyNpr(res, tCoord0);
  res = VVizApplyBoundary(res, mask, tCoord0, tCoord1);
  res = VVizComputeMaskGlobalStyle(res, sf, sb, tCoord0, tCoord1);

  VVizOutputColor(res);
}

vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, VVIZ_DATATYPE sb, vec3 tcoord0, vec3 tcoord1)
{
#if VVIZ_MASK_USES_GLOBAL_DRAW_STYLE
  vec4 globalColor = VVizComputePreIntegrated(sf, sb, VVizGlobalDataDrawStyleId);
  globalColor = VVizApplyNpr(globalColor, tcoord0);
  globalColor = VVizApplyBoundary(globalColor, VVizGlobalDataDrawStyleId, VVizGlobalDataDrawStyleId, tcoord0, tcoord1);
  return VVizOverOperator(globalColor, fragColor);
#else
  return fragColor;
#endif
}
