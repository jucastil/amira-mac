#extension GL_ARB_draw_buffers : enable

uniform float VVizGradientThreshold;

varying vec4 VVizHalfVec;

uniform bool VVizSurfaceScalar;
uniform float VVizSurfaceScalarExponent;

vec4 VVizEdgeImageSpace(vec4 fragColor, vec3 viewVec, vec3 normal, float gradNorm);
vec4 VVizFrontToBackComposition(vec4 color);

vec4 VVizEdgeImageSpace(vec4 fragColor, vec3 viewVec, vec3 normal, float gradNorm)
{
#ifndef VVIZ_EDGE2D_NOMRT
  if ( gradNorm > VVizGradientThreshold )
    normal /= gradNorm;
  if ( VVizSurfaceScalar )
  {
    float t = 1.-pow((1-gradNorm), VVizSurfaceScalarExponent);
    normal *= t;
  }
  float In = dot(normal, vec3(1.))/3.;

  float viewSpaceZ = VVizHalfVec.w;

  vec4 distInfos = vec4(viewSpaceZ, In, 1., fragColor.w);
  gl_FragData[1] = VVizFrontToBackComposition(distInfos);
#endif

  return fragColor;
}
