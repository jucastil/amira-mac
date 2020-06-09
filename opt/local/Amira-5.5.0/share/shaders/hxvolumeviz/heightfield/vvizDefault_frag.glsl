vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
vec3 VVizComputeCoordinates(const vec3);
void VVizOutputColor(vec4 color);
vec3 VVizComputeGradient(vec3 tcoord);
vec4 VVizComputeLighting(vec3 n, vec4 col);

void main()
{
  vec3 tCoord0 = VVizComputeCoordinates(gl_TexCoord[0].xyz);
  vec3 grad = VVizComputeGradient(tCoord0);
  vec3 normal = normalize(gl_NormalMatrix*grad);

#ifndef VVIZ_NODATA
  VVIZ_DATATYPE sf = VVizCombineData(tCoord0.xy);
#else
  VVIZ_DATATYPE sf = VVIZ_DATATYPE(0.);
#endif

  vec4 col = VVizComputeVolumeRendering(sf);
  col = VVizComputeLighting(normal, col);

  VVizOutputColor(col);
}
