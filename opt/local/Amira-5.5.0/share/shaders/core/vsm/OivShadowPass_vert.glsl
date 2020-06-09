void OivSetupShadowVertex();

void main()
{
  OivSetupShadowVertex();
  gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
#if !defined(OIV_USE_ATI)
  gl_ClipVertex = gl_ModelViewMatrix*gl_Vertex;
#endif
}
