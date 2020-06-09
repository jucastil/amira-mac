void VVizComputeLightingVectors();
vec4 VVizGenerateVertex();
void VVizComputeTexCoord();

void main()
{
  vec4 vertex = VVizGenerateVertex();
  VVizComputeLightingVectors();
  VVizComputeTexCoord();

  gl_Position = gl_ModelViewProjectionMatrix*vertex;
  gl_FrontColor = gl_Color;
#ifndef OIV_USE_ATI
  gl_ClipVertex = gl_ModelViewMatrix*vertex;
#endif
}
