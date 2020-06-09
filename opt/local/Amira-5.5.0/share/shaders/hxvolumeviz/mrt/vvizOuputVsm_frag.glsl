void OivGenerateShadowMap();

void VVizOutputColor(vec4 color)
{
  if ( color.w > 0. )
    OivGenerateShadowMap();
  else
    discard;
}
