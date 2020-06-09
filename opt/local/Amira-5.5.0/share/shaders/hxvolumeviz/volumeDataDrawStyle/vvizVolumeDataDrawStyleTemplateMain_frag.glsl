void main()
{
  vec4 res = vec4(0.);
  VVIZ_COMPUTE_RES_COLOR
  VVizOutputColor(res);
  VVizClipVoxel();
}

