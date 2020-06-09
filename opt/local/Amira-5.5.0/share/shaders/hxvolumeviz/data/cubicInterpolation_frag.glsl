#ifndef VVIZ_DATA2D
uniform sampler3D VVizData;
#else
uniform sampler2D VVizData2D;
#endif

#ifndef VVIZ_DATARGBA
#define VVizDefaultData VVIZ_DATATYPE(0.0)
#else
#define VVizDefaultData VVIZ_DATATYPE(0,0,0,1)
#endif

uniform sampler1D VVizCubicInterpolationTex;

uniform vec3 VVizDu;
uniform vec3 VVizDv;
uniform vec3 VVizDw;

vec2 VVizComputeCoordinates(const vec2 tCoord);

VVIZ_DATATYPE
VVizTextureData(sampler3D data, vec3 coord)
{
#ifndef VVIZ_DATARGBA
  return texture3D(data, coord).w;
#else
  return texture3D(data, coord);
#endif
}

VVIZ_DATATYPE
VVizGetData(sampler3D tex, vec3 tcoord)
{
 float texSize = 256.0;
 vec3 volSize = 1./vec3(VVizDu.x, VVizDv.y, VVizDw.z);

  vec3 posOfs = tcoord/vec3(VVizDu.x, VVizDv.y, VVizDw.z);
  // position info interpolation texture
  posOfs = posOfs * 1./texSize + 0.5;

  // cubic interoplation values
  //  vec.xyz = (left offset, right offset, left weight)
  //                     right weight is 1.-left weight
  vec3 xInterp = texture1D(VVizCubicInterpolationTex, posOfs.x).xyz;
  vec3 yInterp = texture1D(VVizCubicInterpolationTex, posOfs.y).xyz;
  vec3 zInterp = texture1D(VVizCubicInterpolationTex, posOfs.z).xyz;

  // compute all 8 neighbours coordinates
  // l, r = left, right
  // u, d =up, down
  // f, b = front, back
  vec3 ldb = -xInterp.x * VVizDu + tcoord;
  vec3 rdb =  xInterp.y * VVizDu + tcoord;

  vec3 lub = -yInterp.x * VVizDv + ldb;
  vec3 rub = -yInterp.x * VVizDv + rdb;

  ldb =  yInterp.y * VVizDv + ldb;
  rdb =  yInterp.y * VVizDv + rdb;

  vec3 luf = -zInterp.x * VVizDw + lub;
  vec3 ruf = -zInterp.x * VVizDw + rub;
  vec3 ldf = -zInterp.x * VVizDw + ldb;
  vec3 rdf = -zInterp.x * VVizDw + rdb;

  lub =  zInterp.y * VVizDw + lub;
  rub =  zInterp.y * VVizDw + rub;
  ldb =  zInterp.y * VVizDw + ldb;
  rdb =  zInterp.y * VVizDw + rdb;

  VVIZ_DATATYPE fVal[4], bVal[4];
  // fetch data set values : front values in fVal
  //   back values in bVal
  //   x is upper left, y is upper right
  //   z is lower left, w is lower right
  fVal[0] = VVizTextureData(VVizData, luf);
  fVal[1] = VVizTextureData(VVizData, ruf);
  fVal[2] = VVizTextureData(VVizData, ldf);
  fVal[3] = VVizTextureData(VVizData, rdf);

  bVal[0] = VVizTextureData(VVizData, lub);
  bVal[1] = VVizTextureData(VVizData, rub);
  bVal[2] = VVizTextureData(VVizData, ldb);
  bVal[3] = VVizTextureData(VVizData, rdb);

  // interpolate 4 values along z axis
  fVal[0] = mix(bVal[0], fVal[0], zInterp.z);
  fVal[1] = mix(bVal[1], fVal[1], zInterp.z);
  fVal[2] = mix(bVal[2], fVal[2], zInterp.z);
  fVal[3] = mix(bVal[3], fVal[3], zInterp.z);
  
  // interpolate along is axis (mix(x,z) and mix(y,w)
  fVal[0] = mix(fVal[2], fVal[0], yInterp.z);
  fVal[1] = mix(fVal[3], fVal[1], yInterp.z);

  // finally mix along x axis
  return mix(fVal[1], fVal[0], xInterp.z);
}

VVIZ_DATATYPE VVizGetData(vec3 tcoord)
{
#ifndef VVIZ_DATA2D
  return VVizGetData(VVizData, tcoord);
#else
  return VVizDefaultData;
#endif
}

VVIZ_DATATYPE VVizGetData(sampler2D tex, vec2 tcoord)
{
#ifndef VVIZ_DATARGBA
  return texture2D(tex, VVizComputeCoordinates(tcoord)).w;
#else
  return texture2D(tex, VVizComputeCoordinates(tcoord));
#endif
}

VVIZ_DATATYPE VVizGetData(vec2 tcoord)
{
#ifdef VVIZ_DATA2D
  return VVizGetData(VVizData2D, tcoord);
#else
  return VVizDefaultData;
#endif
}
