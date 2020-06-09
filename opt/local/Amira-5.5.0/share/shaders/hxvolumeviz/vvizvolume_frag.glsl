uniform int VVizGlobalDataDrawStyleId;
vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord);
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
vec3 VVizComputeCoordinates(const vec3);
void VVizOutputColor(vec4 color);
vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf, int tfId);
int VVizGetMask(vec3 tcoord);
bool VVizIsOutsideVolume(vec3 tcoord);
vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, vec3 tcoord0, vec3 tcoord1);

vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, int maskBack, vec3 texCoordFront, vec3 texCoordBack);
vec4 VVizOverOperator(vec4 underCol, vec4 overCol);

void main()
{
  VVizClipVoxel();

  vec3 tCoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tCoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);

  VVIZ_DATATYPE sf = VVizCombineData(tCoord0);
  int maskFront = VVizGetMask(tCoord0);

  vec4 res = VVizComputeVolumeRendering(sf, maskFront);
  res = VVizApplyNpr(res, tCoord0);
  res = VVizApplyBoundary(res, maskFront, tCoord0, tCoord1);
  res = VVizComputeMaskGlobalStyle(res, sf, tCoord0, tCoord1);

  VVizOutputColor(res);
}

vec4 VVizComputeMaskGlobalStyle(vec4 fragColor, VVIZ_DATATYPE sf, vec3 tcoord0, vec3 tcoord1)
{
#if VVIZ_MASK_USES_GLOBAL_DRAW_STYLE
  vec4 globalColor = VVizComputeVolumeRendering(sf, VVizGlobalDataDrawStyleId);
  globalColor = VVizApplyNpr(globalColor, tcoord0);
  globalColor = VVizApplyBoundary(globalColor, VVizGlobalDataDrawStyleId, VVizGlobalDataDrawStyleId, tcoord0, tcoord1);
  return VVizOverOperator(globalColor, fragColor);
#else
  return fragColor;
#endif
}
