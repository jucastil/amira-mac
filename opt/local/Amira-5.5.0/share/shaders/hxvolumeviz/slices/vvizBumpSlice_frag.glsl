vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
VVIZ_DATATYPE VVizCombineData(vec2 tcoord);
void VVizClipVoxel();
void VVizOutputColor(vec4 color);
vec2 VVizComputeCoordinates(const vec2 tCoord);

vec4 VVizBumpSlice(vec4 col, float bumpScale);

uniform float VVizScale;

void main()
{
  VVizClipVoxel();

  VVIZ_DATATYPE vox = VVizCombineData(VVizComputeCoordinates(gl_TexCoord[0].xy));
  vec4 col = VVizComputeVolumeRendering(vox);

  vec4 res = VVizBumpSlice(col, VVizScale);
  VVizOutputColor(res);
}
