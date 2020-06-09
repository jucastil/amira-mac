vec4 VVizComputeIsoMaterial(VVIZ_DATATYPE sf, VVIZ_DATATYPE sb);
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
void VVizOutputColor(vec4 color);

vec3 VVizComputeCoordinates(const vec3);
vec4 VVizApplyNpr(vec4 fragColor, vec3 viewVec, vec3 grad,
                  float gradNorm, vec3 normal);
vec4 VVizApplyNpr(vec4 fragColor, vec3 tcoord);
vec4 VVizApplyBoundary(vec4 fragColor, int maskFront, vec3 texCoordFront, vec3 texCoordBack);
int VVizGetMask(vec3 tcoord);

#if VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION
vec4 VVizComputeGeobodies(vec3 tCoordFront, vec3 tCoordBack);
#endif

void main()
{
  VVizClipVoxel();

  vec3 tCoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 tCoord1 = VVizComputeCoordinates(gl_TexCoord[1].xyz);

  int maskFront = VVizGetMask(tCoord0);

#if VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION
  vec4 res = VVizComputeGeobodies(tCoord0, tCoord1);
#else
  VVIZ_DATATYPE sf = VVizCombineData(tCoord0);
  VVIZ_DATATYPE sb = VVizCombineData(tCoord1);
  vec4 res = VVizComputeIsoMaterial(sf, sb);
#endif //VVIZ_DRAWSTYLE_SEGMENTED_INTERPOLATION


  res = VVizApplyNpr(res, tCoord0);
  res = VVizApplyBoundary(res, maskFront, tCoord0, tCoord1);
  VVizOutputColor(res);
}
