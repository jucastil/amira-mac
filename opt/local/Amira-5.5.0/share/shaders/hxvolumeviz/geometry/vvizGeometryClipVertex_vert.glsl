varying vec4 VVizPosition;

void VVizClipVertex(vec4 vert)
{
  VVizPosition = gl_ModelViewMatrix*vert;
}
