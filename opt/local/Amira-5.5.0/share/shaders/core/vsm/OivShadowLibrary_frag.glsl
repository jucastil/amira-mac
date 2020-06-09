//OIV_VERTEX_LIGHTSPACE is set to OivVertexLightSpaceGeom
//if there is a geometry shader, OivVertexLightSpace otherwise

varying vec4 OIV_VERTEX_LIGHTSPACE;
uniform sampler2D OivShadowMap;
uniform float OivShadowIntensity;

uniform float OivLightBleedingReduction = 0.01;
uniform float OivMinVariance = 0.001;

float OivComputeShadow()
{
  float fragDepth = OIV_VERTEX_LIGHTSPACE.z;

  vec2 texCoordDepth = OIV_VERTEX_LIGHTSPACE.xy/OIV_VERTEX_LIGHTSPACE.w;
  texCoordDepth = texCoordDepth*vec2(0.5)+vec2(0.5);
  texCoordDepth = clamp(texCoordDepth, 0., 1.);
  vec2 sm = texture2D(OivShadowMap, texCoordDepth).xy;

  float sigma2 = sm.y-sm.x*sm.x;
  sigma2 = max(sigma2, OivMinVariance);
  float tmp = (fragDepth-sm.x);
  float p = sigma2/(sigma2+tmp*tmp);
  p = smoothstep(OivLightBleedingReduction, 1., p);

  float shadow = fragDepth <= sm.x ? 1. : 0.;

  return max(max(shadow, p), OivShadowIntensity);
}
