vec3 VVizTexGen(vec4 vert)
{
  vec3 res;
  res.x = dot(gl_ObjectPlaneS[0], vert);
  res.y = dot(gl_ObjectPlaneT[0], vert);
  res.z = dot(gl_ObjectPlaneR[0], vert);

  return res;
}


void main()
{
  gl_TexCoord[0].xyz = VVizTexGen(gl_MultiTexCoord0);
  gl_Position = ftransform();
}
