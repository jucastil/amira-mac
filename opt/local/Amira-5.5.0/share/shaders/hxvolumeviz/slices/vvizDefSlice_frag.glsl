vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
void VVizClipVoxel();
void VVizOutputColor(vec4 color);
vec2 VVizComputeCoordinates(const vec2 tCoord);

uniform float VVizScale;

void main()
{
  VVizClipVoxel();

  VVIZ_DATATYPE vox = VVizCombineData(VVizComputeCoordinates(gl_TexCoord[0].xy));
  vec4 col = VVizComputeVolumeRendering(vox);

  VVizOutputColor(col);
}
