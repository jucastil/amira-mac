vec4 VVizFrontToBackComposition(vec4 color);
float OivComputeShadow();

void VVizOutputColor(vec4 color)
{
  float shadow = OivComputeShadow();
  color.xyz *= shadow;
  gl_FragColor = VVizFrontToBackComposition(color);
}
