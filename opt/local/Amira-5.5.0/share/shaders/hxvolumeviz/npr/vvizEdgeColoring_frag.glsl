uniform float VVizEdgeThreshold;
uniform vec3 VVizEdgeColor;

vec3 VVizApplySurfaceScalar(vec3 baseColor, vec3 lightedColor, float gradLength);

float VVizEdgeIntensity(vec3 viewVec, vec3 normal, float gradNorm)
{
  if(gradNorm < VVizEdgeThreshold)
    normal = viewVec;

  float intensity = pow(max(dot(normal, viewVec),0), 1.);
  intensity = VVizApplySurfaceScalar(vec3(1.), vec3(intensity), gradNorm).x;

  return intensity;
}

vec4 VVizEdgeColoring(vec4 fragColor, vec3 viewVec, vec3 normal, float gradNorm)
{
  float a = VVizEdgeIntensity(viewVec, normal, gradNorm);
  fragColor.xyz = mix(VVizEdgeColor, fragColor.xyz, a);

  return fragColor;
}
