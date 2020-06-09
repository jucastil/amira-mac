varying vec4 OIV_VERTEX_LIGHTSPACE;

//GPU gems 3 chapter 8
void OivGenerateShadowMap()
{
  float dx = dFdx(OIV_VERTEX_LIGHTSPACE.z);
  float dy = dFdy(OIV_VERTEX_LIGHTSPACE.z);

  float depth = OIV_VERTEX_LIGHTSPACE.z;
  gl_FragColor.x = depth;
  gl_FragColor.y = depth*depth+0.25*(dx*dx+dy*dy);

  //FIXME: Should not be needed
  gl_FragColor.w = 1.;
}
