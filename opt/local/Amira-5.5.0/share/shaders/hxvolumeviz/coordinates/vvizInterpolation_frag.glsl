vec3 VVizNoInterpolation(vec3 v)
{
  return v;
}

/**
 * Interpolation must also be deactivated when doing isosurface lookup texture
 */
vec2 VVizIsosurfaceLookupIndex(float sf, float sb)
{
  return vec2(sf, sb);
}
