void VVizComputeBackSliceTexCoord();
void VVizComputeFrontSliceTexCoord();
void VVizComputeLightingVectors();
void VVizComputeTangentSpaceLightingVectors();
void VVizCalcDistToUniformGrid(vec4 vertex);
vec4 VVizGenerateVertex();

void main()
{
  vec4 vertex = VVizGenerateVertex();
  VVizComputeBackSliceTexCoord();
  VVizComputeFrontSliceTexCoord();
  VVizComputeLightingVectors();
  VVizComputeTangentSpaceLightingVectors();
  VVizCalcDistToUniformGrid(gl_ModelViewMatrix*vertex);

  gl_Position = gl_ModelViewProjectionMatrix*vertex;
  gl_FrontColor = gl_Color;
#ifndef OIV_USE_ATI
  gl_ClipVertex = gl_ModelViewMatrix*vertex;
#endif
}
