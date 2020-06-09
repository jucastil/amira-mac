varying vec4 OivVertexLightSpace;
uniform sampler2D OivShadowMap;

const float LightBleedingReduction = 0.01;
const float MinVariance = 0.001;

float OivComputeShadow()
{
  vec3 texCoordDepth = OivVertexLightSpace.xyz/OivVertexLightSpace.w;
  texCoordDepth = texCoordDepth*vec3(0.5)+vec3(0.5);
  //texCoordDepth.z -= 0.001;
//  texCoordDepth.z -= 0.01;
  //gl_FragColor = gl_Color;
  //gl_FragColor = texCoord.xyxy;
  vec4 sm = texture2D(OivShadowMap, texCoordDepth.xy);

  float sigma2 = sm.y-sm.x*sm.x;
  sigma2 = max(sigma2, MinVariance);
  float tmp = (texCoordDepth.z-sm.x);
  float p = sigma2/(sigma2+tmp*tmp);
  p = smoothstep(LightBleedingReduction, 1., p);

  float shadow = texCoordDepth.z <= sm.x ? 1. : 0.;

  return max(shadow, p);
}

float OivComputeShadowEsm()
{
  vec3 texCoordDepth = OivVertexLightSpace.xyz/OivVertexLightSpace.w;
  texCoordDepth = texCoordDepth*vec3(0.5)+vec3(0.5);
  texCoordDepth.z -= 0.001;
  vec4 sm = texture2D(OivShadowMap, texCoordDepth.xy);

  float k = 30.;
  return exp(k*sm.x)*exp(-k*texCoordDepth.z);
}
