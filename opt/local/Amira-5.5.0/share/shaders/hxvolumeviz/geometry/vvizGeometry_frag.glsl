vec4 VVizComputeVolumeRendering(VVIZ_DATATYPE sf);
VVIZ_DATATYPE VVizCombineData(vec3 tcoord);
void VVizClipVoxel();
void VVizOutputColor(vec4 color);

void main()
{
  VVizClipVoxel();

  VVIZ_DATATYPE vox = VVizCombineData(gl_TexCoord[0].xyz);
  vec4 col = VVizComputeVolumeRendering(vox);

  VVizOutputColor(vec4(col.xyz*gl_Color.xyz, col.w*gl_Color.w));
}
