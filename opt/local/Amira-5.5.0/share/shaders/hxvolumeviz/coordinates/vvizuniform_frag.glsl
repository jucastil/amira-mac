vec3 VVizJitter(vec3 tcoord);
vec3 VVizNoInterpolation(vec3 v);

vec3 VVizComputeCoordinatesGradient(vec3 v)
{
  return VVizJitter(v);
}

vec3 VVizComputeCoordinates(const vec3 v)
{
  return VVizNoInterpolation(VVizComputeCoordinatesGradient(v));
}

