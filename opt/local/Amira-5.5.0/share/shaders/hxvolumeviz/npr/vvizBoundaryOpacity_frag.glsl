uniform float VVizBoundaryIntensity;
uniform float VVizBoundaryThreshold;
uniform float VVizGradientThreshold;

vec4 VVizBoundaryOpacity(vec4 fragColor, float gradNorm)
{
  if(gradNorm < VVizGradientThreshold)
    gradNorm = 0.;

  if(gradNorm > 1.)
    gradNorm = 1.;

  float boundOpacity = VVizBoundaryIntensity*pow(gradNorm, VVizBoundaryThreshold);
  fragColor.w += boundOpacity;
  fragColor.w = clamp(fragColor.w, 0., 1.);

  return fragColor;
}
