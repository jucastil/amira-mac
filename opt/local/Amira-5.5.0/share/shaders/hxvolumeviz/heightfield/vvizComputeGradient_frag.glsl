uniform sampler2D VVizNormalTexture;
uniform float VVizHeightfieldScale;

vec3 VVizComputeGradient(vec3 tcoord)
{
  vec3 n = vec3(texture2D(VVizNormalTexture, tcoord.xy).xy, 1.);
  n = n*2.-1.;

  //Inverse projection
  float denom = 2./(1.+ dot(n.xy, n.xy));
  n.xy *= denom;
  n.z = (denom-1.);

  //Scale to avoid precision error
  n.xy *= VVizHeightfieldScale;

  return n;
}
