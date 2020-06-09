uniform mat4 VVizModelMatrix;
uniform float VVizGeomOffset;

vec3 VVizTexGen(vec4 vert);

vec3 VVizComputeTextureCoordinates(vec4 vertex, vec3 normal)
{
  return VVizTexGen(VVizModelMatrix*(vertex+vec4(normalize(gl_Normal)*VVizGeomOffset, 0.)));
}
