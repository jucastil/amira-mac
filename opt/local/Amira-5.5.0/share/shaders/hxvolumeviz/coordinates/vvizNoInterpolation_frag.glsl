uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

vec3 VVizNoInterpolation(vec3 v)
{
  vec3 texSize = vec3(1./VVizDu.x, 1./VVizDv.y, 1./VVizDw.z);
  return (floor(v*texSize)+0.5)*vec3(VVizDu.x, VVizDv.y, VVizDw.z);
}

vec2 VVizNoInterpolation(vec2 v)
{
  vec2 texSize = vec2(1./VVizDu.x, 1./VVizDv.y);
  return (floor(v*texSize)+0.5)*vec2(VVizDu.x, VVizDv.y);
}

/**
 * Interpolation must also be deactivated when doing isosurface lookup texture
 */
vec2 VVizIsosurfaceLookupIndex(float sf, float sb)
{
  return vec2(sf, sf);
}
