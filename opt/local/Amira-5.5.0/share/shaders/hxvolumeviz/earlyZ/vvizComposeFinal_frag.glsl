uniform sampler2D colorTex;
uniform sampler2D depthTex;

void main()
{
  gl_FragColor = texture2D(colorTex, gl_TexCoord[0].xy);
  gl_FragDepth = texture2D(depthTex, gl_TexCoord[0].xy).x;
}
