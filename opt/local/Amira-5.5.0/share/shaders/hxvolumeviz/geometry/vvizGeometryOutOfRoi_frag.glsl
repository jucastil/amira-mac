void VVizClipVoxel();
void VVizOutputColor(vec4 color);

varying vec4 VVizPosition;

void main()
{
  VVizClipVoxel();

  bool inRoi = true;
  for ( int i = 0; i < 6; i++ )
    inRoi = inRoi && (dot(gl_ClipPlane[i], VVizPosition) < 0.);
  
  if ( inRoi )
    discard;

  VVizOutputColor(gl_Color);
}
