vec3 VVizNoInterpolation(vec3 v);
vec3 VVizJitter(vec3 tcoord);

uniform sampler1D VVizRectilinearMapping;
uniform int VVizRectilinearMappingSize;

uniform vec3 VVizRootTileDimensions;
uniform vec3 VVizTileFactor;
uniform vec3 VVizTileOrigin;


uniform vec3 VVizVolumeDimensions;

uniform vec3 VVizTileDimensions;
uniform vec3 VVizTileMinIJK;
uniform vec3 VVizTileMaxIJK;
uniform vec3 VVizUVWMin;
uniform vec3 VVizUVWMax;

/* apply texture rectilinear mapping */
/* map a linear IJK coordinate to global RECTIlinear [0..1] coordinate */
/* just a texture lookup */
vec3 mapGlobalCoordinates(const vec3 v) {
  // back slicing assume clamping when getting out of dataset. Make sure we have the same behavior
  vec3 r = clamp(v, vec3(0., 0., 0.), VVizVolumeDimensions-1.) +
    vec3(1.5,
         VVizRootTileDimensions.x + 2. + 2.,
         VVizRootTileDimensions.x + 4. + VVizRootTileDimensions.y + 2.);
  r /= float(VVizRectilinearMappingSize);
  return vec3(texture1D(VVizRectilinearMapping, r.x).x,
              texture1D(VVizRectilinearMapping, r.y).x,
              texture1D(VVizRectilinearMapping, r.z).x);
}

/* map a tile linear [0..1] space coordinate to global RECTIlinear [0..1] space coordinate */
vec3 mapNormalizedCoordinates(const vec3 v) {
  return mapGlobalCoordinates(v * (VVizTileMaxIJK - VVizTileMinIJK) + VVizTileMinIJK);
}

/* map a tile linear [0..1] space coordinate to a [0..1] RECTILINEAR tile space coordinate */
vec3 mapTileCoordinates(const vec3 v) {
  return VVizUVWMin +
    ((mapNormalizedCoordinates(v) * VVizVolumeDimensions -1. - VVizTileOrigin) / VVizTileFactor)
    * (VVizUVWMax - VVizUVWMin);
}

vec3 VVizComputeCoordinatesGradient(vec3 v) {
  return VVizJitter(mapTileCoordinates(v));
}

vec3 VVizComputeCoordinates(const vec3 v)
{
  return VVizNoInterpolation(VVizComputeCoordinatesGradient(v));
}
