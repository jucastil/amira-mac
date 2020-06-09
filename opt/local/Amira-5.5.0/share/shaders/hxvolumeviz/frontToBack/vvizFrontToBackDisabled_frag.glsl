//DEPRECATED FILE only used for ART scenarios
uniform bool VVizUseFrontToBack;

vec4 VVizFrontToBackComposition(vec4 color)
{
  if ( VVizUseFrontToBack )
    color.xyz *= color.w;

  return color;
}
