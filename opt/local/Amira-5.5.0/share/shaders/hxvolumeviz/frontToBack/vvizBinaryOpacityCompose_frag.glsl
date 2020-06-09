uniform vec2 invScreenSize;
uniform sampler2D renderedVolumeTex;

//Write the volume bbox in the zbuffer, only if the rendered image's alpha != 0
void main()
{
  vec2 tcoord = gl_FragCoord.xy*invScreenSize;

  float alpha = texture2D(renderedVolumeTex, tcoord).w;
  if ( alpha == 0. )
    discard;
  gl_FragColor = vec4(1.);
}
